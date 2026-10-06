#!/usr/bin/env python3
"""Function-by-function decompilation with cheap models in a feedback loop.

    python3 tools/decomp/llm_loop.py Graph.cpp [--models a,b] [--rounds 5] [--switch-after 2]

Run inside a worktree (tools/decomp/parallel.py new ...). The model never
sees the repository: every call is `opencode run` with the `plain` agent (all
tools denied) and gets exactly what it needs. Models form a chain (default:
the free Space Bunny, then DeepSeek V4.1 Flash): a function moves on to the
next model after --switch-after rounds without acceptance or when a model
does not answer.

1. Header: the generated header (build-decomp/include-gen), the exact symbol
   signatures and the Ghidra drafts go in; decomp/include/<Class>.h comes
   out. It must compile with the original sizeof, field offsets and vtable.
2. Functions, in rounds, all pending functions in parallel. The prompt is
   tools/decomp/prompts/idioms.md (the same for every call, so it is cached),
   the class header, accepted examples with similar drafts (examples.py), then
   the ASM and the Ghidra draft; one definition comes out. Each candidate is
   compiled with the accepted ones (objdiff): MATCH is accepted; DIFF
   candidates get generated differential tests (autotest.py) in one game run.
   A passing test accepts the function; compile errors, failing tests and the
   instruction diff go back to the same model session for the next round.
3. promote.py moves what the TU uses from the generated headers into
   decomp/include; the TU must then build without them.

Accepted functions land in decomp/src/<TU>; check.py and mutate.py --accept
take it from there. Log: build-decomp/llm-loop/<TU>/.
"""
from __future__ import annotations

import argparse
from concurrent.futures import ThreadPoolExecutor
import difflib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import time

sys.path.insert(0, str(Path(__file__).resolve().parent))
import autotest  # noqa: E402
import elfdb  # noqa: E402
import examples  # noqa: E402
import ghidra_cpp  # noqa: E402
import headers  # noqa: E402
import hybrid  # noqa: E402
import objdiff  # noqa: E402
import promote  # noqa: E402

ROOT = elfdb.ROOT
AGENT_DIR = Path("/tmp/opencode/llm-loop")
IDIOMS = Path(__file__).resolve().parent / "prompts" / "idioms.md"
# Free model first; the cheap paid one takes over what it does not get accepted.
MODELS = ("opencode-go/space-bunny-free#high", "opencode-go/deepseek-v4.1-flash#high")
WRITTEN = ("function", "ctor", "dtor", "static")
ASM_LABEL = re.compile(r"\b(?:__asm__|asm)\s*(?:volatile\s*)?\(\s*\"_Z")
AGENT = """---
description: Answers with code only, no tools
mode: primary
permissions:
  - action: "*"
    resource: "*"
    effect: deny
---

You translate decompiled x86-64 code (GCC 4.4.7 -O2, Linux) back into the C++98 source
it was compiled from. Answer with exactly one fenced ```cpp code block and nothing else.
"""


class Model:
    def __init__(self, model, log):
        self.model, self.log = model, log
        self.sent = self.received = 0
        agent = AGENT_DIR / ".opencode" / "agents" / "plain.md"
        agent.parent.mkdir(parents=True, exist_ok=True)
        if not agent.exists() or agent.read_text() != AGENT:
            agent.write_text(AGENT)
            time.sleep(30)  # the OpenCode service reloads agents asynchronously

    def ask(self, prompt, session=None, tag=""):
        """Returns (code, session id)."""
        cmd = ["opencode", "run", "--agent", "plain", "-m", self.model, "--format", "json"]
        if session:
            cmd += ["--session", session]
        errors = []
        for attempt in range(5):
            try:
                # opencode takes its directory from PWD, not from the process working directory.
                result = subprocess.run(cmd + [prompt], cwd=AGENT_DIR, capture_output=True, text=True, timeout=900,
                                        env=dict(os.environ, PWD=str(AGENT_DIR)))
            except subprocess.TimeoutExpired:
                errors.append("timeout")
                continue
            text, sid = "", session
            for line in result.stdout.splitlines():
                try:
                    event = json.loads(line)
                except ValueError:
                    continue
                sid = event.get("sessionID", sid)
                if event.get("type") == "text":
                    text += event["part"].get("text", "")
                elif event.get("type") == "error":
                    errors.append(str(event.get("error"))[:300])
            if text:
                break
            time.sleep(15 * (attempt + 1))
        self.sent += len(prompt)
        self.received += len(text)
        with open(self.log / "calls.log", "a") as f:
            f.write(f"===== {tag} session={sid}\n--- prompt ({len(prompt)} chars)\n{prompt}\n--- answer\n{text}\n"
                    + (f"--- errors\n{chr(10).join(errors)}\n" if errors else ""))
        blocks = re.findall(r"```(?:cpp|c\+\+|c)?\s*\n(.*?)```", text, re.S)
        # No code block (a refusal, or a model imitating tool calls): no answer.
        return (blocks[-1].strip() if blocks else ""), sid


