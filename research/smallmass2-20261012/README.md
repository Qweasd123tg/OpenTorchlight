# Smallmass2: персонажи, AI, инвентарь и состояние игры — 12 октября 2026

Добавлено **44 новых адреса оригинала**, соответствующих **42 определениям C++98** и двум автоматически сгенерированным удаляющим деструкторам (D0). Объём исходного машинного кода этих адресов — **23 213 байт**.

Общая приёмка: **2751 → 2795 из 5247 функций**. Все 2751 прежних принятых адресов сохранены.

Исходная handoff-ветка: `3a72c325996de885ffed2995d1490768eddf008c`. Её деревья `decomp/` и `tools/decomp/` совпадают с `main` после PR101 (`cd9af3912a1117937655a5db023569c98f268142`). Поэтому пакет можно переносить на эту базу main без переноса архивных handoff-материалов.

## Состав

| Исходный TU | Определения C++ | Адреса оригинала | MATCH | Поведенческая приёмка |
|---|---:|---:|---:|---:|
| `Console.cpp` | 4 | 4 | 0 | 4 |
| `GameGlobals.cpp` | 2 | 3 | 3 | 0 |
| `Inventory.cpp` | 3 | 3 | 0 | 3 |
| `ObjectControl3D.cpp` | 3 | 3 | 1 | 2 |
| `character.cpp` | 17 | 17 | 3 | 14 |
| `charactersavestate.cpp` | 2 | 3 | 3 | 0 |
| `monster.cpp` | 6 | 6 | 0 | 6 |
| `player.cpp` | 5 | 5 | 1 | 4 |

- **Персонажи:** изучение заклинаний; обновление и завершение активного навыка; управление целью; направление на цель; перемещение, телепортация и постановка на землю; эффекты попадания и рыбалки; анимации AI; поиск пути по имени; удаление питомцев; смена типа персонажа.
- **Монстры:** наличие и выбор атакующих/защитных навыков; инициализация времени между атаками; поведение во время анимации FIDGET.
- **Инвентарь:** запуск навыков от эффектов экипировки; экипировка в заданную позицию; переключение основного и запасного оружия с исходным порядком уведомлений.
- **Игрок:** стартовые расходники, сброс характеристик и навыков, запись и загрузка сведений о подземелье.
- **Состояние игры и редактор:** конструкторы и деструкторы CGameGlobals/CCharacterSaveState, отображение шаблона чанка и два пересечения с плоскостью.
- **Консоль:** выдача навыка, переключение ускорения, тряска камеры, создание существ по классу спауна.

## Существенные детали оригинала

1. Конструкторы используют шаг роста **10** у внутренних TArrayList. Значение по умолчанию у восстановленного шаблона — 2; явное значение 10 довело оба конструктора до MATCH.
2. Выбор навыков сохраняет отдельные проверки начальной и постоянной стоимости маны, перезарядки, свойства текущего уровня, типов цели, enabled/executed-by-property и принадлежности цели к стороне. Выбор атакующего навыка восстанавливает прежний навык, когда список подходящих вариантов пуст; защитный выбор имеет другую ветвь завершения.
3. В `performingSkillAI` оригинал получает позицию через ссылку на целевого персонажа даже в ветви, где в проверку дальности передаётся предмет. Это поведение сохранено; соответствующий указатель может быть нулевым. Сравнение изолирует вызванные зависимости и проверяет именно наблюдаемый порядок вызовов. Это не утверждение о безопасности такого состояния при живом запуске игры.
4. Перемещение сохраняет снятие объекта с карты избегания препятствий, повторную попытку проверки проходимости после сдвига начальной точки на 0,4 и восстановление участия в карте только при исходном включённом состоянии.
5. `CDungeonTracker::load` читает дополнительные поля при версиях больше 2 и больше 5. Загружаемые записи добавляются к существующему вектору; предварительного очищения в оригинале нет.
6. `swapWeaponSet` запоминает четыре ссылки перед изменением слотов. Вызовы equipped/unequipped и уведомления слушателей идут в исходном порядке; затем пересчитываются бонусы и эффекты.
7. Сохранены граничные сравнения с float, включая обработку NaN в направлении на цель, времени навыка и вероятности срабатывания эффекта. Имена полей, которым не удалось приписать точный смысл, оставлены нейтральными.

