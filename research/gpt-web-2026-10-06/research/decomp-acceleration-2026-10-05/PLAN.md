# Bounded acceleration experiment

Approved direction: improve the conveyor using a measured experiment on several
large, unaccepted game functions. Do not launch additional coding agents. Do not
modify another worker's source TUs or replace the existing accepted baseline.

## New gap to test (not yet a performance claim)

Incoming 2464d59's types_export.py maps header prototypes only to db.functions.
The current export has 3167 prototypes, 106 with Ogre/CEGUI names, but ZERO
prototypes at the 1004 imported PLT addresses. CEGUI::Window is absent from its
class layouts. During GameUI recovery, imported return types/hidden-return and
UTF-8 constructor overloads required manual correction.

Hypothesis: exporting exact prototypes from the pinned Ogre/CEGUI SDK for the
imported functions improves Ghidra output for large callers. This is distinct
from redoing the newly delivered in-project prototype export. It may prove
unhelpful; compiler success or shorter output alone will not count as correctness.

## Protocol

1. Verify incoming pipeline against current accepted code, including the old
   throw/catch reproducer; preserve the separate merge/deduplication record
2. Inventory large unaccepted functions in the fresh draft packet, recording
   timeouts, original sizes and imported call sites; select a small fixed set
3. Export SDK declarations using original GCC/DWARF, matching exact mangled names;
   record provenance and check ABI-sensitive return shapes before application
4. Compare baseline and enriched Ghidra export on the SAME saved analysis project
   with the SAME timeout/payload settings. Record wall time and failed exports
5. Compare call arguments/return shapes to disassembly/compiler probes and count
   exact verified fixes, regressions, remaining unknowns and compilation outcomes
6. Report a measured result or a negative result. Do not claim game-wide speedup
   or fewer human hours without actually measuring those quantities

The GameUI draft and its verification gaps remain preserved separately.
