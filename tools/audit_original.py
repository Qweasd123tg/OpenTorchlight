#!/usr/bin/env python3
"""Recover UI command identifiers and input evidence from the supported build."""

import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
import struct
import xml.etree.ElementTree as ET
import zipfile

from original import Original, direct_transfers, instructions


INPUT_FUNCTIONS = [
    "CGame::begin(void*)",
    "CGame::frameEnded(Ogre::FrameEvent const&)",
    "SDLEventHandler::ProcessEvent(SDL_Event const&)",
    "CGameClient::keyEvent(unsigned int, unsigned int, long)",
    "CGameClient::mouseEvent(unsigned int, unsigned int)",
    "CGameClient::processInput(void*, float, bool)",
    "CGameClient::processMenuInput(void*, float, bool)",
    "CGameClient::processIngameInput(void*, float, bool)",
    "CGameClient::clickLeft()",
    "CGameClient::clickRight(long long, bool, bool)",
    "CGameClient::moveToMouse(bool)",
    "CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)",
    "CCharacter::setTarget(CCharacter*)",
    "CCharacter::setTargetItem(CItem*)",
    "CCharacter::attack()",
    "CGameUI::processInput(CGameClient*, void*, float, bool)",
    "CGameUI::processIngameInput(void*, float, bool)",
    "CGameUI::handleKeyPresses()",
    "CGameUI::keyEvent(unsigned int, unsigned int, long)",
    "CGameUI::mouseEvent(unsigned int, unsigned int)",
    "CGameUI::handle_onClick(CEGUI::EventArgs const&)",
    "CGameUI::mapToFunctions(CEGUI::Window*)",
    "CGameUI::onClick(ELayoutFunction)",
    "UpdateCursorPos(long, long)", "GetCursorPos(POINT*)", "SetCursorPos(int, int)",
    "UpdateKeyState(unsigned int, bool)", "GetAsyncKeyState(unsigned int)",
    "GetKeyState(unsigned int)", "ClearKeyState()",
    "CKeyManager::keyPressed(unsigned int)", "CKeyManager::keyHeld(unsigned int)",
    "CKeyManager::keyReleased(unsigned int)", "CKeyManager::capture()",
    "CKeyManager::flush()", "CKeyManager::flushAll()",
    "CKeyManager::keyEvent(unsigned int, unsigned int)",
    "CMouseManager::mouseEvent(unsigned int, unsigned int)",
    "CMouseManager::buttonHeld(EMouseButton)", "CMouseManager::buttonPressed(EMouseButton)",
    "CMouseManager::buttonDoubleClick(EMouseButton)", "CMouseManager::capture()",
    "CMouseManager::flush()", "CMouseManager::flushAll()", "CMouseManager::update(void*)",
    "CMouseManager::virtualMousePosition(float, float, float, float)",
]


def recover_commands(original):
    # This static array has a separate copy in many translation units.
    table = original.symbol("KLayoutFunctionNames", address=0x14B7DC0)
    count = table.size // 8
    # Confirmed constructor sequence for the fingerprint-checked executable.
    listing = original.disassemble(0xA850BD, 0xB43)
    source = destination = None
    commands = {}
    for address, op, operands in instructions(listing):
        match = re.fullmatch(r"\$0x([0-9a-f]+),%(esi|edi)", operands)
        if op == "mov" and match:
            if match[2] == "esi":
                source = int(match[1], 16)
            else:
                destination = int(match[1], 16)
        if op == "call":
            if source is not None and destination is not None and (
                table.address <= destination < table.address + table.size
            ):
                if "basic_string(char const*" not in operands:
                    raise ValueError("Unexpected command table initializer")
                index, remainder = divmod(destination - table.address, 8)
                if remainder or index in commands:
                    raise ValueError("Invalid or duplicate command table entry")
                commands[index] = {
                    "id": index, "name": original.string(source),
                    "string_address": hex(source), "initializer_call": hex(address),
                }
            source = destination = None
    if set(commands) != set(range(count)):
        raise ValueError(f"Incomplete command table: {len(commands)}/{count}")
    return [commands[i] for i in range(count)], listing