def asm_of(tu, f):
    packet = ROOT / "build-decomp" / "scaffold" / tu / "asm"
    found = sorted(packet.glob(f"{f['address']}_*.s")) if packet.exists() else []
    if found:
        text = found[0].read_text()
        return text[text.find(f"{int(f['address'], 16):016x}"):] if f"{int(f['address'], 16):016x}" in text else text
    return "(no ASM in the packet; run tools/decomp/scaffold.py)"


def return_from_code(f):
    """float, double or bool when the original sets xmm0 or al that way before every ret it
    reaches straight-line; None when the code does not show it (Ghidra's guess stays)."""
    start = int(f["address"], 16)
    out = subprocess.run(["objdump", "-d", "--no-show-raw-insn", "-w", f"--start-address={start:#x}",
                          f"--stop-address={start + f['size']:#x}", str(elfdb.default_elf())],
                         capture_output=True, text=True, env={"LC_ALL": "C", "PATH": "/usr/bin:/bin"}).stdout
    insns = [(m.group(1), m.group(2).strip()) for m in re.finditer(r"^\s+[0-9a-f]+:\t(\S+)[ \t]*([^#<\n]*)", out, re.M)]
    insns = [("ret", "") if mnemonic in ("rep", "repz") and ops.startswith("ret") else (mnemonic, ops)
             for mnemonic, ops in insns]
    kinds = set()
    for i, (mnemonic, _) in enumerate(insns):
        if not mnemonic.startswith("ret"):
            continue
        kind = None
        for prev, ops in reversed(insns[max(0, i - 12):i]):
            if prev.startswith(("ret", "jmp", "call")):
                break
            dest = ops.split(",")[-1].strip()
            if dest == "%xmm0":
                kind = "float" if prev.endswith("ss") else "double" if prev.endswith("sd") else "xmm"
                break
            if dest in ("%eax", "%rax", "%ax", "%al"):
                if dest == "%al" or prev.startswith("movzb"):
                    kind = "bool"
                elif ops in ("%eax,%eax", "$0x0,%eax", "$0x1,%eax") and prev in ("xor", "mov"):
                    kind = "flag"
                else:
                    kind = "int"
                break
        kinds.add(kind)
    for scalar in ("float", "double"):
        if scalar in kinds and not kinds - {scalar, "xmm", None}:
            return scalar
    if "bool" in kinds and not kinds - {"bool", "flag", None}:
        return "bool"
    return None


