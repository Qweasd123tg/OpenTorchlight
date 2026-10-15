# Archived small-function recovery, 2026-10-15

The final canonical check passed: **903 headless tests, zero failures**.
Acceptance is **3062 / 5,247 game addresses**: 2344 MATCH and
718 BEHAVIORAL. All 2,979 addresses accepted at `bd6a514` remain
accepted, and every previous strong MATCH remains MATCH.

This batch adds **83 exact MATCH game addresses**, covering 5103 original
bytes: all 82 selected archive-backed methods plus the existing editor-manager
destructor, whose original code shape is recovered by explicitly instantiating
its existing array destructor. ABI aliases at one original address count once.
Weak library/template/compiler helper emissions receive no game credit.

## Restored code

- EditorObjectManager: selected pivot/working plane, snapping settings, highlighting,
  event forwarding, editor update, and construction.
- Particle wrappers: flipbook/ribbon/sorting settings, local-space propagation,
  dynamic property conversion, and PropertyNode methods.
- SkillManager and SkillProperty: skill lookup, levels, activation/count/point access,
  enablement, deletion, and owning-unit access.
- DynamicPropertyFile: typed value access, callbacks, non-local lookup and file fallback.
- Descriptor callbacks: inverse string-to-ID lookups using the original tables
  restored by the previous batch; emitter-wrapper creation.

The archive bodies were transferred selectively into current full TUs. Old TUs
were not overwritten wholesale. 91 existing explicit definitions in the
changed TUs are byte-for-byte preserved. Four previously absent source TUs were
added; the final build contains 285 production TUs.

## Layout and preparation fixes

Opaque regions are named only where the original ASM establishes their use.
Editor-control padding splits preserve offsets. Particle-technique and ribbon
pointer unions preserve existing member representations. CSkill remains 0x160,
CSkillManager 0x98 and CDynamicPropertyFile 0x140; the candidate asserts also
check fifteen used member offsets. Dynamic-property vectors/string fields and
pointer-returning particle getters now use the ABI required by their accessors.
The spawn-order string-to-ID callback is static unsigned int, as shown by its
rdx value argument and eax result.

The editor constructor exposed a preparation gap: the generic TArrayList destructor
already existed, but the resolver's reviewed exact-instantiation table omitted
TArrayList<CEditorBaseObject*>. The added entry is limited to original address
0x740b90, size 26, both weak D1/D2 aliases, and the existing pinned header SHA.
Unknown specializations, changed bodies, mismatched ELF/DB identity and stale
snapshots still fail closed. The resolver module's 157 tests pass.

Library call-only class declarations stay local to the two owning source files.
Shared headers keep opaque pointer declarations, so type export does not mistake
an empty call-only definition for a complete one-byte ParticleUniverse layout.
Moving the declarations out of the temporary shared header left both complete
object digests unchanged. Types were exported from the final headers after the
final static MATCH inventory.

The registration fixture now recognizes the exact original/linked aliases of the
restored missile inverse callback. Its regression keeps the two missile callbacks,
unrelated callbacks, unknown pointers and null distinct. Five targeted identity
and registration tests passed before the full suite.

## Evidence and scope

`functions.json` lists every newly accepted game address and its final full-object
digest. `objects.json` pins all production objects; `source-preservation.json`
records unchanged definitions, and `validation.json` records the baseline, counts
and fresh comparison-input digest. Test summaries accompany them.

The unchanged original ELF is
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Current GCC 4.4.7/C++98 comparisons, not historical archive labels, establish MATCH.
Historical helper DIFFs are not promoted or included in game acceptance.

This validates the headless hybrid and the addressed functions. Windowed gameplay
and a standalone complete game were not evaluated.
