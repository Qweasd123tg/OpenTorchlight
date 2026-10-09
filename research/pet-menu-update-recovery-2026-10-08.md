# CPetMenu::update(float), 2026-10-08

Original ELF 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
Address 0xb9b0d0; 26069 original bytes. Readable C++98 candidate for the complete
pet-menu update entry, preserving the previously accepted createMenus method.

## Differential evidence

The final standalone fixture completes 2048 original-versus-compiled pairs,
with two frames each, zero differences and zero incomplete comparisons. It
crosses four owner categories (including absent owner), four open/closed states,
four layouts, four skill-hover states, four numeric/text profiles and two
callback-mutation modes. Additional deterministic variations cover notification
flags, pulse phase, viewport presence, both rotation flags, scale and resolution,
cold/empty/prefilled caches and old widget text. The second frame tests cached
text and accumulated state. A null tooltip is included on fully-closed paths.

All renderer/model/entity/bone, viewport/camera/render-window, orientation,
settings, character-statistic, translation and skill-tooltip dependencies are
controlled before invoking either actual entry. The fixture records ordered
calls, callback arguments and virtual-call targets, window text/properties,
parentage/visibility/positions, orientation matrices, menu fields and all three
translation caches. It changes camera identity and its virtual table during
viewport argument getters; the original dispatch ordering is retained.

Eight intentionally wrong variants produce completed differences: pulse period,
rotation multiplication order, magic baseline side, decoding the cached MP label
as UTF-8, ignoring queued closing animation, viewport height, omitted category
closure, and hiding the old tooltip when the skill manager is absent. These are
not merely compile failures or child crashes.

## Original details retained

There are 16 new offset assertions and two size assertions; the previous Pet
creation checks remain. Rotation operates on the owner's model, with left taking
precedence when both flags are set. Current orientation is multiplied on the
right by the Y rotation. The model pointer is reloaded after the matrix callback.
The viewport uses the original 97/166/135/169 scaling constants, negative-left
clipping and actual-width/height aspect ratio calculation.

A category-41/42 owner triggers virtual setOpen(false). Fully closed menus return
after hiding the two socket layers and detaching an existing tooltip. While
closing, both playing and queued CLOSE animations prevent premature teardown.
A missing skill manager or missing skill returns without hiding the old tooltip.

XP uses a wide cache and displays label:current/gate without a space after the
colon. MP/HP caches are CEGUI::String objects. Their translated UTF-8 bytes are
assigned through the original byte-widening std::string path; silently changing
this to UTF-8 decoding changes original behavior, including BMP labels. The final
label uses a colon plus space. Damage getter ordering differs from StatsMenu:
maximum baseline precedes actual maximum and minimum, and magic uses only the
false-side baseline maximum. These details were read from ASM and checked.

## Limits

This is behavioral evidence under controlled collaborators, not normalized byte
MATCH or a rendered full-game test. The fixture uses elapsed values 0.125 and 0,
with varied phase values including finite multi-wrap, NaN and negative infinity.
Positive infinity and sufficiently huge positive phase can make the original
subtraction loop nonterminating; those inputs are not claimed as completed
comparisons. The loop is preserved rather than silently replaced with modulo.
Allocation failures, every exception path and all possible inputs are not proved.
Only authorized headless runs occurred; original ELF/assets remain read-only.

The full Stage and independent repository check passed, as recorded below.

## Final validation

Stage publication and the independent root tools/decomp/check.py both pass:
161 tests, zero failures, exit 0. Acceptance is 1178/5247 functions, 632097
original bytes: 1149 normalized MATCH and 29 behavioral acceptances. This adds
one address and 26069 bytes to the previous 1177-function result. Eight negative
controls were rejected with completed differences. No remote push was performed.
