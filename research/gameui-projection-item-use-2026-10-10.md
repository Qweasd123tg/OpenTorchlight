# GameUI projection and item-use dispatch

10 October 2026. Restores four original GameUI methods in one coherent class batch, amortizing full-suite validation across 2,517 original bytes.

## Screen projection

CGameUI::getScreenPosition (0xa82f40, 782 bytes) uses the pinned Ogre matrix/vector operations and preserves both reciprocals, returned depth multiplication, raw floating operation order, unary Y negation, and callback-sensitive viewport rereads. Matrix4 is passed by value as 64 stack bytes; Vector3 returns through XMM0/XMM1. The 0x1680 gap is refined into named viewport fields without changing layout. The forwarded orientation-Y-axis parameter is named cameraUpOffset.

Projection alone compiled to MATCH on the first natural implementation. Its fixture passes 244 direct raw-bit normal pairs and 40 two-tick real lifecycle pairs, with four expected callback unwinds checked separately and excluded from normal coverage. Inputs include signed zeros, subnormals, extreme finite values, infinities, signed NaN payloads, one-ULP transitions, independent denominators, valid aliases, callback mutations, bounded real panel helpers, and matrix-by-value snapshots. Nine incorrect arithmetic/ordering variants are rejected by completed differential mismatches. Several fail on ordinary finite inputs by one ULP.

## Item-use and dragged-item routing

The additional bodies are returnDraggedItem (0xa8f4e0, 663 bytes), performItemUse (0xa92080, 664 bytes), and useItem (0xa92320, 408 bytes). Source preserves the original safe-pointer operations, actor roles, inventory/drop/delete routing, callback rereads, signed-short modifier routing, pet-state checks, and collaborator call boundaries. No unrelated method, new source-file ownership, or weak CTextEvent implementation is invented.

The prepared source prefix is preserved, but compiler scheduling/register allocation changes five existing emitted bodies: menuItemClick, two skill tooltip/foldout bodies, and two UTF-16 string helpers. No prior MATCH regresses. Fresh full-suite evidence is required, including 1,800 direct comparisons for the addressed _M_mutate helper; old receipts or unchanged source text are not substituted for final-build verification.

All original tests remain. Targeted original/recovered fixtures use verified layouts and guarded backing; exceptions are separate from normal receipt counts. Negative controls must produce completed mismatches rather than merely crashing the observer. Detailed accepted comparison counts are listed below from the executed final suite.

## Aggregate verification

Isolated Stage validation and an independent root check both pass all 423 headless tests. All previously accepted addresses are retained. Root verification uses the verified shared compiler cache without skipping final source/object checks.

- 0xa82f40: CGameUI::getScreenPosition(Ogre::Vector3 const*, Ogre::Vector3 const*, Ogre::Matrix4); final status MATCH; original 782 bytes.
- 0xa8f4e0: CGameUI::returnDraggedItem(); final status MATCH; original 663 bytes.
- 0xa92080: CGameUI::performItemUse(CLevel&, CEquipment*, CCharacter*, CCharacter*, CCharacter*); final status MATCH; original 664 bytes.
- 0xa92320: CGameUI::useItem(CLevel&, CEquipment*); final status DIFF; original 408 bytes.

Final-suite comparison receipts for the new batch:

- coverage gameui_item_return_dragged 0xa8f4e0 completed 113 different 0 incomplete 0
- coverage gameui_item_perform_use 0xa92080 completed 212 different 0 incomplete 0
- coverage gameui_item_use_routing 0xa92320 completed 170 different 0 incomplete 0
- coverage gameui_item_use_composed 0xa92320 completed 42 different 0 incomplete 0
- coverage gameui_item_click_composed 0xa924c0 completed 22 different 0 incomplete 0
- coverage gameui_projection_exact_bits 0xa82f40 completed 244 different 0 incomplete 0
- coverage gameui_projection_lifecycle_composed 0xa8f100 completed 40 different 0 incomplete 0

Focused negative controls: 9 projection and 17 item-use variants rejected.

Accepted addresses: 2356 (2120 MATCH, 236 behavioral). Accepted original bytes: 1144480.

This does not establish complete standalone/live gameplay or recover generic weak CTextEvent update/createText and allocation/shutdown bodies.