## Проверка

- Новые функции: **11 MATCH** и **33 BEHAVIORAL** по уникальным адресам.
- Написаны четыре групповых файла сравнений и общий вспомогательный заголовок: 33 адресных теста, **5472 завершённых пар** вызовов оригинала и замены, без расхождений и незавершённых пар. Совпавшее падение не считается успешным сравнением.
- Полный финальный прогон: `tlhybrid: 773 tests, 0 failed`.
- Общий результат снимка: **2197 MATCH + 598 BEHAVIORAL = 2795**.
- Публикация выполнена через `Stage.validate()` и `Stage.publish()` на одном экземпляре Stage. После проверки исходники не редактировались.
- Побайтно проверены конечные объекты всех **280** производственных TU; отпечатки входов корневого checkout и Stage совпали.
- Использован закреплённый тулчейн проекта: GCC 4.4.7 / C++98, исходные флаги оптимизации проекта. Отдельные изменения инструментов не входят в пакет.
- SHA-256 оригинального ELF: `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`. Бинарник и ресурсы игры в коммит не включены.
- Проверка ограничена objdiff и headless-гибридом. Оконный запуск, прохождение игры и самостоятельный запуск без оригинального бинарника не проверялись.

Фактические результаты: [validation.json](validation.json), [полный журнал самотеста](selftest.log), [хеши производственных объектов](objects.json), [адреса и выполненные сравнения](functions.json).

## Что не вошло в приёмку

- Прежние 70 адресов локального пакета `076a8890` исключены из выбора и не пересекаются с текущей пачкой. В доступной GitHub-базе их исходного локального коммита нет; этот пакет не заявляет их восстановление.
- Разобраны `SetPetsEnabled` (`0xaec900`) и `createEquipmentAndEquip` (`0x8132f0`). Оба символа имеют локальную связь в исходных TU. Текущий hybrid loader выдаёт unresolved import при попытке их подмены; они отложены и не входят в 44 адреса. Инструменты загрузчика ради этого пакета не менялись.
- PR100/save и приостановленное направление B definition/parser не изменялись.

## Адреса

