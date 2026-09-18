# Family packet: `InputLogicEvent`

Members: **41**. Subsystems: other=23, world=7, render_animation=4, interaction=2, items=1, combat=1, audio=1, frontend=1, effects_skills=1.

> Same method name is a batching hint, not proof of identical behavior. Pick a representative, then record every member delta.

## Member matrix

| Address | Class | Subsystem | A | P | W | C | Evidence/source |
|---|---|---|:---:|:---:|:---:|:---:|---|
| `0x005addf0` | `CDescriptor` | other |  |  |  |  | `—` |
| `0x005adeb0` | `CCameraShakeDescriptor` | render_animation |  |  |  |  | `—` |
| `0x005b21f0` | `CCollisionShapeDescriptor` | other |  |  |  |  | `—` |
| `0x005bb7d0` | `CDamageShapeDescriptor` | other |  |  |  |  | `—` |
| `0x005dfae0` | `CItemDescriptor` | items |  |  |  |  | `—` |
| `0x005ea290` | `CLayoutDescriptor` | world |  |  |  |  | `—` |
| `0x006079c0` | `CMonsterDescriptor` | combat |  |  |  |  | `—` |
| `0x006192c0` | `CPathControllerDescriptor` | other |  |  |  |  | `—` |
| `0x006218a0` | `CPositionableObjectDescriptor` | other |  |  |  |  | `—` |
| `0x006258a0` | `CPropertyNodeDescriptor` | other |  |  |  |  | `—` |
| `0x0062ea50` | `CRandomGroupDescriptor` | other |  |  |  |  | `—` |
| `0x0064e290` | `CSoundObjectDescriptor` | audio |  |  |  |  | `—` |
| `0x00652850` | `CUnitSpawnerDescriptor` | world |  |  |  |  | `—` |
| `0x0065f2d0` | `CCounterDescriptor` | other |  |  |  |  | `—` |
| `0x00662e90` | `CInteractiveDescriptor` | interaction |  |  |  |  | `—` |
| `0x00667710` | `CLogicTimerDescriptor` | world |  |  |  |  | `—` |
| `0x0066b2f0` | `COutputIncrementorDescriptor` | other |  |  |  |  | `—` |
| `0x0066ed00` | `CPuzzleRandomizerDescriptor` | other |  |  |  |  | `—` |
| `0x006724e0` | `CRandomChoiceDescriptor` | other |  |  |  |  | `—` |
| `0x00676700` | `CTeleportDescriptor` | other |  |  |  |  | `—` |
| `0x0067d6f0` | `CTriggerDescriptor` | other |  |  |  |  | `—` |
| `0x00684270` | `CUnitTriggerDescriptor` | other |  |  |  |  | `—` |
| `0x0068ef20` | `CWarperDescriptor` | world |  |  |  |  | `—` |
| `0x00693000` | `CAffectorDescriptor` | other |  |  |  |  | `—` |
| `0x006e4040` | `CParticleEmitterWrapperDescriptor` | render_animation |  |  |  |  | `—` |
| `0x006ec830` | `CParticleTechWrapperDescriptor` | render_animation |  |  |  |  | `—` |
| `0x00797b00` | `CLogicGroupDescriptor` | world |  |  |  |  | `—` |
| `0x007bd400` | `CTimelineDescriptor` | world |  |  |  |  | `—` |
| `0x00d979b0` | `CEditorButtonDescriptor` | other |  |  |  |  | `—` |
| `0x00d9d4b0` | `CEditorImageDescriptor` | other |  |  |  |  | `—` |
| `0x00da24c0` | `CAnimationPlayerDescriptor` | other |  |  |  |  | `—` |
| `0x00da7770` | `CCameraControllerDescriptor` | render_animation |  |  |  |  | `—` |
| `0x00dac690` | `CSkipCutsceneDescriptor` | other |  |  |  |  | `—` |
| `0x00dafdd0` | `CGameStateControllerDescriptor` | frontend |  |  |  |  | `—` |
| `0x00dba0b0` | `CQuestControllerDescriptor` | interaction |  |  |  |  | `—` |
| `0x00dbef10` | `CSkillControllerDescriptor` | effects_skills |  |  |  |  | `—` |
| `0x00e5d3a0` | `CMusicObjectDescriptor` | other |  |  |  |  | `—` |
| `0x00e66b90` | `CCinematicDescriptor` | other |  |  |  |  | `—` |
| `0x00e70610` | `CMoneyTakerDescriptor` | other |  |  |  |  | `—` |
| `0x00ea6660` | `CWaypointActivatorDescriptor` | other |  |  |  |  | `—` |
| `0x00eba640` | `CDungeonObjectDescriptor` | world |  |  |  |  | `—` |

## Delta checklist (fill per member; do not infer from the representative)

For each member record: early exits; field writes; constants; loop bounds; resource names; direct/indirect callees; event subscriptions; RNG source/order; ownership/lifetime; error path; side effects; caller wiring.

## Suggested workflow

1. Choose the best-evidenced member as representative.
2. Extract a common skeleton only after comparing at least two members.
3. Encode member differences as data/profile fields when semantics match.
4. Keep exceptions separate instead of growing flags indefinitely.
5. Wire the family into a real scenario before researching another large family.
