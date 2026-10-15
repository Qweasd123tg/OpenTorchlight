"""Advisory shard costs and timing diagnostics, never behavioral acceptance.

The linked registration table supplies the exact order used by loader.c.
Exact profiles retain their inventory/input binding. Per-object hints can also
reuse unchanged compiled fixtures with the same shared test runtime. Costs only
reorder the complete shard permutation; missing hints use an estimate or index order.
"""
from __future__ import annotations

import hashlib
import json
import math
import os
from pathlib import Path
import re
import struct
import tempfile

import elfimage
import toolchain


def fixture_digest(root):
    """Content, not mtimes; include shared headers and the loader/test ABI."""
    root = Path(root)
    paths = sorted(p for directory in (root / "decomp/hybrid", root / "decomp/include")
                   for p in directory.rglob("*") if p.is_file()
                   and p.suffix in (".c", ".cpp", ".h", ".hpp", ".inc"))
    if not paths:
        raise ValueError("no fixture inputs")
    digest = hashlib.sha256()
    for path in paths:
        digest.update(path.relative_to(root).as_posix().encode() + b"\0")
        digest.update(hashlib.sha256(path.read_bytes()).digest())
    return digest.hexdigest()


def shared_runtime_digest(root):
    """Common test ABI/runtime; engine header effects are in each compiled .o."""
    root = Path(root)
    directory = root / "decomp/hybrid"
    paths = sorted(p for p in directory.rglob("*") if p.is_file()
                   and p.suffix in (".c", ".cpp", ".h", ".hpp", ".inc")
                   and not (p.is_relative_to(directory / "tests") and p.suffix == ".cpp"))
    if not paths:
        raise ValueError("no shared test runtime inputs")
    digest = hashlib.sha256()
    for path in paths:
        digest.update(path.relative_to(root).as_posix().encode() + b"\0")
        digest.update(hashlib.sha256(path.read_bytes()).digest())
    return digest.hexdigest()


def inventory(blob):
    """Read the ELF64 tlhybrid_test pairs; never execute the blob."""
    image = elfimage.load(blob, require_original=False)
    section = image.section(".tlhybrid.tests")
    if section.size % 16:
        raise ValueError("misaligned test registration table")
    names = [image.cstring(image.u64(section.addr + offset))
             for offset in range(0, section.size, 16)]
    if any(not name or re.search(r"\s", name) for name in names) or len(set(names)) != len(names):
        raise ValueError("invalid or duplicate registered test names")
    return names


def _unique_object(pairs):
    result = {}
    for key, value in pairs:
        if key in result:
            raise ValueError("duplicate timing profile key")
        result[key] = value
    return result


def _read_json(path):
    with Path(path).open("rb") as stream:
        data = stream.read(4 * 1024 * 1024 + 1)
    if len(data) > 4 * 1024 * 1024:
        raise ValueError("timing metadata exceeds 4 MiB")
    return json.loads(data, object_pairs_hook=_unique_object)


def _verified_inputs(blob):
    metadata = _read_json(blob.with_name("selftest-inputs.json"))
    if (not isinstance(metadata, dict) or type(metadata.get("schema")) is not int
            or metadata["schema"] not in (1, 2)
            or metadata.get("blob_sha256") != hashlib.sha256(blob.read_bytes()).hexdigest()):
        raise ValueError("stale test input sidecar")
    rows = metadata.get("test_objects")
    if not isinstance(rows, list) or not rows or len(rows) > 8192:
        raise ValueError("missing or excessive test objects")
    seen = set()
    for row in rows:
        if (not isinstance(row, list) or len(row) != 2 or not all(isinstance(x, str) for x in row)
                or not re.fullmatch(r"test_[^/\\]+\.o", row[0]) or row[0] in seen
                or not re.fullmatch(r"[0-9a-f]{64}", row[1])):
            raise ValueError("invalid test object input")
        seen.add(row[0])
        if hashlib.sha256((blob.parent / row[0]).read_bytes()).hexdigest() != row[1]:
            raise ValueError("changed test object")
    return metadata


