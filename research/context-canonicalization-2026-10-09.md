# Canonical standard string signatures and DSO argument order

Reviewed context tool improvement. No game bodies or declarations changed.

The exact-overload lookup correctly rejected missing parameter types, but the
shared parser moved trailing const before expanding the long std::wstring type.
Consequently a genuine `const std::wstring&` declaration did not match the
identical demangled standard basic_string type. Normalize only the two exact
standard char/wchar_t basic_string aliases before parsing, on both existing
source and symbol parameter text. Do not normalize custom traits, allocators,
lookalike namespaces, or modern inline ABI namespaces. Return/static status
remains unproved; parameter/reference/member-CV distinctions remain strict.

The reviewed DSO-handle rule required EDX/ESI/EDI assignment order. The original
updateSlots entry uses EDI/EDX/ESI at0xa99fce..0xa99fd8. Three independent immediate
assignments commute, so accept any permutation only when all three registers
are assigned exactly once, EDX is the exact ELF-proven handle, and the next
instruction calls the actual imported __cxa_atexit. A branch into a partial
setup or the call invalidates recognition. Every handle reference must still
satisfy the rule; no namespace/name-only blanket exception is introduced.

111 focused tests passed, including all six argument permutations and negative
alias, qualifier, ABI, branch-entry and incomplete-assignment cases. A complete
isolated tool-suite tree passed524 tests (523 passed, one existing Ghidra/JDK
skip). An initial symlink-based discovery attempt failed due to module path
identity and was replaced with a real isolated tree; no assertion was skipped.

On original CGameUI::updateSlots(0xa98c20,10237bytes), five gaps become two:
getUnitDataByGuid and getSkillCoolingTime remain genuine missing declarations.
The existing DataGroup and StringUtilities headers are retained; the unrelated
fallback GameNamespaces header is no longer needed. The three removed gaps are
the DSO handle and the two already-declared standard-string functions. The
original entry was inspected, not invoked.

Final root verification:524 tool tests (523 passed, one existing Ghidra/JDK skip) and169 full headless tests passed. Acceptance remains1209 functions /793735 bytes. No game code or acceptance rule changed.
