# Меню: состояния списка, ввод, звук и стоимость подготовки

## Источники

ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
CEGUI Base SHA-256 `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`.
Ресурсы: `media/UI/characterload.layout`, `settingsmenu.layout`,
`GuiLook.looknfeel`. Все оригинальные входы прочитаны из установленной игры.

## Список персонажей

`CContinueGameMenu::createMenus @0xc404c0` сохраняет:

| Поле | Окно |
|---|---|
| `+0xd0 + 8*i` | Player1…5 |
| `+0xf8 + 8*i` | Player1Name…5Name |
| `+0x120 + 8*i` | Player1Desc…5Desc |
| `+0x148 + 8*i` | PlayerHighlight1…5 |
| `+0x170/+0x178` | ScrollUp/ScrollDown |
| `+0x180/+0x188/+0x190` | Continue/CharacterName/CharacterModsWarning |
| `+0x198/+0x1a0` | DeleteConfirm/Delete |

`original-code`: `updateCharacterList @0xc3b2f0` обходит пять строк от scroll.
Занятые slot/name/description показываются (`0xc3b3a9/0xc3b3bb/0xc3b3cd`),
пустые slot/name/description/highlight скрываются (`0xc3b725..0xc3b752`).
Highlight видим при `selected == scroll+i` (`0xc3c571`), затем вызывается
`moveToFront` (`0xc3c57e`). ScrollUp видим при scroll!=0; ScrollDown — при
scroll+5<count. Continue/Delete видимы при непустом списке.

`Window::moveToFront_impl(false) @0x116550` сначала поднимает предков,
затем при ZOrderingEnabled переставляет окно в конец его AlwaysOnTop-группы
(`0x116633..0x11664e`). `UiLayoutState::move_to_front` переносит этот эффект
в presentation tree. ActivationEventArgs и полный жизненный цикл CEGUI
остаются за границей этого чистого запроса.

`onClick @0xc3fe80`: Delete показывает DeleteConfirm (`0xc3febc`), Decline
скрывает (`0xc3ff29`), Accept проверяет видимость (`0xc3ff41`), скрывает
(`0xc3ff57`), затем удаляет персонажа (`0xc3ff5f`). Порт скрывает prompt до
дискового запроса. Пока запрос ожидается, смена выбранного слота блокируется
адаптером приложения; Escape отменяет prompt. Это явно portable input policy.

`update @0xc3a350` обновляет CharacterName из preview-персонажа
(`0xc3a49a`), либо очищает строку. Сейчас имя приходит из выбранного `.otc`.
`PlayerNDesc` также остаётся кратким `.otc`-адаптером. Original SVB, preview
object, полная строка description и проверка модов остаются открытыми.

Производственная цепочка: `Frontend::frame` → `continue_menu_layout_state`
→ `UiLayout::resolve` → единый paint list. Проверки `ui_menu_state_test`
передают значения count/scroll/selected/confirmation непосредственно в чистую
функцию и проверяют свойства, наследование видимости и порядок окон.

## Звук и указатель

`CSettingsMenu::setOpen @0xbd5560`: MusicVolume получает max=1 (`0xbd5827`)
и сохранённый float (`0xbd5839`). `update @0xbd47e0` читает тот же float
(`0xbd4851`), вызывает live updateAudioLevels (`0xbd489d`), сохраняет float
(`0xbd4e30`) или восстанавливает сохранённые audio levels при Cancel
(`0xbd5090..0xbd512f`). Геометрия и преобразования ползунка: [ui-slider.md](ui-slider.md).

Приложение потребляет текущий draft пока открыты настройки, clean после
отмены, applied после успешной записи. Новый трек получает актуальную
громкость, а не значение стартовых options. Существующий audio backend
воспроизводит музыку; настройка эффектов сохраняется, полный звуковой mixer открыт.

Ресурсные Hover/Pushed получают физическое положение/удержание указателя.
Keyboard focus и выбранный персонаж остаются отдельными состояниями.
Поиск цели других страниц также использует полное дерево и parent-chain.
Capture/modal, double/triple grouping и исходный Continue double-click
подключены к общему runtime: [закрытие CEGUI frontend](cegui-frontend-closure.md).
Три Settings Combobox также подключены к typed draft/persistence; полный
world-shadow/ParticleUniverse renderer остаётся за UI-пакетом.

## Подготовка и отрисовка

`port-native`: frontend кеширует разрешённый кадр до изменения модели или
viewport. Положение указателя накладывается на копию кеша. `UiSkinCache`
кеширует команды Falagard по всем используемым свойствам, состоянию и viewport;
100 повторных одинаковых запросов дают одну компиляцию. Кеш ограничен 512 окнами.

Подготовка main menu загружает playable classes и свои ресурсы. Каталоги
spawn/unit types/quests/merchant/skills создаются при первом create/load
или прямом входе в игровой режим и затем переиспользуются. Полный eager
перебор `loader.load` удалён; потребители пользуются кеширующей загрузкой.
Время старта и FPS этим изменением не измерены.

GLES получает четыре цвета вершин и исходную диагональ TL→BR, включая
неодноцветные ColourRect. Inline Serif-текст: [ui-inline-text.md](ui-inline-text.md).
Сцена/камера: [menu-scene.md](menu-scene.md). Проверки этого прохода —
числовые, ресурсные и компиляция; приложение и кадры не запускались.

Полное UI completion остаётся partial: персонажи/питомец в preview,
проводка pet/difficulty, resolution list/FSAA, native saves, полный CEGUI
и игровые панели требуют своих producer/consumer цепочек.