def artifact_fingerprints(blob):
    """Prefer verified built-test objects; old builds use the complete blob hash."""
    blob = Path(blob)
    fallback = {"kind": "blob", "sha256": hashlib.sha256(blob.read_bytes()).hexdigest()}
    try:
        rows = _verified_inputs(blob)["test_objects"]
        sha = hashlib.sha256(json.dumps(rows, separators=(",", ":")).encode()).hexdigest()
        return [{"kind": "test-objects", "sha256": sha}, fallback]
    except (OSError, TypeError, ValueError, RecursionError):
        return [fallback]


def object_inventory(path):
    """Decode registration pairs from ELF relocations, never source/ordinal guesses."""
    try:
        obj = elfimage.load_object(path)
    except StopIteration as error:
        raise ValueError("object has no symbol table") from error
    sections = [section for section in obj.sections if section.name == ".tlhybrid.tests"]
    if not sections:
        return []
    if len(sections) != 1 or sections[0].size % 16:
        raise ValueError("invalid object test registration table")
    section = sections[0]
    relocs = obj.relocs.get(section.index, [])
    by_offset = {row.offset: row for row in relocs}
    if len(by_offset) != len(relocs) or set(by_offset) != set(range(0, section.size, 8)):
        raise ValueError("incomplete object test registration relocations")
    names = []
    for offset in range(0, section.size, 16):
        name, entry = by_offset[offset], by_offset[offset + 8]
        for row in (name, entry):
            if row.type != elfimage.R_X86_64_64 or not 0 < row.symbol.shndx < len(obj.sections):
                raise ValueError("unsupported object test registration relocation")
            target = obj.sections[row.symbol.shndx]
            position = row.symbol.value + row.addend
            if not 0 <= position < target.size:
                raise ValueError("object test registration target out of bounds")
        if not obj.sections[entry.symbol.shndx].flags & 4:  # SHF_EXECINSTR
            raise ValueError("test entrypoint is not executable")
        data = obj.section_bytes(name.symbol.shndx)
        position = name.symbol.value + name.addend
        end = data.index(b"\0", position, min(len(data), position + 4096))
        names.append(data[position:end].decode("latin-1"))
    if any(not name or re.search(r"\s", name) for name in names) or len(set(names)) != len(names):
        raise ValueError("invalid or duplicate object test names")
    return names


def object_inputs(blob, root, names):
    """Bind each name to a verified object and all shared compiled test helpers."""
    blob = Path(blob)
    metadata = _verified_inputs(blob)
    shared = shared_runtime_digest(root)
    if metadata["schema"] != 2 or metadata.get("shared_runtime_sha256") != shared:
        raise ValueError("missing or changed shared test runtime inputs")
    rows = [[sha, object_inventory(blob.parent / name)] for name, sha in metadata["test_objects"]]
    registered = [name for _, group in rows for name in group]
    if len(registered) != len(set(registered)) or set(registered) != set(names):
        raise ValueError("object registrations do not cover linked test inventory")
    # A registration-free object may implement helpers used by any fixture.
    shared_key = hashlib.sha256(json.dumps([shared, sorted(sha for sha, group in rows if not group)],
                                          separators=(",", ":")).encode()).hexdigest()
    return {"shared_sha256": shared_key, "objects": [row for row in rows if row[1]]}


def object_profile_path(shared, obj):
    key = hashlib.sha256((shared + ":" + obj).encode()).hexdigest()
    return toolchain.cache_dir() / "selftest-object-costs" / (key + ".json")


def _object_costs(inputs):
    costs = {}
    for sha, names in inputs["objects"]:
        try:
            profile = _read_json(object_profile_path(inputs["shared_sha256"], sha))
            if (not isinstance(profile, dict)
                    or set(profile) != {"schema", "shared_sha256", "object_sha256", "inventory", "seconds", "sha256"}
                    or type(profile["schema"]) is not int or profile["schema"] != 1
                    or profile["sha256"] != _profile_hash(profile)
                    or profile["shared_sha256"] != inputs["shared_sha256"]
                    or profile["object_sha256"] != sha or profile["inventory"] != names):
                raise ValueError("invalid object timing profile")
            values = profile["seconds"]
            if not isinstance(values, list) or len(values) != len(names) or any(
                    type(value) not in (int, float) or not math.isfinite(value) or value < 0 for value in values):
                raise ValueError("invalid object costs")
            costs.update(zip(names, values))
        except (OSError, TypeError, ValueError, OverflowError, RecursionError):
            continue
    return costs


