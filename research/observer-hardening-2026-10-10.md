# Test observation completeness and scalable hook storage

10 October 2026. Test-only infrastructure hardening following a real 64-to-65 hook-site capacity failure during GameUI restoration. No original game source, layout, ownership, acceptance threshold, or comparison receipt requirement changes.

## Scalable detour storage

Detour::Set retains its allocation-free inline block and grows with mmap-backed chunks when actual unique original/linked sites exceed that block. It does not invoke the application's allocation hooks, relocate live backups, or drop a collaborator. Duplicate sites, relative-jump range checks, reverse-order byte/protection restoration, and dual-address interception are retained. The owning object cannot be copied.

Storage, jump-range, and protection failures remain explicit. Failed restoration of code bytes or page protections aborts the test child immediately, including explicit restore calls whose existing callers do not check a result. Failure to unmap an already-empty bookkeeping block remains separately flagged and nonfatal; it does not leave an installed hook. The existing exact-disjoint visible-label fixture split remains valid and unchanged.

Controls exercise 63/64/65 and 4,097 actual executable sites; original/linked aliases; allocator/callback isolation; successful reuse and regrowth; allocation/protection/release failures; and prevention of execution after failed restoration. Five deliberately incorrect variants are rejected.

## Complete observations required

- Virtual-call and logic-event logs reject either overflow rather than comparing a retained prefix.
- AI watcher logs reject two equal overflow flags; target-array counts must fit observed storage before content comparison.
- GameUI text-event-list and Astar stack observers reject unobserved tails, retaining bounded traversal and cycle protection.
- Teleport comparison uses an explicit completeness gate; equal discarded-event counts do not establish equality.
- File-system deletion logs separate stored and total counts and check bounds before comparing, preventing out-of-bounds observer reads.
- Nine UI creation spies reject wchar strings whose terminator was not observed within the unchanged readable budget. They never read an extra element beyond the guard.

Existing cases, capacities, event contents and original valid-input domains remain unchanged. Current fixture reachability of every latent overflow was not assumed. Increasing all constants would only postpone the incomplete-observation bugs.

## Validation

Repository-runnable regression files: tools/decomp/test_detour_storage.py, test_observation_limits.py, and test_remaining_observation_completeness.py. Twelve unittest groups pass against the frozen candidate and again after integration. The observer controls exercise exact bounds, one-sided and two-sided overflow, identical prefixes with omitted differing tails, resets, guard pages, and incomplete receipts. Eighteen observer old-behavior mutations and five detour mutations were rejected in focused verification.

Fresh isolated Stage validation and independent root check both pass all 415 headless tests. All 2,352 previously accepted addresses remain accepted (2,117 exact MATCH); every original source translation-unit object digest is unchanged. No new gameplay function is claimed by this change. Headless results do not establish complete live gameplay.

## Remaining improvements

The audit separately identified generated-input boundary coverage, explicit arena/pool setup budgets, and migration of legacy pipe/timer runners to the framed observer. Those require verified original preconditions and separately reviewed changes. Capture/receipt safeguards and resource-pool concurrency limits are deliberately unchanged.
