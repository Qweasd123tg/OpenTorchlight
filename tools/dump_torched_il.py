#!/usr/bin/env python3
"""Print resolved CIL for selected methods from TorchED's Editor.exe.

Requires the optional analysis packages only in a temporary location:

    python3 -m pip install --target /tmp/torched-pydeps dnfile dncil
    PYTHONPATH=/tmp/torched-pydeps python3 tools/dump_torched_il.py ...
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path
from typing import Any

try:
    import dnfile  # type: ignore[import-not-found]
    from dncil.cil.body import CilMethodBody  # type: ignore[import-not-found]
    from dncil.cil.body.reader import CilMethodBodyReaderBytes  # type: ignore[import-not-found]
    from dncil.clr.token import Token  # type: ignore[import-not-found]
except ImportError as error:
    raise SystemExit("dnfile and dncil are required; see this script's docstring") from error


def type_row_name(row: Any) -> str:
    namespace = str(getattr(row, "TypeNamespace", ""))
    name = str(getattr(row, "TypeName", ""))
    if name:
        return f"{namespace}.{name}" if namespace else name
    return str(getattr(row, "Name", type(row).__name__))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--editor", required=True, type=Path)
    parser.add_argument(
        "--method",
        required=True,
        help="regular expression matched against Namespace.Type.Method",
    )
    args = parser.parse_args()

    image = dnfile.dnPE(str(args.editor))
    tables = image.net.mdtables
    def rows(name: str) -> list[Any]:
        return list(getattr(tables, name, ()) or ())

    type_definitions = rows("TypeDef")
    methods = rows("MethodDef")
    fields = rows("Field")
    member_refs = rows("MemberRef")
    method_specs = rows("MethodSpec")

    method_owner = {
        id(method.row): type_row_name(definition)
        for definition in type_definitions
        for method in definition.MethodList
    }
    field_owner = {
        id(field.row): type_row_name(definition)
        for definition in type_definitions
        for field in definition.FieldList
    }
    core_import = {
        id(mapping.MemberForwarded.row): (
            str(mapping.ImportScope.row.Name),
            str(mapping.ImportName),
        )
        for mapping in rows("ImplMap")
    }

    def method_name(row: Any) -> str:
        result = f"{method_owner.get(id(row), '?')}.{row.Name}"
        if id(row) in core_import:
            library, native = core_import[id(row)]
            result += f" [{library}!{native}]"
        return result

    def member_ref_name(row: Any) -> str:
        parent = getattr(row.Class, "row", None)
        if parent is None:
            owner = "?"
        elif hasattr(parent, "TypeName"):
            owner = type_row_name(parent)
        elif hasattr(parent, "Name"):
            owner = method_name(parent) if id(parent) in method_owner else str(parent.Name)
        else:
            owner = type(parent).__name__
        return f"{owner}.{row.Name}"

    def resolve_token(token: Token) -> str:
        row_id = token.rid
        if token.table == 0x70:
            value = image.net.user_strings.get(row_id)
            return repr(value.value if value is not None else "<invalid user string>")
        table_rows: dict[int, list[Any]] = {
            0x01: rows("TypeRef"),
            0x02: type_definitions,
            0x04: fields,
            0x06: methods,
            0x0A: member_refs,
            0x1B: rows("TypeSpec"),
            0x2B: method_specs,
        }
        selected_rows = table_rows.get(token.table)
        if selected_rows is None or row_id < 1 or row_id > len(selected_rows):
            return str(token)
        row = selected_rows[row_id - 1]
        if token.table in (0x01, 0x02):
            return type_row_name(row)
        if token.table == 0x04:
            return f"{field_owner.get(id(row), '?')}.{row.Name}"
        if token.table == 0x06:
            return method_name(row)
        if token.table == 0x0A:
            return member_ref_name(row)
        if token.table == 0x2B:
            target = getattr(row.Method, "row", None)
            if target is None:
                return str(token)
            if id(target) in method_owner:
                return method_name(target)
            return member_ref_name(target)
        return str(token)

    pattern = re.compile(args.method, re.I)
    matches = []
    for row_id, method in enumerate(methods, 1):
        full_name = method_name(method)
        if method.Rva and pattern.search(full_name):
            matches.append((row_id, method, full_name))

    if not matches:
        parser.error(f"no method matched {args.method!r}")

    for match_index, (row_id, method, full_name) in enumerate(matches):
        if match_index:
            print()
        print(f"# {full_name} token=0x{0x06000000 | row_id:08x} rva=0x{method.Rva:x}")
        body = CilMethodBody(CilMethodBodyReaderBytes(image.get_data(method.Rva)))
        for instruction in body.instructions:
            operand = instruction.operand
            rendered = (
                resolve_token(operand)
                if isinstance(operand, Token)
                else "" if operand is None else str(operand)
            )
            print(f"IL_{instruction.offset:04x}: {instruction.mnemonic:<14} {rendered}".rstrip())
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
