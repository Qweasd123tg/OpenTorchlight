# Что находится внутри официального TorchED SDK

## Итог

TorchED не содержит исходный C++-код Torchlight. Он всё равно оказался одним
из самых полезных источников для восстановления игры: вместе с редактором
поставляется отдельная 32-битная сборка родного движка `Core.dll`, а управляемая
оболочка `Editor.exe` описывает границу вызовов этого движка почти как заголовочный
файл.

В `Core.dll` найдены 193 именованных экспорта и RTTI 302 классов движка. Имена
всех этих 302 классов присутствуют и в деманглированных символах оригинального
Linux-бинарника. Среди них `CGame`, `CLevel`, `CPlayer`, `CCharacter`,
`CMonster`, `CInventory`, `CSkill`, `CQuest`, `CAstarPathfinder`, `CRandomizer`,
`CLogicGroup`, `CPropertyNode`, `CUnitSpawner` и `CTimeline`.

Это доказывает общность значительной части структуры редактора и игры, но не
байтовую идентичность функций. `Core.dll` собран для Windows x86 и редакторского
режима, а исследуемая игра — для Linux x86-64. Сравнивать их нужно по именам
классов, константам, строкам, графам вызовов и наблюдаемому поведению.

Полная машинно читаемая инвентаризация лежит в
[`torched-sdk.json`](torched-sdk.json). Она генерируется скриптом
[`tools/audit_torched.py`](../tools/audit_torched.py); бинарники SDK в репозиторий
не копируются.

## Проверенный дистрибутив

Исследован `TorchEDInstaller-1.0.exe` размером 402 491 888 байт:

- MD5: `01ac7edcc21538da202b222933a5e621`;
- SHA-256: `47d2f9cb00bb4754c293b473a76f7eeaeb3155274ad6aaa1ac9145ceaf86e216`.

MD5 совпадает со значением на странице сохранившегося дистрибутива ModDB.
Официальное объявление Runic Games от 16 ноября 2009 года описывает TorchED как
редактор игры, а страница Steam — как комплект инструментов, применявшихся при
создании Torchlight:

- https://www.runicgames.com/blog/2009/11/16/torched-is-here/
- https://www.moddb.com/games/torchlight/downloads/editor-sdk
- https://store.steampowered.com/app/41500/Torchlight/

После распаковки получено 21 602 файла общим размером 1 363 609 262 байта.
Основные группы: 6 003 `DAT`, 3 322 `mesh`, 2 776 `dds`, 2 023 `layout`,
1 600 `skeleton`, 1 193 `material`, 181 `animation` и 110 XML-представлений
моделей. Есть 15 официальных PDF по редактору, уровням, случайным квестам,
частицам, анимациям, гардеробу и импорту моделей.

Файлов `.c`, `.cc`, `.cpp`, `.cs`, `.h`, `.hpp`, `.lib` и `.pdb` нет.
`Editor.exe` содержит ссылку на нераспространявшийся файл отладки
`c:\builder\Projects\Editor\Editor\obj\ReleaseDLLExternal\Editor.pdb`.
У `Core.dll` отладочный каталог отсутствует.

## Родной движок `Core.dll`

`Core.dll` имеет размер 10 218 640 байт и SHA-256
`4d8b29844e3ae133300cec6ce631c577df58f122ddd7ececf7e77b64e00508e8`.
Это обычная PE32 DLL с родным C++-кодом, без CLR-заголовка. Она импортирует OGRE
и другие компоненты исходного Windows-движка.

193 экспорта покрывают следующие участки:

- запуск, остановку и обновление редакторского runtime;
- создание, удаление, выбор, свойства и иерархию объектов сцены;
- загрузку и сохранение `LAYOUT`, комнаты и параметры chunk;
- создание узлов и связей логического графа, вызов выходных функций;
- свойства, точки и интерполяцию timeline;
- списки и перезагрузку юнитов, навыков, квестов, подземелий, affix,
  spawnclass, missiles, textures и sound banks;
