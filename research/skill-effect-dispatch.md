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

## 6. Переносимый срез §6 — PORTED (SkillEventRuntime)

`include/torchlight/skill_event_runtime.hpp`, `src/skill_event_runtime.cpp`,
`tests/skill_event_runtime_test.cpp` (54 assertions with pak / 27 without,
PASS; core 78/78 PASS). Портировано: startSkill гарды/состояние, общий
диспетчер triggerEvent/hasEvent (поддержаны start + missile callbacks 6/7,
остальные 8 типов — явный false), каркас startEvent для missile-пути, ветвь
спавнера Missiles, fire-sink launches (`template_missing`/`spawn_refused`),
постеры MISSILEHIT (damage open) / MISSILEDIE. Стадии в реестре:
analyzed+ported+wired; compared=false (дифференциала с вызовом оригинала
нет, только поведенческий контроль SEEKING).

Найдено при переносе (возвращено в границу, а не угадано):
- SEEKING-спавн идёт НЕ через флаг SPAWN ON CREATE (в ресурсе false), а через
  TIMELINEOBJECT `Spawn Units` при TIMEPERCENT=0.0. Парсер layout расширен
  аддитивно (`LayoutManifest::timeline_points`: timeline/target/input/percent;
  ремап ID при expand_layout_links с lenient-правилом), чекпоинт-идентичность
  не тронута. Runtime: при START выполняются точки ровно 0.0 через ту же
  сцену; точки >0 и висячие — в `take_deferred_timeline_points`, часы
  таймлайна — open.
- SEEKING COUNT=3: в launch едет `spawner_count=3 + repeated_count_open`,
  sink стреляет один раз; мульти-пуск — open.
- Контроль SEEKING проходит всю цепь без прямого вызова missile runtime из
  теста и без подмены хендлера: cast → START → сцена (флаг + t=0 Spawn Units)
  → launch SEEKINGSHOT → sink → MissileRuntime (был пуст) → HIT → MISSILEHIT,
  второй каст → expiry → MISSILEDIE. Урон скилла (applyWeaponDamage/
  applyEffects внутри хука) — без синка, помечен в каждой MISSILEHIT-записи.

Исходный план среза (порядок кода):

startSkill гарды+cooldown+triggerEvent(START) → triggerEvent/hasEvent +
140/14c + CLONE_ALLOWED + рекурсия 8→5 → startEvent каркас (layout start,
applyEffects/applyWeaponDamage/invokeHitSkills, CExecuteSkillProps
прямой/random, addListeners) → applyEffects→leaf → спавнер-ветвь
Missiles→createAndFireMissile→createMissile→createNewMissileRef→fireMissile +
колбэки →triggerEvent(6/7) к существующему CMissile runtime.

Из него сознательно НЕ портировано (следующие кластеры, не долг): клон-ветвь
140/14c + CLONE_ALLOWED, рекурсия 8→5, applyEffects/applyWeaponDamage/
invokeHitSkills тела, CExecuteSkillProps, остальные spawn-типы, часы
таймлайна, оценка шанса/кулдауна из данных скилла, привязка каста к вводу.

## 7. Срез appliers — PORTED (hit-hook SkillEventRuntime)

Порядок хука измерен автором (`cb83d3 canEffect → cb8413 weapon → cb842b
effects → cb8439 hitSkills → cb8463 cmp 6 → cb84a9/cb84c0 trigger(6)`;
постеры invokeHitSkills `cb72f4 UNITHIT / cb738a UNITDIE` с гейтами `cb72b2 /
cb7348`; гарды входа applyWeaponDamage `cb7bb4/cb7bbd`): портирован как
порядок + гейты с портированным смыслом + постеры, не тела вычислений.

Ресурсный путь SEEKING (read-only pak, сверено своим парсером):
`SEEKING.DAT.adm` root SKILL: 12 LEVEL-рунов, каждый — только EVENT_START
(warmup.layout) + EVENT_TRIGGER (seeking.layout, WEAPONDAMAGEPCT,
SOAKSCALEPCT, USEDPS); L1 = 40.0/60.0; EFFECT/AFFIX/DAMAGE записей нет
вообще. Значит нога effects для SEEKING — ресурсно-доказанный no-op, а нога
weapon — скаляры лестницы. `DESCRIPTION='Fires 3 projectiles...'` коррелирует
с COUNT=3, но одновременность трёх пусков не доказана — повторение остаётся
open (без изменений).

Что портировано: загрузчик `load_skill_trigger_levels` (лестница +
effect_entries, present=false вместо дефолтов, отсутствие файла — nullopt);
гейт rung в start_skill (issue `level`, без клампа); привязка rung/caster к
запуску и далее к missile (роль setSkillOwner); последовательность хита —
запрос weapon-ноги (точные скаляры rung, число НЕ вычисляется: контракт входа
будущего бэкенда performAttack/rollAttack), no-op effects-ноги при 0 записей
/ `take_open_effect_legs` иначе, постеры UNITHIT всегда + UNITDIE по факту
смерти от вызывающей стороны (у runtime нет HP), затем MISSILEHIT.
`damage_application_open` остаётся true: открыта именно численность урона.

Семейство (не унифицировано, только каталог callsites): те же appliers зовут
`characterEffectedByDamageShape @0xcc1c40`, `itemEffectedByDamageShape
@0xcb84f0`, `startEvent @0xcc4300` (5× applyEffects, weapon, hitSkills,
2× executeSkill) — общий executor-кандидат на следующий проход по графу.
