# Large menu construction pilot

Targets: CMerchantMenu::createMenus() at 0xb6ed20 (34170 original bytes) and CStashMenu::createMenus() at 0xbfbe20 (33050). This draft preserves the previously accepted MerchantMenu::setPetSlotIcon. Do not merge until shared headers are reconciled with the concurrent PC work.

## Verified snapshot

Based on main ae84cf63855833c0551d2c220278bb3db92f09c7, original ELF 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b, GCC 4.4.7 and original runtime/resources. The full check.py exits 0: 108 headless tests, 0 failures. Accepted addresses increase 896 → 898 and bytes 59265 → 126485. Exactly 0xb6ed20 and 0xbfbe20 are added; none removed. These counts describe this staged snapshot, not a claim that main has already changed. Machine comparison remains DIFF for both methods.

Each method has 392 normally completed resource-backed comparisons with zero different/incomplete receipts. The hierarchy, explicit UnifiedPosition/UnifiedSize and mouse-pass-through properties come from the provided game's layout XML: 214 Merchant windows and 122 Stash windows. Recursive lookup respects ancestry and reparenting. Other GUI behavior is deliberately observed through bounded collaborator spies. A separate synthetic hierarchy contributes 392 comparisons per method. Scope includes argument/call ordering, callback identity and binding, selected fields, slot indices, parent relationships, and temporary connection reference-count lifetime.

The previously accepted pet-slot method passes 12960 comparisons when compiled in the combined Merchant TU and new headers. Separate scratch fixtures exercised 30 subscription-exception cases per method, all matching. Those exception cases are not normal-completion receipts and are not part of the 108-test aggregate. The early negative control 0.75 → 1.0 caused 166/288 mismatches before restoration. Four additional Merchant layout-name variants (short ASCII, 120-character ASCII,non-ASCII UTF-8 bytes,invalid UTF-8 bytes) matched; no constructor-conversion bug was established there.

## Corrections required after model generation

Space Bunny Free generated both initial bodies. Neither first draft compiled. Correct SDK declarations, compiler diagnostics, type/layout facts and original ELF symbols were supplied. Supervisor checks and fixes then found:
- omitted MSockets creation and the +0x30 parent initialization in Merchant
- reversed property key/value arguments in Merchant formatting
- extended lifetimes of four Connection temporaries across later subscriptions
- qualified EventSet:: calls suppressing virtual dispatch in Stash
- position reads moved across property changes, and reordered hide/search operations
- Stash clearing slot indices instead of assigning 0…399
- missing Stash primary virtual slot 19 and an incorrect sizeof claim

The Stash vtable groups now match the original. Used offset probes pass 53 Merchant and 62 Stash assertions. The compiled Stash size is 13352, not 13346; an independent proof of every unused field/type or original allocation is not claimed. Partial generated-header markers keep unused return hypotheses out of trusted export. The two new GameUI declarations have no hidden-return-pointer calling convention at the observed sites; their unused result declarations and entity accessor remain shared-header integration points.

## Limits and integration

No gameplay, real rendering, or save interaction was run. These fixtures are not a universal proof over arbitrary callbacks, all allocation failures, every GUI implementation or complete exception metadata. The layout snapshots describe this supplied asset version, not every mod. Some field names/types and exact source return spellings remain reconstruction hypotheses. Test success does not erase these limits.

Shared edits are GameUI.h and SceneNodeObject.h. The common SubMenu header is unchanged. Keep this PR draft while the user works on their PC; reconcile their committed snapshot and rerun the aggregate before merging. Original binaries and full game assets are not included.
