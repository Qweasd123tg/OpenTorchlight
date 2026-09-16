> Обновление large-10: тексты меню, динамические имена, optionsmenu-пауза и
> дефект загрузки атласа реализованы в ограниченном переносимом подмножестве.
> См. `UI_MENU_COMPLETION_RESULT_RU.md`. Это задание целиком НЕ закрыто:
> нет текущего прогона настоящего pak, оригинального font/DPI differential,
> полного Falagard/9-slice/теней, inventory и точных HUD-формул.
> Начинать с актуального верха `NEXT_CHECKS.md`, а не повторять потерянные подписи.

# Задание GPT Pro: добить оригинальный интерфейс

> Это задание следующего прохода. Оно уточняет `NEXT_CHECKS.md` и продолжает
> `research/ui-visuals.md`. Работать поверх архива целиком, начиная с текущего
> состояния: core 41/41, assets 31/31, reference 11/11, render 5/5 на настоящих
> pak и ELF. Ничего из принятого не ломать.

## Что уже сделано в UI-проходе (не переделывать с нуля)

* `<Font>` CEGUI 0.6.2 + FreeType: `src/ui_font.cpp`,
  `include/torchlight/ui_font.hpp`. Масштаб снят с pinned
  `libCEGUIBase.so.1` (`Font::notifyScreenResolution @0xd18e0`,
  `FreeTypeFont::updateFont @0xe07b0`). DPI=96 — `inferred`.
* HUD из `bottomhud.layout`: `src/ui_hud.cpp`; полосы HP/mana/XP и подписи
  хоткеев. Точная бар-математика `CGameUI::updateIngameUI @0xab8100` не снята.
* Кнопки меню: картинки `NormalImage/HoverImage/PushedImage` читаются из
  `media/UI/GuiLook.looknfeel`; подписи — из layout.
* Проверки: `original_ui_font_resource` (настоящий pak),
  HUD-кадры в `gles_ui_headless` (`--hud-fixture`).

## Что «обрезано» и должно быть доделано

### 1. Главный экран и меню New/Load (приоритет)

Сейчас `Frontend::frame` (`src/frontend.cpp`) кладёт в кадр только
`StaticImage`-декорации без callback; все `GuiLook/StaticText` /
`StaticTextOutline` из layout **теряются**. Поэтому не видны CopyrightInfo,
CharacterModsWarning, TabTextA/B, подписи полей; заголовок рисуется
захардкоженным «OPENTORCHLIGHT» (`src/gles_ui_renderer.cpp`).

Нужно:

* добавить в `FrontendFrame` список текстовых виджетов (rect+text+font) и
  рисовать их ресурсным шрифтом; placeholder «1» и пустые — пропускать;
* заголовок брать из layout (или не рисовать, если в оригинале его нет);
* разобрать, какие `Window` окон являются кнопками по `onClick`, и не
  дублировать их текст поверх скина;
* проверить `charactercreate.layout` и `characterload.layout` на реальном pak:
  все подписи/табы/имена слотов должны рисоваться из layout, а не синтетикой
  порта; порт-специфичные контролы сохранить как явно помеченные supplemental.

### 2. Пауза

Сейчас `pause` — синтетические кнопки. В оригинале это
`media/UI/optionsmenu.layout` (Title «Options», кнопки Settings, ExitGame,
ReturnToGame; `ReturnToGame` → resume). Подключить этот layout, честно
обозначить, что Settings не реализован, а сохранение — порт-дополнение
(`.otc`, не оригинальный `.SVB`). Не выдавать Exit to Title за оригинальное
поведение без трассы.

### 3. Инвентарь и окна персонажа

Сейчас инвентарь — диагностический список строк поверх прямоугольников
(`draw_inventory_overlay`, `GlesUiRenderer::draw_overlay`). Нужно:

* отрисовать `media/UI/inventorymenu.layout`: рамку, слоты, табы
  Equipment/Spells/Fish, картинки `UIIcons`/`itemicons`;
* связать слоты с предметами порта (иконки экипировки: цель —
  `CEquipment::createIcon @0x882e30`, сейчас unseen);
* при отсутствии точного маппинга — явный `prototype`, не подменять
  оригинальный layout выдуманной сеткой.

### 4. Шрифты: бит-в-бит с оригиналом

* Исполнить оригинальный `CEGUI::FreeTypeFont` изолированно (pinned
  `libCEGUIBase.so.1`, те же TTF и параметры экрана) и сравнить атлас глифов
  с `src/ui_font.cpp` (метрики и пиксели; допускается документированное
  расхождение только из-за версии FreeType).
* Закрепить DPI: снять с оригинального renderer-пути, а не принимать 96.
* Статус результата — `library-derived` точно или явная граница.

### 5. Falagard-подмножество

Разобрать `GuiLook.looknfeel` для нужных типов: состояния кнопок
(normal/hover/pushed/disabled), составные рамки окна
(`WindowTopLeft/Top/Right/BottomLeft/...`), тени текста, области Label.
Не изобретать скин: имена и раскладка — из looknfeel/scheme.

### 6. HUD-формулы

`updateIngameUI @0xab8100` не декомпилируется Ghidra (timeout). Снять участок
`0xab885b..0xab8974` дизассемблером, получить точные формулы позиции/размера
полос HP/mana/XP (округления, якорь, mouseover) и заменить `inferred`
в `src/ui_hud.cpp` differential-тестом по неизменённым байтам, как сделано
для золота и XP.

### 7. Остальное из `NEXT_CHECKS.md`

Порядок после главного экрана: inventory → stats/skills/journal →
merchant/stash/quest dialog. `--desktop` harness (тестовый композитор)
по-прежнему NOT RUN: не выдавать его за выполненный.

## Общие правила

* Читать `AGENTS.md`; статусы `original-code`, `library-derived`,
  `resource-derived`, `inferred`, `prototype` обязательны.
* Сначала ресурс/ASM-доказательство, потом код; differential-тесты для
  численных участков; CTest для каждой новой цепочки.
* Не поднимать таймауты/допуски ради зелёного, не отключать проверки.
* Ассеты и ELF — read-only, в архив не копировать.
* Держать зелёными `--core --assets --render` на настоящем pak;
  `--reference` запускает интегратор, не заявлять его выполнение без ELF.

## Результат прохода

Один авторитетный ZIP, cumulative patch к текущему архиву и русский отчёт:
что именно стало как в оригинале (с адресами/ресурсами и доказательствами),
что осталось `inferred`/`prototype`, какие проверки это подтверждают.
