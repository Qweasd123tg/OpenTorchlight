# Массовая декомпиляция, партия 3 — 13 октября 2026

Восстановлены **44 новых определения C++98 и 44 уникальных адреса оригинала**, **37 491 байт** машинного кода. Приёмка партии: **1 MATCH + 43 BEHAVIORAL**. Эти адреса не входят ни в первый пакет Smallmass2, ни в повторно восстановленные 69 определений.

База — `5194eb31eb2f2f8876c4f673d5f85040c8d77a6a`. Ранее восстановленные 114 адресов PR #102 сохранены. Три партии вместе добавляют **155 определений C++98, 158 уникальных адресов и 76 881 байт** относительно handoff `3a72c325996de885ffed2995d1490768eddf008c`.

## Состав партии

| Исходный TU | Новые определения / адреса | MATCH | BEHAVIORAL |
|---|---:|---:|---:|
| `character.cpp` | 22 | 1 | 21 |
| `player.cpp` | 9 | 0 | 9 |
| `Inventory.cpp` | 6 | 0 | 6 |
| `monster.cpp` | 6 | 0 | 6 |
| `Console.cpp` | 1 | 0 | 1 |

- **Персонажи:** дальности атаки/удара/навыка и линия видимости; прозрачность и частицы; прерывание и события навыков; запуск оружейных навыков; опыт и смерть от периодических эффектов; питомцы, трансформация, слава и рыбалка; стартовая экипировка и инвентарь торговца.
- **Игрок:** удаление обычных и квестовых предметов; анимации, рыболовные модели и сброс уровня; менеджер заданий; учёт посещённых подземелий; создание обычных и картографических порталов.
- **Инвентарь:** возможность экипировки, предметы для сравнения, подбор первого свободного места, оба варианта подбора предмета и пересчёт эффектов комплектов.
- **Монстры:** бегство, обычное ожидание, обход цели, дальний атакующий/защитный AI и движение во время прыжка вниз.
- **Консоль:** рекурсивное включение/отключение дерева питомцев.

## Детали, подтверждённые оригиналом

1. Дальность удара зависит от масштаба **Z**. Проверки расстояния до персонажа и предмета различаются ограничениями по высоте. В линии видимости сохранена формула ограничения высоты конечной точки, включая исходный порядок операций с float.
2. Оружейные навыки и события анимации используют локальную ориентацию `SceneNode::getOrientation()`. При получении позиции оружия используются отдельные точки привязки правой и левой руки. Оснастки наблюдают вызовы, аргументы, результат и изменённые поля.
3. При начислении опыта сохранены знаковое изменение беззнакового счётчика, ограничение уровня, передача опыта питомцам/хозяину и журнал убийств. Смерть от эффектов учитывает исходные группы эффектов, типы урона, владельца эффекта и порядок наград.
4. Начальная экипировка обрабатывает девять прямых имён и девять классов спауна. В `loadAndEquipSpawnClass` оригинал использует первый флаг зачарования для каждого выбранного предмета; это поведение сохранено. Торговец учитывает магические/уникальные предметы и исходные правила удаления неподходящих объектов.
5. Удаление предметов игроком обрабатывает собственный инвентарь и только первого питомца. Сохранены различия между GUID предмета и квеста, удаление целой стопки и уменьшение количества на единицу. Неполное объединение стопок в `pickupEquipment` переносит доступное количество и возвращает нулевой указатель, как оригинал.
6. Пересчёт комплектов применяет каждый найденный комплект один раз, проверяет пороги числа надетых вещей и обновляет восемь таблиц по 145 типам эффектов. Для ненулевых значений, включая NaN, сохранены исходные условия добавления в таблицу.
7. Восстановлены фактические типы полей рыбалки: модель `CGenericModel*` по смещению `0x830` и узел `Ogre::SceneNode*` по `0x848`. `CDungeonTracker` использует исходный аллокатор Ogre; размеры и расположение полей сохранены.
8. Возвратный портал учитывает имя подземелья, глубину и признак города. При несовпадении вне города оригинал завершает функцию до обновления автомапы. Названия для учёта подземелий и картографических порталов переводятся в верхний регистр.
9. Поведение монстров сохраняет отдельные пороги случайного выбора навыков и перемещения, предел расстояния до хозяина и порядок переходов состояния. Для координат случайного назначения оригинал в нескольких местах сочетает `getPosition(false)` и `getPosition(true)`; вызовы восстановлены буквально.
10. `jumpDownAI` использует исходный изменяемый ABI `CPath::GetPoint(unsigned int)` через именованное объявление. Существующий const-вариант из чужого TU не изменён. Сохранены поворот в первой половине пути, синхронизация времени анимации и переход после приземления.

