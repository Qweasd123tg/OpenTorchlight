# Создание персонажа: исходные Editbox и реальный consumer

Проверено 2026-09-30. Подключённый срез CNewGameMenu; полные игровые
функции остаются `partial`. Оригинал и ресурсы используются только для чтения.
SHA-256 ELF, CEGUI, pak, layout и vendor tree закреплены в
`cegui-source-inputs.json`. Это развитие существующего System и стенда,
без новой библиотеки UI или отдельного дерева для страницы создания.

## Источники и контракт

`original-code`: просмотрены адресные тела `createMenus @0xc5d730`,
`setOpen @0xc5c5a0`, `update @0xc5cc30`, `onClick @0xc5c040`,
`handle_Submit @0xc53f40` и `handle_SubmitPet @0xc5c2f0`. Эти большие
игровые функции не объявляются полностью перенесёнными: ниже перечислен
проверенный срез и неподключённые эффекты.

- Constructor `0xc5e3b8` передаёт CDropdown flags=1: model-null, как Main.
  Create загружает `media/UI/charactercreate.layout`, вызывает scale(false)
  `0xc5d8f5`, mapToFunctions `0xc5d901`, mapEventHandlers `0xc5d90c`,
  прикрепляет layout к root `0xc5d918` и обнуляет позицию `0xc5d954`.
  Native wrapper использует эту же цепочку и ранее проверенные контейнеры.
- В общей карте полей Name Editbox — pointer64 `+0xd0` (writer `0xc5db16`),
  PetName — pointer64 `+0xd8` (writer `0xc5dcc6`). Инициализация до загрузки
  и полный native object lifetime не закрыты. Readers: setOpen, update и оба
  Submit; собственных строкового редактора и состояния caret у Frontend нет.
- Name TextAccepted подписан `0xc5db84` на `0xc53f40`; PetName TextAccepted
  `0xc5dd34` — на `0xc5c2f0`. Первый Submit при непустом Name активирует
  PetName (`0xc53f44..0xc53f5c`) и возвращает true. Второй возвращает true
  при пустом PetName (`0xc5c30d`), при пустом Name активирует его (`0xc5c470`),
  иначе запускает ветвь создания. Enter в первом поле не создаёт персонажа.
- SetOpen сначала вызывает base (`0xc5c5b8`), при open=true очищает Name
  `0xc5c67a`, активирует его `0xc5c697`, задаёт PetName `Spot` из UTF-8
  literal `0xff3168` через `0xc5c826`, выбирает Destroyer (`0xfa7a50` ->
  `0xc5c85e`) и Dog (`0xfa8378` -> `0xc5c8a7`). Native UI переносит очистку,
  фокус и Spot; Frontend выбирает Destroyer по NAME, а не позиции каталога.
  Dog/gameplay selection и preview остаются открытыми, см. остаток.
- Update проверяет длину Name `0xc5cca6`, затем PetName `0xc5cd97`; видимость
  CreatePlayer задаётся `0xc5cdb1`. Это непустые исходные строки без trim и
  ASCII whitelist. DISPLAYNAME читается из ресурса `0xc5cdf6` и потребляется
  Window::setText `0xc5cfa9`; description — getDescription `0xc5cff4` ->
  `0xc5d1d3`. Порт передаёт resource display name и description как UTF-8.
- OnClick select1=14 передаёт sender name в setCreationClass `0xc5c0fe`,
  затем активирует Name `0xc5c112`. Typed class GUID в существующем
  FrontendRequest потребляется реальным PlayerSession. Back остаётся
  существующим state request/закрытием страницы.

`resource-derived`: оба `GuiLook/Editbox` имеют MaxTextLength=12 в
неизменённом `charactercreate.layout`. ValidationString там не переопределён.
Строка и длина принадлежат CEGUI UTF-32, наружу отдаётся библиотечный UTF-8.
Редактор не ограничен самодельным набором ASCII символов.

`library-derived`: stock CEGUI 0.6.2 Editbox выполняет font glyph availability,
validation, ограничение длины, caret, выделение, Delete, Backspace и TextAccepted.
Его defaults и порядок действий используются непосредственно из исходников.
Version match не объявляется полным Runic ABI/vendor сравнением. Устранён
выявленный прежний inferred-патч: shipped `Font::getCharAtPixel
@0xd1830..0xd18df` посещает буквальные glyphs и не пропускает colour tags;
upstream loop сохранён. Адреса операций — в `ui-inline-text.md`.

