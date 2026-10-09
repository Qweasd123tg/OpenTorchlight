# Pass6 / pass7 independent intake, 2026-10-09

## Inputs and reproducibility

The immutable MATCH kit is based on 824e3d3a33242c9ea775ca8a5ff36e87d6fd23ee.
Its ZIP SHA256 is 118c87228c8dade99f2efe9b010320f33c0afcde424b87d5bfbb7e2c2436b569;
all 5942 listed file hashes were checked. The original ELF SHA256 is
91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b.

Pass6 ZIP SHA256: 63ff5b635284c70c7046bd4090e9feab2e1c1b15529abf7d0c7877123d62bcd7.
Pass7 ZIP SHA256: ab2053de2e8d4002fb85e18e168a1607e49ad9ea92161a48ac952c813f16ebd3.
All 970 and 1172 package manifest entries were checked, respectively.

After authorization and source review, each package's reproduce.py ran in a
separate new copy of the immutable kit with the pinned GCC 4.4.7-3 compiler.
No original executable, generated fixture executable, or game was run by these
reproducers. The environment was reduced to the needed paths and compiler
settings; this is not a claim of an OS-level network sandbox.

Both full reproductions passed. All 60 / 67 candidate source files and
23 / 31 package headers reproduced exactly. Their own comparison pipelines
reported 483 / 523 cumulative addresses, with no baseline or preceding-pass
regressions. These cumulative package totals must not be added to the current
project's accepted count. The supplied tests passed: 111 smallmatch and 114
objdiff tests, 225 total.

## Independent comparison

The unchanged current project comparator independently compiled all 67 pass7
candidate TUs with the reproduced package headers. No imported comparator was
loaded for this check. All 40 new pass7 addresses and 59 of the 61 new pass6
addresses passed. Two were deferred because the existing fail-closed literal
width check could not certify the linked data:

- 0x869b60: CCollisionModel::unloadModel()
- 0xc62f90: CDataValue::GetValueTypeAsString()

This initial check proves neither current-header compatibility nor the final
integration. All 99 initially selected addresses also passed with the current project's
headers after selective integration, with every previously matched address
preserved. The final publication gate nevertheless refused the first attempt:
14 additions share translation units with old, still-unaccepted DIFF bodies.
Appending a definition changes the complete object digest. No fresh behavioral
comparison certifies those old bodies, so their files must remain unchanged.
The guard was retained; no per-instruction similarity was substituted for it.

The reduced integration consists of 84 definitions / 85 original addresses and
5130 original machine-code bytes. Strict Stage validation and the independent root check both passed all 177
headless tests. The transaction verified the published object identities.
The branch now accepts 1298 / 5247 game functions, 858553 original bytes:
1255 normalized MATCH and 43 behavioral acceptances. These 85 additions are
normalized MATCH; the comparison implementation remains unchanged.

The following 14 already-MATCH additions are saved for a later integration with
fresh evidence for the older bodies in their complete translation units:

- 0xe73a10: CCinematics::getCinematic(unsigned int)
- 0x5dfc10: CItemDescriptor::DescriptorObjectBeingDeleted(CEditorBaseObject*)
- 0x607e50: CMonsterDescriptor::DescriptorObjectBeingDeleted(CEditorBaseObject*)
- 0x63d3f0: CRoomPieceDescriptor::DescriptorObjectHasBeenInited(CEditorBaseObject*)
- 0x63d380: CRoomPieceDescriptor::update(float)
- 0x67d770: CTriggerDescriptor::update(float)
- 0x7cd430: CAffix::updateAffixDuration(float)
- 0x65f2d0: CCounterDescriptor::InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*)
- 0x7eba30: CEffectManager::clearOutDescriptions()
- 0xc77c30: CGameSpeed::getGameSpeed()
- 0x6258a0: CPropertyNodeDescriptor::InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*)
- 0xe20690: CSkillController::unlearnSkill()
- 0xa08070: CSoundObject::reset()
- 0x67d6f0: CTriggerDescriptor::InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*)

## Imported literal-flow checker: four negative probes

Both packages contain byte-identical objdiff_literal_flow.py. The following
static adversarial sequences retain character-width evidence when they should
reject it. These are confirmed evidence-tracker defects, not a demonstrated
false MATCH for a real Torchlight function.

Common prefix for the first three cases:

    mov $0x4000,%ebx
    mov %rbx,%rdi
    call wcslen

Then one of:

    mov $0x10,%bl
    mov $0x10,%bx
    xor %bl,%bl

Followed by:

    mov %rbx,%rax
    pop %rbx
    ret

Partial writes retain upper pointer bits. The tracker drops the full register
origin, misses the later returned derived pointer, and retains the earlier
NUL-consumer witness. A partial overwrite must invalidate that origin rather
than silently forgetting its subsequent uses.

The fourth probe is an implicit length clobber:

    mov $0x4000,%edi
    call wcslen
    mov %rax,%rdx
    cltd
    mov $0x4000,%esi
    call std::wstring::assign(wchar_t const*, unsigned long)
    ret

CLTD/CDQ writes EDX implicitly. The tracker retains the old exact-wcslen length
proof because it only scans explicitly mentioned registers. Consequently it
admits the second materialization as a bounded NUL read without a valid length
proof. Unknown implicit register effects need fail-closed handling.

The existing project comparator is retained unchanged. No package claim is
accepted by importing these permissive normalization rules.

## Integration scope

Based on PR #12, commit 9acac9659f0bb9e5f5334e7c48c71aa3507a6bf3.
This is a selective 17-TU / 13-header transfer, not the cumulative old-base patch.
Current declarations and every pre-existing MATCH were retained. In particular,
Level::addItem, the current resource-manager declarations, and the inventory
return-type correction were not overwritten. No StringUtilities implementation
or UTF8 interface was changed. Header additions needed only by deferred methods
were omitted. Existing include/static-initialization order was preserved.

Package comparator changes are excluded. The 483/523 cumulative package totals
and the 225 package tests are reproduction evidence, not additional accepted
functions or substitutes for the strict current-project gate. No merge, windowed
game launch, or standalone-game completion is claimed.
