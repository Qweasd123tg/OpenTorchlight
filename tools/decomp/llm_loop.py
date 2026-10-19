#!/usr/bin/env python3
"""Bounded function recovery in an isolated, resumable publication.Stage.

    python3 tools/decomp/llm_loop.py Graph.cpp --address 0x123 --prepare-only
    python3 tools/decomp/llm_loop.py Graph.cpp --address 0x123 --attempt PATH

Default: at most 16 definitions, at most 4096 original bytes each, free model
only, diagnostics/artifacts retained in the Stage, no publication. Existing
definitions are always preserved. Model calls are parallel; compile and check
operations are serial. --no-autotest rejects DIFFs without running a game.
--publish explicitly runs unchanged Stage validation/publication safeguards.
Resume requires the same selection, model settings and immutable inputs.
"""
from __future__ import annotations

import argparse
from concurrent.futures import ThreadPoolExecutor
from contextlib import nullcontext, redirect_stdout
import difflib
import fcntl
import hashlib
import json
import os
from pathlib import Path
import re
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
import toolchain  # noqa: E402
import llm_definitions as definitions  # noqa: E402
from llm_model import Model  # noqa: E402
from llm_context import ContextIndex, _standard_string_aliases  # noqa: E402
from llm_packet import DEFAULT_MAX_CHARS, build_prompt  # noqa: E402

ROOT = elfdb.ROOT
IDIOMS = Path(__file__).resolve().parent / "prompts" / "idioms.md"
# Paid providers are used only when explicitly named.
MODELS = ("opencode/space-bunny-free",)
WRITTEN = ("function", "ctor", "dtor", "static")
ASM_LABEL = re.compile(r"\b(?:__asm__|asm)\s*(?:volatile\s*)?\(\s*\"_Z")


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


def select_functions(db, tu_name, addresses=(), limit=16, max_size=4096, excluded=()):
    """Resolve symbol/address aliases before deduplicating source definitions."""
    tus = [t for t in db["tus"] if t["name"] == tu_name and t.get("kind") == "game"]
    if len(tus) != 1 or Path(tu_name).name != tu_name:
        raise ValueError("expected one canonical game TU name")
    tu = tus[0]
    funcs = sorted((f for f in db["functions"].values() if f["tu"] == tu["id"]
                    and f["kind"] in WRITTEN and "thunk to " not in f["demangled"]
                    and not any(n.endswith("D0Ev") for n in f["names"])),
                   key=lambda f: int(f["address"], 16))
    canonical, aliases = {}, {}
    for f in funcs:
        key = definitions.identity(f)
        canonical.setdefault(key, f)
    for f in db["functions"].values():
        main = canonical.get(definitions.identity(f)) if f["tu"] == tu["id"] else None
        if main and not any(n.endswith("D0Ev") for n in f["names"]):
            aliases[int(f["address"], 16)] = main
            for name in f["names"]:
                aliases[name] = main
    chosen = {}
    for address in addresses:
        try:
            key = int(address, 16)
        except ValueError:
            key = address
        if key not in aliases:
            raise ValueError(f"{address}: not an eligible symbol/address of {tu_name}")
        f = aliases[key]
        if f["size"] > max_size:
            raise ValueError(f"{address}: exceeds --max-size {max_size}")
        chosen[f["address"]] = f
    selected = sorted(chosen.values() if addresses else
                      (f for f in canonical.values() if f["size"] <= max_size
                       and not (definitions.closure(f, db) & set(excluded))),
                      key=lambda f: int(f["address"], 16))
    if addresses and len(selected) > limit:
        raise ValueError("explicit selection exceeds --limit")
    selected = selected[:limit]
    if not selected:
        raise ValueError("no eligible functions selected")
    return tu, selected


def atomic_json(path, data):
    import publication
    publication._replace_file(path.parent, path.name, json.dumps(data, indent=2, sort_keys=True).encode())


def packet_inputs(root):
    """Draft/header inputs are copied; db/scaffold may be read-only links."""
    out = {}
    import type_inputs
    out["type-return-matches"] = type_inputs.matched_addresses(root)
    for name in ("db", "scaffold", "drafts", "include-gen", "types.json", "examples.json"):
        base = root / "build-decomp" / name
        # Instruction/normalization caches are derived and mutable, not work
        # inputs. They must not inflate every checkpoint or break a restart.
        files = [base / "elfdb.json"] if name == "db" else sorted(base.rglob("*")) if base.is_dir() else [base]
        for path in files:
            if path.is_file():
                out[path.relative_to(root).as_posix()] = toolchain.sha256(path)
    elf = elfdb.default_elf()
    out["elf"] = {"path": str(elf.resolve()), "sha256": toolchain.sha256(elf)}
    return out


def _repair_progress(root, db):
    """Strict admission input, never a replacement acceptance registry."""
    import acceptance
    import evidence
    def unique(pairs):
        result = {}
        for key, value in pairs:
            if key in result:
                raise ValueError("duplicate progress key")
            result[key] = value
        return result
    raw = (Path(root) / "build-decomp/progress.json").read_bytes()
    data = json.loads(raw, object_pairs_hook=unique)
    known = db["functions"]
    addresses = data.get("accepted") if isinstance(data, dict) else None
    if (not re.fullmatch(r"[0-9a-f]{64}", str(db.get("original_elf_sha256", "")))
            or not isinstance(data, dict) or data.get("schema") != 1
            or data.get("original_elf_sha256") != db.get("original_elf_sha256")
            or not isinstance(addresses, list) or not all(isinstance(a, str) and a in known for a in addresses)
            or len(addresses) != len(set(addresses)) or type(data.get("accepted_functions")) is not int
            or data["accepted_functions"] != len(addresses) or not isinstance(data.get("units"), list)
            or not isinstance(data.get("comparison_evidence"), dict)):
        raise ValueError("repair requires complete compatible canonical progress")
    protected = set(addresses)
    for address, receipt in data["comparison_evidence"].items():
        ev = receipt.get("evidence") if isinstance(receipt, dict) else None
        if (address not in known or not isinstance(ev, dict) or receipt.get("policy") != acceptance.POLICY_VERSION
                or receipt.get("method") != "executed-call-pair" or ev.get("schema") != evidence.SCHEMA
                or receipt.get("original_elf_sha256") != db["original_elf_sha256"]
                or any(not isinstance(ev.get(k), str) or not re.fullmatch(r"[0-9a-f]{64}", ev[k])
                       for k in ("object_digest", "inputs_digest"))):
            raise ValueError("invalid repair protection receipt")
        protected.add(address)  # Stale behavioral receipts remain protected.
    for unit in data["units"]:
        if not isinstance(unit, dict) or not isinstance(unit.get("functions"), list):
            raise ValueError("invalid repair progress unit")
        for row in unit["functions"]:
            if not isinstance(row, dict) or row.get("status") not in ("MATCH", "DIFF", "MISSING", "EXTRA"):
                raise ValueError("invalid repair progress function")
            if row["status"] == "MATCH" and row.get("address"):
                protected.add(row["address"])
    return data, hashlib.sha256(raw).hexdigest(), protected


