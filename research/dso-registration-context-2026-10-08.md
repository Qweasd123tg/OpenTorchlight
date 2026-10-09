# Compiler DSO registration context, 2026-10-08

The packet preparer treated the original zero-size local __dso_handle at
0xf9f788 as missing game data belonging to Fl_Double_Window.cxx. This is the
last ELF STT_FILE attribution, not a game declaration to restore.

The Itanium C++ ABI DSO destruction API describes the linker-provided handle:
https://itanium-cxx-abi.github.io/cxx-abi/abi.html#dso-dtor
The original CSkillTooltip::showTooltip at 0xaaeeb0 has nine exact registrations
of its translated local-static strings with __cxa_atexit at PLT 0x5551e8.

The correction recognizes only a zero-size LOCAL STT_OBJECT with the exact
__dso_handle identity in the original ELF and a read-only allocated PROGBITS
section. Every reference within the selected function must be the exact
immediate edx/esi/edi registration triple followed by the original imported
__cxa_atexit target. A DB name or disassembly annotation alone is insufficient.
Unsupported sequences retain the previous blocking behavior. This emits an
ABI explanation, never a guessed game declaration or source body.

Six new regression methods cover repeated registrations and 23 identity/sequence
mutations, extra nonregistration uses, and unrelated missing game data.
The focused suite passes 59 tests. On the original 24781-byte skill-tooltip
function, only the false __dso_handle gap disappears. All ten genuine missing
method/global declarations remain blocking and selected headers are unchanged.
No recovered function is added or accepted by this preparation-only correction.

Full verification: 448 tool tests (447 passed, one existing Ghidra/JDK skip),
then 164 headless comparisons/tests passed. Accepted coverage remains
1179 functions / 643054 original bytes. The existing scaffold-only audit
recognizes 15 of 32 packets containing the handle address; all other patterns
remain conservative gaps. This is not a whole-game coverage claim.
