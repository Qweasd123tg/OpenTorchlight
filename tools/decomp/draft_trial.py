#!/usr/bin/env python3
"""Trial build of converted Ghidra drafts for TUs nobody has written yet.

    python3 tools/decomp/draft_trial.py Achievement.cpp ...   # chosen TUs
    python3 tools/decomp/draft_trial.py --all                 # every game TU without decomp/src

For each TU the drafts of its functions (ghidra_draft.py drafts, converted by
ghidra_cpp.py) are joined into one file named like the original TU, with
the hand-written and generated headers (headers.py) of every class they
name. The file is compiled; functions on which the compiler reports errors
are dropped and the rest compiled again, until it builds. objdiff then
compares what is left with the original.

Results: build-decomp/trial/<TU>.cpp (the part that compiles) and
build-decomp/trial/summary.json (status per function). Nothing here goes
into decomp/src by itself.
"""
from __future__ import annotations

import argparse
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
import json
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
import elfdb  # noqa: E402
import ghidra_cpp  # noqa: E402
import headers  # noqa: E402
import objdiff  # noqa: E402

ROOT = elfdb.ROOT
OUT = ROOT / "build-decomp" / "trial"
DRAFTS = ROOT / "build-decomp" / "drafts"
WRITTEN = ("function", "ctor", "dtor", "static")
# -fpermissive: Ghidra's int/enum/void* mixes are warnings, not errors (code is the same).
EXTRA = ["-Dprivate=public", "-Dprotected=public", "-fpermissive", "-w",
         "-iquote", str(ROOT / "build-decomp" / "include-trial"), "-I", str(headers.OUT)]
# Names Ghidra prints without their namespace: header and using-declaration.
UNQUALIFIED = {"Vector3": ("OgreVector3.h", "Ogre::Vector3"), "Vector2": ("OgreVector2.h", "Ogre::Vector2"),
               "Quaternion": ("OgreQuaternion.h", "Ogre::Quaternion"), "SceneManager": ("OgreSceneManager.h",
               "Ogre::SceneManager"), "SceneNode": ("OgreSceneNode.h", "Ogre::SceneNode"),
               "Window": ("CEGUIWindow.h", "CEGUI::Window"), "UVector2": ("CEGUIUDim.h", "CEGUI::UVector2"),
               "UDim": ("CEGUIUDim.h", "CEGUI::UDim"), "String": ("CEGUIString.h", "CEGUI::String"),
               "length_error": ("stdexcept", "std::length_error"),
               "ColourValue": ("OgreColourValue.h", "Ogre::ColourValue"),
               "SharedPtr": ("OgreSharedPtr.h", "Ogre::SharedPtr"),
               "BoundSlot": ("CEGUIBoundSlot.h", "CEGUI::BoundSlot"), "Rect": ("CEGUIRect.h", "CEGUI::Rect"),
               "Image": ("CEGUIImage.h", "CEGUI::Image"), "Tooltip": ("CEGUITooltip.h", "CEGUI::Tooltip"),
               "locale": ("locale", "std::locale"), "_Rb_tree_node_base": ("map", "std::_Rb_tree_node_base")}
MAX_ROUNDS = 8


