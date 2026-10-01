#!/usr/bin/env python3
"""Generate production code from reviewed recipes, never infer a new contract.

The two supported recipes use full pinned function-body hashes and explicitly
reviewed C++ adapters. --original re-extracts and compares the accepted operands
and table; portable builds use the content-checked accepted snapshot. No model,
network, original process launch or automatic transfer/completion promotion.
"""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import re
import struct

from automation_state import validate_output, write_json
from original import Original, SUPPORTED_SHA256
from audit_original import recover_commands

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = (
    ("CGameUI::mapToFunctions(CEGUI::Window*)", 0xA980E0, 0x374,
     "e5d99feeacf01fc1e70d24261bed0a118bbf2ce98a83f76900c635d13673740e"),
    ("UTILITIES::randomBetween(float, float)", 0xC92A70, 0x97,
     "029823ef315b58d8a9be2cc5a3fb4b0152187a73aa80dead361adcdfb4278014"),
    ("UTILITIES::randomBetweenVolatile(float, float)", 0xC92B50, 0x97,
     "a3aabbf2806b39bc69df1d47004b7bbe68ed593c70a11373e465cd2f2b57ec67"),
)
OUTPUTS = {"ui_bindings.hpp": "ui_bindings.hpp.in", "mwc_float.hpp": "mwc_float.hpp.in"}


def content_hash(value: dict) -> str:
    return hashlib.sha256(json.dumps(value, sort_keys=True, separators=(",", ":"),
                                      ensure_ascii=True).encode()).hexdigest()


def extract(original: Original) -> dict:
    functions = []
    for name, address, size, expected in FUNCTIONS:
        symbol = original.symbol(name)
        body_hash = hashlib.sha256(original.read(address, size)).hexdigest()
        if (symbol.address, symbol.size, body_hash) != (address, size, expected):
            raise ValueError(f"Unsupported full source body: {name}")
        functions.append({"name": name, "address": hex(address), "size": size, "body_sha256": body_hash})
    profiles = []
    for base in (0xC92A70, 0xC92B50):
        # Reviewed immediate locations within the complete 151-byte source body.
        profiles.append({
            "multiplier": hex(struct.unpack("<I", original.read(base + 0x26, 4))[0]),
            # 83 e0 ff is AND eax, sign-extended imm8, not an imm32 encoding.
            "low_mask": hex(struct.unpack("<b", original.read(base + 0x1F, 1))[0] & 0xFFFFFFFF),
            "shift": original.read(base + 0x1C, 1)[0],
            "fraction_mask": hex(struct.unpack("<Q", original.read(base + 0x5A, 8))[0]),
            "exponent_bits": hex(struct.unpack("<Q", original.read(base + 0x67, 8))[0]),
            "one_bits": hex(struct.unpack("<Q", original.read(0xFC8170, 8))[0]),
        })
    if profiles[0] != profiles[1]:
        raise ValueError("RNG family operands differ; shared recipe needs new review")
    commands, _ = recover_commands(original)
    result = {"schema": 1, "original_elf_sha256": original.sha256,
              "recipes": ["ui_binding_adapter_v1", "mwc_float_adapter_v1"],
              "source_functions": functions, "ui_commands": commands, "mwc_operands": profiles[0]}
    result["content_sha256"] = content_hash(result)
    return result


def validate(manifest: dict) -> None:
    if (set(manifest) != {"schema", "original_elf_sha256", "recipes", "source_functions", "ui_commands", "mwc_operands", "content_sha256"}
            or manifest["schema"] != 1 or manifest["original_elf_sha256"] != SUPPORTED_SHA256
            or manifest["recipes"] != ["ui_binding_adapter_v1", "mwc_float_adapter_v1"]):
        raise ValueError("Unsupported recovery recipe/schema/original build")
    payload = {key: value for key, value in manifest.items() if key != "content_sha256"}
    if manifest["content_sha256"] != content_hash(payload):
        raise ValueError("Accepted recovery snapshot content hash changed")
    expected = [{"name": name, "address": hex(address), "size": size, "body_sha256": digest}
                for name, address, size, digest in FUNCTIONS]
    if manifest["source_functions"] != expected:
        raise ValueError("Source bodies do not match reviewed recipe versions")
    commands = manifest["ui_commands"]
    if not isinstance(commands, list) or len(commands) != 97:
        raise ValueError("UI contract needs all 97 original commands")
    for i, row in enumerate(commands):
        if (set(row) != {"id", "name", "string_address", "initializer_call"} or row["id"] != i
                or not isinstance(row["name"], str) or not re.fullmatch(r"[A-Z0-9_]+", row["name"])
                or not re.fullmatch(r"0x[0-9a-f]+", row["string_address"])
                or not re.fullmatch(r"0x[0-9a-f]+", row["initializer_call"])):
            raise ValueError(f"Unsupported UI command record {i}")
    operands = manifest["mwc_operands"]
    # Adapter types/widths and equal/unordered dispatch were reviewed for these
    # exact operands. Changing them requires a new recipe, not a default guess.
    if operands != {"multiplier": "0x29777b41", "low_mask": "0xffffffff", "shift": 32,
                    "fraction_mask": "0xfffffffffffff", "exponent_bits": "0x3ff0000000000000",
                    "one_bits": "0x3ff0000000000000"}:
        raise ValueError("Unsupported MWC operand/width contract")