def profile_key(names, digest, artifact):
    return hashlib.sha256(json.dumps([names, digest, artifact], ensure_ascii=True,
                                     sort_keys=True, separators=(",", ":")).encode()).hexdigest()


def profile_path(names, digest, artifact):
    return toolchain.cache_dir() / "selftest-costs" / (profile_key(names, digest, artifact) + ".json")


def _profile_hash(profile):
    payload = {key: value for key, value in profile.items() if key != "sha256"}
    return hashlib.sha256(json.dumps(payload, sort_keys=True, separators=(",", ":"),
                                     allow_nan=False).encode()).hexdigest()


def _profile(names, digest, artifact, costs):
    profile = {"schema": 1, "key": profile_key(names, digest, artifact), "inventory": names,
               "fixture_sha256": digest, "artifact": artifact, "seconds": costs}
    profile["sha256"] = _profile_hash(profile)
    return profile


def plan(blob, root, only, shards, *, timing_path=None):
    """Return a full permutation and optional exact selected inventory."""
    result = {"order": list(range(shards)), "method": "index", "reason": "no timing profile",
              "selected": None, "predicted_seconds": None}
    try:
        names = inventory(blob)
    except (OSError, TypeError, ValueError, KeyError, IndexError, struct.error) as error:
        result["reason"] = "inventory unavailable: " + str(error)
        return result
    prefixes = tuple(p for p in only.split(",") if p) if only else None
    selected = [name for name in names if prefixes is None or name.startswith(prefixes)]
    result["selected"] = selected
    result["inventory"] = names
    try:
        digest = fixture_digest(root)
        artifacts = artifact_fingerprints(blob)
        result["fixture_sha256"] = digest
        result["artifact"] = artifacts[0]
        result["profile_key"] = profile_key(names, digest, artifacts[0])
        try:
            result["object_inputs"] = object_inputs(blob, root, names)
        except (OSError, TypeError, ValueError, KeyError, IndexError, struct.error, RecursionError):
            pass  # Old or malformed sidecars retain exact-profile/blob behavior.
        if os.environ.get("OTL_SELFTEST_ORDER", "predicted") == "index":
            result["reason"] = "index order requested"
            return result
        errors = []
        for artifact in artifacts:
            path = Path(timing_path) if timing_path is not None else profile_path(names, digest, artifact)
            try:
                profile = _read_json(path)
                if not isinstance(profile, dict) or type(profile.get("schema")) is not int or profile["schema"] != 1:
                    raise ValueError("unsupported timing profile")
                if (set(profile) != {"schema", "key", "inventory", "fixture_sha256", "artifact", "seconds", "sha256"}
                        or profile["sha256"] != _profile_hash(profile)):
                    raise ValueError("corrupt timing profile checksum/schema")
                if profile.get("inventory") != names:
                    raise ValueError("changed or unknown test inventory")
                if profile.get("fixture_sha256") != digest or profile.get("artifact") != artifact:
                    raise ValueError("changed fixture/header/artifact inputs")
                if profile.get("key") != profile_key(names, digest, artifact):
                    raise ValueError("timing profile key mismatch")
                costs = profile.get("seconds")
                if not isinstance(costs, list) or len(costs) != len(names) or any(
                        type(value) not in (int, float) or not math.isfinite(value) or value < 0 for value in costs):
                    raise ValueError("invalid or incomplete test costs")
                by_name = dict(zip(names, costs))
                predicted = [sum(by_name[name] for name in selected[index::shards]) for index in range(shards)]
                if not all(math.isfinite(value) for value in predicted):
                    raise ValueError("overflow in predicted shard cost")
                result.update(order=sorted(range(shards), key=lambda index: (-predicted[index], index)),
                              method="longest-predicted-first", reason="exact inventory and fixture/artifact inputs",
                              predicted_seconds=predicted, profile_used=str(path))
                return result
            except (OSError, TypeError, ValueError, OverflowError, RecursionError) as error:
                errors.append(str(error))
        if timing_path is None and result.get("object_inputs"):
            by_name = _object_costs(result["object_inputs"])
            known = sorted(by_name[name] for name in selected if name in by_name)
            if known:
                middle = len(known) // 2
                estimate = (known[middle - 1] / 2 + known[middle] / 2
                            if len(known) % 2 == 0 else known[middle])
                predicted = [sum(by_name.get(name, estimate) for name in selected[index::shards])
                             for index in range(shards)]
                if all(math.isfinite(value) for value in predicted):
                    result.update(order=sorted(range(shards), key=lambda index: (-predicted[index], index)),
                                  method="object-predicted-first", reason="verified test objects and shared runtime; unknown costs estimated",
                                  predicted_seconds=predicted, known_costs=len(known),
                                  estimated_costs=len(selected) - len(known), estimated_test_seconds=estimate)
                    return result
        result["reason"] = "timing profile ignored: " + "; ".join(errors)
    except (OSError, TypeError, ValueError, OverflowError, RecursionError) as error:
        result["reason"] = "timing inputs unavailable: " + str(error)
    return result