def _repair_deleting_destructor(row_address, owner, db, canonical_rows, compare_rows):
    """Keep an already MATCH independent D0 wrapper protected during D1 repair."""
    wrapper = db['functions'].get(row_address, {})
    names = wrapper.get('names', [])
    if (row_address == owner['address'] or wrapper.get('tu') != owner.get('tu')
            or owner.get('kind') != 'dtor' or wrapper.get('kind') != 'dtor'
            or len(names) != 1 or not names[0].endswith('D0Ev')
            or set(owner.get('names', [])) != {names[0][:-4] + 'D1Ev', names[0][:-4] + 'D2Ev'}
            or wrapper.get('scope') != owner.get('scope') or wrapper.get('size') != 18):
        raise ValueError('repair target/alias is accepted or protected: ' + row_address)
    # A pin is narrower than a body-repair permission: inspect the exact native
    # GCC wrapper and its references, then require two fresh strong MATCH rows.
    import elfimage
    import struct
    image = elfimage.load(elfdb.default_elf())
    if image.sha256 != db.get('original_elf_sha256'):
        raise ValueError('repair deleting destructor ELF input differs')
    address = int(row_address, 16)
    code = image.read(address, 18)
    if (code[:5] != b'\x53\x48\x89\xfb\xe8'
            or code[9:14] != b'\x48\x89\xdf\x5b\xe9'
            or address + 9 + struct.unpack('<i', code[5:9])[0] != int(owner['address'], 16)
            or image.plt.get(address + 18 + struct.unpack('<i', code[14:18])[0])
                != '_ZN4Ogre12NedAllocImpl12deallocBytesEPv'):
        raise ValueError('repair deleting destructor native references differ')
    saved = []
    for rows in (canonical_rows, compare_rows):
        found = [row for row in rows if row.get('address') == row_address]
        if (len(found) != 1 or found[0].get('status') != 'MATCH'
                or found[0].get('weak') is not False or found[0].get('name') != names[0]
                or found[0].get('size') != 18 or found[0].get('original_size') != 18
                or not re.fullmatch(r'[0-9a-f]{16}', str(found[0].get('code', '')))):
            raise ValueError('repair requires an unchanged strong MATCH deleting destructor: ' + row_address)
        saved.append(found[0])
    if saved[0]['code'] != saved[1]['code']:
        raise ValueError('repair deleting destructor changed in fresh baseline: ' + row_address)
    return {'address': row_address, 'name': names[0], 'code': saved[0]['code']}


def _repair_thunk(row_address, owner, db, canonical_rows, compare_rows):
    """Pin only an independently emitted non-virtual adjustment thunk."""
    if any(name.endswith('D0Ev') for name in db['functions'].get(row_address, {}).get('names', [])):
        return _repair_deleting_destructor(row_address, owner, db, canonical_rows, compare_rows)
    thunk = db['functions'].get(row_address, {})
    names = thunk.get('names', [])
    mangled = [re.fullmatch(r'_ZThn?[0-9]+_(.+)', n) for n in names]
    if (row_address == owner['address'] or thunk.get('tu') != owner.get('tu')
            or thunk.get('kind') != 'function'
            or not thunk.get('demangled', '').startswith('non-virtual thunk to ')
            or not names or not all(mangled)
            or any('_Z' + match.group(1) not in owner.get('names', []) for match in mangled if match)
            or definitions.identity(thunk) != definitions.identity(owner)):
        raise ValueError('repair target/alias is accepted or protected: ' + row_address)
    saved = []
    for rows in (canonical_rows, compare_rows):
        found = [r for r in rows if r.get('address') == row_address]
        if (len(found) != 1 or found[0].get('status') != 'MATCH'
                or found[0].get('weak') is not False or found[0].get('name') not in names
                or not re.fullmatch(r'[0-9a-f]{16}', str(found[0].get('code', '')))):
            raise ValueError('repair requires a strong unchanged MATCH adjustment thunk: ' + row_address)
        saved.append(found[0])
    if saved[0]['name'] != saved[1]['name'] or saved[0]['code'] != saved[1]['code']:
        raise ValueError('repair adjustment thunk changed in fresh baseline: ' + row_address)
    return {'address': row_address, 'name': saved[0]['name'], 'code': saved[0]['code']}


def validate_repair_thunks(snapshot, final_rows):
    """A body repair never grants permission to replace its accepted thunk."""
    for pinned in snapshot.get('protected_thunks', []):
        found = [r for r in final_rows if r.get('address') == pinned['address']]
        if (len(found) != 1 or found[0].get('status') != 'MATCH'
                or found[0].get('weak') is not False or found[0].get('name') != pinned['name']
                or found[0].get('code') != pinned['code']):
            raise RuntimeError('repair changed or omitted protected MATCH adjustment thunk: ' + pinned['address'])


def _coherent_repair_aliases(function, rows):
    """The two original C1/C2 or D1/D2 names may share one emitted body."""
    if len(rows) != 2 or function.get("kind") not in ("ctor", "dtor"):
        return False
    names = sorted(row.get("name", "") for row in rows)
    if len(set(names)) != 2 or set(names) != set(function.get("names", ())):
        return False
    if len(names[0]) != len(names[1]):
        return False
    different = [i for i, (a, b) in enumerate(zip(*names)) if a != b]
    if len(different) != 1:
        return False
    at = different[0]
    marker = "C" if function["kind"] == "ctor" else "D"
    if (at == 0 or at + 1 == len(names[0]) or names[0][at - 1] != marker
            or names[0][at + 1] != "E" or (names[0][at], names[1][at]) != ("1", "2")):
        return False
    body = [{k: v for k, v in row.items() if k not in ("name", "demangled")}
            for row in rows]
    return (body[0] == body[1]
            and re.fullmatch(r"[0-9a-f]{16}", str(body[0].get("code", ""))) is not None
            and type(body[0].get("size")) is int and body[0]["size"] > 0)


def repair_snapshot(root, tu, functions, db, compare_rows):
    """Bind explicit unaccepted-body repair to existing source/protection inputs."""
    root = Path(root)
    progress, digest, protected = _repair_progress(root, db)
    if not functions or not isinstance(compare_rows, list):
        raise ValueError("explicit repair targets and baseline comparison required")
    for row in compare_rows:
        if not isinstance(row, dict):
            raise ValueError("invalid repair baseline comparison")
        if row.get("status") == "MATCH" and row.get("address"):
            protected.add(row["address"])
    units = [u for u in progress["units"] if u.get("tu") == tu]
    if (len(units) != 1 or units[0].get("unknown") != []
            or not re.fullmatch(r"[0-9a-f]{64}", str(units[0].get("object_digest", "")))):
        raise ValueError("repair requires one known canonical progress TU")
    object_digest = units[0]["object_digest"]
    if any(row.get("object_digest") != object_digest
           for row in units[0]["functions"] + compare_rows):
        raise ValueError("repair progress object differs from fresh baseline")
    targets = []
    protected_thunks = {}
    for f in functions:
        address = f["address"]
        if (f != db["functions"].get(address) or f.get("kind") not in WRITTEN
                or "thunk to " in f.get("demangled", "") or any(n.endswith("D0Ev") for n in f.get("names", []))
                or f.get("tu") != next(
                (t["id"] for t in db["tus"] if t.get("name") == tu and t.get("kind") == "game"), None)):
            raise ValueError("repair target is not an owning-TU definition")
        if address in protected:
            raise ValueError("repair target/alias is accepted or protected: " + address)
        for sibling in sorted(definitions.closure(f, db) & protected):
            protected_thunks[sibling] = _repair_thunk(
                sibling, f, db, units[0]['functions'], compare_rows)
        for rows in (units[0]["functions"], compare_rows):
            found = [r for r in rows if r.get("address") == address]
            if ((len(found) != 1 and not _coherent_repair_aliases(f, found))
                    or any(row.get("status") != "DIFF" or row.get("weak") is not False
                           or row.get("name") not in f["names"]
                           or not re.fullmatch(r"[0-9a-f]{64}", str(row.get("object_digest", "")))
                           for row in found)):
                raise ValueError("repair requires an existing strong unaccepted DIFF: " + address)
        targets.append(address)
    source = root / "decomp/src" / tu
    if source.resolve() != root.resolve() / "decomp/src" / tu:
        raise ValueError("redirected repair source")
    return {"schema": 1, "tu": tu, "addresses": sorted(targets),
            "source_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
            "progress_sha256": digest, "protected": sorted(protected), "compare_rows": compare_rows,
            "protected_thunks": [protected_thunks[a] for a in sorted(protected_thunks)]}


