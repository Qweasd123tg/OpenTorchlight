# CStatsMenu::update(float), 2026-10-08

Original ELF: 91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.
Target: 0xc0c4e0, 33659 original bytes, statsmenu.cpp.

The candidate reconstructs the actual menu update in C++98. Its first standalone
and combined-build tests completed 4608 original-versus-compiled comparisons,
with two consecutive frames in each case. Neither a MATCH claim nor a rendered
UI validation is made. Stage publication completed with 156 tests and no failures. It preserves
all previous 1173 accepted addresses and adds this function: 1174 accepted,
508537 original bytes. Independent check.py passed in the combined batch, as recorded below.

## Behavior and evidence

The matrix spans owner/null owner, partial-open/closed flags, twelve statistic
profiles, six UI scales (including signed zero, infinity and NaN), four
translation-cache profiles, and stable/changing collaborator results. It records
ordered calls and final window text, tooltips, visibility, hierarchy, counters,
translation caches, panel coordinates and screen edge.

The original reads both resolution settings even when fully closed. Unused or
reclaimable points show the points controls and queue tip 7. A changed level
label resets all four invested counters. XP and fame bars update only when their
text changes; the fame bar deliberately uses the XP height. Attribute, HP and MP
colours preserve repeated getter calls. Damage tooltips preserve the secondary
weapon tooltip's position before the damage queries. Resistance window offsets
are 0x138/0x140/0x150/0x148 for enum values 5/3/2/4; points use 0x130.

Model animation and three skeletal bone lookups run even without an owner.
Closure waits for both playing and queued CLOSE to clear before hiding the model
and removing the root window. Pinned-SDK virtual-slot probes distinguish the
skeleton bone lookup from a superficially similar SceneManager camera slot.
There are 35 compile-time menu field checks and separately verified skeleton and
entity offsets. The header is explicitly partial; no full allocation size claim.

Six deliberately faulty source variants were rejected with completed differing
observations: wrong fame height, omitted invested-counter reset, swapped
resistance windows, omitted secondary tooltip, omitted model hide, and wrong
screen margin. These are regression sensitivity checks, not additional restored
functions.

## Pinned string helpers

The TU emits Ogre's UTF-8 verifier (0x56bf40), whose machine-code bytes match but
exception metadata is not proven by objdiff. A separate fixture compares 72
valid and malformed inputs, including exception category/message. Another
fixture compares 1800 UTF-16 string _M_mutate cases (0x56b4b0): empty/nonempty,
in-place/growing, shared/unshared, insertion/deletion/replacement. The insertion
span is intentionally uninitialized by that primitive, so both sides initialize
only that span before observing the resulting string, preserved shared copy and
terminator. Both helper fixtures pass in the combined build.

Publication now recognizes the exact pinned libstdc++ UTF-16 _Rep::_M_dispose
EXTRA symbol. Its Itanium Sb substitution was missed by the existing std
namespace template rule. This is not an original game-function acceptance or a
general allowance for Sb members. Tests reject invented string members and
lookalike cleanup symbols; all 421 tooling tests ran, with 420 passing and the
existing Java-dependent skip. The existing gates for changed DIFF bodies,
comparison evidence, missing definitions and unsupported SDK extras remain.

## Unicode limitation

Pinned CEGUI 0.6.2's String::encoded_size(utf8*,len) has an unsafe four-byte branch:
it subtracts two continuation bytes from len while advancing the input by three.
That reads past the input and can inflate d_cplength, exposing an uninitialized
trailing codepoint. The original and rebuilt function both retain this dependency.
The main fixture covers Latin, Greek, Cyrillic and CJK BMP text; supplementary
plane text is excluded from deterministic byte comparison for this documented
reason. The dependency was not silently patched, and uninitialized bytes were
not normalized into a passing result.

## Safety and scope

Only the headless original-vs-compiled selftest is run, exiting before game main.
Original ELF and assets remain read-only. No rendering or full-game fidelity is
claimed. No GitHub push is performed.

## Final validation

The independent root tools/decomp/check.py exited 0 with 157 tests, zero failures.
Final acceptance: 1175/5247, 542082 original bytes; 1149 normalized MATCH and 26
behavioral acceptances. All 941 original baseline addresses remain accepted.
The root tooling suite ran 442 tests: 441 passed, 1 existing Ghidra/Java skip.
Upstream aa472cf8982c0efcb89fbf7203ba64f2e2cfacce was preserved through a clean
three-way merge of 19 files. Every fetched file matches its canonical Git blob
hash. No candidate code from the upstream Luna pilot was installed.