def ordered_results(rows, shards):
    """Do not let duplicate/missing worker results masquerade as full coverage."""
    results = [None] * shards
    for index, result in rows:
        if type(index) is not int or not 0 <= index < shards or results[index] is not None:
            raise ValueError("invalid or duplicate selftest shard result")
        results[index] = result
    if any(result is None for result in results):
        raise ValueError("missing selftest shard result")
    return results


def validate_inventory(results, selected):
    """Extra completeness check before hybrid's unchanged exit/summary parser.

    An unreadable registration table disables prediction and leaves the legacy
    parser in charge. A readable table must match every fresh process report.
    """
    if selected is None:
        return
    begin = re.compile(r"tlhybrid: begin (\S+)")
    timing = re.compile(r"tlhybrid: timing (\S+) ([0-9]+\.[0-9]+) seconds")
    verdict = re.compile(r"tlhybrid: (\S+)\s+(PASS|FAIL) \((\d+)\)")
    summary = re.compile(r"tlhybrid: (\d+) tests, (\d+) failed")
    for index, result in enumerate(results):
        expected = selected[index::len(results)]
        lines = result.stderr.splitlines()
        starts = [m.group(1) for line in lines if (m := begin.fullmatch(line))]
        times = [m.group(1) for line in lines if (m := timing.fullmatch(line))]
        verdicts = [m.groups() for line in lines if (m := verdict.fullmatch(line))]
        summaries = [m.groups() for line in lines if (m := summary.fullmatch(line))]
        failures = sum(status == "FAIL" for _, status, _ in verdicts)
        if (starts != expected or times != expected or [name for name, _, _ in verdicts] != expected
                or summaries != [(str(len(expected)), str(failures))]
                or any((status == "FAIL") != (int(count) != 0) for _, status, count in verdicts)):
            raise ValueError(f"shard {index}/{len(results)} test inventory/report incomplete or duplicated")


def _atomic_json(path, data):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = None
    try:
        fd, temporary = tempfile.mkstemp(prefix="." + path.name + "-", dir=path.parent)
        with os.fdopen(fd, "w") as stream:
            json.dump(data, stream, indent=1, allow_nan=False)
            stream.write("\n")
        os.replace(temporary, path)
    finally:
        if temporary is not None:
            Path(temporary).unlink(missing_ok=True)


def _warning(message):
    try:
        import sys
        print(message, file=sys.stderr)
    except Exception:
        pass  # Optional diagnostics must never mask the actual build/test result.


def write_inputs(blob, objects, root=None):
    """Build-time diagnostic sidecar, without changing the manifest or receipts."""
    try:
        metadata = {"schema": 1, "blob_sha256": hashlib.sha256(Path(blob).read_bytes()).hexdigest(),
                    "test_objects": [[Path(path).name, hashlib.sha256(Path(path).read_bytes()).hexdigest()]
                                     for path in objects]}
        if root is not None:
            metadata.update(schema=2, shared_runtime_sha256=shared_runtime_digest(root))
        _atomic_json(Path(blob).with_name("selftest-inputs.json"), metadata)
    except (OSError, TypeError, ValueError) as error:
        _warning("selftest input diagnostics unavailable: " + str(error))


