# SkillMenu remaining lifetime, opening and skill assignment

Six original entries restored, 3687 original bytes: constructor 0xbe39e0,
D1/D2 destructor 0xbdfde0, deleting destructor 0xbdfeb0, recursive event mapping
0xbe1600, setOpen 0xbe1130, and handle_SetSkill 0xbe0de0. D0 is strict MATCH;
the other five are accepted only through fresh original/candidate comparisons.
The constructor/map/open instruction sizes match, but unresolved metadata or
other differences remain DIFF; no normalization or acceptance rule was relaxed.
All measured CSkillMenu member entries are now accepted, without alias inflation.

## Runtime comparisons

- Constructor: 64 completed cases with missing/present sound records, two object
  byte patterns and collaborator replacement. Entire object, GUID arrays 0..99,
  array growth 10, sound names/IDs, settings reads, call order and canaries checked.
  52 expected exception unwinds are separately compared, not normal acceptance.
- D1 and D0: 64 completed cases each with all eight tooltip/model/bank presence
  combinations, four child-array shapes and replacement during virtual deletion.
  Deletion order, conditional pointer clearing, array/base cleanup and deallocation
  are observed. 24 expected unwinds are separately checked.
- Event mapping: 2304 completed cases over flat, chain and branching six-window
  trees, every property-presence mask, empty/nonempty values and exceptions from
  property lookup or subscription. These exceptions are caught inside the original
  function, and traversal continues. Postorder recursion, event names, exact member
  pointer and receiver, reference counts and unchanged menu bytes are compared.
- setOpen: 864 completed cases over all four transitions, six pane values,
  absent/detached/attached tooltip, animation state, collaborator mutations and
  one/two repeated calls. Sound/animation parameters, UI ordering, tab visibility,
  tooltip removal, full bytes and canaries checked. 54 expected unwinds excluded
  from normal acceptance.
- Skill assignment: 1296 completed cases cover null window/missing skill,
  effective level, activation class, property/enabled flags, full-width GUIDs,
  empty/Unicode/embedded-NUL/long names and collaborator replacement. By-value
  string copying, copy-on-write detachment and restored reference counts checked.
  45 expected exception unwinds excluded from normal acceptance.

Fourteen compiled intentional defects are rejected by completed differences,
not crashes/incomplete pairs. The final clean focused run passes all 13 tests,
including all 2048 existing layout cases. Layout callback capture adds only the
known set-skill original/replacement identity; wrong-handler substitution still
fails and this-adjustment remains compared.

The aggregate initially exposed an inlining-sensitive creation fixture: its
mapper detour was bypassed after the mapper became visible to the flattened
caller. Creation now exercises the real mapper on both sides with initialized
empty child vectors and controlled absent properties. Dedicated map tests retain
full populated-tree, subscription and caught-exception coverage. All 784 creation
cases and 24 expected creation unwinds remain checked.

A missing nonvirtual Character::setActiveSkillByName(std::wstring) declaration
was added after checking the symbol, original body and its caller. It does not
change Character layout or virtual slots. Fresh prepare-only context was generated
before implementing the caller. Other Character bodies were not changed.

Normal Stage.validate/publish and independent root check.py pass all 227 tests.
All prior accepted addresses remain; exactly these six entries are added.
Total: 1390/5247 functions, 995831 original bytes, 1297 MATCH + 93 behavioral.
These are bounded headless tests; interactive startup/playability was not tested.
