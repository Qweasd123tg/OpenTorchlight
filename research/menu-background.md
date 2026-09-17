# Фон главного меню: механизм найден, тема по умолчанию открыта

## Доказано (original-code, ELF `91b41ae9…`)

- Фон — настоящая 3D-сцена: `CGameClient::loadMenuLevel(int,int,wstring)`
  @`0x584b80` делает `getLevelTemplateDataForDepth` + `CLevel` + `loadRoomLayout`
  + `Camera::setPosition/lookAt` + `stopMusic/playMusic`. Вызывается из
  `CGameClient::setGameState` (3 сайта) для меню-состояний.
- Имя данжа хранится в `CGameClient+0x1098` (`setCurrentDungeon`), с
  оверрайдом через командную строку (`CCmdLineParser::GetStringParam`).
- Формат правил меню — обычный LEVEL `.adm`: `MAINMENU_TOWNRULES` и др.
  грузятся существующим `LevelSceneLoader::load_rules` (проверено пробой:
  OK, `randomized=0`). Генератор портя их соберёт без нового парсера.
- В бинарнике НОЛЬ байтовых/UTF-16 вхождений `MAINMENU/TOWNRULES/1X1SINGLE`:
  выбор темы идёт через данные/строковую таблицу, не хардкод.
- Музыка рядом: `playMusic` зовётся из `loadMenuLevel` и из `loadLevel`
  (имя файла = `StringUpper(...)` от имени уровня). Маппинг тем→треки
  (`MINES.OGG` и т.д.) и роль `TITLE.OGG` — открыты.
- Живой трейс оригинала (`~/.runicgames/.../CEGUI.log`, 19с, убит на
  сплэше) подтверждает порядок загрузки: `LOADING.LAYOUT` первый, затем
  bulk-прелоад всех меню. До меню-состояния трейс не дошёл.

## Открыто следующим шагом

- Дефолтное имя данжа (глобальный wstring-инит `CGameClient`, таблица
  @`0x1424558`) и значения камеры меню: нужен Ghidra-разбор `setGameState`
  или живой трейс до меню (здесь нет Xvfb).
- До тех пор порт фон НЕ рисует (не выдумывать тему) — но сплэш загрузки
  `loading.layout` уже показывается первым кадром по механизму оригинала.
