# GameUI skill-selection callbacks

10 October 2026. Restores three original GameUI callbacks (2,272 original bytes): skill selection hover, foldout selection, and main skill/hotbar click.

Source preserves GUID width, callback-sensitive actor/manager/item rereads, slot and sentinel routing, effective-level nonzero semantics, skill target getter call order, owner/follower drag handling, capture and detach order, and COW string cleanup. CEGUI Rect memory order is top,bottom,left,right; the original performs three independent getPixelRect calls and computes third width + second left, first top. That operation order and IEEE behavior are retained.

Three nonvirtual declarations are added without layout changes: bool CGameClient::clickRight(long long,bool,bool), void CGameUI::activateItemSlot(int,bool), and int CSkill::getTargetType(). The last declaration models the verified 32-bit integer return ABI and existing int property field. The original source spelling (int versus a 32-bit enum) is unknown; no enum names or dependency implementations are invented.

The candidate was first explored in an isolated pending-baseline preview. After the preceding batch was accepted, a new Stage and new prepare-only package were created from the accepted root; all decomp bytes matched the preview package before candidate integration. No prior receipt was substituted for final-build validation.

## Verification

Normal focused comparisons: 134 hover, 262 selection, 624 main click, all completed with zero differences or incomplete observations. Twenty-two expected dependency unwinds are checked separately and excluded from normal coverage. Fixtures include integer boundaries and full-width GUIDs, valid guarded object backing, RTTI/layout checks, callback mutation, signed zeros, subnormals, finite extremes, infinities and NaNs, whole relevant state and ordered traces, COW reference counts and heap-use checks on exception cleanup.

Seven old emitted DIFF bodies changed register allocation/scheduling while source prefix and collaborator call boundaries were preserved: showFoldout, showTooltip, updateIngameUI, handleKeyPresses, processIngameInput, showEquipmentTooltip and create. Their original-versus-final comparisons run afresh in both full suites. No old MATCH regresses and all previous accepted addresses remain accepted.

Both isolated Stage and independent root checks pass all 426 tests. 10 focused negative controls reject incorrect candidates through completed differential mismatches.

- 0xa94d30: CGameUI::handle_SkillSelectMouseOver(CEGUI::EventArgs const&); DIFF; 299 original bytes.
- 0xa94e60: CGameUI::handle_SkillSelectClick(CEGUI::EventArgs const&); DIFF; 778 original bytes.
- 0xa9dff0: CGameUI::handle_SkillClick(CEGUI::EventArgs const&); DIFF; 1195 original bytes.

Final target receipts:

- coverage gameui_skill_selection_hover 0xa94d30 completed 134 different 0 incomplete 0
- coverage gameui_skill_selection_select 0xa94e60 completed 262 different 0 incomplete 0
- coverage gameui_skill_selection_click 0xa9dff0 completed 624 different 0 incomplete 0

Accepted: 2359 (2120 MATCH, 239 behavioral), 1146752 original bytes. This is verified callback restoration, not proof of complete standalone/live gameplay.