def validate_repair_snapshot(stage, checkpoint, targets, db):
    """Recheck admission and non-target bytes, without restoring validation authority."""
    selected = checkpoint["settings"]["selected"]
    addresses = checkpoint["settings"].get("repair_addresses", [])
    saved = checkpoint.get("repair")
    if not addresses and saved is None:
        return
    if (not addresses or not isinstance(saved, dict)
            or checkpoint["settings"].get("repair_mode") != "external-prepare-only"
            or checkpoint.get("accepted") or checkpoint.get("round") != 0
            or sorted(addresses) != sorted(targets)
            or sorted(addresses) != sorted(f["address"] for f in selected)):
        raise RuntimeError("repair selection/snapshot mismatch")
    current = repair_snapshot(stage.root, saved.get("tu"), selected, db, saved.get("compare_rows"))
    copied = stage.path / "build-decomp/progress.json"
    if (saved != current or toolchain.sha256(copied) != current["progress_sha256"]
            or stage.baseline.get("decomp/src/" + current["tu"]) != current["source_sha256"]
            or hashlib.sha256(checkpoint["existing"].encode()).hexdigest() != current["source_sha256"]):
        raise RuntimeError("repair source/protection inputs changed; prepare a new attempt")
    import mutate
    def parameter_identity(parameter, named=False):
        p = parameter.strip()
        if any(c in p for c in "()[]=;"):
            raise RuntimeError("repair source signature uses unsupported declarator")
        if named:
            name = re.search(r"([*&]\s*|\s+)([A-Za-z_]\w*)$", p)
            keywords = {"int", "long", "short", "char", "wchar_t", "double", "float", "bool",
                        "void", "const", "volatile", "unsigned", "signed"}
            if name and name.group(2) not in keywords:
                p = p[:name.start(2)].strip()
        p = ghidra_cpp.cxx_type(_standard_string_aliases(p))
        p = re.sub(r"(?<=\w)\s+(?=\w)", "|", p)
        return re.sub(r"\s+", "", p)

    def outside_bodies(text):
        masked = mutate.mask(text)
        spans = []
        for f in selected:
            # mutate.definition deliberately tolerates arity-only draft matches.
            # Admission needs the exact qualified signature instead.
            wanted = [parameter_identity(p) for p in ghidra_cpp.split_args(f.get("params") or "")
                      if p != "void"]
            found = []
            qual = f["demangled"].split("(")[0]
            for match in re.finditer(r"(?m)^[\w:<>,*&\s]*?(?<![\w:])(?P<qualified>" +
                                     re.escape(qual) + r")\s*\(", masked):
                prefix = masked[:match.start("qualified")]
                if prefix.rstrip().endswith(":") or prefix.count("{") != prefix.count("}"):
                    continue  # Nested namespace/class/linkage scope is not inferred.
                close = mutate.matching(masked, match.end() - 1, "(", ")")
                if close < 0:
                    continue
                brace, semi = masked.find("{", close), masked.find(";", close)
                if brace < 0 or (0 <= semi < brace):
                    continue
                suffix = " ".join(masked[close + 1:brace].strip().split())
                if f.get("kind") == "ctor" and suffix.startswith(":"):
                    suffix = ""
                actual = [parameter_identity(p, named=True)
                          for p in ghidra_cpp.split_args(masked[match.end():close].strip())
                          if p and p != "void"]
                if actual == wanted and suffix == ghidra_cpp.cv_suffix(f).strip():
                    found.append((brace, mutate.matching(masked, brace, "{", "}")))
            if len(found) != 1:
                raise RuntimeError("repair requires exact unique source signature")
            spans.append(found[0])
        if any(not span or span[0] < 0 or span[1] < span[0] for span in spans):
            raise RuntimeError("repair requires unique existing source bodies")
        ordered = sorted(spans)
        if any(a[1] >= b[0] for a, b in zip(ordered, ordered[1:])):
            raise RuntimeError("overlapping repair bodies")
        for first, last in reversed(ordered):
            text = text[:first] + "{REPAIR_BODY}" + text[last + 1:]
        return text
    candidate = stage.path / "decomp/src" / current["tu"]
    if candidate.resolve() != stage.path.resolve() / "decomp/src" / current["tu"]:
        raise RuntimeError("redirected repair candidate")
    if outside_bodies(checkpoint["existing"]) != outside_bodies(candidate.read_bytes().decode("utf-8")):
        raise RuntimeError("repair changed text outside assigned bodies")