def core_dispatch(original, disassembly):
    """List calls reachable from each main HUD case, without entering callees.

    This covers CGameUI only. Context menus have their own onClick overrides.
    Conditional branches are both explored; the result is not an execution trace.
    """
    parsed = instructions(disassembly)
    code = {address: (op, operands) for address, op, operands in parsed}
    next_address = {a[0]: b[0] for a, b in zip(parsed, parsed[1:])}
    entries = struct.unpack("<85Q", original.read(0xFE4370, 85 * 8))
    result = {}
    for index, entry in enumerate(entries, 11):
        pending = [entry]
        visited, calls, unresolved = set(), {}, set()
        while pending:
            address = pending.pop()
            if address in visited:
                continue
            visited.add(address)
            if address not in code:
                unresolved.add(hex(address))
                continue
            op, operands = code[address]
            target = re.match(r"([0-9a-f]+) <(.+)>", operands)
            fallthrough = next_address.get(address)
            if op.startswith("ret"):
                continue
            if op in {"call", "callq"}:
                if target:
                    calls[address] = {"instruction": hex(address), "symbol": target[2]}
                else:
                    unresolved.add(f"{address:#x}: {op} {operands}")
            elif op.startswith("j"):
                if target:
                    pending.append(int(target[1], 16))
                else:
                    unresolved.add(f"{address:#x}: {op} {operands}")
                if op in {"jmp", "jmpq"}:
                    continue
            if fallthrough is not None:
                pending.append(fallthrough)
        result[index] = {"entry": hex(entry), "calls": list(calls.values()),
                         "unresolved": sorted(unresolved)}
    return result


def read_layouts(archive, commands):
    by_name = {command["name"]: command for command in commands}
    layouts, bindings = [], []
    with zipfile.ZipFile(archive) as zipped:
        for path in sorted(zipped.namelist()):
            if not path.lower().startswith("media/ui/") or not path.lower().endswith(".layout"):
                continue
            raw = zipped.read(path)
            root = ET.fromstring(raw)  # Fail on malformed layouts; never silently omit controls.
            windows = list(root.iter("Window"))
            layouts.append({"path": path, "windows": len(windows),
                            "sha256": hashlib.sha256(raw).hexdigest()})
            for window in windows:
                declarations = [(p.get("Name"), p.get("Value")) for p in window.findall("Property")]
                properties = dict(declarations)
                for ordinal, (key, value) in enumerate(declarations):
                    if key and key.lower().startswith("on") and value:
                        command = by_name.get(value.upper())
                        bindings.append({
                            "layout": path, "window": window.get("Name"),
                            "widget": window.get("Type"), "event": key, "callback": value,
                            "command_id": command["id"] if command else None,
                            "property_ordinal": ordinal,
                            "superseded_by_later_declaration": any(k == key for k, _ in declarations[ordinal + 1:]),
                            "position": properties.get("UnifiedPosition"),
                            "size": properties.get("UnifiedSize"),
                            "declared_visible": properties.get("Visible"),
                            "verification": "static binding; runtime behavior pending",
                        })
    return layouts, bindings