class Loop:
    def __init__(self, tu_name, models, rounds, switch_after=2, jobs=4, resume=False):
        if ROOT == elfdb.ROOT:
            raise RuntimeError("Loop requires publication.Stage.activate(); live-tree experiments are forbidden")
        # Work in progress compiles against the generated headers; finish() promotes what it uses.
        os.environ["OTL_EXTRA_INCLUDE"] = str(headers.OUT)
        self.db = elfdb.load_db()
        self.tu = next(t for t in self.db["tus"] if t["name"] == tu_name)
        self.rounds, self.switch_after, self.jobs = rounds, switch_after, jobs
        self.work = ROOT / "build-decomp" / "llm-loop" / tu_name
        shutil.rmtree(self.work, ignore_errors=True)
        self.work.mkdir(parents=True)
        self.models = [Model(m, self.work) for m in models]
        self.examples = examples.load()
        self.by_model = {}
        self.funcs = sorted((f for f in self.db["functions"].values() if f["tu"] == self.tu["id"]
                             and f["kind"] in WRITTEN and not any(n.endswith("D0Ev") for n in f["names"])),
                            key=lambda f: f["address"])
        # One entry per definition: C1/C2 constructor copies share a source definition.
        seen, unique = set(), []
        for f in self.funcs:
            key = (f["demangled"], f["kind"])
            if key not in seen:
                seen.add(key)
                unique.append(f)
        self.funcs = unique
        self.classes = sorted({(f.get("scope") or "").split("::")[0] for f in self.funcs} - {""})
        self.original = objdiff.Original(db=self.db)
        self.methods = ghidra_cpp.known_methods(self.db)
        self.signatures = ghidra_cpp.signatures_of(self.db)
        self.enums = ghidra_cpp.parse_enums()
        self.source = ROOT / "decomp" / "src" / tu_name
        import ghidra_draft
        state, reasons = ghidra_draft.draft_state(tu_name, self.db)
        self.stale_note = (f"; STALE, made before these changes: {'; '.join(reasons)}. Where it disagrees with "
                           "the header, the header is right" if state == "stale" else "")
        self.accepted = {}  # address -> code
        self.status = {}
        self.resume = resume
        self.existing = ""  # --resume: the TU as found; its functions are kept as they are

    def draft(self, f):
        raw = ROOT / "build-decomp" / "drafts" / self.tu["name"] / "raw" / f"{f['address']}.c"
        if not raw.exists():
            return "(no draft)"
        try:
            return ghidra_cpp.convert(raw.read_text(errors="replace"), self.methods, f, self.signatures, self.enums)
        except Exception:  # noqa: BLE001
            return raw.read_text(errors="replace")

    # -- header -------------------------------------------------------------
    def header(self):
        out = {}
        hand = headers_by_class()
        for cls in self.classes:
            gen = ROOT / "build-decomp" / "include-gen" / f"{cls}.h"
            if cls in hand:
                out[cls] = hand[cls][0]  # an existing header is used as it is, completed with this TU's methods
                added = self.complete_hand_header(cls, out[cls])
                if added:
                    print(f"  header {out[cls]}: declared {len(added)} methods of this TU it lacked", flush=True)
                continue
            if not gen.exists():
                continue
            name = (cls[1:] if re.match(r"C[A-Z]", cls) else cls) + ".h"
            size = (json.loads((ROOT / "build-decomp" / "types.json").read_text())["classes"].get(cls) or {}).get("size")
            sigs = "\n".join(f"  {f['demangled']}" for f in self.db["functions"].values()
                             if (f.get("scope") or "") == cls and f["kind"] in WRITTEN)
            drafts = "\n\n".join(self.draft(f) for f in self.funcs if (f.get("scope") or "") == cls)
            hand = ", ".join(sorted(p.name for p in (ROOT / "decomp" / "include").glob("*.h")))
            prompt = (f"Write the header decomp/include/{name} for class {cls}.\n\n"
                      f"Generated draft header (bases, virtual order and field OFFSETS are verified; field names, "
                      f"field types and return types are guesses):\n```cpp\n{gen.read_text()}```\n\n"
                      f"Exact method signatures from the symbols:\n{sigs}\n\n"
                      f"Ghidra decompilation of the methods (drafts, types may be wrong):\n```cpp\n{drafts}\n```\n\n"
                      "Requirements:\n"
                      f"- keep the base classes, the virtual methods in the same order and every field at the same "
                      f"offset; sizeof({cls}) must stay {size};\n"
                      "- fix return types (float for values returned in xmm0, bool for flags...), constness and "
                      "field types (std::wstring, TArrayList<T> for 24-byte lists, class pointers), and give "
                      "fields meaningful m_-prefixed names;\n"
                      f"- include only what you need from: {hand}, GenTypes.h (enums), GenGlobals.h;\n"
                      f"- guard macro {name.upper().replace('.', '_')}; C++98.")
            path = ROOT / "decomp" / "include" / name
            for model in self.models:
                code, sid = model.ask(prompt, tag=f"header {cls} {model.model}")
                for attempt in range(4):
                    path.write_text(code.rstrip() + "\n")
                    error = self.check_header(name, cls, size) if code else "no answer"
                    if not error or not code or attempt == 3:
                        break
                    code, sid = model.ask(f"The header does not compile or changes the layout:\n{error}\n"
                                          "Return the corrected full header.", sid, tag=f"header {cls} fix")
                if not error:
                    break
            else:
                # Fall back to the generated one, written like a promoted header.
                text = gen.read_text().replace(promote.GENERATED_NOTE, promote.PARTIAL_NOTE)
                path.write_text(re.sub(r"\bGEN_\w+_H\b", promote.guard(name), text))
                print(f"  header {cls}: models failed, using the generated header")
            out[cls] = name
            # Generated headers that pulled in the draft now get the real one.
            for other in (ROOT / "build-decomp" / "include-gen").glob("*.h"):
                other.write_text(other.read_text().replace(f'#include "{cls}.h"', f'#include "{name}"'))
            gen.unlink()
        self.headers = out

    def complete_hand_header(self, cls, name):
        """Declares in a hand-written header the non-virtual methods of this TU it lacks (partial
        headers declare only what other code used), so candidates can be written as members.
        Return types come from the Ghidra prototypes; declarations whose types the header
        cannot name are left out. Returns the declarations added."""
        path = ROOT / "decomp" / "include" / name
        text = path.read_text(errors="replace")
        m = re.search(rf"^(?:class|struct)\s+(?:__attribute__\(\(\w+\)\)\s+)?{re.escape(cls)}\s*(?::[^{{;]*)?\{{",
                      text, re.M)
        end = text.find("\n};", m.end()) if m else -1
        if end < 0:
            return []
        body = text[m.end():end]
        if not hasattr(self, "_decls"):
            self._decls = headers.Gen()
        gen = self._decls
        extra, forward, system, seen = [], set(), set(), set()
        for f in self.funcs:
            method = f.get("method") or ""
            params = tuple(re.sub(r"\s+", "", ghidra_cpp.cxx_type(p))
                           for p in ghidra_cpp.split_args(f.get("params") or "") if p != "void")
            identity = (method, params, ghidra_cpp.cv_suffix(f).strip())
            if (f.get("scope") != cls or f.get("vslots") or f["kind"] not in ("function", "ctor")
                    or identity in seen or any((p, cv) == identity[1:]
                                               for p, cv, _ in headers.declared_signatures(body, method))):
                continue
            seen.add(identity)
            deps = {"sys": set(), "local": set(), "forward": set()}
            ghidra = gen.ghidra_return(f)
            # The code decides only where Ghidra guessed an integer: its void/bool/float are reliable.
            code = return_from_code(f) if f["kind"] == "function" and ghidra not in ("void", "bool", "float",
                                                                                     "double") else None
            decl = gen.method_decl(f, cls, deps, ret=code)
            if not decl or "GenTypes.h" in deps["local"] or deps["sys"] - {"string"}:
                continue
            if any(f'"{h}"' not in text and h != name for h in deps["local"]):
                continue
            extra.append(decl)
            forward |= deps["forward"] - {cls}
            system |= deps["sys"]
        if not extra:
            return []
        indent = next((re.match(r"[ \t]*", l).group(0) for l in body.splitlines()
                       if l.strip() and not l.strip().endswith(":")), "    ") or "    "
        labels = list(re.finditer(r"^[ \t]*(public|private|protected)[ \t]*:", body, re.M))
        first_public = next((i for i, l in enumerate(labels) if l.group(1) == "public"), None)
        block = "".join(f"{indent}{d}\n" for d in extra)
        private_default = m.group(0).lstrip().startswith("class")
        if first_public is None and (labels or private_default):
            body = body.rstrip("\n") + "\npublic:\n" + block.rstrip("\n")
        elif first_public is not None and first_public + 1 < len(labels):
            at = labels[first_public + 1].start()
            body = body[:at] + block + body[at:]
        else:
            body = body.rstrip("\n") + "\n" + block.rstrip("\n")
        head = text[:m.start()]
        fwd = "".join(f"class {n};\n" for n in sorted(forward)
                      if not re.search(rf"\b(?:class|struct)\s+{n}\b", text))
        if "string" in system and "#include <string>" not in text:
            guard = re.search(r"#define \w+\n", head)
            head = head[:guard.end()] + "#include <string>\n" + head[guard.end():] if guard else \
                "#include <string>\n" + head
        path.write_text(head + fwd + text[m.start():m.end()] + body + text[end:])
        return extra

    def check_header(self, name, cls, size):
        """None when the header compiles with the original size, field offsets and vtable slots."""
        text = (ROOT / "decomp" / "include" / name).read_text()
        body = text[text.find(f"class {cls}"):]
        body = body[:body.find("\n};")]
        layout = json.loads((ROOT / "build-decomp" / "types.json").read_text())["classes"].get(cls) or {}
        allowed = {fd["offset"] for fd in layout.get("fields", [])}
        allowed |= {int(m, 16) for m in re.findall(r"m_gap([0-9A-F]+)\b", (ROOT / "build-decomp" / "include-gen" /
                                                                          f"{cls}.h").read_text())} \
            if (ROOT / "build-decomp" / "include-gen" / f"{cls}.h").exists() else set()
        fields = re.findall(r"^\s+(?!virtual|static|typedef|enum|class|struct|public|private|protected|friend)"
                            r"[\w:<>,*& ]+?[\s*&](\w+)\s*(?:\[[^\]]*\])?\s*(?:__attribute__\(\(.*?\)\))?;", body, re.M)
        probe = self.work / "header_check.cpp"
        checks = [f"typedef char size_ok[sizeof({cls}) >= {size} && sizeof({cls}) <= {(size + 7) // 8 * 8} ? 1 : -1];"
                  ] if size else []
        if allowed:
            for field in fields:
                cond = " || ".join(f"__builtin_offsetof({cls}, {field}) == {o}" for o in sorted(allowed))
                checks.append(f"typedef char offset_of_{field}[({cond}) ? 1 : -1];")
        probe.write_text(f'#include "{name}"\n' + "\n".join(checks) + "\n")
        try:
            dump = headers.class_dump(probe, ["-w", "-I", str(headers.OUT)])
        except SystemExit as error:
            lines = [l for l in str(error).splitlines() if "error" in l]
            moved = [m for m in (re.search(r"'offset_of_(\w+)'", l) for l in lines) if m]
            if moved:
                return (f"Fields at offsets that do not exist in the original layout: "
                        f"{', '.join(sorted({m.group(1) for m in moved}))}. Keep every field at its original offset "
                        f"(offsets: {', '.join(hex(o) for o in sorted(allowed))}).")
            return "\n".join(lines)[:2500]
        return headers.vtable_mismatch(self.db, cls, dump)

    # -- functions ----------------------------------------------------------
    def unit(self, extra=()):
        parts = ['#include "EmptyStrings.h"'] + [f'#include "{g}"' for g in ("GenTypes.h", "GenGlobals.h", "GenNamespaces.h")
                                                 if (headers.OUT / g).exists()]
        parts += [f'#include "{h}"' for h in self.headers.values()]
        names = set()
        for code in list(self.accepted.values()) + list(extra):
            names.update(re.findall(r"\b[A-Za-z_]\w*\b", code))
        incl = {p.name for p in (ROOT / "decomp" / "include").glob("*.h")}
        hand = headers_by_class()
        for n in sorted(names):
            if n in hand:
                parts += [f'#include "{h}"' for h in hand[n] if h not in self.headers.values()]
            elif (ROOT / "build-decomp" / "include-gen" / f"{n}.h").exists() and f"{n}.h" not in incl:
                parts.append(f'#include "{n}.h"')
        body = [self.accepted[a] for a in sorted(self.accepted)] + list(extra)
        if self.existing:
            lines = self.existing.splitlines()
            n = 0
            while n < len(lines) and (lines[n].startswith("#include") or not lines[n].strip()):
                n += 1
            parts = [l for l in lines[:n] if l.strip()] + parts
            body = ["\n".join(lines[n:]).strip("\n")] + body
        return "\n".join(dict.fromkeys(parts)) + "\n\n" + "\n\n".join(body) + "\n"

    def compile(self, f, code):
        """(status, detail): compile-error / MATCH / DIFF with the instruction diff."""
        if ASM_LABEL.search(code):
            return "compile-error", ("Symbols bound with asm labels are not source code. Define the function as "
                                     "the member the header declares, and call other functions through their "
                                     "classes (object->method(...)).")
        trial = self.work / "trial" / f["address"] / self.tu["name"]
        trial.parent.mkdir(parents=True, exist_ok=True)
        trial.write_text(self.unit([code]))
        try:
            result = objdiff.compare_source(trial, self.original, quiet=True)
        except SystemExit as error:
            lines = [l.split(": error: ", 1)[-1] for l in str(error).splitlines() if "error" in l][:12]
            return "compile-error", "\n".join(lines) + self.name_hints(lines)
        if result.get("unknown"):
            return "compile-error", "Calls functions the game does not have:\n" + "\n".join(
                f"- {r['name']}; the game has: {'; '.join(r['known']) or 'no such member'}"
                for r in result["unknown"]) + "\nCall the existing overload (mind constness and references)."
        row = next((r for r in result["functions"] if r.get("address") == f["address"]), None)
        if not row:
            return "compile-error", "the definition did not produce the function (wrong signature?)"
        if row["status"] == "MATCH":
            return "MATCH", ""
        return "DIFF", self.instruction_diff(trial, f)

    def name_hints(self, lines):
        """Real symbols close to the names the compiler did not find."""
        if not hasattr(self, "_symbols"):
            self._symbols = {}
            for g in self.db["functions"].values():
                if g.get("method"):
                    self._symbols.setdefault(g["method"], set()).add(g["demangled"])
        hints = []
        for line in lines:
            m = re.search(r"'(\w+)' (?:was not declared|is not a member of '([\w:]+)'|has not been declared)", line)
            if not m:
                continue
            want, scope = m.group(1), m.group(2)
            close = difflib.get_close_matches(want, list(self._symbols), n=4, cutoff=0.7)
            found = [d for name in close for d in sorted(self._symbols[name])
                     if not scope or d.startswith(scope + "::")][:6]
            if found:
                hints.append(f"Functions in the program with a similar name to '{want}': " + "; ".join(found))
        return ("\n" + "\n".join(dict.fromkeys(hints))) if hints else ""

    def instruction_diff(self, trial, f):
        with __import__("tempfile").TemporaryDirectory() as tmp:
            obj, globalized = objdiff.compile_for_diff(trial, tmp, quiet=True)
            ours = objdiff.object_functions(obj, self.original.resolver(self.tu), self.original.side.name_at, globalized)
        mine = next((v["norm"] for k, v in ours.items() if k in f["names"]), [])
        theirs = self.original.normalized(f)
        diff = [l for l in difflib.unified_diff(mine, theirs, "yours", "original", lineterm="", n=2)]
        return "\n".join(diff[:80])

    def prompt_for(self, f):
        draft = self.draft(f)
        chosen = examples.choose(self.examples, draft, exclude={f["address"]})
        header = "\n\n".join((ROOT / "decomp" / "include" / h).read_text() for h in self.headers.values())
        # Same text first for every call (the provider caches the prefix), then this TU, then this function.
        return (IDIOMS.read_text() + "\n"
                + (f"Class header:\n```cpp\n{header}```\n\n" if header else "")
                + (f"Accepted functions of the game next to their drafts, for the style and the idioms:\n\n"
                   f"{examples.render(chosen)}\n\n" if chosen else "")
                + f"Write the C++98 definition of `{f['demangled']}` exactly as declared in the header.\n\n"
                f"Original machine code (objdump):\n```\n{asm_of(self.tu['name'], f)}\n```\n\n"
                f"Ghidra decompilation (a draft; types and temporaries may be wrong{self.stale_note}):\n"
                f"```cpp\n{draft}\n```\n\n"
                "Rules: C++98; use the header's names; call other functions normally (std::wstring, "
                "TArrayList methods instead of inlined internals); globals are declared in GenGlobals.h, other "
                "classes in their headers (already included); no includes; return only this definition.")

    def ask(self, item, round_no):
        """Next candidate for a pending function. A function moves on to the next model of
        the chain after `switch_after` rounds without acceptance, or when a model does not answer."""
        f = item["f"]
        if item["tries"] >= self.switch_after and item["model"] + 1 < len(self.models):
            item.update(model=item["model"] + 1, tries=0, session=None)
        while True:
            if item["session"] and item["feedback"]:
                prompt = item["feedback"]
            else:
                prompt = self.prompt_for(f)
                if item.get("code") and item["feedback"]:
                    prompt += (f"\n\nAn earlier attempt was not accepted:\n```cpp\n{item['code']}\n```\n"
                               f"{item['feedback']}")
            model = self.models[item["model"]]
            code, sid = model.ask(prompt, item["session"], tag=f"{f['address']} round {round_no} {model.model}")
            if code or item["model"] + 1 >= len(self.models):
                break
            item.update(model=item["model"] + 1, tries=0, session=None)
        item["tries"] += 1
        return f["address"], code, sid

    def run(self):
        print(f"{self.tu['name']}: {len(self.funcs)} functions, classes {', '.join(self.classes)}", flush=True)
        self.header()
        print(f"  header: {', '.join(self.headers.values())}", flush=True)
        if self.resume and self.source.exists():
            self.keep_existing()
        pending = {f["address"]: {"f": f, "session": None, "feedback": None, "model": 0, "tries": 0}
                   for f in self.funcs if f["address"] not in self.status}
        for round_no in range(1, self.rounds + 1):
            if not pending:
                break
            with ThreadPoolExecutor(self.jobs) as pool:
                answers = list(pool.map(lambda item: self.ask(item, round_no), pending.values()))
            diffs = {}
            for address, code, sid in answers:
                item = pending[address]
                item["session"], item["code"] = sid, code
                self.by_model[address] = self.models[item["model"]].model
                if not code:
                    item["feedback"] = None
                    continue
                status, detail = self.compile(item["f"], code)
                if status == "MATCH":
                    self.accepted[address] = code
                    self.status[address] = "MATCH"
                    del pending[address]
                elif status == "compile-error":
                    item["feedback"] = (f"It does not compile:\n{detail}\n"
                                        "Return the corrected full definition only.")
                else:
                    diffs[address] = detail
            if diffs:
                self.test(pending, diffs, round_no)
            done = sum(1 for s in self.status.values())
            print(f"  round {round_no}: accepted {done} of {len(self.funcs)} "
                  f"({sum(1 for s in self.status.values() if s == 'MATCH')} MATCH); pending {len(pending)}", flush=True)
        if self.accepted or not self.existing:
            self.source.write_text(self.unit())
        for address, item in pending.items():
            self.status[address] = "not accepted"
        if not self.finish():
            raise RuntimeError(f"final TU was not accepted; attempt retained in {self.work}")
        traffic = {m.model: {"sent": m.sent, "received": m.received} for m in self.models}
        (self.work / "result.json").write_text(json.dumps({
            "status": self.status, "by_model": {a: self.by_model.get(a) for a in self.status},
            "traffic": traffic}, indent=1))
        for model, t in traffic.items():
            print(f"  {model}: {t['sent'] // 1000}K chars sent, {t['received'] // 1000}K received")
        tested = sorted(a for a, s in self.status.items() if s == "tested")
        if tested:
            print(f"  generated tests passed for {len(tested)}; check their strength and record them with\n"
                  f"  python3 tools/decomp/mutate.py --accept {' '.join(tested)}")
        return self.status

    def keep_existing(self):
        """--resume: functions the TU already defines stay; only the missing ones are asked for."""
        try:
            rows = self.compare()["functions"]
        except SystemExit:
            kept = self.work / "abandoned.cpp"
            shutil.copy(self.source, kept)
            print(f"  the existing TU does not compile; kept as {kept}, starting fresh", flush=True)
            return
        present = {r["address"] for r in rows if r.get("address") and r["status"] != "MISSING"}
        self.existing = self.source.read_text()
        for f in self.funcs:
            if f["address"] in present:
                self.status[f["address"]] = "existing"
        print(f"  resumed: {len(self.status)} of {len(self.funcs)} functions already written", flush=True)

    def finish(self):
        """Moves the declarations the TU (and the class headers written for it) use from the
        generated headers into decomp/include and checks that it builds without them, with
        the same results. A TU without accepted functions is removed, its headers stay."""
        try:
            before = self.compare()
        except SystemExit as error:
            print(f"  the TU does not compile:\n{str(error)[:1500]}")
            return False
        written = promote.promote(self.source)
        saved = os.environ.pop("OTL_EXTRA_INCLUDE", None)
        try:
            after = self.compare()
        except SystemExit as error:
            print(f"  promoted {', '.join(written)}, but the TU no longer compiles without the generated "
                  f"headers:\n{str(error)[:1500]}")
            return False
        finally:
            if saved is not None:
                os.environ["OTL_EXTRA_INCLUDE"] = saved
            if not self.accepted and not self.existing:
                self.source.unlink(missing_ok=True)
        final = {r["address"]: r for r in after["functions"] if r.get("address")}
        changed = [a for a, status in self.status.items() if status == "MATCH"
                   and final.get(a, {}).get("status") != "MATCH"]
        if changed or after.get("unknown"):
            print(f"  final signatures/MATCH changed: {changed}; publication refused")
            return False
        if before.get("object_digest") != after.get("object_digest"):
            tested = [f for f in self.funcs if self.status.get(f["address"]) == "tested"]
            if tested:
                made, skipped = autotest.Generator().write(tested)
                if skipped or len(made) != len(tested):
                    print("  final object changed; differential tests unavailable; publication refused")
                    return False
                saved = os.environ.pop("OTL_EXTRA_INCLUDE", None)
                try:
                    blob, loader = hybrid.build(out=self.work / "final-test", src=ROOT / "decomp/src",
                                                tests=sorted(autotest.OUT.glob("*.cpp")), verbose=False)
                    code, report = hybrid.selftest(blob, loader, only=",".join("auto_" + f["address"][2:] for f in made))
                    completed = set()
                    for line in report:
                        m = re.match(r"\s+stats auto_(\w+) same (\d+) both-failed \d+ different (\d+)(?: incomplete (\d+))?", line)
                        if (m and int(m.group(2)) >= autotest.MIN_COMPLETED
                                and int(m.group(3)) == 0 and int(m.group(4) or 0) == 0):
                            completed.add("0x" + m.group(1))
                    if code or completed != {f["address"] for f in made}:
                        print("  final object changed and its differential retest failed; publication refused")
                        return False
                finally:
                    if saved is not None:
                        os.environ["OTL_EXTRA_INCLUDE"] = saved
        print(f"  promoted into decomp/include: {', '.join(written) or 'nothing'}"
              + "; final object checked without generated includes")
        return True

    def compare(self):
        return objdiff.compare_source(self.source, self.original, quiet=True)

    def test(self, pending, diffs, round_no):
        """Generated differential tests for every DIFF candidate in one game run."""
        candidates = {a: pending[a]["code"] for a in diffs}
        # Candidates must compile together with the accepted functions.
        text = self.unit(candidates.values())
        self.source.write_text(text)
        try:
            objdiff.compare_source(self.source, self.original, quiet=True)
        except SystemExit:
            for a in candidates:  # fall back: test them one by one next round
                pending[a]["feedback"] = ("Your definition compiles alone but conflicts with the other functions "
                                          "of the file. Return it again.")
            return
        funcs = [pending[a]["f"] for a in candidates]
        made, skipped = autotest.Generator().write(funcs)
        tests = sorted(autotest.OUT.glob("*.cpp"))
        verdicts = {}
        if made:
            os.environ["OTL_SELFTEST_TIMEOUT"] = str(60 + 12 * len(made))
            try:
                blob, loader = hybrid.build(out=self.work / "test", src=ROOT / "decomp/src", verbose=False, tests=tests)
                test_code, report = hybrid.selftest(blob, loader, only=",".join(f"auto_{f['address'][2:]}" for f in made))
                if test_code != 0:
                    print(f"  hybrid selftest failed with exit code {test_code}; no candidates accepted", flush=True)
                    report = []
            except subprocess.TimeoutExpired:
                report = []
            except SystemExit as error:  # the game build itself is broken: no verdicts this round
                print(f"  hybrid build failed: {str(error)[:300]}", flush=True)
                report = []
            for line in report:
                m = re.match(r"\s+stats auto_(\w+) same (\d+) both-failed (\d+) different (\d+)(?: incomplete (\d+))?", line)
                if m:
                    verdicts[f"0x{m.group(1)}"] = tuple(int(x or 0) for x in m.groups()[1:])
            cases = {}
            for line in report:
                m = re.match(r"\s+auto_(\w+) case (\d+): (.*)", line)
                if m:
                    cases.setdefault(f"0x{m.group(1)}", m.group(3))
        for a, code in candidates.items():
            v = verdicts.get(a)
            if v and v[2] == 0 and v[3] == 0 and v[0] >= autotest.MIN_COMPLETED:
                self.accepted[a] = code
                self.status[a] = "tested"
                del pending[a]
                continue
            if v and v[2]:
                why = (f"A differential test ran the original and your function on the same generated object and "
                       f"arguments and saw a difference ({cases.get(a, '')}). The capture is the return value, "
                       "8 bytes of heap usage, then the object's bytes (field offsets as in the header).")
            elif a in skipped or not v:
                why = "No differential test could be generated for it, so only the instructions can be compared."
            else:
                why = "The differential test was inconclusive (the original crashes on most generated inputs)."
            if round_no >= self.rounds - 1 and not (v and v[2]):
                # Untestable and still DIFF near the end: keep it out of the game, record it.
                (self.work / "untested").mkdir(exist_ok=True)
                (self.work / "untested" / f"{a}.cpp").write_text(code)
            pending[a]["feedback"] = (f"{why}\nInstruction diff of your build against the original "
                                      f"(normalized, - yours, + original):\n```\n{diffs[a]}\n```\n"
                                      "Fix the logic so it behaves like the original (byte identity is optional). "
                                      "Return the full definition only.")


