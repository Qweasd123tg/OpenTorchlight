# Политика окна и мыши оригинала

Статус: захват мыши — `original-code`; размер/фулскрин — зафиксировано, не всё
перенесено (меню настроек отсутствует).

## Оригинал (ELF `91b41ae9…`, SDL2)

- Создание окна (~`0x568605`): `SDL_CreateWindow(..., flags=0x3)` →
  `SDL_SetWindowIcon` → **`SDL_SetWindowGrab(1)`**. Захват включён сразу.
- `CGame::frameEnded`: оконный режим — `SetWindowGrab(0)` + `SetWindowFullscreen(0)`
  (@`0x556ddf/0x556ded`); фулскрин — `Fullscreen(0)` → `SetWindowPosition(0,0)` →
  `SetWindowSize(w,h)` → `Fullscreen(1)` → **`SetWindowGrab(1)`** (@`0x55715f`).
  Размер — из настроек `KSETTINGS_RES_WIDTH/HEIGHT`, трекинг `gLastWidth/Height`,
  `GResizeWidth/Height`, флаг `GRecreateUI`.
- `SetCursorPos @0xf63240` — заглушка (`xor %eax; ret`): Linux-порт позицию
  курсора программно не двигает.
- Курсор: `CGameUI::updateHardwareCursor` — `SDL_ShowCursor(0/1)` +
  `SDL_SetCursor` по `ECursorState` (до 5 состояний + дефолт).

Итог: в фулскрине (дефолт) мышь захвачена и не уходит из окна; размер окна —
только из настроек, произвольного ресайза нет.

## Порт (Wayland)

- SDL2 нет; захват = `zwp_pointer_constraints_v1.confine_pointer` с
  `LIFETIME_PERSISTENT` на всё окно (`src/linux_desktop_main.cpp`,
  `maybe_confine`). Протокол вендорен:
  `tools/wayland-protocols/pointer-constraints-unstable-v1.xml`,
  SHA-256 `f980fac900ba1dcfbbe97f588fc17b893926bd2b57624563653a1bfe4d035948`
  (апстрим wayland-protocols, unstable v1). Без протокола — честный фолбэк без
  захвата + notice в stderr.
- Композитор сам отпускает захват при потере фокуса окном; выйти можно Alt-Tab.
  Оконные декорации композитора при захвате недоступны — как в фулскрине
  оригинала.
- Фиксированный размер из настроек и меню настроек — открыто (окно пока
  следует compositor-configure 1280x720 + ресайз; шрифтовой автоскейл от
  фактического размера повторяет `notifyScreenResolution`).
