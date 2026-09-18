# Ролевые промпты и внешние пакеты

## Промпты (prompts/)

Три ролевых промпта для делегирования code-first работы дешёвой модели:
исследователь (пакеты доказательств), портировщик (реализация по контракту),
ревьюер-интегратор (приёмка по caller/context/order/lifetime).

Происхождение: внешний набор `OpenTorchlight-codefirst-toolkit.zip`
(получен 2026-09-18, лежит вне репозитория рядом с ELF/pak как read-only вход).
Приняты дословно, кроме двух ссылок на отсутствующие у нас файлы:
`WORKFLOW_RU.md` → `research/code-first.md`,
`START_HERE.md пакета` → запись анализа пакета (например
`research/inventory-open.md`). Смысл и запреты не менялись.

## Готовые пакеты (вне репозитория)

`ready-packets/` набора (inventory-lifecycle, panel-open-family,
ui-scale-contract) в репозиторий НЕ копируются. Проверено при приёмке:

- ASM-тела побайтово совпадают с pinned ELF SHA-256
  `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`
  (полное сравнение `setOpen @0xb4eb70`, точечное `CMerchantMenu::setOpen`);
- все 44 файла пакетов сошлись с `payload_sha256` их манифестов;
- `callsites.json` — места вызовов И переходов из ASM с явными варнингами
  (порядок адресов ≠ порядок исполнения), полезен как дополнение к
  `research/original-callsites.tsv`, которого на этой машине нет.

Порядок работы: при старте пакета извлечь его тела из набора, перепроверить
по ELF как выше и только потом класть срезы в `research/disassembly/`.

## Что из набора НЕ принято

26-файловый патч (`install_workflow.py --check` сам отказался: база набора
старше текущего дерева), `codefirst.py`/`codefirst_lib` (неревьювнутый дубль
наших `function_package.py`/`audit_registry_sync.py`), локальная бюрократия
`/.codefirst/`, `QUEUE.md`/`families.json` как процесс (только как вход).