class Trial:
    def __init__(self):
        self.db = elfdb.load_db()
        self.original = objdiff.Original(db=self.db)
        self.methods = ghidra_cpp.known_methods(self.db)
        self.signatures = ghidra_cpp.signatures_of(self.db)
        self.enums = ghidra_cpp.parse_enums()
        gen = headers.Gen()
        self.header_of = {name: f"{name}.h" for name in gen.game_classes if (headers.OUT / f"{name}.h").exists()}
        self.header_of.update(gen.hand)

    def drafts(self, tu):
        out = []
        for f in sorted((f for f in self.db["functions"].values() if f["tu"] == tu["id"] and f["kind"] in WRITTEN
                         and not any(n.endswith("D0Ev") for n in f["names"])), key=lambda f: f["address"]):
            raw = DRAFTS / tu["name"] / "raw" / f"{f['address']}.c"
            if not raw.exists():
                continue
            try:
                code = ghidra_cpp.convert(raw.read_text(errors="replace"), self.methods, f, self.signatures,
                                          self.enums)
            except Exception:  # noqa: BLE001 - a draft is optional
                continue
            out.append((f, code))
        return out

    def includes(self, parts):
        names = set()
        for f, code in parts:
            names.update(re.findall(r"\b[A-Za-z_]\w*\b", code))
            if f.get("scope"):
                names.add(f["scope"].split("::")[0])
        files = sorted({self.header_of[n] for n in names if n in self.header_of})
        bare = sorted(n for n in names if n in UNQUALIFIED)
        return ['#include "EmptyStrings.h"', "#include <string>", "#include <vector>", '#include "TArrayList.h"',
                '#include "GenTypes.h"', '#include "GenGlobals.h"', '#include "GenNamespaces.h"'] + \
               [f"#include <{UNQUALIFIED[n][0]}>" for n in bare] + \
               [f'#include "{h}"' for h in files] + ["", "using std::wstring;", "using std::string;"] + \
               [f"using {UNQUALIFIED[n][1]};" for n in bare] + [""]

    def run(self, tu):
        parts = self.drafts(tu)
        if not parts:
            return tu["name"], {}
        work = OUT / "work" / tu["name"].replace("/", "_")
        work.mkdir(parents=True, exist_ok=True)
        source = work / tu["name"]
        head = self.includes(parts)
        dropped = {}
        for _ in range(MAX_ROUNDS):
            lines, spans = list(head), []
            for f, code in parts:
                start = len(lines) + 1
                lines += code.splitlines() + [""]
                spans.append((start, len(lines), f))
            source.write_text("\n".join(lines) + "\n")
            try:
                result = objdiff.compare_source(source, self.original, extra=EXTRA, quiet=True)
                break
            except SystemExit as error:
                found = [(int(m.group(1)), m.group(2).strip()) for m in
                         re.finditer(re.escape(source.name) + r":(\d+): error: (.*)", str(error))]
                bad = {}
                for a, b, f in spans:
                    for n, message in found:
                        if a <= n <= b:
                            bad.setdefault(f["address"], message)
                if not bad:  # errors only in headers
                    header = re.search(r"([\w.]+\.h):\d+: error: (.*)", str(error))
                    why = f"header-error {header.group(1)}: {header.group(2)}" if header else "header-error"
                    return tu["name"], dict(dropped, **{f["address"]: why for f, _ in parts})
                for address, message in bad.items():
                    dropped[address] = f"compile-error {message}"
                parts = [(f, code) for f, code in parts if f["address"] not in bad]
                if not parts:
                    return tu["name"], dropped
        else:
            return tu["name"], dict(dropped, **{f["address"]: "compile-error (rounds exhausted)" for f, _ in parts})
        statuses = dict(dropped)
        drafted = {f["address"] for f, _ in parts}
        for row in result["functions"]:
            # Only the TU's own drafted functions; inline functions of included headers also show up.
            if row.get("address") in drafted and row["status"] in ("MATCH", "DIFF"):
                statuses[row["address"]] = row["status"] if row["status"] == "MATCH" else f"DIFF {row['score']:.2f}"
        for f, _ in parts:
            statuses.setdefault(f["address"], "not-emitted")
        (OUT / tu["name"]).parent.mkdir(parents=True, exist_ok=True)
        (OUT / tu["name"]).write_text(source.read_text())
        return tu["name"], statuses


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("tus", nargs="*")
    parser.add_argument("--all", action="store_true")
    parser.add_argument("--jobs", type=int, default=3)
    args = parser.parse_args()
    trial = Trial()
    done = {p.name.lower() for p in (ROOT / "decomp" / "src").rglob("*.cpp")}
    if args.all:
        tus = [t for t in trial.db["tus"] if t["kind"] == "game" and t["name"].lower() not in done
               and (DRAFTS / t["name"] / "raw").exists()]
    else:
        tus = [t for t in trial.db["tus"] if t["name"] in args.tus]
    OUT.mkdir(parents=True, exist_ok=True)
    summary_path = OUT / "summary.json"
    summary = json.loads(summary_path.read_text()) if summary_path.exists() else {}
    with ThreadPoolExecutor(args.jobs) as pool:
        for name, statuses in pool.map(trial.run, tus):
            summary[name] = statuses
            c = Counter(s.split()[0] for s in statuses.values())
            print(f"{name:40} {dict(c)}", flush=True)
    objdiff.save_norm_cache(trial.original)
    summary_path.write_text(json.dumps(summary, indent=1))
    sizes = {a: f["size"] for a, f in trial.db["functions"].items()}
    total, by_bytes = Counter(), Counter()
    for statuses in summary.values():
        for address, status in statuses.items():
            key = status.split()[0]
            total[key] += 1
            by_bytes[key] += sizes.get(address, 0)
    print(f"\nall trials: {dict(total)}")
    print(f"bytes:      {dict(by_bytes)}")


if __name__ == "__main__":
    main()