def generate(manifest: dict) -> dict[str, str]:
    validate(manifest)
    replacements = {**{key: str(value) for key, value in manifest["mwc_operands"].items()},
                    "command_names": "\n".join('    "' + row["name"] + '",' for row in manifest["ui_commands"])}
    outputs = {}
    for name, template in OUTPUTS.items():
        source = (ROOT / "tools/recovery_templates" / template).read_text(encoding="utf-8")
        for key, value in replacements.items():
            source = source.replace("@" + key + "@", value)
        if re.search(r"@[a-z_]+@", source):
            raise ValueError(f"Unresolved template field in {name}")
        outputs[name] = source
    return outputs


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", type=Path, default=ROOT / "research/recovery-contracts.json")
    parser.add_argument("--original", type=Path)
    parser.add_argument("--extract", type=Path, help="export reviewed source data to ignored build or /tmp")
    parser.add_argument("--out-dir", type=Path)
    parser.add_argument("--check", action="store_true", help="check generated files without rewriting")
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    protected = [args.manifest, *([args.original.resolve().parent] if args.original else [])]
    report_allowed = False
    try:
        if args.report:
            validate_output(ROOT, args.report, protected)
            report_allowed = True
        original = Original(args.original) if args.original else None
        if args.extract:
            if original is None or args.out_dir or args.check:
                raise ValueError("--extract needs --original and cannot generate/check outputs")
            validate_output(ROOT, args.extract, protected)
            data = extract(original)
            validate(data)
            write_json(args.extract, data)
            print(f"extracted 3 reviewed bodies / 97 UI commands: {args.extract}")
            return 0
        if args.out_dir is None:
            raise ValueError("generation/check needs --out-dir")
        validate_output(ROOT, args.out_dir, protected, directory=True)
        if args.report:
            validate_output(ROOT, args.report, protected)
        manifest = json.loads(args.manifest.read_text(encoding="utf-8"))
        validate(manifest)
        if original is not None and manifest != extract(original):
            raise ValueError("Accepted snapshot differs from pinned original extraction")
        outputs = generate(manifest)
        changed = []
        for name, content in outputs.items():
            path = args.out_dir / name
            equal = path.is_file() and path.read_text(encoding="utf-8") == content
            if not equal:
                if args.check:
                    raise ValueError(f"Generated code stale/missing: {path}")
                path.parent.mkdir(parents=True, exist_ok=True)
                # Replace only generated output; preserve mtime on exact reuse.
                import tempfile
                with tempfile.NamedTemporaryFile(mode="w", encoding="utf-8", dir=path.parent,
                                                 prefix=path.name + ".", delete=False) as stream:
                    stream.write(content)
                    temporary = Path(stream.name)
                temporary.replace(path)
                changed.append(name)
        if args.report:
            write_json(args.report, {"schema": 1, "kind": "reviewed-code-generation", "status": "PASSED",
                "input_mode": "live-original" if original else "accepted-snapshot",
                "original_elf_sha256": manifest["original_elf_sha256"], "recipes": manifest["recipes"],
                "manifest_sha256": hashlib.sha256(args.manifest.read_bytes()).hexdigest(),
                "generator_inputs": {str(path.relative_to(ROOT)): hashlib.sha256(path.read_bytes()).hexdigest()
                    for path in [Path(__file__), ROOT / "tools/original.py", ROOT / "tools/audit_original.py",
                                 *[ROOT / "tools/recovery_templates" / name for name in OUTPUTS.values()]]},
                "outputs": {name: hashlib.sha256(content.encode()).hexdigest() for name, content in outputs.items()},
                "changed_outputs": changed, "original_status_promotions": 0})
        print(f"recovered code: {len(outputs)} outputs; {len(changed)} changed; " +
              ("live original compared" if original else "accepted snapshot"))
        return 0
    except (OSError, ValueError, TypeError, KeyError) as exc:
        if report_allowed:
            write_json(args.report, {"schema": 1, "kind": "reviewed-code-generation",
                                     "status": "FAILED", "reason": str(exc), "original_status_promotions": 0})
        parser.exit(2, f"recovery generation: {exc}\n")


if __name__ == "__main__":
    raise SystemExit(main())