## Исправление связывания статических функций

Четыре функции партии имеют внутреннюю связь в своём TU: `SetPetsEnabled`, `createEquipmentAndEquip`, `loadAndEquip` и `loadAndEquipSpawnClass`. Ранее отдельный объект с таблицей подмен не мог разрешить ссылки на такие символы.

`tools/decomp/hybrid.py` теперь добавляет для фактически определённой статической функции глобальное имя `__tlhybrid_local_<TU>_<symbol>`, указывающее на тот же код. Исходный символ сохраняет `STT_LOCAL`; машинные инструкции не меняются. Номер TU предотвращает столкновение одинаковых имён из разных файлов. Таблица подмен ссылается на это дополнительное имя.

Новый тест собирает два ELF-объекта с одинаковым статическим именем и разными телами, затем связывает отдельную таблицу ссылок. Проверены связь исходного символа, совпадение адреса/размера/типа дополнительного имени и разрешение обеих ссылок. Вся группа `test_hybrid*.py`: **17 тестов, 0 ошибок**. Правила objdiff, порог приёмки и учёт завершённых сравнений не менялись.

## Проверка и сохранность

- Общий результат: **2865 → 2909 из 5247**; **2213 MATCH + 696 BEHAVIORAL**. Все ранее принятые адреса сохранены.
- Новая партия: **43 адресных теста, 11984 завершённых пар оригинал/замена**, 0 расхождений и 0 незавершённых пар. Равные падения не принимаются.
- Отдельно: **2 оснастки шаблонных функций, 432 завершённых пар** для `TArrayList<CEquipmentRef*>::add` (`0x926260`) и `std::vector<bool>::_M_insert_aux` (`0x85ad10`). Проверены рост буфера, сохранность элементов и вставка битов в начале, середине и конце. Эти weak-определения не включены в 44 новые игровые функции.
- Полный итоговый прогон: **`tlhybrid: 874 tests, 0 failed`**.
- `Stage.validate()` и `Stage.publish()` выполнены на одном экземпляре Stage. Производственные исходники и оснастки после проверки не менялись.
- Подтверждены совпадающие отпечатки входов и объекты **281 производственных TU** после публикации.
- Прежний адрес `0x91cf50`: MATCH → BEHAVIORAL; он сохранён в общей приёмке и не включён в число новых адресов.
- Закреплённые GCC 4.4.7, C++98, оптимизация `-O2 -fno-strict-aliasing`, зависимости проекта. Оригинальный бинарник и ресурсы не изменялись и в PR не включены.
- Проверены objdiff и headless-гибрид; оконный запуск и прохождение игры не выполнялись.
- SHA-256 ELF: `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.

Доказательства: [validation.json](validation.json), [functions.json](functions.json), [полный журнал](selftest.log), [хеши объектов](objects.json), [тесты линковки](tool-tests.log). Предыдущие партии: [Smallmass2](../smallmass2-20261012/README.md) и [Restore69](../restore69-20261012/README.md).

## Все новые адреса

| Адрес | Функция | Приёмка | Байты | Завершённые пары |
|---|---|---|---:|---:|
| `0xaec900` | `SetPetsEnabled(CCharacter*, bool)` | BEHAVIORAL | 167 | 128 |
| `0x91bdc0` | `CInventory::canEquip(CEquipment*, bool)` | BEHAVIORAL | 1241 | 384 |
| `0x91c2a0` | `CInventory::getComparisonItems(CEquipment*, CEquipment**, CEquipment**)` | BEHAVIORAL | 924 | 384 |
| `0x924440` | `CInventory::calculateEffectValues()` | BEHAVIORAL | 970 | 80 |
| `0x924bd0` | `CInventory::pickupEquipment(CEquipment*, int, bool)` | BEHAVIORAL | 1503 | 448 |
| `0x9251b0` | `CInventory::pickupEquipment(CEquipment*, bool)` | BEHAVIORAL | 766 | 384 |
| `0x925970` | `CInventory::equipEquipmentIntoFirstFreeLocation(CEquipment*)` | BEHAVIORAL | 951 | 384 |
| `0x811230` | `CCharacter::interrupt(bool)` | BEHAVIORAL | 1010 | 256 |
| `0x811650` | `CCharacter::updateSkillKeys(float)` | BEHAVIORAL | 905 | 256 |
| `0x812950` | `CCharacter::setVisible(bool, bool)` | BEHAVIORAL | 1307 | 256 |
| `0x812e70` | `CCharacter::updateOpacity(float, bool)` | BEHAVIORAL | 756 | 256 |
| `0x8132f0` | `createEquipmentAndEquip(CCharacter*, CDataGroup*, wchar_t const*, EEQUIP_LOCATIONS, bool)` | BEHAVIORAL | 253 | 192 |
| `0x822850` | `CCharacter::awardExperience(CLevel&, CCharacter*, int, bool)` | BEHAVIORAL | 764 | 384 |
| `0x8245c0` | `CCharacter::doWeaponSkill(CEquipment*)` | BEHAVIORAL | 852 | 256 |
| `0x824a50` | `CCharacter::inStrikeRange(CCharacter*, CItem*, CEquipment*)` | BEHAVIORAL | 934 | 384 |
| `0x824e60` | `CCharacter::validLineOfSight(CLevel&, bool)` | BEHAVIORAL | 927 | 256 |
| `0x826140` | `CCharacter::inAttackRange(EATTACK_RANGE_TYPE)` | BEHAVIORAL | 813 | 384 |
| `0x826470` | `CCharacter::inSkillRange(long long, bool)` | BEHAVIORAL | 872 | 384 |
| `0x827b20` | `CCharacter::performSkill()` | BEHAVIORAL | 908 | 256 |
| `0x82e4b0` | `CCharacter::startFishing()` | MATCH | 670 | MATCH |
| `0x831f90` | `CCharacter::addPet(CCharacter*)` | BEHAVIORAL | 708 | 192 |
| `0x836cb0` | `CCharacter::generateMerchantInventory()` | BEHAVIORAL | 940 | 256 |
| `0x837630` | `CCharacter::fameUp()` | BEHAVIORAL | 1229 | 128 |
| `0x83bd10` | `loadAndEquipSpawnClass(CCharacter*, CDataGroup*, wchar_t const*, EEQUIP_LOCATIONS)` | BEHAVIORAL | 1058 | 192 |
| `0x83c140` | `CCharacter::fishingAICatch(float, CLevel&)` | BEHAVIORAL | 943 | 128 |
| `0x83d930` | `CCharacter::updateHP(CLevel&, float)` | BEHAVIORAL | 819 | 256 |
| `0x83e6f0` | `loadAndEquip(CCharacter*, CDataGroup*, wchar_t const*, EEQUIP_LOCATIONS)` | BEHAVIORAL | 424 | 128 |
| `0x83e8a0` | `CCharacter::createDefaultEquipment()` | BEHAVIORAL | 546 | 64 |
| `0x842150` | `CCharacter::transformCharacter(std::wstring, float)` | BEHAVIORAL | 844 | 128 |
| `0x8d59a0` | `CMonster::fleeAI(float, CLevel&)` | BEHAVIORAL | 667 | 384 |
| `0x8e02b0` | `CMonster::idleAINormal(float, CLevel&, bool)` | BEHAVIORAL | 1026 | 512 |
| `0x8e06e0` | `CMonster::idleAICircler(float, CLevel&, bool)` | BEHAVIORAL | 1188 | 512 |
| `0x8e0b90` | `CMonster::idleAIRangedCaster(float, CLevel&, bool)` | BEHAVIORAL | 796 | 512 |
| `0x8e0eb0` | `CMonster::idleAIRangedDefender(float, CLevel&, bool)` | BEHAVIORAL | 649 | 512 |
| `0x8e1580` | `CMonster::jumpDownAI(float, CLevel&)` | BEHAVIORAL | 1021 | 256 |
| `0x8e4490` | `CPlayer::createPortals(CLevel&)` | BEHAVIORAL | 581 | 384 |
| `0x8f0d10` | `CPlayer::updateAnimation(float)` | BEHAVIORAL | 585 | 256 |
| `0x8f1380` | `CPlayer::removeItemFromInventoryOrPetsInventoryByGuid(long long, bool, bool, UNITTYPES::EUNITTYPES)` | BEHAVIORAL | 850 | 256 |
| `0x8f16e0` | `CPlayer::removeQuestItemFromInventoryOrPetsInventoryByGuid(long long, long long, bool, bool, UNITTYPES::EUNITTYPES)` | BEHAVIORAL | 1042 | 256 |
| `0x8f4780` | `CPlayer::loadModel(std::wstring, std::wstring)` | BEHAVIORAL | 842 | 128 |
| `0x8f5670` | `CPlayer::openMapPortal(std::wstring, CLevel&)` | BEHAVIORAL | 416 | 256 |
| `0x8f5810` | `CPlayer::levelResetting()` | BEHAVIORAL | 1082 | 128 |
| `0x8f5c50` | `CPlayer::updateDungeonTracking(std::wstring, int)` | BEHAVIORAL | 1058 | 256 |
| `0x8f8260` | `CPlayer::setQuestManager(CQuestManager*)` | BEHAVIORAL | 684 | 192 |
