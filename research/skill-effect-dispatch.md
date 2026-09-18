# Skill effect/event dispatch — исполнительный слой (разведка, не перенос)

ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Статус: analyzed (агент-разведка + точечная сверка ASM/ресурсов автором);
ported/wired/compared = false. Смещения структур — только навигация из
декомпа, контрактом не считаются.

## 1. Цепочка (каждое звено измерено)

```
doWeaponSkill @0x8245c0 :824860 call cd4930
  (или performSkill @0x827b20 / executeProcs / trigger — те же →cd4930)
→ CSkillManager::executeSkill(CSkill*) @0xcd4930 :cd49f5 call ca9150
  (альтерн. executeSkill(wstring) @0xcd45c0 :cd47d2 call ca9150)
→ CSkill::startSkill @0xca9150 :ca92d1 call ca5950 (esi=EVENT_START=0)
→ CSkill::triggerEvent @0xca5950 → CSkillEvent::startEvent @0xcc4300
→ CLayout::start + спавнер-сцена (timeline «Spawn Units»)
→ CUnitSpawner::spawn @0xa17780 / update @0xa17830
→ spawnUnitByIndex @0xa167a0 :a16c8a compare, fallthrough :a16cb4 call a0adc0
→ CUnitSpawner::createAndFireMissile @0xa0adc0
     :a0add9 call createMissile @0xd6f520
     :a0ae8c jmp fireMissile @0xd04610 (tail-call!)
→ CResourceManager::createMissile @0xd6f520 :d6f550 jmp d0b0d0 (обёртка)
→ CMissilePreloader::createNewMissileRef @0xd0b0d0
→ CMissile::CMissile @0xd05fb0 / initialize @0xd00650
→ CMissile::fireMissile @0xd04610 → существующий runtime
→ обратные хуки missileBeingFired @0xcc0ce0 / missileApplyingEffects @0xcb8360
  / missileDieing @0xcb7670 → triggerEvent(6/7) → startEvent hit/die-подлейаутов
```

Проверено автором в objdump: `a0add9`, `a0ae8c jmp d04610`, `d6f550 jmp
d0b0d0`, `cb77e9 mov $0x7 + cb7804 call ca5950`,
`cb8413 call applyWeaponDamage + cb842b call applyEffects + cb84a9 mov $0x6
+ cb84c0 call ca5950`, `ca9178/ca91b0/ca91be/ca91c6/ca91ce/ca91d3` гарды
startSkill, ветка `a16c8a/a16c9e/a16cb4`. Ресурс: SEEKING.LAYOUT.adm содержит
`Unit Spawner0 / SPAWN ON CREATE / Missiles / SEEKINGSHOT / Spawn Units`,
`media/Missiles/SEEKINGSHOT.LAYOUT.adm` существует (контрольный представитель).

## 2. Общий executor + подтверждённые различия

- `CSkill::startSkill @0xca9150`: гарды (caster null, `+0x90` null), сброс
  `+0x65`, `assignSkillAnimations @0xca4a00`, `calculateEffectiveSkillLevel
  @0xca7740`, `rollSkillChance @0xc9db70` (fail → return 0), safe-pointer swap
  caster/target, cooldown-инит, `triggerEvent(this, START)`.
- `CSkill::triggerEvent @0xca5950`: индексный диспетчер (`cmp $0xa`,
  `shl $3 + prop+0x58`), ветвь `+0x140==0 → прямой startEvent`, иначе
  `+0x14c==0 → skip`, иначе очередь клонов + `cloneEventForSkill @0xcdd240`;
  рекурсия `DIEBYEFFECT(8)→UNITDIE(5)`; `gSKILL_EVENT_TYPE_CLONE_ALLOWED
  @0xff4fe8` = `00 00 01 01 01 01 01 00 00 01 00`.
