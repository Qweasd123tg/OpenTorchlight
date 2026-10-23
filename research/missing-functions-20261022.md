# Восстановление отсутствовавших функций — 22 октября 2026

Срез поверх `45b93c7308f3d7ea6cf371e11e80efaf2df86b7b`: только новые
определения, не доводка уже найденных методов из пакета issue #140.
Пачка содержит 39 различных игровых адресов: 22 MATCH и 17 функций,
подтверждённых сравнительными самотестами на 1000 парах входов.
Алиасы конструкторов и деструкторов по одному адресу не удваивают счёт.
Чужие локальные изменения в эту пачку не входят.

## Адресная проверка

| TU | Оригинальный адрес | Метод | Результат |
|---|---|---|---|
| AffectorWrapper.cpp | `0xa18140` | конструктор | MATCH |
| BoxColliderWrapper.cpp | `0xa1b0c0` | конструктор | MATCH |
| ColorWrapper.cpp | `0xa1d480` | `setColors(float*, unsigned int)` | MATCH |
| ColorWrapper.cpp | `0xa1dd50` | конструктор | MATCH |
| ColorWrapper.cpp | `0xa1e2e0` | `getColors(unsigned int&)` | сравнительный самотест |
| ForceWrapper.cpp | `0xa1f0b0` | конструктор | MATCH |
| PlaneColliderWrapper.cpp | `0xa237f0` | `updatePlane()` | MATCH |
| PlaneColliderWrapper.cpp | `0xa24340` | конструктор | MATCH |
| VortexWrapper.cpp | `0xa29840` | конструктор | MATCH |
| AnimationSet.cpp | `0xa4dd50`, `0xa4e140` | обычный и deleting-деструкторы | MATCH |
| ParticleCache.cpp | `0xde6670`, `0xde6a90` | обычный и deleting-деструкторы | MATCH |
| Particle.cpp | `0xa2a140` | `looping()` | MATCH |
| Particle.cpp | `0xa2a290`, `0xa2a620`, `0xa2ab30` | `Stop`, `Start`, `getNumberOfParticlesUpdating` | сравнительные самотесты |
| Particle.cpp | `0xa30da0` | `getDynPropFromArray` | сравнительный самотест |
| ParticleDynProperties.cpp | `0xa31c00` | `getArrayFromDynProp` | сравнительный самотест |
| RoomPiece.cpp | `0x9fa5a0` | `updateAnimation` | MATCH |
| DescriptorController.cpp | `0x5c8ad0` | деструктор | сравнительный самотест |
| RandomNames.cpp | `0xe066e0` | деструктор | сравнительный самотест |
| FileUtilities.cpp | `0xc74490`, `0xc76860` | `setFileTime`, `CreateAppDataDirectory` | сравнительные самотесты |
| Achievements.cpp | `0xec65a0` | деструктор | сравнительный самотест |
| Achievements.cpp | `0xec66c0` | deleting-деструктор | MATCH |
| ModFileFilter.cpp | `0xc83c80`, `0xc844a0` | `saveModFile`, деструктор | сравнительные самотесты |
| ModFileFilter.cpp | `0xc845c0` | deleting-деструктор | MATCH |
| dungeon.cpp | `0x934190` | деструктор | сравнительный самотест |
| dungeon.cpp | `0x934700` | deleting-деструктор | MATCH |
| WeaponTrail.cpp | `0xa4cb20`, `0xa4c900`, `0xa4aed0` | конструктор с именем, `init`, `uninit` | MATCH |
| WeaponTrail.cpp | `0xa4cc90`, `0xa4cdb0` | обычный и deleting-деструкторы | MATCH |
| WeaponTrail.cpp | `0xa4cdd0`, `0xa4a0f0`, `0xa4a470` | конструктор с data group, `fadeOut`, `update` | сравнительные самотесты |

MATCH включает проверку метаданных исключений инструментом `objdiff.py`.
Общие счётчики проекта этим адресным результатом не заменяются.

## Сравнительные самотесты

Все новые тесты находятся в `decomp/hybrid/tests/`. Каждый требует завершённых
вызовов обеих сторон; одинаковое падение не считается совпадением. Отрицательные
контроли намеренно искажают результат кандидата и обязаны обнаружить различие.

