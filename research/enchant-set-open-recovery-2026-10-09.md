# CEnchantMenu::setOpen(bool,EAIState) recovery, 2026-10-09

Original `_ZN12CEnchantMenu7setOpenEb8EAIState`, address `0xb243c0`, 3829 original bytes; pinned ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`. Complete assembly, unwind paths, jump table and literal data were reviewed. The full existing enchantmenu.cpp is preserved. Narrow declarations add this overload and three verified GenericModel animation collaborators without changing their bodies or class layout.

## Behavior

The requested mode is stored even on unchanged-open/closed paths. Closing returns the service-slot item to inventory, or drops it at the current character's position when pickup fails. Close sound and animation precede clearing the transition/open flags. Opening preserves both settings reads, six separate lazily translated strings and mode-specific title/button text, including truncation at an embedded wide NUL before UTF-8 conversion.

The model is shown and either blends or plays its opening animation depending on the current closing animation, then queues the looping idle animation. Background parenting, move-to-back, context tip, open flag and virtual layout update preserve ordering and callback-visible receiver reloads.

## Evidence

768 completed differential cases with no differences or incomplete observations. The matrix crosses all four open/closed transitions, twelve mode values including boundary/out-of-range values, four translation/inventory/animation profiles, callback mutation on/off and one/two calls per side. The two-call cases exercise cold/warm translation caches and retries for empty translations; only the final call is registered as the per-function comparison target.

The test compares ordered calls and arguments, translated and converted strings, receiver changes, parent changes and complete initialized menu, character, inventory, model, window, equipment, settings, resource and UI buffers. Controlled conversion covers BMP and embedded-NUL inputs; it is not a claim about arbitrary non-BMP rendering.

Candidate: 3461 bytes, normalized DIFF with no unknown original references. All thirteen deliberate faults were rejected by completed differences: mode write, service slot, pickup flag, drop position, close sound, transition flag, translation-cache retry, socket title, open sound, model visibility, opening speed, idle-loop flag and context tip. Full strict Stage and independent root validation each passed all 189 tests with zero failures. Accepted total: **1306 of 5247 game functions, 901201 original bytes**, comprising 1255 normalized MATCH and 51 behavioral acceptances. Large-function recovery series: 35. No universal exception-equivalence or standalone-playability claim.
