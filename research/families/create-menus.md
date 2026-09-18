# Family packet: `createMenus`

Members: **27**. Subsystems: other=17, interaction=6, effects_skills=2, items=1, frontend=1.

> Same method name is a batching hint, not proof of identical behavior. Pick a representative, then record every member delta.

## Member matrix

| Address | Class | Subsystem | A | P | W | C | Evidence/source |
|---|---|---|:---:|:---:|:---:|:---:|---|
| `0x00ad7a50` | `CCombineMenu` | other |  |  |  |  | `research/batch-menu-pass.json; research/disassembly/batch/00ad7a50-*.asm; research/menu-key-loops.json` |
| `0x00b05390` | `CDialogMenu` | interaction |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |
| `0x00b0f540` | `CDieMenu` | other |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |
| `0x00b196f0` | `CDropdownMenu` | other |  |  |  |  | `—` |
| `0x00b2e0a0` | `CEnchantMenu` | effects_skills |  |  |  |  | `research/batch-menu-pass.json; research/disassembly/batch/00b2e0a0-*.asm; research/menu-key-loops.json` |
| `0x00b3c270` | `CFishingMenu` | other |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |
| `0x00b45080` | `CInteractiveMenu` | interaction |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |
| `0x00b569e0` | `CInventoryMenu` | items |  |  |  |  | `research/inventory-open.md; research/disassembly/b569e0-inventory-createmenus.asm` |
| `0x00b6ed20` | `CMerchantMenu` | interaction |  |  |  |  | `research/batch-menu-pass.json; research/disassembly/batch/00b6ed20-*.asm` |
| `0x00b7f580` | `CModalMenu` | other |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |
| `0x00b87ff0` | `COptionsMenu` | other |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |
| `0x00b93350` | `CPetMenu` | other |  |  |  |  | `research/batch-menu-pass.json; research/disassembly/batch/00b93350-*.asm` |
| `0x00bb08f0` | `CQuestDialogMenu` | interaction |  |  |  |  | `research/batch-menu-pass.json; research/disassembly/batch/00bb08f0-*.asm; research/menu-key-loops.json` |
| `0x00bc6b90` | `CQuestMenu` | interaction |  |  |  |  | `research/batch-menu-pass.json; research/disassembly/batch/00bc6b90-*.asm; research/menu-key-loops.json` |
| `0x00bd6ea0` | `CSettingsMenu` | other |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |
| `0x00be19c0` | `CSkillMenu` | effects_skills |  |  |  |  | `research/batch-menu-pass.json; research/disassembly/batch/00be19c0-*.asm; research/menu-key-loops.json` |
| `0x00bfbe20` | `CStashMenu` | interaction |  |  |  |  | `research/batch-menu-pass.json; research/disassembly/batch/00bfbe20-*.asm` |
| `0x00c14860` | `CStatsMenu` | other |  |  |  |  | `—` |
| `0x00c22580` | `CStatsMenuFill` | other |  |  |  |  | `—` |
| `0x00c404c0` | `CContinueGameMenu` | other |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |
| `0x00c4a810` | `CDifficultyMenu` | other |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |
| `0x00c52a10` | `CMainMenu` | frontend |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |
| `0x00c5d730` | `CNewGameMenu` | other |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |
| `0x00e3b5e0` | `CJournalMenu` | other |  |  |  |  | `research/batch-menu-pass.json; research/disassembly/batch/00e3b5e0-*.asm; research/menu-key-loops.json` |
| `0x00e4c800` | `CTipMenu` | other |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |
| `0x00e9b180` | `CCinematicMenu` | other |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |
| `0x00ea58b0` | `CWaypointMenu` | other |  |  |  |  | `research/batch-menu-pass.json;research/inventory-open.md` |

## Delta checklist (fill per member; do not infer from the representative)

For each member record: early exits; field writes; constants; loop bounds; resource names; direct/indirect callees; event subscriptions; RNG source/order; ownership/lifetime; error path; side effects; caller wiring.

## Suggested workflow

1. Choose the best-evidenced member as representative.
2. Extract a common skeleton only after comparing at least two members.
3. Encode member differences as data/profile fields when semantics match.
4. Keep exceptions separate instead of growing flags indefinitely.
5. Wire the family into a real scenario before researching another large family.
