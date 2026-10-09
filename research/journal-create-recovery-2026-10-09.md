# CJournalMenu::createMenus recovery, 2026-10-09

Original `_ZN12CJournalMenu11createMenusEv`, address `0xe3b5e0`, 2692 original bytes; pinned ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`. Complete assembly, unwind paths and literals were reviewed. Header gaps are split into verified fields without changing the layout. Existing TU bodies are retained; its standalone empty-wide-string declaration is replaced by the existing shared declaration header needed for CFileInfo.

## Behavior

The method reads display dimensions, creates the journal model, generates extremes and assigns mesh bounds. It preserves the original aspect/ratio formula and model visibility, then creates the root window and subscribes mouse movement. File resolution and layout loading retain full-length byte widening, including embedded NUL, before screen scaling and function mapping.

The blocker, close button, journal content, bottom frame and top frame retain their original parenting, layering, flags and callback wiring. The model's position virtual function is selected before the settings callback, while its receiver is reloaded afterward. Temporary Connection, SubscriberSlot, CFileInfo and bounds lifetimes follow the original order.

## Evidence

784 completed original/candidate comparisons, zero differences and incomplete observations, plus 16 supplemental expected exceptions excluded from successful-call coverage. Cases cross seven signed width/height values, eight ratios including signed zero, infinities and NaN, four file-name profiles including long/embedded-NUL/non-ASCII bytes, and callback mutation off/on.

The stronger fixture replaces the current model and virtual table during the ratio callback, root window during sizing, and UI during scaling. It compares ordered calls, full initialized fixture buffers, callback identity and member-pointer adjustment, Connection refcounts and COW-string lifetimes. Expected faults cover both event subscriptions and verify partial-state/lifetime equivalence.

Candidate: 6301 bytes, normalized DIFF, no unknown original references. All thirteen deliberate faults were rejected by completed differences: model extremes, bounds flag, aspect divisor, model position/visibility, root name/passthrough/subscription, layout flag, screen scaling, close-button rise/handler and frame lookup. Full strict Stage and independent root check each passed all 191 tests. Root acceptance is 1307/5247 functions, 903893 original bytes: 1255 MATCH and 52 accepted by differential self-test. No universal exception-equivalence or standalone-playability claim.
