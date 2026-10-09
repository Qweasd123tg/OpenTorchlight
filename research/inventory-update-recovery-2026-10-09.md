# Inventory frame update recovery

CInventoryMenu::update(float), original address 0xb4f9d0, 8731 original bytes.
Full TU retained; changes are confined to the active decomp track.

## Behavior recovered

- Notification-tab pulse, visible-page behavior and conditional property updates.
- Localized GP label with original lazy static cache and UTF8 conversion.
- Weapon-set mismatch guarded by alive, attacking and skill checks; original
  sound 18, character toggle, then virtual layout update order.
- Left-priority model rotation and original matrix multiplication order.
- Closed-state overlay cleanup, close-animation/queue checks and viewport 3 removal.
- Inventory top/bottom bone anchoring, panel screen edge and clamped wardrobe
  viewport, with the original one-pixel width fallback.
- Hovered-skill lookup and tooltip placement/removal, including null-manager and
  missing-skill early returns.

## Verification

1024 completed original/candidate comparisons with zero differences/incomplete
captures. Each case observes two frames, call order, arguments, UI and character
state. Cases cross owner presence, open/closed state, tab/viewport layouts, hover
states, four behavior profiles and collaborator mutation. Inputs include Unicode
and empty/cached labels, signed gold extremes, fractional and degenerate screen
sizes, negative/NaN phases and signed zero. Positive-infinite phase is not used:
the original subtraction loop would not terminate.

Independent checkbox/weapon-set state variation and observed branch mask 0x1ff
confirm coverage of alive/attack/skill rejection and successful sound/toggle/layout.
Controlled CEGUI/OGRE fixtures reuse the already checked Pet-update approach;
only the target function is compared, without using an original fallback.

All eight deliberate faults were detected through completed unequal comparisons,
zero incomplete captures: tab pulse threshold, money separator, attack guard,
sound ID, rotation direction, minimum viewport width, removed viewport ID and
swapped tooltip coordinates. All three changed headers compile standalone; the
candidate includes 13 offset/size assertions.

Strict Stage and independent root check.py each passed 174 headless tests.
Accepted snapshot: 1212 game functions / 845176 original bytes,
1170 normalized MATCH plus 42 behavioral acceptances.
This is the 26th restored large function in the recovery series.

## Evidence and limits

The original ELF SHA256 is
91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
Two missing Character member declarations were checked against ASM/callers;
no Character implementation is replaced. Secondary weapon flag +0x70e and Inventory
layout fields replace padding without changing size. Equipment pointer +0x1020 is
confirmed by the original getEquipmentInSlot result store at 0xb4d5e1.

The target remains behaviorally accepted, not normalized MATCH. Collaborators
are controlled and comparison covers the function's state/call behavior, not GPU
pixels or standalone game execution. No rendered game window was launched, and
no acceptance gate was weakened. External smallmatch pass4/pass5 material is
excluded from these counts.