def headers_by_class():
    """Class or namespace name -> hand-written headers declaring it."""
    out = {}
    for h in sorted((ROOT / "decomp" / "include").glob("*.h")):
        text = h.read_text(errors="replace")
        for m in re.finditer(r"^(?:class|struct)\s+(\w+)\s*(?::[^{;]*)?\{|^namespace\s+(\w+)", text, re.M):
            out.setdefault(m.group(1) or m.group(2), []).append(h.name)
    return out


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("tu")
    parser.add_argument("--models", default=",".join(MODELS),
                        help="comma-separated chain; a function moves on after --switch-after rounds")
    parser.add_argument("--rounds", type=int, default=5)
    parser.add_argument("--switch-after", type=int, default=2)
    parser.add_argument("--jobs", type=int, default=4, help="model calls in parallel")
    parser.add_argument("--resume", action="store_true",
                        help="keep the functions an existing decomp/src/<TU> defines, ask only for the rest")
    parser.add_argument("--overwrite", action="store_true",
                        help="replace an existing decomp/src/<TU> with what this run accepts (default: refuse)")
    parser.add_argument("--ignore-owner", action="store_true", help="work on a TU decomp/owners.json gives to "
                        "someone else than $OTL_OWNER")
    args = parser.parse_args()
    import parallel
    owner = parallel.owned_by_others(args.tu)
    if owner and not args.ignore_owner:
        raise SystemExit(f"{args.tu} belongs to {owner} (decomp/owners.json); set OTL_OWNER or --ignore-owner")
    if (ROOT / "decomp" / "src" / args.tu).exists() and not (args.resume or args.overwrite):
        raise SystemExit(f"decomp/src/{args.tu} exists: --resume keeps its functions, --overwrite replaces it")
    started = time.time()
    import publication
    stage = publication.Stage()
    print(f"isolated attempt: {stage.path}")
    with stage.activate():
        import llm_loop as engine
        status = engine.Loop(args.tu, args.models.split(","), args.rounds, args.switch_after, args.jobs,
                             args.resume).run()
    stage.validate()
    print("published:", ", ".join(stage.publish()) or "unchanged")
    from collections import Counter
    print(f"done in {(time.time() - started) / 60:.1f} min: {dict(Counter(status.values()))}")


if __name__ == "__main__":
    main()
