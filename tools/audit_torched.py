#!/usr/bin/env python3
"""Inventory an extracted TorchED SDK without copying any of its files.

The basic audit needs only Python and GNU binutils.  If ``dnfile`` is available,
the script also recovers the managed P/Invoke boundary from Editor.exe.  A
temporary install is enough:

    python3 -m pip install --target /tmp/torched-pydeps dnfile dncil
    PYTHONPATH=/tmp/torched-pydeps python3 tools/audit_torched.py ...
"""

from __future__ import annotations

import argparse
import collections
import hashlib
import json
import re
import subprocess
from pathlib import Path
from typing import Any


SOURCE_EXTENSIONS = (".c", ".cc", ".cpp", ".cs", ".h", ".hpp", ".lib", ".pdb")
ELEMENT_TYPES = {
    0x01: "void",
    0x02: "bool",
    0x03: "char",
    0x04: "int8",
    0x05: "uint8",
    0x06: "int16",
    0x07: "uint16",
    0x08: "int32",
    0x09: "uint32",
    0x0A: "int64",
    0x0B: "uint64",
    0x0C: "float32",
    0x0D: "float64",
    0x0E: "string",
    0x16: "typedref",
    0x18: "native int",
    0x19: "native uint",
    0x1C: "object",
}


def run(*command: str) -> str:
    result = subprocess.run(command, check=True, capture_output=True, text=True)
    return result.stdout


def digest(path: Path, algorithm: str) -> str:
    result = hashlib.new(algorithm)
    with path.open("rb") as source:
        while block := source.read(1024 * 1024):
            result.update(block)
    return result.hexdigest()


def file_record(path: Path) -> dict[str, Any]:
    return {
        "name": path.name,
        "size": path.stat().st_size,
        "sha256": digest(path, "sha256"),
        "file_type": run("file", "-b", str(path)).strip(),
    }


def native_inventory(core: Path) -> tuple[list[str], list[str]]:
    headers = run("objdump", "-p", str(core))
    exports: list[str] = []
    in_names = False
    for line in headers.splitlines():
        if "[Ordinal/Name Pointer] Table" in line:
            in_names = True
            continue
        if in_names:
            match = re.match(r"\s*\[\s*\d+\].*\s([A-Za-z_][A-Za-z0-9_]*)$", line)
            if match:
                exports.append(match.group(1))

    # MSVC RTTI type descriptors use .?AVClassName@@ for ordinary classes.
    strings = run("strings", "-a", str(core))
    classes = sorted(
        {
            match.group(1)
            for match in re.finditer(r"^\.\?AV([A-Za-z_][A-Za-z0-9_]*)@@$", strings, re.M)
        }
    )
    return exports, classes


class SignatureReader:
    def __init__(self, data: bytes):
        self.data = data
        self.position = 0

    def byte(self) -> int:
        value = self.data[self.position]
        self.position += 1
        return value

    def compressed_uint(self) -> int:
        first = self.byte()
        if first & 0x80 == 0:
            return first
        if first & 0x40 == 0:
            return ((first & 0x3F) << 8) | self.byte()
        return (
            ((first & 0x1F) << 24)
            | (self.byte() << 16)
            | (self.byte() << 8)
            | self.byte()
        )


