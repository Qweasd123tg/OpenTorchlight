# Parallel GameUI dependency restoration

10 October 2026. Restores 18 original GameUI functions (4,276 original bytes) in three independent six-function slices, merged into one full-TU candidate before final validation.

## Scope

- Item/hover and deletion: clearMenuMouseOvers, activateItemSlot, updateHardwareCursor, both notifyOfDeletion overloads and setMouseOverItem.
- Menu/input dispatch: processMenuInput, mouseEvent, keyEvent, updateMenuUI, processInput and update.
- Visibility/transitions: bothCoveredPartial, setInteractiveMenuVisible, setIngameUIVisible, togglePause, toggleConsole and toggleInventory.

Each worker first received a fresh verified prepare-only package. The combined header union was separately prepared for all 18 targets, then re-prepared from the preceding accepted root. Complete source prefixes were preserved and only disjoint method suffixes appended. No foreign translation-unit bodies or ownership files were changed.

## ABI and preservation

The shared-header union is limited to six headers. It adds established SDL cursor APIs, missing GameUI declarations, Level::setAutomapVisible(bool), KSETTINGS_ALLOW_CONSOLE and the 32-bit Linux scancode function. MenuManager::processInput's long-long placeholder is corrected to bool based on original exits, AL-consuming callers and its bool virtual tail call. The scancode return is modeled as unsigned 32 bits consumed by CEGUI; original source signedness/spelling is not recoverable from the mangled name. No virtual slot, field offset or object layout changes.

Before aggregate validation, combined GCC4.4.7 objdiff preserves all 172 previous emitted rows and old call/tail-call sequences exactly. All18 new normalized records match their individual candidates:14 MATCH and 4 DIFF. Individual matching does not substitute for combined final-TU tests; both full suites execute the combined source and shared headers.

## Tests

Focused groups passed 3,381 completed original/recovered pairs, including 48 real multi-method composition pairs. Eighty-four dependency exception witnesses match separately and do not count as completed target calls. Full guarded state, pointer registration/index changes, deletion ordering, callback-induced rereads, dirty high ABI register bits, signed integer boundaries, float bit patterns and event/window state are observed. Invalid observer exhaustion fails rather than silently truncating.

All 31 incorrect variants are rejected through completed differential mismatches: 12 item/hover, 11 dispatch (including manager return width, scancode width and signed-short Shift ABI), 8 visibility transitions. Independent source/ABI/fixture review found no remaining blocking defect.

Isolated Stage and independent root both pass all 446 headless tests. Every previously accepted address is preserved.

- 0xa82ae0: CGameUI::bothCoveredPartial(); MATCH; 277 original bytes.
- 0xa83300: CGameUI::clearMenuMouseOvers(); MATCH; 149 original bytes.
- 0xa83b30: CGameUI::setInteractiveMenuVisible(bool); DIFF; 137 original bytes.
- 0xa83cf0: CGameUI::activateItemSlot(int, bool); MATCH; 112 original bytes.
- 0xa83d60: CGameUI::updateHardwareCursor(); DIFF; 153 original bytes.
- 0xa84050: CGameUI::notifyOfDeletion(CItem*); MATCH; 226 original bytes.
- 0xa84160: CGameUI::processMenuInput(void*, float, bool); MATCH; 201 original bytes.
- 0xa842c0: CGameUI::mouseEvent(unsigned int, unsigned int); MATCH; 215 original bytes.
- 0xa843a0: CGameUI::keyEvent(unsigned int, unsigned int, long); MATCH; 302 original bytes.
- 0xa844d0: CGameUI::updateMenuUI(float, CGameClient*, Ogre::RenderWindow*); MATCH; 609 original bytes.
- 0xa84870: CGameUI::setIngameUIVisible(bool); MATCH; 340 original bytes.
- 0xa8e2d0: CGameUI::togglePause(); MATCH; 356 original bytes.
- 0xa8e560: CGameUI::toggleConsole(); MATCH; 132 original bytes.
- 0xa8ea20: CGameUI::toggleInventory(); DIFF; 290 original bytes.
- 0xa8f390: CGameUI::setMouseOverItem(CItem*, bool); MATCH; 180 original bytes.
- 0xa92c00: CGameUI::notifyOfDeletion(CCharacter*); DIFF; 464 original bytes.
- 0xab80c0: CGameUI::processInput(CGameClient*, void*, float, bool); MATCH; 59 original bytes.
- 0xacbb40: CGameUI::update(float, CGameClient*, Ogre::RenderWindow*); MATCH; 74 original bytes.

Final new-target comparison receipts:

- coverage gameui_item_hover_clear 0xa83300 completed 192 different 0 incomplete 0
- coverage gameui_item_hover_activate 0xa83cf0 completed 365 different 0 incomplete 0
- coverage gameui_item_hover_cursor 0xa83d60 completed 45 different 0 incomplete 0
- coverage gameui_item_hover_delete_item 0xa84050 completed 162 different 0 incomplete 0
- coverage gameui_item_hover_set 0xa8f390 completed 196 different 0 incomplete 0
- coverage gameui_item_hover_delete_actor 0xa92c00 completed 457 different 0 incomplete 0
- coverage gameui_item_hover_composition 0xa8f390 completed 48 different 0 incomplete 0
- coverage gameui_dispatch_menu_input 0xa84160 completed 74 different 0 incomplete 0
- coverage gameui_dispatch_mouse_event 0xa842c0 completed 56 different 0 incomplete 0
- coverage gameui_dispatch_key_event 0xa843a0 completed 132 different 0 incomplete 0
- coverage gameui_dispatch_menu_ui 0xa844d0 completed 149 different 0 incomplete 0
- coverage gameui_dispatch_process_input 0xab80c0 completed 56 different 0 incomplete 0
- coverage gameui_dispatch_update 0xacbb40 completed 56 different 0 incomplete 0
- coverage gameui_menu_visibility_covered 0xa82ae0 completed 236 different 0 incomplete 0
- coverage gameui_menu_visibility_interactive 0xa83b30 completed 148 different 0 incomplete 0
- coverage gameui_menu_visibility_ingame 0xa84870 completed 130 different 0 incomplete 0
- coverage gameui_menu_visibility_pause 0xa8e2d0 completed 176 different 0 incomplete 0
- coverage gameui_menu_visibility_console 0xa8e560 completed 415 different 0 incomplete 0
- coverage gameui_menu_visibility_inventory 0xa8ea20 completed 288 different 0 incomplete 0

Changed compiled unit objects relative to preceding accepted root: decomp/src/gameui.cpp.

Accepted: 2377 (2134 MATCH, 243 behavioral), 1151028 original bytes. This is source restoration with headless comparison evidence, not proof of complete live gameplay.
