#!/usr/bin/env python3
"""Lexical candidates for caller/sink review, NOT proof of wiring or its absence.

Pass 1: defined text symbols from the built static libs (nm), demangled to
torchlight:: names. Pass 2: inline/header-defined functions.
Read each source file once. Header declarations never count as production
consumers. Same-file callers, overloads, comments and indirect dispatch require
manual review; the tool does not mark functions wired/unwired.

This is a work-list, not a gate: entry points, probes (dlopen) and
transcription data without a runtime executor are expected hits, kept in the
allowlist or marked accordingly.

Usage:
  python3 tools/audit_sinks.py --root . --symbol panel_profile [--lib build-verification/libtorchlight_core.a]
"""
import argparse
import os
import re
import subprocess
from pathlib import Path
from functools import lru_cache

SKIP_NAMESPACES = ("std::", "__gnu_cxx::", "__detail::")
ENTRYPOINTS = ("main",)
PROBE_PREFIXES = ("render_",)
HEADER_BODY_RE = re.compile(
    r"(?<![\w:>.~-])([a-z_]\w*)\s*\([{{}};]*\)\s*(?:const\s*)?(?:noexcept\s*)?(?:override\s*)?\{"
)
KEYWORDS = {"if", "for", "while", "switch", "catch", "return", "sizeof",
            "decltype", "noexcept", "static_assert", "operator"}


def nm_symbols(lib):
    out = subprocess.run(["nm", "--defined-only", lib], capture_output=True,
                         text=True, check=True).stdout
    addrs = {}
    for line in out.split("\n"):
        parts = line.split()
        if len(parts) == 3 and parts[1] == "T":
            addrs[parts[2]] = parts[0]
    names = subprocess.run(["c++filt"], input="\n".join(addrs),
                           capture_output=True, text=True, check=True).stdout.split("\n")
    result = []
    for mangled, demangled in zip(addrs, names):
        base = re.sub(r"\[abi:[^\]]*\]", "", demangled).split("(")[0]
        if not base.startswith("torchlight::"):
            continue
        if (mangled.startswith("_GLOBAL") or ".cold" in demangled or
                " vtable for " in demangled or " typeinfo " in demangled):
            continue
        parts = base.split("::")
        short = parts[-1]
        # constructors/destructors: called at construction sites under many
        # spellings; they are noise in a caller audit.
        if len(parts) >= 2 and (short == parts[-2] or short == "~" + parts[-2]):
            continue
        result.append((mangled, base))
    return result


def lib_sources(lib):
    out = subprocess.run(["ar", "t", lib], capture_output=True,
                         text=True, check=True).stdout
    mapping = {}
    for member in out.split():
        if member.endswith(".cpp.o"):
            mapping[member] = "src/" + member[:-len(".cpp.o")] + ".cpp"
    return mapping


@lru_cache(maxsize=4)
def reference_index(root):
    """One process-local snapshot; no mtime cache or semantic claims."""
    result = {"src": {}, "include": {}, "tests": {}}
    for top in result:
        for path in sorted((Path(root) / top).rglob("*")):
            if not path.is_file() or path.suffix not in {".cpp", ".hpp", ".h", ".py"}:
                continue
            text = path.read_text(encoding="utf-8", errors="replace")
            relative = str(path.relative_to(root))
            for token in set(re.findall(r"[A-Za-z_]\w*", text)):
                result[top].setdefault(token, set()).add(relative)
    return result


def references(root, short):
    return set(reference_index(root)["src"].get(short, ()))


def defines(path, short):
    try:
        with open(path, encoding="utf-8", errors="replace") as fh:
            text = fh.read()
    except OSError:
        return False
    return bool(re.search(
        r"(?m)(?:^|[{;}\s])(?:[\w:]+::)?" + re.escape(short) +
        r"\s*\([{};]*\)\s*(?:const\s*)?(?:noexcept\s*)?(?:override\s*)?[{;]",
        text))


def test_refs(root, short):
    return set(reference_index(root)["tests"].get(short, ()))


def header_functions(root):
    found = {}
    inc = os.path.join(root, "include", "torchlight")
    if not os.path.isdir(inc):
        return found
    for fn in os.listdir(inc):
        if not fn.endswith(".hpp"):
            continue
        with open(os.path.join(inc, fn), encoding="utf-8",
                  errors="replace") as fh:
            text = fh.read()
        for m in HEADER_BODY_RE.finditer(text):
            name = m.group(1)
            if name in KEYWORDS:
                continue
            found.setdefault(name, set()).add("include/torchlight/" + fn)
    return found


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", default=".")
    ap.add_argument("--lib", action="append", default=[])
    ap.add_argument("--symbol", default="", help="limit review to a name substring")
    args = ap.parse_args()
    root = args.root
    libs = args.lib or [os.path.join(root, "build-verification",
                                     "libtorchlight_core.a"),
                        os.path.join(root, "build-verification",
                                     "libtorchlight_application.a")]

    entries = []
    for lib in libs:
        if not os.path.exists(lib):
            print("skip missing lib %s" % lib)
            continue
        for mangled, full in nm_symbols(lib):
            if args.symbol and args.symbol not in full:
                continue
            short = full.split("::")[-1]
            if short in ENTRYPOINTS or short.startswith(PROBE_PREFIXES):
                continue
            refs = references(root, short)
            entries.append((full, short, refs))

    for name, defns in sorted(header_functions(root).items()):
        if args.symbol and args.symbol not in name:
            continue
        refs = references(root, name)
        entries.append(("header:" + name, name, refs))

    candidates, multiple_files = [], []
    for full, short, refs in entries:
        if len(refs) > 1:
            multiple_files.append((full, len(refs)))
        else:
            candidates.append((full, short, tuple(sorted(refs))))

    print("lexical symbols: %d; multiple src files: %d; zero/single-file candidates: %d"
          % (len(entries), len(multiple_files), len(candidates)))
    print("Not a wiring gate: same-file calls, overloads, comments and indirect consumers require review.")
    for full, short, refs in sorted(set(candidates)):
        tested = test_refs(root, short)
        mark = " *" if tested else ""
        extra = (" tested-by " + ",".join(sorted(tested))) if tested else ""
        print("  %s%s src=%s%s" % (full, mark, ",".join(refs) or "none", extra))


if __name__ == "__main__":
    main()
