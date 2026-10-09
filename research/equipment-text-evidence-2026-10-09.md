# Equipment text evidence upgrades, 2026-10-09

Two existing production functions are retained unchanged and their legacy fixtures are upgraded together. Strict context packets, original control flow/calls and formatting behavior were reviewed. Packet-only declaration clarifications spell out an existing default allocator and repeat the existing inline removeWhiteSpace signature; neither is a production change.

## getEquipmentEffects

Original 0x88c150, 3813 bytes; candidate 3685 bytes, normalized DIFF, no unknown references.

768 completed cold/warm original/candidate comparisons, zero differences or incomplete observations. The function checks identification once, obtains dynamic/passive/transfer descriptions first normally and then for sockets, appends skill text, and preserves newline-only trimming, separators and the final newline. A callback can clear identification without stopping the already-started pass; a later warm call sees the new state.

The fixture observes the exact invoked function, full returned wide text, ordered calls/activation/flags, complete initialized equipment bytes and callback counts. Inputs include empty/newline-only strings, spaces/tabs/carriage returns, Unicode and embedded NUL. The existing trim regression is retained unchanged: 14 edge cases, 19531 exhaustive small strings and one long boundary case. Optional malloc counting was not loaded in this run, so allocation equivalence is not claimed.

## skillDescription

Original 0x87e640, 2771 bytes; candidate 2760 bytes, normalized DIFF, no unknown references.

7200 completed cold/warm/capacity comparisons, zero differences or incomplete observations. The function retains retry-on-empty Level translation, SKILL_TO_GIVE name/display-name and item-level fallbacks, signed level formatting, newline rules and dynamically reloaded skill-manager/count access. Enabled/property-executed flags and description arguments are preserved.

Cases cover missing managers, level extrema, empty/Unicode/embedded-NUL translation and skill text, manager replacement, list shrink/growth and reduced logical capacity. The fixture compares full initialized equipment/manager/skill buffers with narrow named-pointer/storage canonicalization, initialized skill identities, returned text and ordered collaborator calls. It retains real DataGroup, TArrayList and knownSkills services; exhaustive DataGroup internals are not claimed.

## Acceptance

Both fixtures now require exact original/replacement invocation and complete reports; neither matching crashes nor incomplete captures count. All twenty-four independently compiled negative controls were rejected by completed differences, with zero incomplete observations. Strict full Stage and independent root validation each passed all 192 tests. Root acceptance: 1313/5247 functions, 928361 original bytes, including 1255 MATCH and 58 behavioral acceptances. No universal exception or standalone-playability claim.