class Loop:
    def __init__(self, tu_name, models, rounds, switch_after=2, jobs=4, resume=False, *,
                 addresses=(), limit=16, max_size=4096, prepare_only=False, no_autotest=False,
                 model_timeout=180, model_retries=2, attempt_resume=False, max_prompt_chars=DEFAULT_MAX_CHARS,
                 repair_addresses=()):
        if ROOT == elfdb.ROOT:
            raise RuntimeError("Loop requires publication.Stage.activate(); live-tree experiments are forbidden")
        if repair_addresses and (not prepare_only or addresses):
            raise ValueError("repair addresses require prepare-only and cannot mix ordinary selection")
        addresses = repair_addresses or addresses
        self.repair = None
        # Work in progress compiles against the generated headers; finish() promotes what it uses.
        os.environ["OTL_EXTRA_INCLUDE"] = str(headers.OUT)
        self.db = elfdb.load_db()
        self.source = ROOT / "decomp" / "src" / tu_name
        self.original = objdiff.Original(db=self.db)
        self.baseline_rows = []
        self.existing = ""
        if not attempt_resume and self.source.exists():
            self.existing = self.source.read_bytes().decode("utf-8")
            self.baseline_rows = self.baseline_compare()["functions"]
        excluded = {r["address"] for r in self.baseline_rows if r.get("address")
                    and r["status"] not in ("MISSING", "EXTRA")}
        request = []
        if addresses:
            _, explicit = select_functions(self.db, tu_name, addresses, limit, max_size)
            request = [f["address"] for f in explicit]
        if attempt_resume:
            saved = json.loads((ROOT / "build-decomp/llm-loop" / tu_name / "checkpoint.json").read_text())
            selected = saved["settings"]["selected"]
            if any(self.db["functions"].get(f["address"]) != f for f in selected):
                raise RuntimeError("checkpoint selected identities changed")
            self.tu, self.funcs = select_functions(self.db, tu_name, [f["address"] for f in selected], limit, max_size)
        else:
            self.tu, self.funcs = select_functions(self.db, tu_name, addresses, limit, max_size, excluded)
        self.rounds, self.switch_after, self.jobs = rounds, switch_after, jobs
        self.work = ROOT / "build-decomp" / "llm-loop" / tu_name
        self.work.mkdir(parents=True, exist_ok=True)
        self.model_names = list(models)
        self.models = []
        self.prepare_only, self.no_autotest = prepare_only, no_autotest
        self.model_timeout, self.model_retries = model_timeout, model_retries
        self.max_prompt_chars = max_prompt_chars
        self.attempt_resume = attempt_resume
        self.settings = {"tu": tu_name, "models": list(models), "rounds": rounds,
                         "switch_after": switch_after, "jobs": jobs, "limit": limit, "max_size": max_size,
                         "no_autotest": no_autotest, "model_timeout": model_timeout, "model_retries": model_retries,
                         "selected": self.funcs, "selection_request": request, "max_prompt_chars": max_prompt_chars}
        if repair_addresses:
            self.settings["repair_addresses"] = [f["address"] for f in self.funcs]
            self.settings["repair_mode"] = "external-prepare-only"
            if not attempt_resume:
                self.repair = repair_snapshot(ROOT, tu_name, self.funcs, self.db, self.baseline_rows)
        self.examples = examples.load()
        self.by_model = {}
        self.classes = sorted({(f.get("scope") or "").split("::")[0] for f in self.funcs} - {""})
        self.methods = ghidra_cpp.known_methods(self.db)
        self.signatures = ghidra_cpp.signatures_of(self.db)
        self.enums = ghidra_cpp.parse_enums()
        import ghidra_draft
        state, reasons = ghidra_draft.draft_state(tu_name, self.db,
                                                addresses=[f["address"] for f in self.funcs], root=ROOT)
        self.stale_note = (f"; unavailable current draft inputs: {'; '.join(reasons)}"
                           if state != "fresh" else "")
        self.accepted = {}  # address -> code
        self.status = {}
        self.resume = resume
        self.allowed_headers = set()
        self.pending = {}
        self.items = {}
        self.round_no = 0

    def checkpoint(self):
        import publication
        atomic_json(self.work / "checkpoint.json", {
            "schema": 1, "settings": self.settings, "inputs": packet_inputs(ROOT),
            "repair": getattr(self, "repair", None),
            "tree": publication.tree_state(ROOT), "immutable": self.immutable,
            "accepted": self.accepted, "status": self.status, "existing": self.existing,
            "headers": self.headers, "pending": self.pending, "round": self.round_no,
            "items": self.items, "by_model": self.by_model, "allowed_headers": sorted(self.allowed_headers)})

    def restore(self):
        import publication
        data = json.loads((self.work / "checkpoint.json").read_text())
        if (data.get("schema") != 1 or data.get("settings") != self.settings
                or data.get("inputs") != packet_inputs(ROOT)
                or data.get("tree") != publication.tree_state(ROOT)):
            raise RuntimeError("checkpoint inputs/settings changed; refusing resume")
        if self.settings.get("repair_addresses"):
            metadata = json.loads((ROOT / "stage.json").read_text())
            from types import SimpleNamespace
            stage = SimpleNamespace(root=Path(metadata["root"]), path=ROOT, baseline=metadata["baseline"])
            validate_repair_snapshot(stage, data, self.settings["repair_addresses"], self.db)
            self.repair = data["repair"]
        elif data.get("repair") is not None:
            raise RuntimeError("unexpected repair checkpoint")
        self.immutable = data["immutable"]
        if (ROOT / "stage.json").exists():
            metadata = json.loads((ROOT / "stage.json").read_text())
            baseline = metadata["baseline"]
            if self.immutable["tree"] != baseline:
                raise RuntimeError("checkpoint immutable baseline changed")
            if self.immutable["inputs"] != packet_inputs(Path(metadata["root"])):
                raise RuntimeError("immutable work inputs changed since selection")
        if self.immutable["settings"] != self.settings:
            raise RuntimeError("immutable model/selection settings changed")
        # Never widen publication scope using a checkpoint-provided allowlist.
        self.allowed_headers = set(data["headers"].values())
        selected = {f["address"]: f for f in self.funcs}
        if not (set(data["accepted"]) <= set(selected) and set(data["items"]) <= set(selected)
                and set(data["status"]) <= set(selected) and set(data["pending"]) <= set(data["items"])):
            raise RuntimeError("invalid checkpoint item keys")
        if any(s not in ("MATCH", "tested", "existing", "blocked", "rejected") for s in data["status"].values()):
            raise RuntimeError("invalid checkpoint status")
        for address, item in data["items"].items():
            if (item.get("f") != selected[address] or type(item.get("model")) is not int
                    or not 0 <= item["model"] < len(self.model_names)
                    or type(item.get("tries")) is not int or item["tries"] < 0):
                raise RuntimeError("invalid checkpoint item identity/model/tries")
        if type(data["round"]) is not int or not 0 <= data["round"] <= self.rounds:
            raise RuntimeError("invalid checkpoint round")
        initial_source = self.immutable["tree"].get("decomp/src/" + self.tu["name"])
        existing = data["existing"]
        digest = hashlib.sha256(existing.encode()).hexdigest() if initial_source is not None or existing else None
        if digest != initial_source:
            raise RuntimeError("checkpoint existing source differs from immutable baseline")
        if any(Path(h).name != h or not h.endswith(".h") for h in data["headers"].values()):
            raise RuntimeError("invalid checkpoint header")
        if set(data["headers"]) != set(self.classes):
            raise RuntimeError("checkpoint header owners differ from selected classes")
        for attr in ("accepted", "status", "existing", "headers", "pending", "items", "by_model"):
            setattr(self, attr, data[attr])
        # Reestablish shared per-item state after JSON deserialization.
        self.pending = {a: self.items[a] for a in self.pending}
        self.round_no = data["round"]
        # Status strings are scheduling hints, never acceptance receipts.
        self.status = {a: "blocked" for a, s in self.status.items() if s == "blocked"}
        if self.existing:
            probe = self.work / "baseline" / self.tu["name"]
            probe.parent.mkdir(exist_ok=True)
            probe.write_bytes(self.existing.encode())
            restored_unit = objdiff.compare_source(probe, self.original, quiet=True, scores=False)
            rows = restored_unit["functions"]
            if getattr(self, "repair", None) and restored_unit.get("unknown") != []:
                raise RuntimeError("fresh repair baseline has unknown definitions")
            if getattr(self, "repair", None) and repair_snapshot(
                    ROOT, self.tu["name"], self.funcs, self.db, rows) != self.repair:
                raise RuntimeError("fresh repair baseline changed during resume")
            present = {r["address"] for r in rows if r.get("address") and r["status"] not in ("MISSING", "EXTRA")}
            self.status.update({a: "existing" for a in selected if a in present})
        for address, code in self.accepted.items():
            error = definitions.single_definition(selected[address], code)
            if error:
                raise RuntimeError("invalid restored definition: " + error)
        if self.accepted and not self.prepare_only:
            probe = self.work / "restored" / self.tu["name"]
            probe.parent.mkdir(exist_ok=True)
            probe.write_bytes(self.unit().encode())
            unit = objdiff.compare_source(probe, self.original, quiet=True, scores=False)
            for address in self.accepted:
                status, detail = definitions.verdict(selected[address], unit, self.db)
                if status != "MATCH" or unit.get("unknown"):
                    raise RuntimeError("restored candidate is not freshly MATCH: " + detail)
                self.status[address] = "MATCH"
        self.pending = {a: self.items.get(a, {"f": f, "model": 0, "tries": 0,
                                             "session": None, "feedback": None, "code": ""})
                        for a, f in selected.items() if a not in self.status and a not in self.accepted}
        self.items.update(self.pending)

    def baseline_compare(self):
        saved = os.environ.pop("OTL_EXTRA_INCLUDE", None)
        try:
            result = self.compare()
            if result.get("unknown"):
                raise RuntimeError("existing TU has unknown original definitions")
            return result
        except SystemExit as error:
            raise RuntimeError("existing TU does not compile; preserved unchanged, refusing to start fresh") from error
        finally:
            if saved is not None:
                os.environ["OTL_EXTRA_INCLUDE"] = saved

    def draft(self, f):
        raw = ROOT / "build-decomp" / "drafts" / self.tu["name"] / "raw" / f"{f['address']}.c"
        if not raw.exists():
            return "(no draft)"
        import ghidra_draft
        state, reasons = ghidra_draft.draft_state(self.tu["name"], self.db,
                                                addresses=[f["address"]], root=ROOT)
        if state != "fresh":
            return "(Ghidra draft omitted: " + "; ".join(reasons) + ")"
        try:
            return ghidra_cpp.convert(raw.read_text(errors="replace"), self.methods, f, self.signatures, self.enums)
        except Exception:  # noqa: BLE001
            return raw.read_text(errors="replace")

    # -- header -------------------------------------------------------------
    def header(self):
        before = {p.name: p.read_bytes() for p in (ROOT / "decomp/include").glob("*.h")}
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
                raise RuntimeError(f"no known or generated header for {cls}; prepare inputs first")
            name = (cls[1:] if re.match(r"C[A-Z]", cls) else cls) + ".h"
            path = ROOT / "decomp" / "include" / name
            # A layout snapshot, never a hypothetical model-generated header.
            text = gen.read_text().replace(promote.GENERATED_NOTE, promote.PARTIAL_NOTE)
            path.write_text(re.sub(r"\bGEN_\w+_H\b", promote.guard(name), text))
            out[cls] = name
            # Generated headers that pulled in the draft now get the real one.
            for other in (ROOT / "build-decomp" / "include-gen").glob("*.h"):
                other.write_text(other.read_text().replace(f'#include "{cls}.h"', f'#include "{name}"'))
            gen.unlink()
        self.headers = out
        self.allowed_headers.update(p.name for p in (ROOT / "decomp/include").glob("*.h")
                                    if before.get(p.name) != p.read_bytes())

    def declaration_error(self, f):
        if not f.get("method") or not f.get("scope"):
            return None
        name = self.headers.get(f["scope"].split("::")[0])
        if not name:
            return "No known owning header for selected method."
        from llm_context import DeclarationIdentity, _scan
        sources = {path.name: path.read_text() for path in (ROOT / "decomp/include").glob("*.h")}
        identity = DeclarationIdentity(sources)
        qualified = f["scope"] + "::" + f["method"]
        # The scanner keeps the complete balanced lexical class/namespace path,
        # including nested owners. It never searches a short class-name suffix.
        namespace = any(headers.namespace_bodies(source, f["scope"]) for source in sources.values())
        choices = sources.items() if namespace else [(name, sources[name])]
        matches = [(header, declaration) for header, source in choices
                   for declaration in _scan(source)[0]
                   if declaration.kind == "function" and declaration.qualified == qualified]
        if any(identity.matches(declaration, dict(f, qualified=qualified), header)
               for header, declaration in matches):
            return None
        return "Selected method signature is absent from the known header; declaration unavailable."

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
        extra, forward, system, seen = [], set(), set(), set()
        for f in self.funcs:
            method = f.get("method") or ""
            params = tuple(definitions.mutate.canonical_parameter(ghidra_cpp.cxx_type(p))
                           for p in ghidra_cpp.split_args(f.get("params") or "") if p != "void")
            identity = (method, params, ghidra_cpp.cv_suffix(f).strip())
            if (f.get("scope") != cls or f.get("vslots") or f["kind"] not in ("function", "ctor")
                    or identity in seen or any((tuple(definitions.mutate.canonical_parameter(t) for t in p), cv) == identity[1:]
                                               for p, cv, _ in headers.declared_signatures(body, method))):
                continue
            seen.add(identity)
            if not hasattr(self, "_decls"):
                self._decls = headers.Gen()
            gen = self._decls
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
        extra = list(extra)
        parts = [] if self.existing else ['#include "EmptyStrings.h"'] + [
            f'#include "{g}"' for g in ("GenTypes.h", "GenGlobals.h", "GenNamespaces.h") if (headers.OUT / g).exists()]
        parts += [f'#include "{h}"' for h in self.headers.values()]
        names = set()
        for code in list(self.accepted.values()) + extra:
            names.update(re.findall(r"\b[A-Za-z_]\w*\b", definitions.mutate.mask(code)))
        if self.existing:
            if names & {"EMPTY_STRING", "EMPTY_WSTRING"}:
                parts.append('#include "EmptyStrings.h"')
            for generated in ("GenTypes.h", "GenGlobals.h"):
                path = headers.OUT / generated
                if not path.exists():
                    continue
                text = path.read_text()
                declared = set(re.findall(r"\b(?:enum|class|struct)\s+(\w+)", text))
                declared.update(re.findall(r"\bextern\s+[^;{}]+?\b(\w+)\s*(?:\[[^]]*\])?\s*;", text))
                if names & declared:
                    parts.append(f'#include "{generated}"')
        incl = {p.name for p in (ROOT / "decomp" / "include").glob("*.h")}
        hand = headers_by_class()
        for n in sorted(names):
            if n in hand:
                parts += [f'#include "{h}"' for h in hand[n] if h not in self.headers.values()]
            elif (ROOT / "build-decomp" / "include-gen" / f"{n}.h").exists() and f"{n}.h" not in incl:
                parts.append(f'#include "{n}.h"')
        body = [self.accepted[a] for a in sorted(self.accepted, key=lambda a: int(a, 16))] + extra
        if self.existing:
            present = set(re.findall(r'#\s*include\s*"([^"]+)"', self.existing))
            parts = [p for p in parts if p.split('"')[1] not in present]
        additions = "\n".join(dict.fromkeys(parts)) + "\n\n" + "\n\n".join(body) + "\n"
        return (self.existing + "\n" if self.existing else "") + additions

    def compile(self, f, code):
        """(status, detail): compile-error / MATCH / DIFF with the instruction diff."""
        if ASM_LABEL.search(code):
            return "compile-error", ("Symbols bound with asm labels are not source code. Define the function as "
                                     "the member the header declares, and call other functions through their "
                                      "classes (object->method(...)).")
        error = definitions.single_definition(f, code)
        if error:
            return "compile-error", error
        trial = self.work / "trial" / f["address"] / self.tu["name"]
        trial.parent.mkdir(parents=True, exist_ok=True)
        trial.write_text(self.unit([code]))
        try:
            result = objdiff.compare_source(trial, self.original, quiet=True, scores=False)
        except SystemExit as error:
            lines = [l.split(": error: ", 1)[-1] for l in str(error).splitlines() if "error" in l][:12]
            return "compile-error", "\n".join(lines) + self.name_hints(lines)
        if result.get("unknown"):
            return "compile-error", "Calls functions the game does not have:\n" + "\n".join(
                f"- {r['name']}; the game has: {'; '.join(r['known']) or 'no such member'}"
                for r in result["unknown"]) + "\nCall the existing overload (mind constness and references)."
        status, detail = definitions.verdict(f, result, self.db)
        return status, detail + ("\n" + self.instruction_diff(trial, f) if status == "DIFF" else "")

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
        # Repair feedback is bounded, but later hunks must remain discoverable.
        # Content-addressed files keep feedback from older rounds reproducible.
        full = "\n".join(diff) + ("\n" if diff else "")
        digest = hashlib.sha256(full.encode()).hexdigest()
        directory = self.work / "instruction-diffs"
        directory.mkdir(parents=True, exist_ok=True)
        stem = f"{int(f['address'], 16):#x}-{digest}"
        artifact = directory / (stem + ".diff")
        import publication
        publication._replace_file(directory, artifact.name, full.encode("utf-8"))
        starts = [i for i, line in enumerate(diff) if line.startswith("@@ ")]
        hunks = [{"id": f"hunk-{i + 1}", "header": diff[start],
                  "start_line": start + 1,
                  "end_line": starts[i + 1] if i + 1 < len(starts) else len(diff)}
                 for i, start in enumerate(starts)]
        index = directory / (stem + ".json")
        atomic_json(index, {"schema": 1, "address": f["address"], "sha256": digest,
                            "diff": artifact.name, "line_count": len(diff), "hunks": hunks})
        # The model has no filesystem tools: rotate actual diff text into feedback.
        # Split very long operands too, so one literal cannot consume the budget
        # or permanently hide all following lines. The artifact stays unchanged.
        pages, page, chars = [], [], 0
        for number, line in enumerate(diff, 1):
            chunks = [line[i:i + 4096] for i in range(0, len(line), 4096)] or [""]
            for part, chunk in enumerate(chunks, 1):
                text = (f"[diff line {number}, part {part}/{len(chunks)}] " + chunk
                        if len(chunks) > 1 else chunk)
                if page and (len(page) >= 80 or chars + len(text) + 1 > 8192):
                    pages.append(page)
                    page, chars = [], 0
                page.append((number, text))
                chars += len(text) + 1
        if page or not pages:
            pages.append(page)
        selected = getattr(self, "round_no", 0) % len(pages)
        preview = pages[selected]
        visible = {number for number, _ in preview}
        shown_hunks = [h["id"] for h in hunks
                       if any(h["start_line"] <= number <= h["end_line"] for number in visible)]
        summary = (f"Diff page {selected + 1}/{len(pages)}: {len(visible)}/{len(diff)} original lines; "
                   f"{len(diff) - len(visible)} lines not shown. Long lines/hunks may span pages.\n"
                   f"Visible hunks: {', '.join(shown_hunks) or 'none'}; {len(hunks)} total. "
                   "Pages rotate on later rounds; a bounded run may not show every page.\n"
                   f"Full diff (external review): {artifact}\n"
                   f"Hunk index (1-based inclusive diff lines): {index}\n")
        return summary + "\n".join(text for _, text in preview)

    def prompt_for(self, f):
        if not hasattr(self, "_packet_prompts"):
            self._packet_prompts = {}
        if f["address"] in self._packet_prompts:
            return self._packet_prompts[f["address"]]
        if not hasattr(self, "_context_index"):
            self._context_index = ContextIndex(root=ROOT, db=self.db, image=self.original.image,
                                               headers=headers_by_class())
        draft = self.draft(f)
        chosen = examples.choose(self.examples, draft, exclude={f["address"]})
        prompt = build_prompt(f, root=ROOT, tu=self.tu["name"], headers=self.headers, draft=draft,
                            idioms=(ROOT / "tools/decomp/prompts/idioms.md").read_text(),
                            examples=examples.render(chosen) if chosen else "", stale_note=self.stale_note,
                            max_chars=self.max_prompt_chars, context_index=self._context_index)
        if getattr(self, "repair", None):
            note = ("\n\nExplicit existing-unaccepted repair: replace only this selected body in the full TU; "
                    "do not append a duplicate definition. Read the unchanged full TU from checkpoint.existing "
                    "or external_handoff.submission.source before editing. Other TU text must remain unchanged.\n")
            if len(prompt) + len(note) > self.max_prompt_chars:
                raise ValueError("repair prompt exceeds complete-input budget")
            prompt += note
        self._packet_prompts[f["address"]] = prompt
        return prompt

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
                    addition = (f"\n\nAn earlier attempt was not accepted:\n```cpp\n{item['code']}\n```\n"
                                f"{item['feedback']}")
                    prompt += addition
            if len(prompt) > self.max_prompt_chars:
                item["blocked_reason"] = (f"Complete repair input is {len(prompt)} chars, over the "
                                          f"{self.max_prompt_chars} budget; no code/feedback was truncated.")
                return f["address"], "", item["session"]
            model = self.models[item["model"]]
            code, sid = model.ask(prompt, item["session"], tag=f"{f['address']} round {round_no} {model.model}")
            if code or item["model"] + 1 >= len(self.models):
                break
            item.update(model=item["model"] + 1, tries=0, session=None)
        item["tries"] += 1
        return f["address"], code, sid

    def run(self):
        print(f"{self.tu['name']}: {len(self.funcs)} functions, classes {', '.join(self.classes)}", flush=True)
        import publication
        if self.attempt_resume:
            self.restore()
        else:
            if (self.work / "checkpoint.json").exists():
                raise RuntimeError("attempt already has a checkpoint; use --attempt")
            self.immutable = {"tree": publication.tree_state(ROOT), "inputs": packet_inputs(ROOT),
                              "settings": self.settings}
            if self.source.exists():
                self.keep_existing()
            self.header()
            for f in self.funcs:
                error = self.declaration_error(f)
                if error and f["address"] not in self.status:
                    self.status[f["address"]] = "blocked"
            self.pending = {f["address"]: {"f": f, "session": None, "feedback": None,
                                         "model": 0, "tries": 0, "code": ""}
                            for f in self.funcs if f["address"] not in self.status}
            self.items = dict(self.pending)
            for f in self.funcs:
                if self.status.get(f["address"]) == "blocked":
                    self.items[f["address"]] = {"f": f, "model": 0, "tries": 0,
                        "session": None, "code": "", "feedback": self.declaration_error(f)}
            self.checkpoint()
        if getattr(self, "repair", None):
            metadata = json.loads((ROOT / "stage.json").read_text())
            from types import SimpleNamespace
            stage = SimpleNamespace(root=Path(metadata["root"]), path=ROOT, baseline=metadata["baseline"])
            prepared = {"settings": self.settings, "repair": self.repair, "existing": self.existing,
                        "accepted": self.accepted, "round": self.round_no}
            validate_repair_snapshot(stage, prepared, self.settings["repair_addresses"], self.db)
            # Repair is external-only; keep the full TU intact and merely prepare packets.
            for f in self.funcs:
                address = f["address"]
                if self.status.get(address) == "existing":
                    self.status.pop(address)
                error = self.declaration_error(f)
                if error:
                    self.status[address] = "blocked"
                    self.items[address] = {"f": f, "model": 0, "tries": 0, "session": None,
                                           "code": "", "feedback": error}
                    self.pending.pop(address, None)
                if address not in self.status:
                    item = self.items.setdefault(address, {"f": f, "session": None, "feedback": None,
                                                           "model": 0, "tries": 0, "code": ""})
                    self.pending[address] = item
        prompts = self.work / "prompts"
        prompts.mkdir(exist_ok=True)
        for f in self.funcs:
            if self.status.get(f["address"]) not in ("blocked", "existing"):
                try:
                    (prompts / (f["address"] + ".md")).write_text(self.prompt_for(f))
                except ValueError as error:
                    self.status[f["address"]] = "blocked"
                    self.items[f["address"]]["feedback"] = str(error)
                    self.pending.pop(f["address"], None)
        self.checkpoint()
        if self.prepare_only:
            self.write_result(prepared=True)
            return self.status
        pending = self.pending
        if pending and self.round_no < self.rounds:
            self.models = [Model(m, self.work, timeout=self.model_timeout, retries=self.model_retries)
                           for m in self.model_names]
        for round_no in range(self.round_no + 1, self.rounds + 1):
            if not pending:
                break
            with ThreadPoolExecutor(self.jobs) as pool:
                answers = list(pool.map(lambda item: self.ask(item, round_no), pending.values()))
            diffs = {}
            for address, code, sid in answers:
                item = pending[address]
                if item.get("blocked_reason"):
                    item["feedback"] = item.pop("blocked_reason")
                    self.status[address] = "blocked"
                    del pending[address]
                    continue
                item["session"], item["code"] = sid, code
                self.by_model[address] = self.models[item["model"]].model
                if not code:
                    item["feedback"] = "No code returned; provide the full definition."
                    model = self.models[item["model"]]
                    getter = getattr(model, "error_for", None)
                    error = getter(sid) if callable(getter) else None
                    item["error"] = error if isinstance(error, str) else getattr(model, "last_error", None) or "no-code"
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
            if diffs and not self.no_autotest:
                try:
                    self.test(pending, diffs, round_no)
                finally:
                    self.save_source()
            elif diffs:
                for address, detail in diffs.items():
                    pending[address]["feedback"] = f"DIFF (autotest disabled):\n{detail}\nReturn a corrected definition."
            # Never leave unsupported candidates in the staged source.
            self.save_source()
            self.round_no = round_no
            self.checkpoint()
            done = sum(s in ("MATCH", "tested") for s in self.status.values())
            print(f"  round {round_no}: accepted {done} of {len(self.funcs)} "
                  f"({sum(1 for s in self.status.values() if s == 'MATCH')} MATCH); pending {len(pending)}; "
                  f"blocked {sum(s == 'blocked' for s in self.status.values())}; "
                  f"existing {sum(s == 'existing' for s in self.status.values())}", flush=True)
        if self.accepted:
            self.source.write_text(self.unit())
        for address, item in pending.items():
            self.status[address] = "rejected"
            if item.get("code"):
                rejected = self.work / "rejected"
                rejected.mkdir(exist_ok=True)
                (rejected / (address + ".cpp")).write_text(item["code"])
        if self.accepted and not self.finish():
            self.checkpoint()
            self.write_result(error="final TU was not accepted")
            raise RuntimeError(f"final TU was not accepted; attempt retained in {self.work}")
        self.checkpoint()
        self.write_result()
        traffic = {m.model: {"sent": getattr(m, "sent", 0), "received": getattr(m, "received", 0)} for m in self.models}
        for model, t in traffic.items():
            print(f"  {model}: {t['sent'] // 1000}K chars sent, {t['received'] // 1000}K received")
        tested = sorted(a for a, s in self.status.items() if s == "tested")
        if tested:
            print(f"  generated tests passed for {len(tested)}; check their strength and record them with\n"
                  f"  python3 tools/decomp/mutate.py --accept {' '.join(tested)}")
        return self.status

    def save_source(self):
        if self.accepted:
            self.source.write_text(self.unit())
        elif self.existing or self.immutable["tree"].get("decomp/src/" + self.tu["name"]) is not None:
            self.source.write_text(self.existing)
        else:
            self.source.unlink(missing_ok=True)

    def external_handoff(self, prepared=False, error=None):
        """Describe external submission, never schedule an agent or authorize execution.

        These hashes snapshot preparation before the external worker edits its TU.
        They are not a cycle identity or acceptance receipt; Cycle checks current inputs.
        """
        result = {"schema": 1, "status": "unprepared", "blockers": [], "cycle_argv_template": None}
        if not prepared or error:
            result["blockers"] = [error or "prepare-only result required"]
            return result
        stage = ROOT.resolve()
        checkpoint = self.work / "checkpoint.json"
        metadata_path = stage / "stage.json"
        blockers = result["blockers"]
        expected_work = stage / "build-decomp/llm-loop" / self.tu["name"]
        expected_source = stage / "decomp/src" / self.tu["name"]
        fixtures = stage / "decomp/hybrid/tests"
        # Do not hand an external editor a path redirected outside its assigned Stage.
        for path, expected in ((self.source, expected_source), (self.work, expected_work),
                               (checkpoint, expected_work / "checkpoint.json"),
                               (metadata_path, stage / "stage.json"), (fixtures, fixtures)):
            if path.absolute() != expected or path.resolve() != expected:
                blockers.append("unsafe handoff path: " + str(path))
        if blockers:
            result["status"] = "blocked"
            return result
        targets = []
        for f in self.funcs:
            address = f["address"]
            status = self.status.get(address)
            prompt = self.work / "prompts" / (address + ".md")
            if status == "blocked":
                blockers.append(address + ": " + str(self.items[address].get("feedback") or "blocked"))
            elif status not in ("existing", "MATCH", "tested") and address not in self.accepted:
                if prompt.resolve() != expected_work / "prompts" / (address + ".md"):
                    blockers.append(address + ": unsafe prepared prompt path")
                elif not prompt.is_file() or not prompt.stat().st_size:
                    blockers.append(address + ": missing nonempty prepared prompt")
                else:
                    targets.append({"address": address, "prompt": str(prompt.resolve()),
                                    "sha256": hashlib.sha256(prompt.read_bytes()).hexdigest()})
        if not targets:
            blockers.append("no unimplemented prepared targets")
        root = None
        try:
            metadata = json.loads(metadata_path.read_text())
            root = Path(metadata["root"]).resolve()
            if (metadata.get("schema") != 1 or not isinstance(metadata.get("baseline"), dict)
                    or stage.parent != (root / "build-decomp/attempts").resolve()):
                raise ValueError("Stage metadata/location mismatch")
        except (OSError, ValueError, KeyError, TypeError) as exc:
            blockers.append("saved Stage unavailable: " + str(exc))
        if not checkpoint.is_file():
            blockers.append("prepared checkpoint missing")
        source = self.source.resolve()
        result.update(status="blocked" if blockers else "ready", attempt=str(stage),
                      targets=targets, existing_addresses=[f["address"] for f in self.funcs
                                                          if self.status.get(f["address"]) == "existing"],
                      staged_implemented_addresses=[f["address"] for f in self.funcs
                                                    if f["address"] in self.accepted
                                                    or self.status.get(f["address"]) in ("MATCH", "tested")],
                      checkpoint=str(checkpoint.resolve()),
                      prepared_checkpoint_sha256=hashlib.sha256(checkpoint.read_bytes()).hexdigest()
                                                if checkpoint.is_file() else None,
                      stage_metadata_sha256=hashlib.sha256(metadata_path.read_bytes()).hexdigest()
                                            if metadata_path.is_file() else None,
                      submission={"kind": "full_tu_candidate", "source": str(source),
                                  "prepared_source_exists": source.is_file(),
                                  "prepared_source_sha256": hashlib.sha256(source.read_bytes()).hexdigest()
                                                            if source.is_file() else None,
                                  "preserve_existing_definitions": True,
                                  "fixtures_directory": str(stage / "decomp/hybrid/tests"),
                                  "cycle_spec": "worker_supplied",
                                  "headers_or_tools_changes": "prepare_new_attempt"})
        if getattr(self, "repair", None):
            result["repair"] = {key: self.repair[key] for key in
                                ("schema", "tu", "addresses", "source_sha256", "progress_sha256")}
            result["repair"]["admission_snapshot"] = str(checkpoint.resolve())
            for target in targets:
                target["kind"] = "repair_existing_unaccepted"
            result["submission"]["allowed_edits"] = "assigned bodies only; preserve all other TU text"
        if not blockers:
            result.update(cwd=str(root),
                          cycle_argv_template=[sys.executable, str(root / "tools/decomp/candidate.py"),
                                               self.tu["name"], "--attempt", str(stage),
                                               "--cycle-spec", "{cycle_spec_path}"],
                          substitutions={"cycle_spec_path": "absolute path to worker-supplied cycle spec"},
                          owner_environment="OTL_OWNER must match the assigned TU owner",
                          gate_release="separate explicit resource admission and release; not included")
        return result

    def write_result(self, prepared=False, error=None):
        atomic_json(self.work / "result.json", {
            "status": self.status, "prepared": prepared, "error": error,
            "external_handoff": self.external_handoff(prepared, error),
            "published": [], "existing": [a for a, s in self.status.items() if s == "existing"],
            "diagnostics": {a: s for a, s in self.status.items() if s in ("MATCH", "tested")},
            "rejected": {a: {"reason": item.get("feedback"), "error": item.get("error")}
                         for a, item in self.pending.items() if self.status.get(a) == "rejected"},
            "blocked": {a: self.items[a].get("feedback") for a, s in self.status.items() if s == "blocked"},
            "by_model": self.by_model,
            "artifacts": {"stage": str(ROOT), "work": str(self.work), "source": str(self.source),
                          "prompts": str(self.work / "prompts"), "checkpoint": str(self.work / "checkpoint.json")}})

    def keep_existing(self):
        """--resume: functions the TU already defines stay; only the missing ones are asked for."""
        try:
            rows = self.baseline_compare()["functions"]
        except SystemExit as error:
            raise RuntimeError("existing TU does not compile; preserved unchanged, refusing to start fresh") from error
        if getattr(self, "repair", None) and repair_snapshot(
                ROOT, self.tu["name"], self.funcs, self.db, rows) != self.repair:
            raise RuntimeError("fresh repair baseline changed during preparation")
        present = {r["address"] for r in rows if r.get("address") and r["status"] != "MISSING"}
        self.existing = self.source.read_bytes().decode("utf-8")
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
        self.allowed_headers.update(Path(p).name for p in written)
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
        changed = [f["address"] for f in self.funcs if self.status.get(f["address"]) == "MATCH"
                   and definitions.verdict(f, after, self.db)[0] != "MATCH"]
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
        return objdiff.compare_source(self.source, self.original, quiet=True, scores=False)

    def test(self, pending, diffs, round_no):
        """Generated differential tests for every DIFF candidate in one game run."""
        candidates = {a: pending[a]["code"] for a in diffs}
        # Candidates must compile together with the accepted functions.
        text = self.unit(candidates.values())
        self.source.write_text(text)
        try:
            objdiff.compare_source(self.source, self.original, quiet=True, scores=False)
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
        for m in re.finditer(r"^(?:class|struct)\s+(?:__attribute__\(\(\w+\)\)\s+)?(\w+)\s*(?::[^{;]*)?\{|^namespace\s+(\w+)", text, re.M):
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
    parser.add_argument("--resume", action="store_true", help="compatibility alias; existing definitions are always kept")
    parser.add_argument("--address", action="append", default=[], help="repeatable ELF address or symbol alias in this TU")
    parser.add_argument("--repair-address", action="append", default=[],
                        help="explicit existing unaccepted body; external prepare-only, never a model run")
    parser.add_argument("--limit", type=int, default=16, help="maximum selected definitions")
    parser.add_argument("--max-size", type=int, default=4096, help="maximum original function bytes")
    parser.add_argument("--publish", action="store_true", help="validate the final Stage and explicitly publish")
    parser.add_argument("--no-autotest", action="store_true", help="MATCH diagnostics only; keep DIFF candidates out")
    parser.add_argument("--prepare-only", action="store_true", help="snapshot headers and prompts; no model/game calls")
    parser.add_argument("--source-library", action="store_true", help="prepare immutable authentic C source artifacts, not recovered C++")
    parser.add_argument("--json", action="store_true", help="with --prepare-only: saved handoff on stdout, logs on stderr")
    parser.add_argument("--attempt", type=Path, help="resume this existing Stage; changed inputs fail closed")
    parser.add_argument("--model-timeout", type=int, default=180)
    parser.add_argument("--model-retries", type=int, default=2)
    parser.add_argument("--max-prompt-chars", type=int, default=DEFAULT_MAX_CHARS)
    parser.add_argument("--ignore-owner", action="store_true", help="work on a TU decomp/owners.json gives to "
                        "someone else than $OTL_OWNER")
    args = parser.parse_args()
    if args.source_library and (not args.prepare_only or args.publish or args.repair_address or args.attempt):
        parser.error("--source-library requires fresh --prepare-only without repair/publication")
    if args.json and not args.prepare_only:
        parser.error("--json requires --prepare-only")
    if args.repair_address and (not args.prepare_only or args.publish or args.address):
        parser.error("--repair-address requires --prepare-only without --publish or --address")
    if any(getattr(args, n) <= 0 for n in ("rounds", "switch_after", "jobs", "limit", "max_size", "model_timeout", "max_prompt_chars")) or args.model_retries < 0:
        parser.error("bounds/timeouts must be positive; retries must be nonnegative")
    if args.prepare_only and args.publish:
        parser.error("--prepare-only cannot publish")
    models = [m.strip() for m in args.models.split(",") if m.strip()]
    if not models:
        parser.error("at least one explicit model is required")
    with redirect_stdout(sys.stderr) if args.json else nullcontext():
        result_path = run_attempt(args, models)
    if args.json:
        result = json.loads(result_path.read_text())
        print(json.dumps({"result_path": str(result_path),
                          "external_handoff": result["external_handoff"]}, ensure_ascii=False))


