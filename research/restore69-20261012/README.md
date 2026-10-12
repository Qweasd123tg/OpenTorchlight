# Восстановление потерянных 69 определений — 12 октября 2026

Заново восстановлены **69 определений C++98, закрывающих 70 адресов оригинала**: 69 явных определений и один автоматически сгенерированный удаляющий деструктор D0. Объём — **16 177 байт** исходного машинного кода.

Это свежая декомпиляция состава потерянного локального пакета `076a8890cb2bd7795d1b1dfa4a50bd928427d7c1`. Исходники и старые результаты проверки того пакета не использовались; текущие цифры получены заново.

База этого коммита — `732baa10d24a655bc5a8c44078b8a4e6e9d35ee5`, уже содержащая пакет Smallmass2 из 44 адресов. Общая приёмка: **2795 → 2865 из 5247 функций**. Все прежние принятые адреса сохранены. Вместе два коммита PR #102 добавляют **111 определений C++ и 114 уникальных адресов** относительно handoff `3a72c325`.

## Состав

| Исходный TU | Определения C++ | Адреса | MATCH | BEHAVIORAL |
|---|---:|---:|---:|---:|
| `Console.cpp` | 1 | 1 | 0 | 1 |
| `Itemsavestate.cpp` | 2 | 3 | 3 | 0 |
| `Shape.cpp` | 1 | 1 | 0 | 1 |
| `character.cpp` | 55 | 55 | 11 | 44 |
| `itemgold.cpp` | 1 | 1 | 0 | 1 |
| `player.cpp` | 9 | 9 | 2 | 7 |

- **CCharacter:** состояние навыка, переключение и циклический выбор навыков, удаление известных заклинаний и связанных эффектов, питомцы и хозяин, цели, дальность взаимодействия и атаки, параметры и эффекты персонажа, регенерация маны, блок и отражение, чтение настроек, диспетчер AI и события анимации атаки.
- **CPlayer:** выход из состояний рыбалки, журнальная/Steam-статистика и достижение за золото, смерть и сохранение, поиск сохранённого уровня, добавление путевой точки, глубина подземелья, имя класса и естественная броня.
- **CItemSaveState:** конструктор и деструкторы; исходный порядок освобождения эффектов и вложенных предметов.
- **CItemGold, CShape, CConsole:** обновление частиц и масштаба золота, пять режимов ориентации формы, показ/скрытие консоли и очистка ввода.

## Существенные детали оригинала

1. Смена выбранного навыка может обновить GUID, сохранив указатель на ещё исполняемый навык. Учитываются animationID, возможность прерывания, зацикливание и время. Циклический выбор сохраняет исходные проверки ранга, типа активации, enabled/executed-by-property и завершение обхода при возврате к начальной позиции.
2. Удаление заклинания очищает все совпадающие GUID и указатели текущего/предыдущего навыка, затем сдвигает четыре слота имени и уровня. Деактивация эффектов удаляет навык только для пяти исходных типов эффекта и использует уровень не меньше 1.
3. Удаление питомца сдвигает параллельно std::vector указателей и std::vector<bool>. Проверены первый, средний и последний элементы, отсутствие элемента, а также граница 63/64/65 флагов.
4. Дальность атаки использует масштаб **Z**. При двух видах экипировки выбор минимума/максимума диапазонов зависит от исходных проверок типа оружия. Проверки взаимодействия измеряют расстояние в XZ и вычитают радиусы обоих объектов; пороги исходника — 1,75 / 3,45 / 2,95.
5. Замедление компенсируется эффектом сопротивления только при отрицательной прибавке скорости. Отражение сначала проверяет вероятность, затем собирает максимальные границы отражаемого урона с персонажа и 12 слотов экипировки. Сохранены порядок float-операций и проверки границ.
6. Эффекты оружия используют локальную ориентацию узла, а точка эффекта смещается к поверхности цели и вверх на 1,25. Диспетчер AI восстановлен по таблице переходов оригинала. В interruptAI и setMaster переход выполняется в буквальное состояние 0; существующая константа AISTATE_IDLE равна 2 и здесь не используется.
7. Поиск сохранённого уровня сравнивает и номер, и имя с исходным регистром. Добавление путевой точки не создаёт отсутствующий CDungeonTracker и не добавляет повторный уровень. getMaxDepth предварительно переводит запрошенное имя в верхний регистр.
8. Конструктор CItemSaveState инициализирует только те поля, которые инициализирует оригинал. Деструктор удаляет элементы трёх списков эффектов и вложенные сохранённые предметы. Все три адреса семейства подтверждены MATCH.
9. CShape сохраняет пять исходных режимов и не меняет выходные векторы для неизвестного режима; сравнительная оснастка включает совмещение выходных ссылок. Показ консоли делает окно видимым, активирует его, перемещает вперёд и очищает поле ввода.

## Проверка и публикация