| Файл | Методов | Завершённых пар |
|---|---:|---:|
| ColorWrapperColorsTest.cpp | 1 | 24 |
| ParticlePlaybackRecoveryTest.cpp | 3 | 144 |
| ParticleDynamicRecoveryTest.cpp | 1 | 108 |
| ParticleDynamicArrayRecoveryTest.cpp | 1 | 144 |
| NativeCleanupRecoveryTest.cpp | 2 | 80 |
| OwnerCleanupRecoveryTest.cpp | 4 | 160 |
| FileUtilitiesRecoveryTest.cpp | 2 | 76 |
| WeaponTrailRecoveryTest.cpp | 3 | 264 |
| **Всего** | **17** | **1000** |

Подготовка использует настоящих native-владельцев и SDK-объекты, не подменяя
вызываемые проверяемыми функциями операции. Проверяются очистка/повторное
использование кэшей, разные emitter/technique состояния, запуск/остановка,
типы динамических атрибутов и неудачный RTTI cast, владение и слабые ссылки,
реальные файлы и сериализация mods.dat. У WeaponTrail сравниваются геометрия
и байты vertex buffer, преобразования узлов, материал, затухание и ранние
выходы. Файловые тесты работают только в собственных временных каталогах.

У `CColorWrapper::getColors` исходный и восстановленный нормализованные тела отличаются только
порядком обнуления локальных vector-указателей; DIFF 98,71% не используется
как основание приёмки.

После расширения TU прежний MATCH `CModFileFilter::getEnabledModNames`
стал DIFF: изменилось распределение регистров, эквивалентность EH инструмент
не подтвердил. Существующий `ResourceModQueriesTest.cpp` повторно прошёл
для этого адреса на 120 парах; вместе с `getFilePath` и `getModNames` —
360 завершённых пар, 0 различий, 0 неполных вызовов. Это отдельная
регрессионная проверка, не новые адреса из счётчика 39.

## Исправления объявлений и раскладки

- Символ setter требует `float*`, не прежний `const float*`; число означает
  количество float, с шагом пять на ключ `(time, r, g, b, a)`.
- У `CColliderWrapper` флаг расположен в `+0x11a`, размер и выравнивание базы
  остаются `0x120` и 8. Вместо явного массива padding оставлен tail padding,
  который производный класс может использовать повторно.
- У `CPlaneColliderWrapper` в `+0x11c` начинается `Ogre::Vector3` normal,
  а не прежние поля distance/flags в `+0x120`. Оба новых метода получили MATCH
  с этой раскладкой. Прежние MATCH в Collider/CollisionAvoider/Sphere/Box/Plane
  не регрессировали при адресном сравнении.
- Поле Runic affector в `+0x110` взято из существующего SDK-заголовка
  `ParticleUniverseAffector.h`, а не из придуманной структуры.
- У `CWeaponTrail` восстановлены `std::list<Segment>`, строки, узел,
  параметры ширины/затухания и вектор смещения в `+0x90`. Обращения из
  `CCharacter::updateAnimation` сохраняют прежние адреса; raw padding заменён
  именованным полем. Пять новых методов получили MATCH с этой раскладкой.
- В SDK добавлены объявления native `DynamicAttributeRandom::getMin/getMax`;
  в decomp-заголовке описано проверенное 32-байтное расширение Runic
  `DynamicAttributeRandomCurved`. Обратное преобразование использует настоящий
  глобальный кэш `m_DynamicArrayForProperties`.
- В подготовщике контекста закреплены три ранее блокировавших пакеты weak
  деструктора массивов указателей. Это точечные проверки ELF-адреса, размера,
  алиасов и хеша существующего заголовка, не общий обход блокировок.
  `test_llm_context.py`: 217 тестов PASS.

## Общая проверка

Предыдущий полный запуск на промежуточном рабочем дереве не был зелёным:
одна из четырёх частей превысила лимит 4540 секунд; отдельно был неполный
вызов `complete_fltk_source_29` на `0xf94700`. Это не подтверждает регрессию
данной пачки, но и не даёт права объявить полный PASS.

Итоговый `python3 tools/decomp/check.py` запущен на чистой ветке
`decomp/recover-missing-20261022`, без чужих локальных правок. Первый такой
прогон обнаружил в старом `CharacterAnimationRuntimeTest.cpp` обращение к
переименованному padding-полю WeaponTrail. Оно заменено обращением к тем же
12 байтам `m_positionOffset`; полный прогон перезапущен, его результат
ещё ожидается. Повтор всех 17 новых сравнительных тестов в одном гибриде
этого чистого дерева завершился PASS: 1000 завершённых пар, 0 различий,
0 неполных вызовов; отрицательные контроли прошли. Общий принятый процент
проекта здесь не пересчитывается. Коммит не означает полный PASS всего гибрида.