- `CSkillEvent::startEvent @0xcc4300`: layout start + `applyEffects @0xcb7850`
  / `applyWeaponDamage @0xcb7b70` / `invokeHitSkills @0xcb7290` /
  `CExecuteSkillProps::executeSkill @0xc938e0` (skill-chain: `c939f6 call
  cd4930`, НЕ missile) + `addListeners @0xcc3aa0` (DamageShape/UnitSpawner;
  missile-регистрации нет — missile идёт через спавнер).
- Leaf: `CSkillEffectAndAffixes::applyAffixesAndEffects @0xcac040` (вызовы из
  `applyEffects`: `cb78fd`, `cb7b05`).
- Различия как данные: `CLONE_ALLOWED[11]`, имена spawn-типов,
  per-hook гейты (`+0x48==6/7`, `+0x28!=0`), per-event постеры (§3).

## 3. Каталог EVENT-типов (имя → постер; поведение beyond диспетчеризации — open)

11 имён (`gSKILL_EVENT_TYPE_NAMES`, bss 11×8): START 0, END 1, TRIGGER 2,
TRIGGER_TWO 3, UNITHIT 4, UNITDIE 5, MISSILEHIT 6, MISSILEDIE 7, DIEBYEFFECT 8,
CASTERDIE 9, UNIT_CREATE 10. Постеры (callsite → event): START `ca92d1`;
END `stopSkill ca6035`, `updateSkill ca63b5`; TRIGGER/TRIGGER_TWO
`updateSkillKeys 8117c2/811994`; UNITHIT `invokeHitSkills cb72f4`;
UNITDIE `invokeHitSkills cb738a`, `applyWeaponDamage cb826c`, рекурсия `ca5dbb`;
MISSILEHIT `missileApplyingEffects cb84a9`; MISSILEDIE `missileDieing cb77e9`;
DIEBYEFFECT `applyInstantEffect 8432b2`, `unitStateChange ca5f2f`;
CASTERDIE `fireSkillsOnDeath cd53fb/cd52a7 → triggerSkillEvent @0xccacb0`;
UNIT_CREATE `fireSkillsOnCreate cd551e (гейт hasEvent @0xc9ccf0) →
triggerSkillEvent`. Все triggerSkillEvent-постеры идут через `ccad40 call
ca5950`.

## 4. Поправка к do-weapon-skill.md §3 (важно)

`fireMissile` имеет ДВА кода-рефа, не один: `87f56f call d04610` (equipment
путь) и `a0ae8c jmp d04610` (tail-call из спавнера). Ранний поиск только
`call` пропустил `jmp`. Аналогично `createNewMissileRef`: `87f3d0 call` +
`d6f550 jmp`. Вывод «skill-проектайлы идут через effect engine → спавнер →
тот же CMissile runtime» — подтверждён, путь найден (§1).

## 5. Open (не придумывать)

Точный timeline-`Spawn Units`→`spawn` callsite внутри skill-layout; слоты
`iMissile` vtable→хуки (прямых call нет, только indirect); семантика фильтра
`triggerSkillEvent` (`getTargetType<=6`); поведение
TRIGGER/TRIGGER_TWO/CASTERDIE/UNIT_CREATE/END beyond диспетчеризации;
условия затухания `updateSkill→updateEvent→startEvent`; остальные spawn-типы
beyond имён; тождество строки по `0x14abf60` — agent-read из декомпа
(форма ветки `a16c8a/a16c9e/a16cb4` проверена, имя нет).

## 6. Следующий переносимый срез (по коду, SEEKING — контроль)

startSkill гарды+cooldown+triggerEvent(START) → triggerEvent/hasEvent +
140/14c + CLONE_ALLOWED + рекурсия 8→5 → startEvent каркас (layout start,
applyEffects/applyWeaponDamage/invokeHitSkills, CExecuteSkillProps
прямой/random, addListeners) → applyEffects→leaf → спавнер-ветвь
Missiles→createAndFireMissile→createMissile→createNewMissileRef→fireMissile +
колбэки →triggerEvent(6/7) к существующему CMissile runtime.