def managed_inventory(editor: Path, exports: list[str]) -> dict[str, Any]:
    try:
        import dnfile  # type: ignore[import-not-found]
    except ImportError:
        return {
            "available": False,
            "reason": "Install the optional dnfile package to inspect .NET metadata.",
        }

    image = dnfile.dnPE(str(editor))

    def table(name: str) -> Any:
        return getattr(image.net.mdtables, name, ()) or ()

    def type_name(encoded: int) -> str:
        tag = encoded & 3
        row_id = encoded >> 2
        tables = (table("TypeDef"), table("TypeRef"), table("TypeSpec"), ())
        rows = tables[tag]
        if row_id < 1 or row_id > len(rows):
            return f"token({encoded})"
        row = rows[row_id - 1]
        if tag == 2:
            return "typespec"
        namespace = str(row.TypeNamespace)
        name = str(row.TypeName)
        return f"{namespace}.{name}" if namespace else name

    def signature_type(reader: SignatureReader) -> str:
        element = reader.byte()
        if element in ELEMENT_TYPES:
            return ELEMENT_TYPES[element]
        if element == 0x0F:
            return f"{signature_type(reader)}*"
        if element == 0x10:
            return f"ref {signature_type(reader)}"
        if element in (0x11, 0x12):
            return type_name(reader.compressed_uint())
        if element == 0x13:
            return f"!{reader.compressed_uint()}"
        if element == 0x1D:
            return f"{signature_type(reader)}[]"
        if element == 0x1E:
            return f"!!{reader.compressed_uint()}"
        if element in (0x1F, 0x20):
            modifier = type_name(reader.compressed_uint())
            kind = "modreq" if element == 0x1F else "modopt"
            return f"{kind}({modifier}) {signature_type(reader)}"
        if element == 0x41:
            return f"sentinel {signature_type(reader)}"
        if element == 0x45:
            return f"pinned {signature_type(reader)}"
        if element == 0x15:
            base = signature_type(reader)
            count = reader.compressed_uint()
            arguments = ", ".join(signature_type(reader) for _ in range(count))
            return f"{base}<{arguments}>"
        if element == 0x14:
            base = signature_type(reader)
            rank = reader.compressed_uint()
            sizes = reader.compressed_uint()
            for _ in range(sizes):
                reader.compressed_uint()
            lower_bounds = reader.compressed_uint()
            for _ in range(lower_bounds):
                reader.compressed_uint()
            return f"{base}[rank={rank}]"
        raise ValueError(f"unsupported signature element 0x{element:02x}")

    def decode_signature(data: bytes) -> tuple[str, list[str]]:
        reader = SignatureReader(data)
        calling_convention = reader.byte()
        if calling_convention & 0x10:
            reader.compressed_uint()
        parameter_count = reader.compressed_uint()
        returns = signature_type(reader)
        parameters = [signature_type(reader) for _ in range(parameter_count)]
        if reader.position != len(reader.data):
            raise ValueError("unconsumed signature bytes")
        return returns, parameters

    owners = {
        id(method.row): f"{definition.TypeNamespace}.{definition.TypeName}".strip(".")
        for definition in table("TypeDef")
        for method in definition.MethodList
    }
    import_rows = []
    core_import_by_method_id: dict[int, str] = {}
    dll_counts: collections.Counter[str] = collections.Counter()
    for mapping in table("ImplMap"):
        dll = str(mapping.ImportScope.row.Name).lower()
        dll_counts[dll] += 1
        if dll != "core.dll":
            continue
        method = mapping.MemberForwarded.row
        returns, parameter_types = decode_signature(bytes(method.Signature.value))
        parameter_names = {
            parameter.row.Sequence: str(parameter.row.Name)
            for parameter in method.ParamList
            if parameter.row.Sequence > 0
        }
        parameters = [
            {
                "name": parameter_names.get(index, f"arg{index}"),
                "type": parameter_type,
            }
            for index, parameter_type in enumerate(parameter_types, 1)
        ]
        native_name = str(mapping.ImportName)
        core_import_by_method_id[id(method)] = native_name
        prototype = ", ".join(f"{p['type']} {p['name']}" for p in parameters)
        import_rows.append(
            {
                "managed_owner": owners.get(id(method), ""),
                "managed_name": str(method.Name),
                "native_name": native_name,
                "return_type": returns,
                "parameters": parameters,
                "prototype": f"{returns} {native_name}({prototype})",
            }
        )

    import_names = [row["native_name"] for row in import_rows]
    duplicates = {
        name: count
        for name, count in sorted(collections.Counter(import_names).items())
        if count > 1
    }
    unique_imports = set(import_names)
    export_set = set(exports)
    result = {
        "available": True,
        "type_references": len(table("TypeRef")),
        "type_definitions": len(table("TypeDef")),
        "method_definitions": len(table("MethodDef")),
        "pinvoke_rows": len(table("ImplMap")),
        "pinvoke_rows_by_library": dict(sorted(dll_counts.items())),
        "core_pinvoke_rows": len(import_rows),
        "core_unique_imports": len(unique_imports),
        "duplicate_core_imports": duplicates,
        "imports_without_native_export": sorted(unique_imports - export_set),
        "exports_without_managed_import": sorted(export_set - unique_imports),
        "core_imports": import_rows,
    }

    try:
        from dncil.cil.body import CilMethodBody  # type: ignore[import-not-found]
        from dncil.cil.body.reader import (  # type: ignore[import-not-found]
            CilMethodBodyReaderBytes,
        )
        from dncil.clr.token import Token  # type: ignore[import-not-found]
    except ImportError:
        result["il_call_map"] = {
            "available": False,
            "reason": "Install the optional dncil package to inspect method bodies.",
        }
        return result

    method_rows = list(table("MethodDef"))
    method_by_token = {
        0x06000000 | row_id: method for row_id, method in enumerate(method_rows, 1)
    }
    pinvoke_by_token = {
        token: core_import_by_method_id[id(method)]
        for token, method in method_by_token.items()
        if id(method) in core_import_by_method_id
    }
    call_sites = []
    body_errors = []
    bodies_scanned = 0
    for method in method_rows:
        if not method.Rva:
            continue
        managed_name = f"{owners.get(id(method), '')}.{method.Name}".lstrip(".")
        try:
            body = CilMethodBody(CilMethodBodyReaderBytes(image.get_data(method.Rva)))
        except Exception as error:  # malformed IL should stay visible in the audit
            body_errors.append({"method": managed_name, "error": str(error)})
            continue
        bodies_scanned += 1
        for instruction in body.instructions:
            if instruction.mnemonic not in ("call", "callvirt"):
                continue
            operand = instruction.operand
            if not isinstance(operand, Token) or operand.value not in pinvoke_by_token:
                continue
            call_sites.append(
                {
                    "native_name": pinvoke_by_token[operand.value],
                    "caller": managed_name,
                    "il_offset": instruction.offset,
                }
            )

    called_imports = {site["native_name"] for site in call_sites}
    result["il_call_map"] = {
        "available": True,
        "method_bodies_scanned": bodies_scanned,
        "method_body_errors": body_errors,
        "direct_core_call_count": len(call_sites),
        "core_imports_with_direct_callers": len(called_imports),
        "core_imports_without_direct_callers": sorted(unique_imports - called_imports),
        "call_sites": sorted(
            call_sites,
            key=lambda site: (site["native_name"], site["caller"], site["il_offset"]),
        ),
    }
    return result


