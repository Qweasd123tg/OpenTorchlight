# GameUI action-slot refresh

Target: CGameUI::updateSlots(), 0xa98c20, 10237 original bytes. The complete
original entry is reconstructed in the original gameui.cpp translation unit.
The existing four recovered bodies remain unchanged. Field views use named,
offset-checked members; no replacement UI runtime or generated machine emulator
is introduced.

## Original behavior

- Returns immediately without a player or inventory.
- Refreshes three primary skill icons only when their GUID cache changes.
  The attack icon has a skill_attack fallback; the other two have empty images.
  The first icon refresh also clears the second cooldown label, as the original
  explicitly does. User-data pointers refer to the corresponding stable GUID
  storage, or to the empty GUID sentinel.
- Updates primary cooldown text from ceilf(cooling time), displaying only
  positive integer seconds and avoiding redundant text changes.
- Visits ten hotkey slots, skipping absent buttons. A usable skill takes
  precedence over a configured item. Skill icons reset size on every visit;
  icon/cache changes reset position, tooltip and cached cooldown.
- Cooldown changes update icon tint and text. Skills clear the item GUID cache
  and use button ID zero; item slots use ID 1000 and a pointer to the item cache.
- Item resources supply the ICON value. A missing image returns from the entire
  method. Image width and height are independently Y-scaled through the current
  settings ratio; the aspect-preserving fit uses slot width divided by image
  height, including the original floating-point evaluation order.
- Item-count changes control unsigned count text, dim/normal tint and the
  lazily translated assignment tooltip. Missing resources and empty assignments
  retain their distinct cache and UI clearing conditions/order.

Working return type is void: observed callers discard the result and early
returns retain unrelated player/null values in RAX. Lost source spelling is
not claimed. New dependency declarations are backed by their original callees:
getSkillCoolingTime returns scalar float in XMM0; getUnitDataByGuid tail-calls
the data-group lookup and returns a CDataGroup pointer.

## Proof and limits

The final private fixture completed 592 original-versus-candidate comparisons:
37 scenario configurations, 16 variants, each with a warm-up call and one
AutoTest::invoke-tracked call. Ordered events and both frame snapshots are
compared, including text, images, tints, tooltips, geometry, IDs, GUID/cache
values and normalized user-data pointer identities. Unknown pointers invalidate
the report. It covers null entry dependencies, missing/empty skills and items,
cold/warm caches, fractional and negative cooldowns, NaN/infinity, zero and
negative item counts, null images, missing buttons, changing player/resource
pointers, rebinding windows and reentrant width/settings changes.

The initial harness attempted to mark two invocations in one Capture. The
existing strict report gate rejected it; the harness was corrected to use one
tracked invocation after a captured warm-up. No acceptance gate changed.

All 423 original direct calls (46 callee identities) were inspected; there are
no indirect calls. The linked candidate has 556 direct calls and no indirect
calls. Twenty-three collaborator identities are controlled on both original
and linked sides. Real standard string/CEGUI value operations, ceilf and C++
lifetime support remain. There are no real renderer, sound, platform, inventory
mutation or world effects. Four changed headers also compile independently.

Two natural source forms were compared. Neither is normalized MATCH; the final
entry is 26529 compiled bytes versus 10237 original bytes, with unresolved
EH/literal normalization. Behavioral evidence, not DIFF percentage or a byte
identity claim, is the proposed acceptance basis. These controlled scenarios
do not prove every malformed object graph or exception/allocation schedule.

## Aggregate fixture compatibility

The first full Stage run executed all 170 tests and rejected one existing
label-creation fixture: both children exited 42 before comparison. Its single
64-patch detour set had no room for the now-distinct original and linked
updateSlots entries. The fix places those two redirects in a separate bounded
Set and checks both failure flags; no callback, case, comparison or safety
limit is removed. The unchanged 160 label-creation comparisons and all 592
slot comparisons then passed in the same rebuilt blob. Full Stage/root checks
are repeated before acceptance.

## Emitted SDK constructor

The second aggregate run passed all 170 tests, but the preservation gate still
rejected the newly emitted weak CEGUI::String UTF8 constructor at 0x899960.
Its 768-byte body is not normalized MATCH because EH LSDA equivalence remains
unverified. That failure was not waived. A separate direct original-versus-
linked constructor fixture now passes 80 ASCII/BMP and buffer-boundary cases,
including embedded NUL and quick-buffer/heap transitions. It records decoded
content, size/reserve, encoding state and re-encoded text; malformed/non-BMP
inputs and allocation failures are not claimed. The 160 label and 592 slot
comparisons also passed again with this fixture in the same blob.

## Final validation

Ten intentional faults were rejected through completed original-versus-candidate
differences, with no incomplete reports: primary-label clearing, icon scaling,
missing-image return, item button ID, zero cooldown, skill user-data pointer,
count invalidation, item cache clearing, primary user GUID and item count text.
Strict Stage and independent root checks both passed all 171 headless tests.
Acceptance is 1210 functions / 803972 original bytes, including 1171 normalized
MATCH and 40 behavioral acceptances. This adds one address and 10237 bytes.
No original game window was launched; this is not a standalone rebuild claim.