| Адрес | Функция | Приёмка | Байты |
|---|---|---|---:|
| `0xaef6b0` | `CConsole::cameraShake(std::wstring)` | BEHAVIORAL | 506 |
| `0xaef980` | `CConsole::spawnClassCreate(std::wstring, std::wstring, std::wstring)` | BEHAVIORAL | 558 |
| `0xaf15c0` | `CConsole::equipSkillToPlayer(std::wstring)` | BEHAVIORAL | 298 |
| `0xaf16f0` | `CConsole::addSpeedToPlayer()` | BEHAVIORAL | 598 |
| `0xa51440` | `CGameGlobals::CGameGlobals(wchar_t const*)` | MATCH | 710 |
| `0xa51710` | `CGameGlobals::~CGameGlobals()` | MATCH | 1543 |
| `0xa51d20` | `CGameGlobals::~CGameGlobals() [D0]` | MATCH | 18 |
| `0x91c720` | `CInventory::executeProcs(EEFFECT_TYPE, CBaseUnit*)` | BEHAVIORAL | 688 |
| `0x9256a0` | `CInventory::equipEquipmentIntoSpecificLocation(CEquipment*, EEQUIP_LOCATIONS)` | BEHAVIORAL | 715 |
| `0x925d30` | `CInventory::swapWeaponSet()` | BEHAVIORAL | 710 |
| `0x774330` | `CObjectControl3D::UpdateChunkTemplate()` | MATCH | 470 |
| `0x774b80` | `CObjectControl3D::getMousePlaneInstersect(POINT, Ogre::Plane)` | BEHAVIORAL | 474 |
| `0x7750e0` | `CObjectControl3D::getCameraPlaneIntersect(Ogre::Plane)` | BEHAVIORAL | 498 |
| `0x80f930` | `CCharacter::learnSpell(std::wstring, int)` | BEHAVIORAL | 342 |
| `0x80feb0` | `CCharacter::dropToGround(CLevel&, float, bool)` | MATCH | 554 |
| `0x813ba0` | `CCharacter::updateActiveSkill(float)` | BEHAVIORAL | 693 |
| `0x815910` | `CCharacter::damageDefense(EDAMAGE_TYPES)` | BEHAVIORAL | 265 |
| `0x825310` | `CCharacter::setTarget(CCharacter*)` | BEHAVIORAL | 408 |
| `0x827310` | `CCharacter::playHitParticle(Ogre::Vector3 const&, Ogre::Vector3 const&, float)` | BEHAVIORAL | 461 |
| `0x8274e0` | `CCharacter::facingTarget(CCharacter*, CItem*)` | BEHAVIORAL | 524 |
| `0x827890` | `CCharacter::teleportToMaster(float)` | BEHAVIORAL | 650 |
| `0x829f60` | `CCharacter::moveToPosition(Ogre::Vector3 const&, bool, bool)` | BEHAVIORAL | 584 |
| `0x82a750` | `CCharacter::fishingSplash()` | MATCH | 484 |
| `0x82e750` | `CCharacter::setAIPlayAnimation(std::string const&, bool, float, float)` | BEHAVIORAL | 589 |
| `0x835520` | `CCharacter::removePet(std::wstring)` | BEHAVIORAL | 436 |
| `0x836820` | `CCharacter::spawningAI(float, CLevel&)` | BEHAVIORAL | 607 |
| `0x836a80` | `CCharacter::setPathToFollowByName(std::wstring const&)` | BEHAVIORAL | 549 |
| `0x83c4f0` | `CCharacter::attemptStopOfActiveSkill()` | BEHAVIORAL | 375 |
| `0x83c730` | `CCharacter::performingSkillAI(float)` | BEHAVIORAL | 641 |
| `0x83e570` | `CCharacter::createNewCharacter(std::wstring)` | MATCH | 375 |
| `0x85ba70` | `CCharacterSaveState::CCharacterSaveState()` | MATCH | 494 |
| `0x8644f0` | `CCharacterSaveState::~CCharacterSaveState()` | MATCH | 1032 |
| `0x864900` | `CCharacterSaveState::~CCharacterSaveState() [D0]` | MATCH | 18 |
| `0x8d4bf0` | `CMonster::hasOffensiveSkill()` | BEHAVIORAL | 366 |
| `0x8d4d60` | `CMonster::hasDefensiveSkill()` | BEHAVIORAL | 501 |
| `0x8d4f60` | `CMonster::selectOffensiveSkill(bool)` | BEHAVIORAL | 622 |
| `0x8d51e0` | `CMonster::selectDefensiveSkill()` | BEHAVIORAL | 644 |
| `0x8e1390` | `CMonster::fidgetAI(float, CLevel&)` | BEHAVIORAL | 495 |
| `0x8e2ae0` | `CMonster::unitInit(CDataGroup*, bool)` | BEHAVIORAL | 218 |
| `0x8e43a0` | `CDungeonTracker::save(_IO_FILE*)` | MATCH | 230 |
| `0x8e5020` | `CPlayer::firstTimeSetup()` | BEHAVIORAL | 418 |
| `0x8f4ad0` | `CDungeonTracker::load(_IO_FILE*, unsigned int)` | BEHAVIORAL | 395 |
| `0x8f4fd0` | `CPlayer::resetStatPoints()` | BEHAVIORAL | 716 |
| `0x8f5380` | `CPlayer::resetSkills()` | BEHAVIORAL | 741 |

## Продолжение: восстановлен потерянный пакет

Следующий коммит PR #102 заново восстанавливает прежние 69 определений (70 адресов). Их свежая приёмка и исходники описаны в [отчёте Restore69](../restore69-20261012/README.md). Числа выше относятся к первоначальному пакету Smallmass2 из 44 адресов.
