# Equipment icon evidence upgrade, 2026-10-09

CEquipment::createIcon(CGameUI&, bool), original 0x882e30, 4075 bytes. The implementation already existed, but its legacy test never emitted executed per-function comparison evidence. This change strengthens acceptance evidence without rewriting the production body.

The complete original assembly and cleanup paths were reviewed against the existing source. Direct dependencies and literals were checked through the strict context packet. The packet needed an explicit default std::allocator spelling in an isolated declaration; this ABI-equivalent spelling is not a production change. Numeric constants 96, 64, 0.5 and 1/64, resource keys, window type, property and diagnostic strings were decoded independently from the pinned ELF.

## Observed behavior

Missing data and existing unforced windows return early. Gambler ownership selects the alternative icon; otherwise class-filtered wardrobe entries can replace the icon, retaining the last eligible nonempty entry. New windows use unique names; existing windows reuse the first child. Scaling is height before width. Image dimensions are captured separately around two fresh settings callbacks. A missing first image returns after root creation/sizing. Empty icon names log the diagnostic and use default dimensions. The second image lookup feeds the Image property, followed by mouse passthrough, event muting and conditional parenting.

## Evidence

2560 completed comparisons, zero differences or incomplete observations. Cold and warm calls cover missing data, force and ownership combinations, wardrobe classes, missing images, changing ratio/image dimensions, signed/zero/infinite/NaN ratios, non-ASCII names and embedded-NUL truncation.

The fixture now calls the exact original/replacement function pointers through invocation tracking. It compares returned completion, ordered collaborator calls, and every initialized fake equipment/UI/character/inventory/image/master/window byte, with narrow canonicalization of named pointers, string contents/refcounts and child-vector size/capacity/elements. Real data/string collaborators remain in use. This is not an exhaustive observation of internal DataGroup state or universal exception behavior.

The unchanged candidate is 5357 bytes, normalized DIFF, with no unknown original references. All fourteen independently compiled deliberate faults were rejected by completed differences, with zero incomplete observations. Strict full Stage and independent root validation each passed all 192 tests. Acceptance is 1309/5247 functions, 910500 original bytes: 1255 MATCH and 54 accepted by differential self-test.