## Подключение и платформенная граница

`CeguiMenu` загружает native create layout в общий WindowManager, подписывает
события, управляет attach, экспортирует Falagard quads и читает реальный Name.
`Frontend` получает имя и выбранный class GUID; `Application` передаёт их
в действующее создание кампании и `.otc` SaveStore. Class text больше не теряет
не-ASCII символы при конвертации UTF-16 resource values.

`port-native`: Wayland использует host xkbcommon 1.13.1 для переданного
композитором keymap, modifiers и UTF-8/compose. Raw down/up, committed text
и leave идут через существующий ApplicationHost; временные отметки с pointer
events объединяются в общую упорядоченную доставку. При совпадении времени
сохраняется pointer-first policy адаптера. Leave отпускает CEGUI modifiers.
Repeat берёт rate/delay от Wayland, проверяет repeatability по keymap,
останавливается на release/leave/keymap replacement; повторные UI события
не добавляют gameplay press. Оригинальный OS/IME transport этим не переносится.
Полного Wayland text-input/IME протокола здесь нет.

## Проверки

`original_cegui_creation_contract` на настоящем pak прошёл: отсутствие второго
painter, пустой Name/Spot/default Destroyer вне зависимости от порядка каталога,
12 Unicode codepoints, Shift/Home выделение, UTF-8 replacement, Home/End,
Delete/Backspace, class labels/GUID/фокус, оба Enter gates, пустой PetName,
сырые пробелы без trim, reopen/cancel и снятие modifiers на leave. Проверен
literal-glyph caret контракт на строке с colour tag.

Повторно прошли native Main, Settings и error boundary (4/4 вместе с creation).
Общий Application/GL сценарий создал `Éclair`, вошёл в Town и записал `.otc`;
новый процесс загрузил то же UTF-8 имя и class GUID через Continue.
изолированные артефакты: `build-cegui/ui-repair-evidence/creation-utf8/`.
Это фактическая работа портированного приложения через scripted host,
без исходного процесса и без утверждения OS input delivery.
`paused_settings_render` повторно прошёл после изменения keyboard transport:
21 поле персонажа неизменно, ShowBlood записан, лишнего checkpoint нет.
Артефакты: `build-cegui/ui-repair-evidence/paused-settings-91nzi6ls/`.

Общий Application regression прошёл 5 отдельных процессов и 51 assertion:
создание, движение, inventory/equipment, resize, Options/exit checkpoint,
загрузка, точный replay и три разных класса. Артефакты:
`build-cegui/ui-repair-evidence/application-u09cucl4/`.
Сценарии town-new/continue обновлены под настоящий Options Exit и OPEN/CLOSE;
дополнительных кнопок Save/Save and Exit в оригинальном layout нет.
Exit checkpoint теперь revision1, а не две записи от прежних portable кнопок.
После CLOSE сценарий намеренно разрешает активные world frames; поэтому
старое требование идентичности frozen pixels заменено проверкой 16 полей
стационарного gameplay state. Это не проверка неизменности animation pose.

Desktop и shared Application probe собраны. Изолированное Wayland окно
запускалось, однако виртуальная доставка специальных клавиш не дала
однозначного результата; native Wayland editing не засчитывается проверенным.
Снимок этого окна не является доказательством создания персонажа.
Не выполнялись original frame comparison, performance или Android build.

## Точный остаток

Pet selection, pet-name save/gameplay consumer, character/pet scene preview,
Hardcore/difficulty, getEmptySaveFilename и оригинальные GameUI pending
fields/state transitions ещё не восстановлены. Dog/Cat/Ferret buttons
остаются отключены в наследуемой portable capability policy; это ограничение
порта, не правило оригинала. PetName сейчас реально участвует в исходных
visibility/focus/submit gates, но не заявляется сохранённым игровым именем.
Исходные `.SVB`, mod checks, ResourceManager/preview owner, localization,
полный unwind/cleanup и vendor delta больших методов остаются открытыми.
Callbacks после inject и direct portable campaign creation — адаптеры.

Следующий пакет native Character Load -> `.otc` list/selection/load/delete
теперь подключён: [граница и проверки](cegui-character-load.md).
Обнаруженная при этом байтовая конвертация class display/description исправлена:
потребитель использует UTF-8 конструктор CEGUI; тест включает не-ASCII class text.
OGRE/FreeImage исходники доступны в cache, однако производственная интеграция
этим пакетом не выполнялась.
