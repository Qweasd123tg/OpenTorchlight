# Equipment skill text

`CEquipment::skillDescription()` at `0x87e640`, 2771 original bytes.
Original ELF is the pinned `91b41ae9...5d41724b` input; GCC 4.4.7.

The implementation follows the assembly, including two distinct loops:

- Snapshot SKILL_TO_GIVE child groups, with NAME then DISPLAYNAME fallback.
  An explicitly empty DISPLAYNAME overrides NAME. Child LEVEL falls back to
  the current root LEVEL, then 1. Values are signed when formatted.
- Re-evaluate the current skill manager's ANY count on each iteration and
  fetch from its TArrayList. Enabled, non-property skills receive this item,
  UINT_MAX and true in getDescription.
- Each loop uses its own index for separators. A first manager description
  directly follows existing group text; a later eligible skill can introduce
  a leading newline even if previous skills were skipped. This is intentional
  compatibility with the original, not a whitespace cleanup.
- The translated Level label is cached while nonempty. Empty translation
  causes another lookup on the next call.

`EquipmentSkillDescriptionTest.cpp` compares 3500 cases, twice per side,
using real DataGroups, strings, TArrayLists and the original knownSkills.
Only translation and skill-description collaborators are redirected. Captures
include output with length-preserved NULs, service calls and arguments, list
counts and manager changes. Cases cover absent/empty/display names, unrelated
child groups, root/child level fallback, signed limits, independent group and
manager presence/count dimensions, all enabled/property flag combinations,
empty/multiline/markup/Unicode skill text, cold/warm translation, and callbacks
that grow/shrink the list or switch the current manager.

Sampled mutation pass: 18/20 viable killed (22 candidates probed). Two survivors
alter the defensive index guard (`i != UINT_MAX` to `i != UINT_MAX-1`, or AND to
OR). For valid small lists the enclosing count-controlled loop already implies
that guard; these are not counted as kills. Gigantic corrupt counts, null skill
entries, exceptional allocation behavior and actual skill text generation are
not validated by this fixture. The original reads flags before its null check;
invalid both-crash cases are not accepted as successful comparisons.

The isolated run and targeted mutation scripts change only scratch copies.
Full integrated checks are recorded separately in decomp/README.md.
