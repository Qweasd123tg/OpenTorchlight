# Главный экран: кнопки, класс, имя — resource-derived

Статус: кнопки/тексты — `resource-derived`; 3D-превью персонажа — открыто.

## Ресурсы (read-only pak `8650ad75…`)

- `media/UI/mainmenuframe.layout`: кнопки `NewGame→guiNewGameMenu`,
  `ContinueGame→guiContinueGameMenu`, `ContinueLast→guiContinueGame`,
  `Settings→guiSettingsMenu`, `ExitGame→guiExitApplication`; тексты
  `CopyrightInfo`, `TabTextA/B`, `Credits`. Табы `guiSelectA/C`, кредиты
  `guiSelectB/D` остаются disabled (не реализованы).
- `media/UI/charactercreate.layout`: `Back→guiBack`, `CreatePlayer→guiNewGame`,
  `Destroyer/Vanquisher/Alchemist→guiSelect1` (RadioButton),
  `Dog/Cat/Ferret→guiPet1` (питомец не реализован — disabled с текстом ресурса),
  `CharacterClassHeader/CharacterClass/CharacterClassDescription` Text=1
  (заполняются в рантайме), `EditBox` MaxTextLength=12, `PortraitBox` 140x400
  без привязки (заполняется 3D-превью, см. ниже).