- Новые адреса: **16 MATCH + 54 BEHAVIORAL**.
- Шесть групповых файлов оснасток: **55 адресных тестов, 8480 завершённых пар оригинал/замена, 0 расхождений и 0 незавершённых пар**. Обе стороны вызывают соответствующий оригинальный/восстановленный адрес; равные падения не принимаются.
- Дополнительно: 128 завершённых сравнений `CDungeonTracker::save(FILE*)` (`0x8e43a0`), 0 расхождений. После расширения player.cpp GCC изменил выбор регистра в двух инструкциях этой прежней функции; её исходное тело сохранено, текущая приёмка — BEHAVIORAL.
- Прежняя `CCharacter::removePet(std::wstring)` (`0x835520`) в этом снимке получила MATCH вместо BEHAVIORAL. Оба изменения статусов относятся к первому пакету из 44 адресов; они не увеличивают число заново восстановленных адресов.
- Итоговый полный прогон: `tlhybrid: 829 tests, 0 failed`.
- Общий результат: **2213 MATCH + 652 BEHAVIORAL = 2865**.
- `Stage.validate()` и `Stage.publish()` выполнены на одном экземпляре Stage; после проверки производственные исходники и оснастки не менялись.
- После публикации побайтно проверены объекты **281 производственных TU**, отпечатки входов Stage и рабочего checkout совпали.
- GCC 4.4.7, C++98, -O2 -fno-strict-aliasing и закреплённые зависимости проекта. Инструменты, сторонние библиотеки и оригинальный бинарник не изменялись.
- SHA-256 оригинального ELF: `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
- Область проверки — objdiff и headless-гибрид. Оконный запуск, прохождение игры и самостоятельный запуск без оригинального бинарника не проверялись.

Доказательства: [validation.json](validation.json), [все функции](functions.json), [полный журнал](selftest.log), [хеши объектов](objects.json). Предыдущий пакет PR: [Smallmass2](../smallmass2-20261012/README.md).

## Все восстановленные адреса

| Адрес | Функция | Приёмка | Байты |
|---|---|---|---:|
| `0xaed310` | `CConsole::setVisible(bool)` | BEHAVIORAL | 447 |
| `0x8cb030` | `CItemSaveState::CItemSaveState()` | MATCH | 311 |
| `0x8d2080` | `CItemSaveState::~CItemSaveState()` | MATCH | 742 |
| `0x8d2370` | `CItemSaveState::~CItemSaveState() [D0]` | MATCH | 18 |
| `0xa06700` | `CShape::calculateOrientation(Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&)` | BEHAVIORAL | 804 |
| `0x80e930` | `CCharacter::performingSkill()` | BEHAVIORAL | 65 |
| `0x80ec70` | `CCharacter::removePet(CCharacter*)` | BEHAVIORAL | 210 |
| `0x80eef0` | `CCharacter::getArmorAndTrinketLevelCanEquip(bool)` | BEHAVIORAL | 81 |
| `0x80ef50` | `CCharacter::getWeaponLevelCanEquip(bool)` | BEHAVIORAL | 81 |
| `0x80f2e0` | `CCharacter::stopParticles(bool)` | BEHAVIORAL | 165 |
| `0x80f410` | `CCharacter::setActiveSkill(CSkill*, bool)` | BEHAVIORAL | 236 |
| `0x80f500` | `CCharacter::cycleSkill(int)` | BEHAVIORAL | 424 |
| `0x80f710` | `CCharacter::setAIState(EAIState)` | BEHAVIORAL | 165 |
| `0x80f800` | `CCharacter::getKnownSpell(unsigned int)` | BEHAVIORAL | 127 |
| `0x810170` | `CCharacter::alignment()` | BEHAVIORAL | 71 |
| `0x810200` | `CCharacter::isEnemy(CCharacter*)` | BEHAVIORAL | 196 |
| `0x8102d0` | `CCharacter::isFriend(CCharacter*)` | BEHAVIORAL | 152 |
| `0x812580` | `CCharacter::attackRange()` | BEHAVIORAL | 348 |
| `0x8138a0` | `CCharacter::viewAngle()` | BEHAVIORAL | 142 |
| `0x8139a0` | `CCharacter::dexterity()` | MATCH | 103 |
| `0x813a10` | `CCharacter::maxMana()` | MATCH | 127 |
| `0x814440` | `CCharacter::isPetNearDeath()` | BEHAVIORAL | 124 |
| `0x8144c0` | `CCharacter::magic()` | MATCH | 103 |
| `0x815a20` | `CCharacter::walkingSpeed()` | BEHAVIORAL | 166 |
| `0x815ad0` | `CCharacter::runningSpeed()` | BEHAVIORAL | 166 |
| `0x815c90` | `CCharacter::updateMana(float)` | BEHAVIORAL | 175 |
| `0x816330` | `CCharacter::blocked()` | BEHAVIORAL | 44 |
| `0x8163a0` | `CCharacter::getDmgToReflectFromMissile()` | BEHAVIORAL | 405 |
| `0x822ce0` | `CCharacter::addToAvoidanceMap(CLevel&)` | BEHAVIORAL | 303 |
| `0x823bf0` | `CCharacter::unLearnSpell(std::wstring, int)` | BEHAVIORAL | 482 |
| `0x823ee0` | `CCharacter::inDamageReactRange(CCharacter*)` | BEHAVIORAL | 175 |
| `0x8244a0` | `CCharacter::inInteractionRange()` | BEHAVIORAL | 282 |
| `0x824920` | `CCharacter::setTargetItem(CItem*)` | BEHAVIORAL | 229 |
| `0x824a10` | `CCharacter::notifyOfDeletion(CItem*)` | MATCH | 55 |
| `0x824e00` | `CCharacter::inStrikeRange()` | MATCH | 81 |
| `0x825d40` | `CCharacter::updateAI(float, bool)` | BEHAVIORAL | 548 |
| `0x825f80` | `CCharacter::notifyOfDeletion(CCharacter*)` | MATCH | 23 |
| `0x825fa0` | `CCharacter::setMaster(CCharacter*)` | BEHAVIORAL | 199 |
| `0x827010` | `CCharacter::doWeaponProcs(CEquipment*, CBaseUnit*)` | BEHAVIORAL | 540 |
| `0x827720` | `CCharacter::playStrikeParticle(Ogre::Vector3 const&, Ogre::Vector3 const&, float, bool, bool)` | BEHAVIORAL | 357 |
| `0x82a4e0` | `CCharacter::interruptAI(float, CLevel&)` | MATCH | 184 |
| `0x831ee0` | `CCharacter::getMaximumPetInstances()` | BEHAVIORAL | 170 |
| `0x8325e0` | `CCharacter::getDescription()` | BEHAVIORAL | 184 |
| `0x8326a0` | `CCharacter::diesOnWarp()` | BEHAVIORAL | 168 |
| `0x832750` | `CCharacter::getSpawnInvisible()` | BEHAVIORAL | 168 |
| `0x832800` | `CCharacter::getDestroyOnDeath()` | BEHAVIORAL | 168 |
| `0x8328b0` | `CCharacter::attachesToMaster()` | BEHAVIORAL | 168 |
| `0x834700` | `CCharacter::getMimicName()` | BEHAVIORAL | 184 |
| `0x8347c0` | `CCharacter::getDefaultMerchantTab()` | BEHAVIORAL | 167 |
| `0x834870` | `CCharacter::getSkillTabName(int)` | BEHAVIORAL | 278 |
| `0x834990` | `CCharacter::baseArmorBonus()` | BEHAVIORAL | 228 |
| `0x834ad0` | `CCharacter::getIntroCinematic()` | BEHAVIORAL | 184 |
| `0x834b90` | `CCharacter::playerLevelForMerchantInventory()` | BEHAVIORAL | 170 |
| `0x835ba0` | `CCharacter::setAltSkillByName(std::wstring)` | MATCH | 191 |
| `0x835c60` | `CCharacter::setActiveSkillByName(std::wstring)` | MATCH | 191 |
| `0x837060` | `CCharacter::deactivateEffect(CEffect*)` | BEHAVIORAL | 449 |
| `0x837b00` | `CCharacter::setLeftSkillByName(std::wstring)` | MATCH | 256 |
| `0x83c670` | `CCharacter::handInteractiveSequence(float)` | BEHAVIORAL | 192 |
| `0x83dc70` | `CCharacter::unLearnSpell(int)` | MATCH | 220 |
| `0x848790` | `CCharacter::updateAttack(CLevel&)` | BEHAVIORAL | 215 |
| `0x8c2760` | `CItemGold::update(Ogre::Camera*, Ogre::Vector3 const&, float)` | BEHAVIORAL | 248 |
| `0x8e3ff0` | `CPlayer::setAIState(EAIState)` | BEHAVIORAL | 112 |
| `0x8e41c0` | `CPlayer::incrementJournalStatistic(EJournalStatistic, int)` | BEHAVIORAL | 466 |
| `0x8e47d0` | `CPlayer::die(CCharacter*, Ogre::Vector3 const*, float, bool)` | BEHAVIORAL | 204 |
| `0x8ef600` | `CPlayer::getLevelSavedState(std::wstring, int)` | BEHAVIORAL | 184 |
| `0x8ef6c0` | `CPlayer::hasLevelSavedState(std::wstring, int)` | BEHAVIORAL | 123 |
| `0x8efa70` | `CPlayer::addWaypoint(std::wstring, int)` | MATCH | 326 |
| `0x8f4d90` | `CPlayer::getMaxDepth(std::wstring)` | MATCH | 334 |
| `0x8f52a0` | `CPlayer::getPlayerClassName()` | BEHAVIORAL | 209 |
| `0x8f8510` | `CPlayer::calculateNaturalArmor()` | BEHAVIORAL | 364 |
