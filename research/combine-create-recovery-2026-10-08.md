# CCombineMenu::createMenus recovery, 2026-10-08

Original entry 0xad7a50, 24134 bytes, combinemenu.cpp. Candidate C++98 recreates
its complete normal path: dropdown model and mesh bounds, positioning from
resolution and Y ratio, CEGUI layers, click barrier, resource-layout resolution,
title/dialog/accept lookup, slot-glow image, four slots, subscriptions, stack
labels and two overlay families. Existing setSlotIcon/updateLayout bodies remain
unchanged. No rendered game or original resource write is involved.

The constructor pins SceneManager at +0xb0 and RenderWindow at +0xb8, correcting
an earlier provisional reversed label in private research. Allocation is 0x1b0;
24 field offsets plus the class size are compile-time assertions. Newly declared
handlers are nonvirtual bool members, as shown by their original subscriber
member pointers and return paths. mapEventHandlers is a void dependency, with
ordinary cleanup/catch paths returning without a result and callers discarding
its return. No dependency implementation is invented.

Original-specific details retained:
- both GuiLook lookup (result discarded) and UIIcons lookup;
- model x = -0.5 * ((width - height / 0.75) / YRatio) - 270;
- barrier height scaledY(768) is queried before width scaledY(390);
- exact resource flags false/true/false and original misspelling CombineerSockets;
- equipment slot IDs 15..18, separate userdata indices 0..3;
- MouseOver serves both enter and move, with distinct ItemClick and MouseOut;
- each temporary subscription connection is released before the next;
- ItemSlot names are 1-based, repeated moveToFront is preserved;
- stack labels use original alignment, colour and sibling parent;
- socket overlay position queries parent before slot and adds all four UDim
  components in the original operand order; ordinary glow stays parent-relative.

The first full-entry comparison passed 1568 completed cases, zero differences or
incomplete pairs. An expanded matrix adds nonzero relative UDim scales and long
BMP UTF-8 resource names, covering 3136 cases across seven width/height values,
eight Y ratios (including signed zero, infinities and NaN), reentrant settings
replacement, initial window flags and four resource/geometry variants.
The expanded fixture passed all 3136 completed cases. All nine negative controls were rejected by completed differences. Integrated results follow.

The fixture observes complete collaborator traces, model arguments/bounds,
window properties and geometry, exact callback member-pointer identity and this
adjustment, connection lifetimes, slot arrays, resulting pointers and final
window state. Renderer, filesystem, resource manager and layout mapping are
intercepted before original entry. Pure SDK string/colour operations remain real.
This is controlled-collaborator behavioral evidence, not a byte MATCH or proof
of every exceptional CEGUI allocation/resource-failure path.

## Final validation

Stage publication and the independent root tools/decomp/check.py both pass:
167 tests, zero failures, exit 0. Acceptance is 1186/5247 functions, 757234
original bytes: 1149 normalized MATCH and 37 behavioral acceptances. This adds
one address and 24134 bytes to the previous 1185-function result. Nine negative
controls were rejected with completed differences. No remote push was performed.
