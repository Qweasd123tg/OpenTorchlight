#!/usr/bin/env python3
"""Generate production code from reviewed recipes, never infer a new contract.

The supported recipes use full pinned function-body hashes and explicitly
reviewed C++ adapters, with scalar spans distinguished from whole functions.
--original re-extracts and compares the accepted operands
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
    ("CCharacter::walkingSpeed()", 0x815A20, 0xA6,
     "fb9878d3a82a9f5a207624d95eeeb831978e7515e4c4aacd491b4cac79579f5f"),
    ("CCharacter::runningSpeed()", 0x815AD0, 0xA6,
     "94ceb1acf5e12acd3d4d4f4b17d70c6ac311dc1d32f786e9608346286ace1859"),
    ("CCharacter::defense()", 0x814530, 0x85,
     "c5cbd79cfca267936ee0215e160146b364eb811cc55c577ecbf6ed4a0d8bcb65"),
    ("CCharacter::armorBonus()", 0x8145C0, 0xAE,
     "340be4b2ebbdd6968a2fd72ff637f4a4588d656574fd2ba79a6bd2a1087077f5"),
    ("CCharacter::AC()", 0x814670, 0x61,
     "7e6f5b4f859194cec8b6e704e29ff8675ba0dd1282f1509f0de8955c61865eba"),
    ("CLevelTemplateData::getNumberOfUnitsToCreate(ELEVELLAYOUT_CREATION, unsigned int)", 0x971530, 0xAF,
     "b19fc21490bbd79f68f175b61ff6a8100f53637b66476333550e07390dd11d15"),
    ("CEffectManager::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES)", 0x7EB5F0, 0x1CE,
     "46188dbdd4ffc56f77963c441438498d6739d08c10b442c585894e54b598c37c"),
    ("CCharacter::attack()", 0x82B550, 0x82E,
     "686bc58bb4461ea918e833885759e58c3589a6689d1c9749185e3b6cfa55f4f6"),
    ("CMonster::attackAI(float, CLevel&)", 0x8DFD80, 0x528,
     "a6700ea416f0300d5d7cdf868c94f108fef2aa41a75fbaa520715692d9a21046"),
    ("CMonster::updateAI(float, bool)", 0x8E3A40, 0x426,
     "db17c0e84ada03f40f8a0ef5c5e0a95c2de4939d405a8d1c20794c62ab65a46a"),
    ("CItemGold::unitInit(CDataGroup*, bool)", 0x8CA940, 0x6CE,
     "13b5e749bf1b7ef7ed895091e0a21df3191c366586f7b8c7dd90dd640ca458a9"),
    ("CCharacter::setLevel(unsigned int, bool)", 0x83EAD0, 0x1994,
     "960ca4700df525337ee6f184ba89250dc0e8ab274904e64da89bb540291fb56f"),
    ("CEquipment::buyPrice()", 0x86FC20, 0xE9,
     "bc0bdd41ee15401601541b48fa8849a380c4f51edbe6e93e0ac3a528937b64ed"),
    ("CEquipment::sellPrice()", 0x86FB40, 0xD9,
     "3c475f6abdafdb4cb05a5f35843ca60723e73aabdcf4fbd4e2d45d41842480fe"),
)
RECIPES = ["ui_binding_adapter_v1", "mwc_float_adapter_v1", "gameplay_numeric_adapter_v1"]
# Finite binary32 scalar recipes only. Full owning-body hashes guard source
# identity, and DO NOT mean that all branches of these owners are transferred.
SCALAR_SPANS = (
    (0x7EB5F0, 0x7EB7A0, 0x7EB7A6, "4476f6c973410e8ada34d3da2c889afeffba30930d34fd1ade8ed1ee6d51bfda"),
    (0x82B550, 0x82B976, 0x82B9C5, "02299d125757691c84ba91e8606a95851c8b08e9bbe58ab80af11538fe34988f"),
    (0x82B550, 0x82BCEA, 0x82BD46, "375647ab6819dd2d2e103a1570ff440bee72ba845b26afc0ab19330959f547c5"),
    (0x82B550, 0x82B9E1, 0x82B9E9, "8814f7e67c13b65fd8613d1701c13fabf82543ca07f72822e6c418539259720e"),
    (0x8DFD80, 0x8E00E6, 0x8E013D, "6624c2dd8aaa7d0e6d5924dece5d0bfb27330ad5a721ce8ceee630db82077717"),
    (0x8E3A40, 0x8E3A5B, 0x8E3A6F, "0ab42a682cf76ea1fb7c71e277af01786834f87498db043bedd948a58ba4509e"),
    (0x8CA940, 0x8CAD46, 0x8CAD5B, "0fb86d029081f0308759b77f54b993715cd42b05c10d675fb5c5a80ad8d8fc21"),
    (0x83EAD0, 0x83ECEA, 0x83ECFD, "9aa637a7d502a86db7be6307a21f2cb588a72d00f70589f62c297e308f782c35"),
)
CONSTANTS = {
    "numeric_zero": (0xFA47F8, "00000000"),
    "numeric_one": (0xFA47FC, "0000803f"),
    "numeric_hundred": (0xFA483C, "0000c842"),
    "numeric_recovery_scale": (0xFA86DC, "6f12833c"),
    "numeric_min_attack_speed": (0xFA86E8, "cdcc4c3e"),
    "numeric_ai_speed_multiplier": (0xFCE498, "0000c03f"),
    "numeric_nodes_per_area": (0xFCE4E0, "0000d040"),
}
OUTPUTS = {"ui_bindings.hpp": "ui_bindings.hpp.in", "mwc_float.hpp": "mwc_float.hpp.in",
           "gameplay_numeric.hpp": "gameplay_numeric.hpp.in"}


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
    spans = [{"owner": hex(owner), "start": hex(start), "end": hex(end),
              "body_sha256": hashlib.sha256(original.read(start, end - start)).hexdigest(),
              "scope": "finite-scalar-only"} for owner, start, end, _ in SCALAR_SPANS]
    constants = {name: {"address": hex(address), "bytes_le": original.read(address, 4).hex()}
                 for name, (address, _) in CONSTANTS.items()}
    result = {"schema": 2, "original_elf_sha256": original.sha256,
              "recipes": RECIPES, "source_functions": functions, "ui_commands": commands,
              "mwc_operands": profiles[0], "numeric_constants": constants, "scalar_spans": spans}
    result["content_sha256"] = content_hash(result)
    return result


def validate(manifest: dict) -> None:
    if (set(manifest) != {"schema", "original_elf_sha256", "recipes", "source_functions", "ui_commands", "mwc_operands", "numeric_constants", "scalar_spans", "content_sha256"}
            or manifest["schema"] != 2 or manifest["original_elf_sha256"] != SUPPORTED_SHA256
            or manifest["recipes"] != RECIPES):
        raise ValueError("Unsupported recovery recipe/schema/original build")
    payload = {key: value for key, value in manifest.items() if key != "content_sha256"}
    if manifest["content_sha256"] != content_hash(payload):
        raise ValueError("Accepted recovery snapshot content hash changed")
    expected = [{"name": name, "address": hex(address), "size": size, "body_sha256": digest}
                for name, address, size, digest in FUNCTIONS]
    if manifest["source_functions"] != expected:
        raise ValueError("Source bodies do not match reviewed recipe versions")
    constants = {name: {"address": hex(address), "bytes_le": raw}
                 for name, (address, raw) in CONSTANTS.items()}
    if manifest["numeric_constants"] != constants:
        raise ValueError("Unsupported numeric constant/address/width contract")
    spans = manifest["scalar_spans"]
    if not isinstance(spans, list) or len(spans) != len(SCALAR_SPANS):
        raise ValueError("Scalar-only source boundaries missing")
    for row, (owner, start, end, digest) in zip(spans, SCALAR_SPANS):
        if (set(row) != {"owner", "start", "end", "body_sha256", "scope"}
                or (row["owner"], row["start"], row["end"], row["scope"]) !=
                    (hex(owner), hex(start), hex(end), "finite-scalar-only")
                or row["body_sha256"] != digest):
            raise ValueError("Unsupported scalar-only boundary")
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
                    **{key: struct.unpack("<f", bytes.fromhex(row["bytes_le"]))[0].hex() + "F"
                       for key, row in manifest["numeric_constants"].items()},
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
            print(f"extracted {len(FUNCTIONS)} pinned bodies / {len(SCALAR_SPANS)} scalar boundaries / 97 UI commands: {args.extract}")
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
