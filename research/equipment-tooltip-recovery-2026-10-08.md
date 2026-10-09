# CGameUI::showEquipmentTooltip, 2026-10-08

Original ELF 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
Address 0xaa6bf0; 33458 original bytes. Readable C++98 reconstruction of the
complete equipment tooltip entry, preserving the existing GameUI update body.

## Differential evidence

The two fixtures compare the actual original and compiled entry: 1152 full-content
cases, each with two frames, and 3072 cached-placement cases. All 4224 completed
pairs pass standalone. The combined GameUI build passes 19 tests, including the
17 prior update tests. The earlier placement-helper research is not counted as
acceptance evidence. Full repository validation is recorded separately below.

The full-content matrix covers weapon/armor/ring/shield and overlapping unit
categories; current owner, merchant and gambler; magical/identified states;
zero, one and two comparison panels; cache reuse and GUID change; translated,
empty and BMP Unicode text; positive, zero and negative requirements and prices;
changing actor pointers and getters; signed level comparison; scaling and
font/position changes during callbacks. Observations include ordered calls,
arguments, text, colour properties, visibility, dimensions, positions, cache GUID
and all 16 translation caches. The placement fixture adds boundary/non-finite
coordinates, UDim scales, moving comparison panels and Control-key states.

Seven intentionally wrong variants all produce completed differences: extra
Effects line leading, missing GUID write, always rebuilding cached content,
omitted Control hiding, omitted requirement warning, wrong description font,
and a pointer margin of 38 instead of 39. The first of these exposed a real
candidate error before acceptance: Effects uses plain font height, whereas the
other text blocks add two pixels.

## Original details retained

CEquipmentTooltip has observed size 0x98 and 17 verified fields; 26 compile-time
checks additionally cover the relevant UI and actor/item offsets. ItemHanded at
0x38 is not touched by this routine. Content is rebuilt only when equipment GUID
changes; attachment, placement and keyboard handling still occur on cached calls.
Translations initialize before the cache check. GetAsyncKeyState queries Control
(0x11), and only its signed 16-bit high bit causes detachment.

Gambler text and unidentified magical equipment follow distinct paths. Effects
are queried even for unidentified equipment. Description wrapping deliberately
uses the DefenseRequirement font. Weapon/armor captions, colour precedence,
repeated requirement getters, buy/sell price visibility, and callback order are
retained. Display strings use UTF-8 decoding; colour-property strings preserve
the original Latin-1 constructor. DPS explicitly narrows to unsigned 32 bits.

Placement preserves the original 39/26/52 pixel margins, re-reads versus saved
positions, UDim evaluation at base 1, viewport conversions, and original
floating-point comparison semantics. No screen, renderer or keyboard input is
queried during the fixture: these collaborators are intercepted.

## Limits

This is behavioral acceptance, not a normalized byte MATCH claim or a full-game
playthrough. Comparisons use controlled collaborators in the pinned original
ABI/runtime. They do not establish equivalence for every possible input or
allocation/exception failure. BMP Unicode is exercised; the pinned CEGUI 0.6.2
supplementary-plane limitation documented in the Stats report is not normalized
away. Original ELF/assets stay read-only; all runs exit before game main.

## Final validation

Stage publication and the independent root tools/decomp/check.py both pass:
159 tests, zero failures, exit 0. Acceptance is 1176/5247 functions, 575540
original bytes: 1149 normalized MATCH and 27 behavioral acceptances. This adds
one address and 33458 bytes to the previous 1175-function result. Seven negative
controls were rejected with completed differences. No remote push was performed.