def markdown(report):
    counts = report["counts"]
    lines = [
        "# Карта команд оригинальной Torchlight", "",
        f"SHA-256 бинарника: `{report['binary_sha256']}`.", "",
        f"Проверено {counts['layouts']} XML-окон, {counts['widgets']} элементов Window, "
        f"{counts['bindings']} привязок событий. "
        f"Из них {counts['superseded_bindings']} перекрыты повторным свойством в том же элементе. "
        f"Из таблицы бинарника извлечено {counts['commands']} идентификаторов команд, "
        f"в XML встречается {counts['used_commands']} различных команд.", "",
        "Идентификаторы восстановлены из инициализации KLayoutFunctionNames. "
        "Вызовы ниже получены анализом ветвей CGameUI::onClick; "
        "это возможные вызовы, а не подтверждённая трасса выполнения. "
        "Специализированные меню переопределяют onClick. "
        "Динамически создаваемые слоты, клавиатурные команды и жесты эта таблица не исчерпывает.", "",
        "| ID | Команда | Привязок XML | Вызовы основного HUD |",
        "| --- | --- | ---: | --- |",
    ]
    usage = Counter(b["command_id"] for b in report["bindings"] if not b["superseded_by_later_declaration"])
    for command in report["commands"]:
        calls = command.get("core_dispatch", {}).get("calls", [])
        game_calls = sorted({c["symbol"] for c in calls if c["symbol"].startswith(("CGameUI::", "CCharacter::", "CPlayer::"))})
        detail = "; ".join(f"`{name}`" for name in game_calls) or "Контекстный обработчик / см. JSON"
        lines.append(f"| {command['id']} | `{command['name']}` | {usage[command['id']]} | {detail} |")
    lines += ["", "## Все привязки интерфейса", "",
              "Проверка сенсорного управления для каждой строки пока ожидается.", "",
              "| Файл | Элемент | Событие | Команда | ID | Объявление |",
              "| --- | --- | --- | --- | ---: | --- |"]
    for binding in report["bindings"]:
        state = "Перекрыто следующим свойством" if binding["superseded_by_later_declaration"] else "Последнее свойство"
        lines.append(f"| `{Path(binding['layout']).name}` | `{binding['window']}` | "
                     f"{binding['event']} | `{binding['callback']}` | {binding['command_id']} | {state} |")
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--game-dir", type=Path, required=True)
    parser.add_argument("--output", type=Path, default=Path("research"))
    args = parser.parse_args()
    original = Original(args.game_dir / "Torchlight.bin.x86_64")
    commands, initialization = recover_commands(original)
    listings = {name: original.function(name) for name in INPUT_FUNCTIONS}
    dispatch = core_dispatch(original, listings["CGameUI::onClick(ELayoutFunction)"])
    for command in commands:
        if command["id"] in dispatch:
            command["core_dispatch"] = dispatch[command["id"]]
    layouts, bindings = read_layouts(args.game_dir / "pak.zip", commands)
    unknown = [b for b in bindings if b["command_id"] is None]
    if unknown:
        raise ValueError(f"Unresolved XML command names: {unknown}")
    functions = [s for s in original.symbols if s.kind in "TtWw"]
    report = {
        "schema_version": 1, "binary_sha256": original.sha256,
        "counts": {"layouts": len(layouts), "widgets": sum(l["windows"] for l in layouts),
                   "bindings": len(bindings), "commands": len(commands),
                   "superseded_bindings": sum(b["superseded_by_later_declaration"] for b in bindings),
                   "used_commands": len({b["command_id"] for b in bindings}),
                   "defined_function_symbols": len(functions)},
        "commands": commands, "layouts": layouts, "bindings": bindings,
        "input_functions": [{"symbol": name, "address": hex(original.symbol(name).address),
                             "size": original.symbol(name).size,
                             "transfers": direct_transfers(listings[name])}
                            for name in INPUT_FUNCTIONS],
        "context_dispatchers": [{"symbol": s.name, "address": hex(s.address), "size": s.size}
                                for s in functions if "::onClick(ELayoutFunction" in s.name
                                and not s.name.startswith("global ")],
    }
    evidence = args.output / "disassembly"
    evidence.mkdir(parents=True, exist_ok=True)
    (args.output / "ui-actions.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n")
    (args.output / "ui-actions.md").write_text(markdown(report))
    (evidence / "layout-command-initializers.asm").write_text(initialization)
    for name, listing in listings.items():
        (evidence / f"{original.symbol(name).address:x}.asm").write_text(listing)
    print(json.dumps(report["counts"], indent=2))
    print(f"Written to {args.output}")


if __name__ == "__main__":
    main()
