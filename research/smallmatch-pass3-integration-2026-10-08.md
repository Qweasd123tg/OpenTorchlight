# Integration of user-supplied smallmatch pass3, 2026-10-08

Input: OpenTorchlight-smallmatch-pass3-2026-10-08(1).zip
SHA256: 040499c5ae283cb35c5f1714f7a3bb70dd1fdd137eb76e2f2b43a4f686247b62
All591 manifest hashes were checked; the separately supplied text report is
identical to REPORT_RU.txt. The cumulative patch was not blindly overlaid on the
current tree. The bounded after-pass2 delta was reviewed and transferred into a
fresh isolated Stage, retaining all prior large-function and tool improvements.
No ownership assignment was changed.

The independent pinned-GCC comparison confirms all21 incremental addresses as
normalized MATCH,2321 original bytes, from18 new C++ definitions across five
classes. They were all absent from the previous1187-address acceptance set.
The compiler-generated deleting destructor variants explain the address count.
The34 layout assertions and both new classes' complete vtable/RTTI checks passed.

The supplied tooling adds evidence-only container discovery, reviewed type/layout
manifests, repeated whole-TU pruning of DIFF recipes, and explicit vtable/RTTI
verification. Map versus multimap requires unique-insert evidence; a tree
destructor alone is not promoted into a unique-key map. Original game assets
and the original executable remain read-only. No provider/model calls were made.
The current objdiff/exception rules were not replaced or relaxed by this delta.

Full tool suite:496 tests,495 passed and one existing Ghidra/JDK skip. Full Stage
and independent root check.py:168 headless tests passed,zero failures.
Final acceptance:1208 of5247 functions,783251 original bytes;1170 normalized
MATCH plus38 behavioral acceptances. All previous1187 addresses are retained.
The22 newly recovered large functions remain22; these18 small definitions are
user-supplied additional work, not newly authored large functions.

This integration does not include the separate private StatsMenu::createMenus
candidate or a correction of the known StringConvertUTF8ToWide C++ return-type
problem. Neither is counted as accepted here. No GitHub push was performed.
