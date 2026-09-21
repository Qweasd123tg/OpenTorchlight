# Bounded original skill dispatch trace

Evidence prepared before the experiment, ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Source navigation: `decompiled-core/skill.c`; branches checked in the original
`CSkill::startSkill @0xca9150` and `CSkill::triggerEvent @0xca5950`.

`original-code`: execute those two unchanged function bodies, recording calls
to `CSkillEvent::startEvent @0xcc4300`. This is NOT a full-game trace and NOT a
comparison against SkillEventRuntime. The startEvent body is a recording sink;
animation assignment, effective-level calculation, chance and cooldown getters
are controlled callbacks. No scene, missile or HP execution is claimed.

Shared object fields used by the fixture:

| Owner | Offset | Role / observed use |
|---|---|---|
| CSkill | 0x30 / 0x40 | caster / target safe pointers; already assigned |
| CSkill | 0x50..0x58 | copied direction/offset vector |
| CSkill | 0x64 / 0x65 | active / cleared start flag |
| CSkill | 0x90 | property object |
| CSkill | 0xb8 / 0xc0 / 0xc4 | active-event array / count / capacity |
| CSkill | 0xf8 / 0xfc | initialized 1.0 / cooldown |
| CSkill | 0x100 / 0x104 / 0x108 | timer source / copy / reset |
| CSkill | 0x120 | effective level copied into property |
| CSkillProperty | 0x50 | selected level |
| CSkillProperty | 0x58 / 0x64 | event-vector table / capacity |
| Event vector | 0x0 / 0x8 / 0xc | data / count / capacity |
| CSkillEvent | 0x220 | non-null skips event |
| CSkillEvent | 0x140 / 0x14c | clone branch / clone eligibility |

The fixture preallocates event arrays and excludes allocation, eligible clone
creation and safe-pointer reassignment. Native startEvent dispatch occurs
before appending the event to the active list. Event 8 first recursively posts
5; an inactive skill refuses that nested event but can dispatch 8 itself.

`resource-derived`: the first rung of
`media/skills/vanquisher/seeking/SEEKING.DAT.adm` selects **warmup.layout for
EVENT_START**, **seeking.layout for EVENT_TRIGGER**. The resource audit and
native table dispatch are separate evidence: resource objects are not loaded
into the native fixture. Treating seeking.layout as START is a synthetic test,
not proof of the actual SEEKING lifecycle.

Run `tests/trace_skill_events.py --original <ELF> --pak <pak.zip> --output <JSON>`.

Measured 2026-09-19: **15 / 15** cases pass, about 0.2 seconds locally.
Cases cover null caster/property, failed chance, successful start and timer
writes, separate trigger, success without event handlers, inactive/invalid
events, ordered dispatch with blocked/ineligible-clone skips, and event-8
recursion with active/inactive state. The JSON records observed calls, states,
function-body hashes and the resource-entry hash, without pointer addresses.
CTest `original_skill_event_trace` is in `reference` when ELF and game inputs
are supplied. It deliberately does not promote `compared` for the port.
