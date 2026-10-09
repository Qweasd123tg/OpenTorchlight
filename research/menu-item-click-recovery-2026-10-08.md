# CGameUI::menuItemClick: full item interaction entry

Original: 0xa8f780, 10484 bytes, gameui.cpp.
ELF SHA256: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.

The full C++98 entry is reconstructed from the original instructions and
symbols, with the historical Ghidra listing used only for navigation. The
readable candidate uses named UI/actor field views with 29 compile-time
layout checks and existing item/inventory/menu classes. Parameters follow the
mangled symbol; bool return is supported by caller tests of AL. A 9126-byte
initial natural form was DIFF, so acceptance uses the complete entry comparison,
not similarity percentages or a claim of recovered original source spelling.
The final source inlines its private phases into the public entry.

## Recovered behavior

- Three separate Shift queries and repeated panel-open queries; player/pet and
  service-panel routing, follower presence/AI-state guard.
- Inventory selection including shared stash; destination pane/tab selection,
  special slots -1 and 999, enchant slot14 and combine slots15 through18.
- Skill-item targeting and consumable use; consumed-item deletion, unlimited
  uses (-9999) exception, safe-pointer clearing, cursor/menu/tooltip refresh.
- Quick transfer and precise rollback to the original slot; quest restrictions.
- Shift and drag trading; distinct buy/sell prices, gold direction, shop clones,
  gambler journal increments and unique-item achievements.
- Equip restrictions and socketable exception; identified/capacity guards,
  insertion, elemental regeneration and inventory bonus/effect/equip refresh.
- Same-GUID stack merging, overflow arithmetic, infinite-shop quantity retention,
  swaps and recovery of both displaced items, including world-drop fallback.
- Empty-slot placement and auto-equip retries; comparison-item removal and
  reinsertion/drop; unsuccessful placement returns the dragged item.
- Drag icon parent and absolute dimensions. Evaluation order is Y minus
  scaledY(48), X minus scaledY(32), height scaledY(96), width scaledY(64).
  Mouse coordinates are signed64, and reads across callbacks are retained.
- Six hover caches and three tooltip GUID caches are cleared in original order.

Unknown unit tags 10/37/38 remain numeric rather than acquiring invented names.
Existing documented tags are named via UNITTYPES. Inventory/Pet setTab's ignored
void return is a working declaration, not a uniquely proved lost return type.

## Dependencies and source consistency

Missing methods are declared, not implemented as stubs. Pointer/bool results
are checked against original callers and return paths, rather than inherited
from the generated long-long placeholders. The CResourceManager data-group
createUnit overload delegates to the existing GUID overload and returns its
pointer (or NULL for a NULL group); it is distinct from the old declaration.
This missing overload exposed and motivated the separately verified context
lookup fix. No other worker's function body was changed.

The existing gameui.cpp bodies are retained. Its one local EMPTY_WSTRING
statement is replaced by the existing EmptyStrings.h, preventing duplicate
header definitions. Both EMPTY_STRING and EMPTY_WSTRING are original TU-local
symbols at 0x14b7d00 and 0x14b7d08. Their uses/initialization are included in the
integrated regression check, not assumed harmless.

## Full-entry fixture

3168 completed original-versus-candidate comparisons passed: 33 branch-focused
scenarios, 16 state variants and six pickup-failure schedules. Both sides use
AutoTest::invoke and Coverage. Return value, ordered events and arguments,
weak-reference state, selected skill, gold, item quantities/socket state,
inventory membership, icon parent/position/size, six hover caches and three
tooltip cache values are compared. Unknown pointer identities fail the capture.

All original call sites were inventoried: 246 direct and55 indirect. 58 exact
callee identities are redirected on both original and linked sides, with
bounded detour groups. The two reviewed TSafePointer bodies are retained but
their RunicCore add/remove registration callbacks are intercepted; this also
covers the inlined candidate. All menu and equipment virtual slots used by the
entry have controlled implementations. The C++ unwinder remains real.
Inventory movement, resource creation, currency, achievements, level drops,
sound, cursor and CEGUI effects stay inside the fixture. No game window, Steam
request or real inventory mutation is performed.

The fixture checks signed64 mouse coordinates and a reentrant scaledY change
to mouseX, unlimited shop stock, first-free retries, rollback failures and
both displaced-item paths. It does not prove every possible collaborator
implementation, malformed object graph or exception schedule. No claim of
whole-game completion is made.

All eight changed headers also compile independently. The integrated compiler
caught a missing CItem forward declaration in Character.h; it was corrected
before publication, and all3168 entry comparisons passed again on the corrected
header tree. The fresh r5 preparation packet has no unresolved direct dependency.

The first completed aggregate run reported one incomplete Pet creation child:
original exit0, candidate SIGALRM14, no candidate report. This is not a behavioral
DIFF or a pass. The exact same built blob then passed the full4704-case Pet
fixture twice in isolation, without source or timeout changes. The complete
Stage/root runs are repeated with four workers and the same60 shards to reduce
concurrent load. All fixture deadlines and acceptance rules remain unchanged.

## Final validation

All11 intentional faults were rejected with completed differences: return bool,
transfer rollback, gold sign, socket effect refresh/identified guard, icon width,
pet hover reset, first-free retry, weak-owner clearing, second displaced item
and stack subtraction. Crashes/incomplete reports were not mutation evidence.
Strict Stage and independent root check both passed169 headless tests. Earlier
accepted addresses remain accepted:1209/5247 functions,793735 original bytes,
1170 normalized MATCH and39 behavioral acceptances. This adds one address and
10484 bytes. No game-window launch was performed.
