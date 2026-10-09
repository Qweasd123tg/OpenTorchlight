# Skill-tooltip full-entry recovery, 2026-10-08

Target: CSkillTooltip::showTooltip(CBaseUnit*, CSkill*, float, float),
0xaaeeb0, 24781 original bytes. Original ELF SHA256:
91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.

## Candidate and evidence

The complete body preserves the existing gameui.cpp definitions and adds the
skill tooltip: parent attachment, lazy translated labels, name/level cache,
current skill details, rank, description, mana, cooldown, packed stat icons,
next-level comparison, usage, requirements, overall sizing, and placement.
Thirty-five compile-time assertions cover both class sizes, 27 tooltip fields,
and six accessed skill fields. Dependency signatures were checked against
original callee assembly and caller argument/return usage. Source is C++98.

Focused full-entry comparison: 5120 completed cases, zero differences and zero
incomplete cases. The 3072 content cases run two consecutive frames each;
2048 additional cases isolate cached placement. This is execution of the
original ELF entry against compiled code, with controlled collaborators, not
self-comparison or acceptance inferred from a PASS label.

Content cases cover current levels 0/1/3/UINT_MAX; empty, one, and multi-level
lists; passive and active skills; zero/positive/negative mana and cooldown;
empty/nonempty translated text, BMP Unicode, repeated empty translations,
equal/different next descriptions, missing/present required skills, zero and
nonzero stat bonuses, NaN bonuses, signed next-index boundaries, and reentrant
changes of level, font metrics, stat offsets, and the global UI receiver.
Cached cases additionally exercise nonfinite/negative viewport and dimension
values, attached/detached windows, and root-window mutation between queries.

Two early probe variants intentionally had no rebuild implementation and were
never published or counted as recovered functions. The complete candidate was
then independently compared on the content matrix. The first content fixture
incorrectly tried to set the invocation marker twice; existing instrumentation
correctly rejected both results. The second frame now calls the same entry
directly, as in the repository's other two-frame tests; completeness gates were
not changed.

## Preserved subtleties

- Recalculate effective level at the original call sites; repeated queries
  can observe collaborator changes. Cache comparison snapshots the old index
  before recalculation, even when the callback changes the tooltip's index.
- Current stat selection uses UINT_MAX only for nonzero effective level,
  enabled state and a false executed-by-property flag. Other cases use level1.
- Next index uses a wrapping 32-bit increment then a signed lower clamp to2;
  replacing this with an unsigned max changes boundary behavior.
- Only the first four of six bonus values are displayed, packed into four
  slots. Percentage text uses ceilf(100*bonus), then signed integer formatting.
  Current stat rows add6 pixels; next-level rows add4, and their final block
  adds another6. These constants are intentionally not unified.
- Font extent/line-count call order differs between rows. Next heading is
  positioned before setText; ordinary rows do text before position. The next
  description may be fetched a third time after comparison.
- The rank denominator uses field0x158, then level-list count, then1. Next-level
  availability instead uses the level-list count; it does not use that rank cap.
- The instance UI pointer is used for some scaling/image calls, but placement
  and final padding read the TU-global singleton. It is reloaded between
  callbacks. A completed differential failure caught compiler hoisting in the
  reduced TU; a volatile pointer declaration preserves the observed loads.
  This preserves behavior/ABI, not a claim about the lost source's qualifier.
- Mana uses colon without an inserted space; next heading uses space-colon-space.
  Passive skills show Always Enabled in the mana row, then still query cooldown.
- Placement uses UDim::asAbsolute(1), 26-pixel margins, and the original
  float-to-long-to-unsigned viewport conversion and asymmetric left/top fallback.

## Limits

No rendered game/window was launched. Files, original ELF and assets remained
read-only. Font, window, skill and translation collaborators are intercepted;
this verifies the entry's observable orchestration, not the renderer itself.
The matrix includes BMP Unicode, not the known broken four-byte UTF8 path in
CEGUI0.6.2. Behavioral comparison does not claim normalized byte MATCH.

The full Stage and independent repository check passed, as recorded below.

## Final validation

Stage publication and the independent root tools/decomp/check.py both pass:
166 tests, zero failures, exit 0. Acceptance is 1180/5247 functions, 667835
original bytes: 1149 normalized MATCH and 31 behavioral acceptances. This adds
one address and 24781 bytes to the previous 1179-function result. Eight negative
controls were rejected with completed differences. No remote push was performed.