- тестовый запуск уровня с выбором игрока, класса, питомца, квестов,
  глубины, spawnclass монстров, заполнения уровня и заморозки AI;
- список, приоритет и включение модов.

RTTI содержит 319 описаний классов, из них 302 начинаются с принятого в движке
префикса `C`. Все 302 имени найдены в символах Linux-версии. Поэтому
`Core.dll` можно использовать как второй вид одной архитектуры: когда функция
в Linux-бинарнике сложна, её редакторскую реализацию можно искать по классу,
строкам и связанному экспорту в более компактной DLL.

## Управляемая оболочка `Editor.exe`

`Editor.exe` имеет размер 2 654 864 байта и SHA-256
`8e5e29cef0973388641d08284e51b2e4a254ca7c3dca1e9fcdcbc2c71d8ac480`.
Это .NET-сборка с 326 определениями типов, 411 ссылками на типы и 5 070
методами. Её IL и метаданные можно восстановить значительно точнее, чем
исходный C++.

В сборке 212 P/Invoke-записей: 196 вызовов `core.dll` и 16 вызовов Win32 UI.
196 строк описывают 194 уникальных имени, потому что
`EditorGetObjectProperty` и `EditorSetObjectProperty` имеют по две сигнатуры.
Все 193 реальных экспорта `Core.dll` используются оболочкой. В `Editor.exe`
также остался один устаревший импорт `EditorGetRedoCount`, которого уже нет в
DLL.

Метаданные дают точные типы и имена параметров. Например:

```text
int64 EditorCreateObject(uint32 iSceneID, uint32 iDescriptorID,
                         int64 iObjectIDToClone, bool bCloneChildren)
uint32 EditorCreateLogicObject(int64 nLogicGroupID, int64 nObjectIDToRef)
uint32 EditorCreateLogicLink(int64 nLogicGroupID,
                             uint32 nLogicObjectIDOutput,
                             uint32 nLogicObjectIDInput,
                             uint32 nLogicOutputIndex,
                             uint32 nLogicInputIndex)
void EditorInvokeOutputFunction(int64 nLogicGroupID,
                                uint32 nLogicObjectIDOutput,
                                uint32 nOutputFunctionID)
bool EditorSaveScene(uint32 sceneID, string fileAndPath, bool bSelectedOnly)
uint32 EditorLoadScene(uint32 sceneID, string fileAndPath, bool bClearFirst)
```

Полный список прототипов находится в поле
`managed_metadata.core_imports` JSON-отчёта. Следующий полезный уровень анализа
— разобрать IL методов редактора вокруг этих вызовов. Так можно получить порядок
операций, значения флагов и соответствие элементов UI функциям движка без
угадывания по скриншотам.

## Повторение аудита

SDK сначала нужно извлечь во внешний временный каталог. Скрипт ничего не
запускает и не меняет в SDK:

```sh
python3 -m pip install --target /tmp/torched-pydeps dnfile
PYTHONPATH=/tmp/torched-pydeps python3 tools/audit_torched.py \
  --sdk-dir /tmp/torched-sdk \
  --installer /путь/TorchEDInstaller-1.0.exe \
  --original /путь/Torchlight.bin.x86_64 \
  --output research/torched-sdk.json
```

Без `dnfile` скрипт всё равно считает файлы, хеши, экспорты и RTTI. Пакет нужен
только для чтения .NET-метаданных и восстановления P/Invoke-прототипов.

## Как это меняет план восстановления

Поддержка пользовательских модов остаётся возможной проверкой форматов, но
сейчас она не является следующим этапом. Приоритетнее использовать SDK для
восстановления самой игры:

1. сопоставить 302 общих класса с символами Linux-бинарника;
2. разобрать IL оболочки для логического графа, timeline и тестового запуска;
3. по найденным вызовам и данным восстановить runtime `Logic Group`, триггеров,
   spawner и событий;
4. после этого перейти к выбору цели, бою, предметам, навыкам, квестам и
   сохранениям в переносимой реализации.