def linux_overlap(original: Path, classes: list[str], engine_classes: list[str]) -> dict[str, Any]:
    symbols = run("nm", "-C", "--defined-only", str(original))
    matched = [
        name
        for name in classes
        if re.search(
            rf"(?<![A-Za-z0-9_]){re.escape(name)}(?=::|[<,( ]|$)", symbols, re.M
        )
    ]
    matched_engine = [name for name in engine_classes if name in matched]
    return {
        "binary": file_record(original),
        "torched_rtti_classes_found": len(matched),
        "torched_rtti_classes_missing": sorted(set(classes) - set(matched)),
        "torched_engine_classes_found": len(matched_engine),
        "torched_engine_classes_missing": sorted(set(engine_classes) - set(matched_engine)),
    }


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--sdk-dir", required=True, type=Path)
    parser.add_argument("--installer", type=Path)
    parser.add_argument("--original", type=Path, help="optional symbol-rich Linux binary")
    parser.add_argument("--output", type=Path, help="write JSON here instead of stdout")
    args = parser.parse_args()

    root = args.sdk_dir.resolve()
    editor = root / "Editor.exe"
    core = root / "Core.dll"
    for required in (editor, core):
        if not required.is_file():
            parser.error(f"missing required SDK file: {required}")

    files = sorted(path for path in root.rglob("*") if path.is_file())
    directories = sum(1 for path in root.rglob("*") if path.is_dir())
    extension_counts = collections.Counter(
        path.suffix.lower().removeprefix(".") or "<none>" for path in files
    )
    source_counts = {
        suffix: sum(path.suffix.lower() == suffix for path in files)
        for suffix in SOURCE_EXTENSIONS
    }
    exports, classes = native_inventory(core)
    engine_classes = [name for name in classes if name.startswith("C")]

    strings = run("strings", "-a", str(editor))
    pdb_paths = sorted(set(re.findall(r"[^\r\n\x00]*\.pdb", strings, re.I)))

    report: dict[str, Any] = {
        "format_version": 1,
        "sdk": {
            "file_count": len(files),
            "directory_count_excluding_root": directories,
            "total_bytes": sum(path.stat().st_size for path in files),
            "extension_counts": dict(
                sorted(extension_counts.items(), key=lambda item: (-item[1], item[0]))
            ),
            "source_file_counts": source_counts,
            "documentation_pdfs": [
                str(path.relative_to(root)) for path in files if path.suffix.lower() == ".pdf"
            ],
        },
        "editor": {**file_record(editor), "pdb_paths_in_debug_data": pdb_paths},
        "core": {
            **file_record(core),
            "export_count": len(exports),
            "exports": exports,
            "msvc_rtti_class_count": len(classes),
            "msvc_rtti_classes": classes,
            "engine_class_count": len(engine_classes),
            "engine_classes": engine_classes,
        },
        "managed_metadata": managed_inventory(editor, exports),
    }
    if args.installer:
        installer = args.installer.resolve()
        report["installer"] = {
            **file_record(installer),
            "md5": digest(installer, "md5"),
        }
    if args.original:
        report["linux_original_comparison"] = linux_overlap(
            args.original.resolve(), classes, engine_classes
        )

    payload = json.dumps(report, ensure_ascii=False, indent=2) + "\n"
    if args.output:
        args.output.write_text(payload, encoding="utf-8")
    else:
        print(payload, end="")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