- Имя/описание класса — UNIT DAT через BASEFILE-цепочку:
  `NAME/DISPLAYNAME/DESCRIPTION` (напр. Alchemist: "The Alchemist channels the
  power of Ember…"). Порт: `PlayerPrototype::description` → `FrontendClass`
  → `CharacterClassDescription`; `CharacterClass` ← имя класса.

## Оригинал (ELF `91b41ae9…`)

- `CMainMenu::onClick @0xc4ae80` — диспетчер главного меню (switch по
  `ELayoutFunction`: `0x40/0x42/0x43/0x5e/0x01/0x03/0x04/0x05…`, ветви
  `closeAll`, `toggleSettings`, `canLoad`-гейт).
- `CNewGameMenu::onClick @0xc5c040`, `setOpen @0xc5c5a0`, `update @0xc5cc30`,
  `createMenus @0xc5d730`, `getEmptySave`, `handle_Submit(Pet)` — выбор
  класса/питомца и сабмит. Конструктор берёт `Ogre::SceneManager/Camera`:
  превью персонажа — настоящая 3D-сцена, не картинка.
- `CMenuManager::create @0xc2bbb0`, `setActiveMenu`, `reloadMenuCharacters`,
  `CGameUI::updateMenuUI @0xa844d0`, `CGameUI::onClick @0xa924c0`.

Порт повторяет маршутизацию по имени колбэка (регистронезависимо) из
`research/ui-actions.json`, а не по числовому enum — поведение то же,
числа enum не заявляются.

## Что сделано в порте

- `FrontendClass::description` + `PlayerPrototype::description` (пусто, если нет).
- `frame(create)`: `CHARACTERCLASS←имя`, `CHARACTERCLASSDESCRIPTION←описание`.
- `EditBox` — поле имени; лимит `32→12` по `MaxTextLength`.
- Питомец/Dog/Cat/Ferret, Settings — disabled с ресурсным текстом; табы
  кредитов работают (ниже).

## Табы кредитов (original-code семантика + точный контент, сделано)

- `CMainMenu::onClick @0xc4ae80`: `GUISELECTA/B/C/D` (id 64–67) тогглят две
  фулскрин-панели: A/B — окно @+0xe8 (показать/скрыть), C/D — окно @+0xf0.
  Порт повторяет состояние флагами `show_credits_/show_credits_b_`.
- Контент панели 1 — статический roll из rodata `0xbf2e30..0xbf313f`
  (37 строк: Runic team, Voice Talents, QA/Art, Ogre3d/CEGUI/PU/FMOD).
  Разделитель `\n` — inferred (один setText в один ItemText); `|c..|u`
  инлайн-цвета не поддерживаются рендером (открыто).
- Панель 2 (вероятно моды — `update()` дёргает `getEnabledModNames`) без
  доказанного контента: C/D роучены (не шумят как unsupported), но кнопок не
  создают и панель не открывают. Таб A — только из ресурсов (без фолбэка,
  чтобы не красть фокус на синтетике); закрытие — модальной кнопкой поверх.
- Проверка `frontend_resource_test` на настоящем layout: закрыто→пусто,
  открыто→Runic/Ogre3d, закрытие→пусто.

## Доразбор: превью персонажа и update()

- `CNewGameMenu::update @0xc5cc30` вызывает `CDataGroup::GetDataValue`,
  `CCharacter::getDescription` и дважды `CEGUI::Window::setText` (+`setVisible`):
  это заполнение `CharacterClass`/`CharacterClassDescription` из данных персонажа.
  Порт повторяет источник (`UNIT DESCRIPTION`), сам `getDescription`-диспетчер
  побитово не сверен.
- `CNewGameMenu::setOpen @0xc5c5a0`: `setText/setVisible`, `setCreationClass`,
  `setCreationPet` — выбор класса/питомца уходит в `CGameClient`.
- `CNewGameMenu::createMenus @0xc5d730`: только CEGUI — `loadWindowLayout`,
  `convertToScreenScale`, `mapToFunctions`, `addChildWindow`. Ogre-вызовов нет.
- `PortraitBox` отсутствует в строках ELF (есть только `CharacterClass`,
  `CharacterClassDescription` @`0xbf316d/0xbf3187`): код его не трогает,
  это статическая пустая рамка 140x400. 3D-превью персонажа в create-меню нет.
- Фон главного меню (`media/layouts/MainMenus/MAINMENU_*.LAYOUT`): жёсткой ссылки
  в бинарнике нет (нет строк `MAINMENU`/`.layout`) — выбор сцены идёт через данные,
  отдельное исследование. Порт фон не рисует; кнопки/тексты поверх — по ресурсам.

## Открыто

- Числовой `ELayoutFunction`-диспетчер `CMainMenu/CNewGameMenu::onClick`
  побитово не сверен (маршрутизация по имени эквивалентна по ресурсам).
- Pet-выбор `guiPet1`, difficulty, `getEmptySave`→слот.
- Дата-драйвен фон меню из `media/layouts/MainMenus/` (см. выше).

## Удаление персонажа (original-code, сделано)

- `CContinueGameMenu::onClick @0xc3fe80` зовёт `deleteCharacter @0xc3fd00`;
  тот делает `GetSaveDataPath` + `AssembleAbsolutePath` + `DeleteFile`, затем
  `reloadFiles` + `selectCharacter` + `updateCharacterList`.
- Порт: `SaveStore::remove` (только свой каталог, `valid_slot` против
  траверса, идемпотентный false на отсутствующем), `Frontend` confirm-стейт
  (`delete`→`accept`/`decline`, `FrontendCommand::remove`), кнопки
  accept/decline видны только пока висит confirm — как `DeleteConfirm` в
  оригинале. Проверки: `frontend_test` (без подтверждения не удаляет) и
  `save_checkpoint_test` (удаление/повтор/траверс).

## Описание слота (resource-derived из .otc, сделано)

- Оригинал собирает Desc в `updateCharacterList @0xc3b2f0` из кусочков
  `g_Level/g_Difficulty/g_Easy/Normal/Hard/VeryHard/Hardcore/g_Hrs/Mins/Secs/
  g_Dead/g_Retired` — точная склейка и .SVB-поля (время игры) у нас открыты.
- Порт пишет из своих данных: `Level {level} {Class}` + `, Hardcore`
  (уровень/хардкор добавлены в `SaveSlotInfo` из чекпоинта; класс — по guid).
  Проверка `frontend_resource_test` на настоящем layout. Точные слова
  сложности, время и Dead/Retired — открыто.