def run_attempt(args, models):
    """Run the existing Stage pipeline; JSON output reuses its saved handoff."""
    if args.source_library:
        import source_libraries, elfimage
        source_libraries.select(ROOT, elfdb.load_db(), elfimage.load(elfdb.default_elf()),
                                args.tu, args.address, args.limit, args.max_size)
    else:
        select_functions(elfdb.load_db(), args.tu, args.repair_address or args.address, args.limit, args.max_size)
    import parallel
    owner = parallel.owned_by_others(args.tu)
    if owner and not args.ignore_owner:
        raise SystemExit(f"{args.tu} belongs to {owner} (decomp/owners.json); set OTL_OWNER or --ignore-owner")
    started = time.time()
    import publication
    locks = ROOT / "build-decomp/llm-loop-locks"
    locks.mkdir(parents=True, exist_ok=True)
    with (locks / (args.tu + ".lock")).open("a+") as lock:
        try:
            fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError:
            raise SystemExit(f"another process is working on {args.tu}")
        if args.attempt:
            metadata = json.loads((args.attempt / "stage.json").read_text())
            if Path(metadata["root"]).resolve() != ROOT.resolve():
                raise RuntimeError("attempt belongs to a different checkout")
        stage = publication.Stage.resume(args.attempt, root=ROOT) if args.attempt else publication.Stage()
        # Stage.activate redirects module paths, not Python implementations. The
        # loaded live tools must be precisely the immutable copied tools.
        if publication.tree_state(ROOT) != stage.baseline:
            raise RuntimeError("live source/header/tool inputs changed; refusing attempt reuse")
        copied = publication.tree_state(stage.path)
        if ({n: h for n, h in copied.items() if n.startswith("tools/")} !=
                {n: h for n, h in stage.baseline.items() if n.startswith("tools/")}):
            raise RuntimeError("staged tools differ from runtime snapshot")
        checkpoints = list((stage.path / "build-decomp/llm-loop").glob("*/checkpoint.json"))
        expected = stage.path / "build-decomp/llm-loop" / args.tu / "checkpoint.json"
        if args.attempt and checkpoints != [expected]:
            raise RuntimeError("attempt must contain exactly this TU checkpoint")
        print(f"isolated attempt: {stage.path}")
        with stage.activate():
            import llm_loop as engine
            if args.source_library:
                import source_libraries, elfimage
                source_db = elfdb.load_db()
                source_original = objdiff.Original(db=source_db)
                loop = source_libraries.prepare(engine.ROOT, source_db, source_original.image,
                    args, lambda f: "\n".join("%x: %s %s" % tuple(row) for row in source_original._instructions(f)))
                status = loop.status
            else:
                loop = engine.Loop(args.tu, models, args.rounds, args.switch_after, args.jobs, args.resume,
                                   addresses=args.address, limit=args.limit, max_size=args.max_size,
                                   prepare_only=args.prepare_only, no_autotest=args.no_autotest,
                                    model_timeout=args.model_timeout, model_retries=args.model_retries,
                                   attempt_resume=bool(args.attempt), max_prompt_chars=args.max_prompt_chars,
                                   repair_addresses=args.repair_address)
                status = loop.run()
        if args.publish:
            if not loop.accepted:
                raise RuntimeError("no accepted candidates to publish")
            final = publication.tree_state(stage.path)
            allowed = {"decomp/src/" + args.tu} | {"decomp/include/" + n for n in loop.allowed_headers}
            unexpected = [n for n in set(final) | set(stage.baseline)
                          if final.get(n) != stage.baseline.get(n) and n not in allowed]
            if unexpected:
                raise RuntimeError("unexpected attempt delta: " + ", ".join(sorted(unexpected)))
            stage.validate()
            published = stage.publish()
            result_path = loop.work / "result.json"
            result = json.loads(result_path.read_text())
            result["published"] = published
            atomic_json(result_path, result)
            print("published:", ", ".join(published) or "unchanged")
    from collections import Counter
    print(f"done in {(time.time() - started) / 60:.1f} min: {dict(Counter(status.values()))}")
    return loop.work / "result.json"


if __name__ == "__main__":
    main()
