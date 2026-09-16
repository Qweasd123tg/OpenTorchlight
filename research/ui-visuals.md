# Обновление large-10

Выявленный дефект large-9: GPU получал пустой atlas до растеризации; метрики CPU
и зелёный тест `original_ui_font_resource` не гарантировали видимый текст.
Добавлены `atlas_revision`, загрузка после glyph creation и реальный readback-тест
первого/нового глифа/Unicode/resize. Старый renderer воспроизводимо даёт 0 ярких
пикселей на авторском первом глифе; новый — 153. Это исправление порта, не
доказательство оригинального FreeTypeFont/OGRE output. FreeType 2.13.3 здесь настоящий,
но SDK отсутствует: отдельный стенд использовал проверяемые test-only ABI declarations.

Также добавлены кадр текстовых виджетов, .otc имена и ресурсная optionsmenu-пауза.
Точный список: `research/ui-menu-completion.md`, `UI_MENU_COMPLETION_RESULT_RU.md`.
Нормальный/фокусный/disabled скин — частично; source PushedImage пока не задействован.
Цвета текста/outline shadows/полный Label-area остаются приближёнными или открытыми.

Ниже — историческое исследование large-9.

---

# UI-визуал: оригинальные шрифты, HUD и скин меню

## Что восстанавливается

Первый шаг визуального этапа: вместо диагностических прямоугольников и
прототипного 5x7-шрифта UI рисует ресурсы оригинала:

1. `<Font>`-ресурсы CEGUI 0.6.2 (`media/UI/*.font`) и TTF через FreeType.
2. `media/UI/bottomhud.layout` — статичные картинки HUD и полосы HP/mana/XP.
3. Текстуры кнопок меню (`ButtonStandardRed` и состояния) из
   `media/UI/GuiLook.looknfeel`.

Это `resource-derived` + `library-derived` повторение, не побитовое
воспроизведение кадра оригинала: у оригинала OGRE + `CEGUIOpenGLRenderer`
и полный Falagard. См. границы ниже.

## Шрифты: снятые с pinned-библиотеки правила

Оригинальная библиотека:
`/home/qweasd123tg/Games/Torchlight/game/lib64/libCEGUIBase.so.1`,
SHA-256 `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`.

* `<Font Name Size NativeHorzRes NativeVertRes AutoScaled AntiAlias>` из
  `media/UI/*.font`; `Filename` указывает на `media/ui/Torchlight Regular.TTF`.
* `Font::notifyScreenResolution` @`0xd18e0`: `horzScale = width / NativeHorzRes`,
  `vertScale = height / NativeVertRes`; при `AutoScaled` вызывается
  `updateFont`.
* `FreeTypeFont::updateFont` @`0xe07b0`: `charSize = Size * 64`;
  при `AutoScaled` `charWidth = trunc(charSize * horzScale)`,
  `charHeight = trunc(charSize * vertScale)`; вызов
  `FT_Set_Char_Size(face, charWidth, charHeight, dpiX, dpiY)`.
  DPI берётся у рендерера; для OGRE-пути принято 96 (`inferred`, не доказано
  отдельным ASM).
* Метрики: `face->size->metrics.ascender/height` в 1/64 px.
* Растеризация: `FT_Load_Char(..., FT_LOAD_DEFAULT)` + `FT_Render_Glyph`
  (`NORMAL` при `AntiAlias`, иначе `MONO`) — режим повторяет CEGUI, но результат
  зависит от версии FreeType.

Проверка `original_ui_font_resource` на настоящем pak: 7 шрифтов, 665
ASCII-глифов при 1024x768, непустые метрики. Например `Serif` size=11 →
line=17, ascent=14 px.

## HUD

`UiHud::frame` читает `bottomhud.layout` bounded-парсером (та же семантика
`UnifiedAreaRect`, что уже проверена для меню) и раскладывает окна так:

* статичные `StaticImage`/`ImageButton` с `Image`/`NormalImage` рисуются как есть;
* `PlayerHealthBarSub`, `PlayerManaBarSub` — вертикальные полосы, рост снизу
  вверх; `ExperienceBarSub` — горизонтальная; доля передаётся из состояния
  игрока;
* `Target*` скрываются без цели;
* текст: `LevelName` — имя текущей зоны, `*Hotkey*` — оригинальные подписи
  раскладки.

Оригинальный `CGameUI::updateIngameUI @0xab8100` не декомпилирован (Ghidra
timeout). Поведение полос снято чтением ASM
(`/tmp`-выгрузка не коммитится): подокно баров получает вычисленные позицию и
размер от `manaFloat/maxMana` и `HP/maxHP` (`0xab8881..0xab8974`). Полная
формула якоря/округлений НЕ проверена отдельным differential-тестом — статус
`inferred`.

## Дифференциальная проверка

`gles_ui_headless` на авторской HUD-фикстуре рисует реальным Mesa/EGL
`bottomhud` с четырьмя цветными полосами и проверяет: вертикальный якорь снизу,
доли 0/0.25/0.5/1.0, горизонтальную XP-полосу. Это регрессия порта на авторских
ресурсах, а не сравнение с оригинальным кадром.

## Границы

* Полный Falagard looknfeel не реализован: состояния, 9-slice, тени, клиппинг
  и layout-движок CEGUI повторены частично.
* Пиксельный растр глифов и порядок GL-состояний отличаются от OGRE/CEGUI;
  побитовое совпадение кадра не заявляется.
* `desktop`-группа не проверена: нет тестового Wayland-композитора.
* Следующий шаг: сверка атласа глифов с оригинальным `FreeTypeFont`
  изолированным вызовом, затем `inventorymenu.layout` и полный `updateIngameUI`.
