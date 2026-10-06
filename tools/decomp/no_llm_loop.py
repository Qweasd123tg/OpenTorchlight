#!/usr/bin/env python3
"""Finite deterministic candidate queue, using the existing generators.

    python3 tools/decomp/no_llm_loop.py LogicTimerDescriptor.cpp --provider properties
    python3 tools/decomp/no_llm_loop.py --provider descriptor --limit 3

No model construction or calls. Unsupported jobs are retained with a cause.
Use --publish to validate and publish new MATCH definitions in the original TU.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import time

import candidate
import elfdb
import evidence
import ghidra_cpp
import mutate
import publication


def outline_properties(stage, tu, cls, db, methods=None):
    """Move generated static definitions to their owning TU; weak header code is not a transfer."""
    import descriptors
    header = stage.path / "decomp/include" / descriptors.header_name(cls)
    text = header.read_text()
    masked = mutate.mask(text)
    functions = [f for f in db["functions"].values() if f.get("scope") == cls
                 and f.get("tu") == tu["id"] and re.match(r"(?:Get|Set)_", f.get("method") or "")]
    source = stage.path / "decomp/src" / tu["name"]
    old = source.read_text()
    old_mask = mutate.mask(old)
    edits, bodies, seen = [], [], set()
    for f in functions:
        if methods is not None and f["method"] not in methods:
            continue
        if f["method"] in seen or mutate.definition(old, old_mask, f):
            continue
        seen.add(f["method"])
        pattern = rf"(?m)^([ \t]*)static ([^;\n]*\b{re.escape(f['method'])}\([^\n]*\))\s*\n[ \t]*\{{"
        matches = list(re.finditer(pattern, masked))
        if len(matches) != 1:
            continue
        m = matches[0]
        begin = masked.index("{", m.start())
        end = mutate.matching(masked, begin, "{", "}")
        if end < 0:
            continue
        signature = text[m.start(2):m.end(2)]
        qualifier = re.sub(rf"\b{re.escape(f['method'])}\(", f"{cls}::{f['method']}(" , signature, count=1)
        definition = qualifier + "\n" + text[begin:end + 1]
        if mutate.definition(definition, mutate.mask(definition), f) is None:
            continue
        bodies.append(definition)
        edits.append((m.start(), end + 1, m.group(1) + "static " + signature + ";"))
    for start, end, replacement in sorted(edits, reverse=True):
        text = text[:start] + replacement + text[end:]
    header.write_text(text)
    source.write_text(old.rstrip() + "\n\n" + "\n\n".join(bodies) + "\n")
    return len(bodies)


def provide(stage, tu, provider, db):
    target = stage.path / "decomp/src" / tu["name"]
    with stage.activate():
        if provider == "descriptor":
            import descriptors
            if target.exists():
                raise RuntimeError("descriptor constructor provider will not replace an existing TU")
            cls, base, header, source, complete = descriptors.Generator().generate(tu["id"])
            if not complete:
                raise RuntimeError("descriptor trace incomplete; no candidate published")
            (stage.path / "decomp/include" / descriptors.header_name(cls)).write_text(header)
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_text(source)
        elif provider == "properties":
            import properties
            if not target.exists():
                raise RuntimeError("property provider needs the descriptor's constructor TU")
            generator = properties.Generator()
            stats = generator.generate(tu["id"])
            if not stats.get("MATCH"):
                raise RuntimeError("no supported matching property operations: " + str(dict(stats)))
            funcs = [f for f in db["functions"].values() if f["tu"] == tu["id"] and f.get("scope")
                     and re.match(r"(?:Get|Set)_", f.get("method") or "")]
            if not funcs or not outline_properties(stage, tu, funcs[0]["scope"], db, generator.last_matched):
                raise RuntimeError("no new owning-TU property definitions; header-only weak code is not accepted")
        else:
            raise ValueError(provider)
    return target


def run(tus, provider, publish=False, limit=3, seconds=120):
    import parallel
    db = elfdb.load_db()
    tasks = {t["name"]: t for t in db["tus"] if t["kind"] == "game" and t["name"].endswith("Descriptor.cpp")}
    names = tus or sorted(tasks)
    missing = set(names) - set(tasks)
    if missing:
        raise ValueError("not a game descriptor TU: " + ", ".join(sorted(missing)))
    work = elfdb.ROOT / "build-decomp/no-llm"
    work.mkdir(parents=True, exist_ok=True)
    inputs = evidence.input_digest(db)
    start, results = time.monotonic(), []
    for name in names:
        if len(results) >= limit or time.monotonic() - start >= seconds:
            break
        if publish and parallel.owned_by_others(name):
            results.append({"tu": name, "status": "BLOCKED", "reason": "owned by " + parallel.owned_by_others(name)})
            continue
        key = hashlib.sha256((inputs + provider + name).encode()).hexdigest()
        cache = work / f"{key}.json"
        if cache.exists():
            row = json.loads(cache.read_text())
            if row["status"] != "MATCH":
                results.append({**row, "cached_failure": True})
                continue
        stage = publication.Stage()
        started = time.monotonic()
        try:
            target = provide(stage, tasks[name], provider, db)
            row = candidate.evaluate(name, target, publish=publish, stage=stage, incremental=True)
        except (ValueError, RuntimeError, SystemExit, OSError) as error:
            row = {"tu": name, "status": "BLOCKED", "reason": str(error), "attempt": str(stage.path), "published": False}
        row.update(provider=provider, seconds=time.monotonic() - started, inputs_digest=inputs)
        cache.write_text(json.dumps(row, indent=1, ensure_ascii=False) + "\n")
        results.append(row)
        # A successful publication changes inputs; independent remaining jobs use the new snapshot.
        if row.get("published"):
            inputs = evidence.input_digest(db)
    report = {"schema": 1, "provider": provider, "results": results,
              "budget": {"limit": limit, "seconds": seconds, "elapsed": time.monotonic() - start},
              "stop": "finite task/time budget or selected queue exhausted"}
    (work / "latest.json").write_text(json.dumps(report, indent=1, ensure_ascii=False) + "\n")
    return report


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("tus", nargs="*")
    parser.add_argument("--provider", choices=("descriptor", "properties"), required=True)
    parser.add_argument("--publish", action="store_true")
    parser.add_argument("--limit", type=int, default=3)
    parser.add_argument("--seconds", type=int, default=120)
    args = parser.parse_args()
    if args.limit <= 0 or args.seconds <= 0:
        parser.error("task/time budgets must be positive")
    print(json.dumps(run(args.tus, args.provider, args.publish, args.limit, args.seconds), indent=1, ensure_ascii=False))


if __name__ == "__main__":
    main()
