# Typed generated-test boundaries (Pro N1–N4)

This change fixes the source-level call and observation boundary as one mechanism:

- `ArgumentPlan` carries the declared parameter type, shared call expression,
  deep observations and owned-argument cleanup
- Both calls use the original C++ parameter types. The compiler supplies
  nontrivial value copies/destruction and hidden return storage
- Scalar references receive typed values; wide character buffers are arena-owned
- `std::wstring` arguments are observed by content and destroyed in the parent
  after the paired child calls. Known class arguments reuse the existing field
  observers, including strings and supported list contents
- Return categories are obtained from the exact method signature. A reference
  is observed by arena identity and content without first copying its referent
- External referent identity is unsupported and produces incomplete. This patch
  does not introduce a guessed global/heap identity registry

The old `Void`/`Value` API remains for handwritten tests. It does not retroactively
make every old handwritten test's return observation reference-aware.

## Calibration

`test_autotest_boundaries.py` covers 17 generated signature scenarios, including
value/ref/const-ref strings, signed/unsigned/bool/float references, referents in
and outside the arena, returned strings, void, a class reference with a string
field, and mutable/const wide-character buffers. The two call paths use typed
synthetic reference callees and ordinary C++ candidate methods, not the same
incorrect adapter duplicated on both sides.

Positive controls compare equally; changed references/contents/scalars differ;
unknown external reference identity is incomplete. Each scenario is bounded by
40 cases and stops on the first difference or incomplete observation.

The matrix passed with system GCC 14.2 using the old libstdc++ ABI option, and
with the pinned GCC 4.4.7-3.el6 plus its libstdc++.so.6.0.13. The latter is checked
via the linked binary's resolved library. The host linker and libc are still
used: this is not execution of the original Torchlight process.

On the branch based on main be9f982, the full tools unittest discovery ran 119
checks: 118 passed and one Java/Ghidra compilation check was skipped. Full
`tools/decomp/check.py` was attempted but blocked because the original ELF was
not available. No new accepted game functions or end-to-end speedup is claimed.

## Remaining limits

This is not a universal ABI or object-lifetime model. Complex inheritance,
constructor/destructor variants and thrown exceptions still require targeted
original-process checks. General class field observers retain their existing
layout assumptions and bounds. Arbitrary external handles and custom allocators
are not made observable by this change. Unsupported identities must not count
as successful comparisons. Pro N5 (immediate/address classification) is separate.

## Reconciliation with execution receipts (2026-10-07)

Rebased conceptually onto main `be624aec647c20cec63db283c829cd9e6c616e6e` without replacing its publication recovery, jump-table validation, or receipt mechanism. Generated wrappers now bind an exact `Fn target`, call `beginInvocation(out, target)`, invoke that same typed target, record its exact return category, and mark completion only after the call returns. This avoids template-deduced by-value argument copies while preserving main's registered original/replacement pair validation. The standalone signature matrix registers its exact reference/replacement pairs too.

Validation of this final combined code with pinned GCC 4.4.7 and the original ELF/resources:
- 181 tool tests run: 180 pass, one Java/Ghidra skip
- full `check.py` exits zero; 103 headless tests, zero failures
- 894 game functions MATCH, 52414 machine bytes; 895 accepted including one executed per-function fixture, 53036 machine bytes
- These counts reflect the newer main's stricter jump-table and receipt rules, not newly restored game functions in this patch
- A shared-cache test links pinned non-PIE objects with host g++; explicitly adding `-no-pie` fixes that test's portability on hosts whose default is PIE. Production compiler flags are unchanged

Main already contains the essential prefixed-NOP correction. This reconciliation keeps its implementation, adds the focused padding regression cases, and removes the redundant trailing `xchg` cleanup. N5 immediate classification and mutation-owned data remain separate unresolved work.