def save_costs(schedule, results):
    """Record only complete fresh full-suite timings; no status/receipt is saved.

    Stage and root use the same content-addressed hints across checkout paths.
    Filtered runs cannot replace full-inventory hints. Hints only change order.
    """
    if (schedule["selected"] is None or schedule["selected"] != schedule.get("inventory")
            or not schedule.get("fixture_sha256")):
        return
    validate_inventory(results, schedule["selected"])
    rows = [re.fullmatch(r"tlhybrid: timing (\S+) ([0-9]+\.[0-9]+) seconds", line)
            for result in results for line in result.stderr.splitlines()]
    costs = {match[1]: float(match[2]) for match in rows if match}
    names = schedule["inventory"]
    profile = _profile(names, schedule["fixture_sha256"], schedule["artifact"], [costs[name] for name in names])
    if any(not math.isfinite(value) for value in profile["seconds"]):
        raise ValueError("non-finite recorded test cost")
    _atomic_json(profile_path(names, profile["fixture_sha256"], profile["artifact"]), profile)
    _save_object_costs(schedule.get("object_inputs"), costs)


def _save_object_costs(inputs, costs):
    if inputs is None:
        return
    for sha, names in inputs["objects"]:
        profile = {"schema": 1, "shared_sha256": inputs["shared_sha256"], "object_sha256": sha,
                   "inventory": names, "seconds": [costs[name] for name in names]}
        profile["sha256"] = _profile_hash(profile)
        _atomic_json(object_profile_path(inputs["shared_sha256"], sha), profile)


def seed(blob, root, report_path, shards):
    """Import validated historical durations through an explicit read-only report.

    The historical report is never returned or exposed as a runtime verdict.
    Exact current names/order and fixture digest are bound to these hints only.
    """
    if type(shards) is not int or shards < 1:
        raise ValueError("seed needs a positive original shard count")
    names = inventory(blob)
    report_path = Path(report_path)
    if report_path.suffix == ".json":
        data = json.loads(report_path.read_text(), object_pairs_hook=_unique_object)
        if not isinstance(data, dict) or "report" not in data:
            raise ValueError("seed JSON requires explicit report lines")
        lines = data["report"]
    else:
        # A complete check.log can include compiler diagnostics around the one
        # loader report; all matching loader records still must be exact/unique.
        lines = report_path.read_text().splitlines()
    if not isinstance(lines, list) or any(not isinstance(line, str) for line in lines):
        raise ValueError("seed report must be a list of lines")
    # Aggregated legacy reports are returned in shard-index order. Validate this
    # exact permutation as one report, then recover costs in registration order.
    expected = [name for index in range(shards) for name in names[index::shards]]
    from types import SimpleNamespace
    result = SimpleNamespace(stderr="\n".join(lines))
    validate_inventory([result], expected)
    digest = fixture_digest(root)
    # Save using the original registration order after the strict report check.
    costs = {m[1]: float(m[2]) for line in lines
             if (m := re.fullmatch(r"tlhybrid: timing (\S+) ([0-9]+\.[0-9]+) seconds", line))}
    artifact = artifact_fingerprints(blob)[0]
    profile = _profile(names, digest, artifact, [costs[name] for name in names])
    if any(not math.isfinite(value) for value in profile["seconds"]):
        raise ValueError("non-finite seed test cost")
    target = profile_path(names, digest, artifact)
    _atomic_json(target, profile)
    try:
        inputs = object_inputs(blob, root, names)
    except (OSError, TypeError, ValueError, KeyError, IndexError, struct.error, RecursionError):
        inputs = None
    _save_object_costs(inputs, costs)
    return target


def write_timing(blob, data):
    """One replaceable diagnostic sidecar per blob, outside receipt/report format.

    Concurrent callers use atomic replacement; this is the last completed call,
    not an archive. Callers that need history should retain it with their logs.
    Failure to write diagnostics must not hide a test result or an exception.
    """
    if blob is None:
        return
    try:
        _atomic_json(Path(blob).with_name("selftest-timing.json"), data)
    except (OSError, TypeError, ValueError) as error:
        _warning("selftest timing unavailable: " + str(error))


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    command = sub.add_parser("seed", help="import timing hints only, never acceptance")
    command.add_argument("--blob", type=Path, required=True)
    command.add_argument("--root", type=Path, required=True)
    command.add_argument("--report", type=Path, required=True)
    command.add_argument("--shards", type=int, required=True)
    args = parser.parse_args()
    print(seed(args.blob, args.root, args.report, args.shards))
