#!/usr/bin/env python3
"""Backlog of port code with no caller/sink: implementation + evidence, unwired.

Pass 1: defined text symbols from the built static libs (nm), demangled to
torchlight:: names. Pass 2: inline/header-defined functions.
A symbol is SINKLESS when no file under src/ references it outside its own
definition file. Test-only use is reported separately (tested but unwired).

This is a work-list, not a gate: entry points, probes (dlopen) and
transcription data without a runtime executor are expected hits, kept in the
allowlist or marked accordingly.

Usage:
  python3 tools/audit_sinks.py --root . [--lib build-verification/libtorchlight_core.a ...]
"""
import argparse
import os
import re
import subprocess

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


def references(root, short):
    hits = set()
    for top in ("src", "include"):
        for dirpath, _dirnames, filenames in os.walk(os.path.join(root, top)):
            for fn in filenames:
                if not fn.endswith((".cpp", ".hpp", ".h")):
                    continue
                path = os.path.join(dirpath, fn)
                rel = os.path.relpath(path, root)
                try:
                    with open(path, encoding="utf-8", errors="replace") as fh:
                        text = fh.read()
                except OSError:
                    continue
                if re.search(r"(?<!\w)" + re.escape(short) + r"(?!\w)", text):
                    hits.add(rel)
    return hits


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
    hits = set()
    d = os.path.join(root, "tests")
    if not os.path.isdir(d):
        return hits
    for fn in os.listdir(d):
        if not fn.endswith((".cpp", ".py")):
            continue
        try:
            with open(os.path.join(d, fn), encoding="utf-8",
                      errors="replace") as fh:
                text = fh.read()
        except OSError:
            continue
        if re.search(r"(?<!\w)" + re.escape(short) + r"(?!\w)", text):
            hits.add("tests/" + fn)
    return hits


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
            short = full.split("::")[-1]
            if short in ENTRYPOINTS or short.startswith(PROBE_PREFIXES):
                continue
            refs = references(root, short)
            if len(refs) == 1:
                only = next(iter(refs))
                if defines(os.path.join(root, only), short):
                    refs = set()
            entries.append((full, short, refs))

    for name, defns in sorted(header_functions(root).items()):
        refs = references(root, name)
        if len(refs) == 1:
            only = next(iter(refs))
            if only in defns or defines(os.path.join(root, only), name):
                refs = set()
        entries.append(("header:" + name, name, refs))

    sinkless, wired = [], []
    for full, short, refs in entries:
        if refs:
            wired.append((full, len(refs)))
        else:
            sinkless.append((full, short))

    print("defined symbols tracked: %d; wired: %d; sinkless: %d"
          % (len(entries), len(wired), len(sinkless)))
    print("--- sinkless in src/ (tested-but-unwired marked *) ---")
    for full, short in sorted(set(sinkless)):
        tested = test_refs(root, short)
        mark = " *" if tested else ""
        extra = (" tested-by " + ",".join(sorted(tested))) if tested else ""
        print("  %s%s%s" % (full, mark, extra))


if __name__ == "__main__":
    main()
