# Automatic function triage

> **Архив замороженного направления.** Указания, команды, очереди и числа ниже
> относятся к прежнему снимку; они не задают текущую работу или приёмку.
> Действующий процесс: [decomp](../../../decomp/README.md).

> Historical generated snapshot. Recompute with `tools/auto_triage.py` into
> ignored build or `/tmp`. The 2026-10-02 correction no longer defers editor-named
> shared scene/descriptor code and preserves compiler initializer review:
> [current accepted boundary](menu-preparation-automation.md).

> Scheduling reduction only. These counts are not game-completion percentages and never promote function-transfer stages.

Original function addresses: **17023**.

## Primary mutually-exclusive work classes

| Class | Functions |
|---|---:|
| `compiler_glue` | 5779 |
| `external_source_first` | 3555 |
| `manual` | 3173 |
| `editor_tooling` | 2339 |
| `family_batch` | 650 |
| `lifecycle_wrapper` | 431 |
| `exact_routing` | 377 |
| `exact_leaf` | 302 |
| `technical_symbol` | 293 |
| `modified_library` | 68 |
| `descriptor_binding` | 56 |

## What this means for the queue

- No individual deep-reverse pass needed at this stage: **8797**.
- Match public/bundled source before reversing machine code: **3623**.
- Review as a family/target instead of one function at a time: **1430**.
- Still falls through to individual/manual reverse: **3173**.

The categories above are mutually exclusive, so these headline counts can be added. A forwarding wrapper still depends on its target; a destructor wrapper does not prove the base destructor is trivial.

## External-source candidates

- `ParticleUniverse`: 2891
- `libstdc++/STL`: 460
- `Ogre`: 204
- `CEGUI`: 68

## Recommended use

1. Do not schedule `compiler_glue`, exact tiny wrappers, or editor-tooling functions as standalone feature work.
2. Source-match third-party libraries before any decompilation effort.
3. For `technical_symbol` and `family_batch`, choose representatives and preserve per-member deltas.
4. Spend neural deep-reverse time on the remaining `manual` queue and on integration gaps discovered by scenarios.
