# UI шрифт: DPI 96 и формула FreeTypeFont — library-derived

Статус: `library-derived` (было `inferred` для DPI). Не побитовый кадр оригинала.

## Входы (read-only, хеши зафиксированы)

- ELF: `/home/qweasd123tg/Games/Torchlight/game/Torchlight.bin.x86_64`,
  SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
- `lib64/libCEGUIBase.so.1`,
  SHA-256 `57a888d741b1a0a284915c6d5066fef68c1bcc1ebfd0163f6be8720e3cdda2aa`.
- `lib64/libCEGUIOgreRenderer-1.6.5.so` (OGRE-путь оригинала),
  `lib64/libCEGUIOpenGLRenderer.so` (второй путь CEGUI).
- Ресурсы: `media/UI/*.font` из `pak.zip` (7 шрифтов, `Filename` → `media/ui/Torchlight Regular.TTF`).

## Что доказано дизассемблированием (без запуска игры)

### 1. DPI = 96 — обе реализации CEGUI возвращают 0x60

`OgreCEGUIRenderer::getHorzScreenDPI / getVertScreenDPI`:
```
6d30: b8 60 00 00 00  mov $0x60,%eax ; 96
6d40: b8 60 00 00 00  mov $0x60,%eax ; 96
```
`OpenGLRenderer::getHorzScreenDPI / getVertScreenDPI` (`0x281d0/0x281e0`):
```
281d0: b8 60 00 00 00  mov $0x60,%eax
281e0: b8 60 00 00 00  mov $0x60,%eax
```

Вывод: `FT_Set_Char_Size(..., 96, 96)` в порту — повторение зафиксированной
версии оригинальной библиотеки (`library-derived`), а не подбор.
Прошлый статус `inferred` для DPI закрыт.

### 2. `Font::notifyScreenResolution @0xd18e0` (libCEGUIBase)

```
d18e0: movss (%rsi),%xmm0
d18eb: divss 0x290(%rdi),%xmm0        ; width / NativeHorzRes (0x290)
d18f3: movss %xmm0,0x288(%rdi)        ; horzScale
d18fb: movss 0x4(%rsi),%xmm0
d1900: divss 0x294(%rdi),%xmm0        ; height / NativeVertRes (0x294)
d1908: movss %xmm0,0x28c(%rdi)        ; vertScale
d1910: jne d1918                      ; if AutoScaled(0x284)==0 ret
d1918: jmp *%rax                      ; virtual updateFont (offset 0x18)
```

Порт `UiFont::notify_screen_size` повторяет это 1:1: деление на native,
ранний выход без `AutoScaled`, очистка глифов + `set_char_size`.

### 3. `FreeTypeFont::updateFont @0xe07b0` — формула размера

- `e087e: movss 0x4e8(%rbx),%xmm1` — `Size`; `e0888: mulss %xmm6,%xmm1`,
  где `xmm6 = 64.0f` (`0x42800000` по `0x1d8390`). Итог: `Size*64`.
- `e0848..e0869`: два виртуальных вызова рендерера `*0xb0 / *0xb8`
  (Horz/Vert DPI), результаты → `r12d/ebp` → аргументы `FT_Set_Char_Size`.
- `e0de0..e0def` (ветвь `AutoScaled != 0`):
```
mulss 0x288(%rbx),%xmm2  ; (Size*64) * horzScale
mulss 0x28c(%rbx),%xmm0  ; (Size*64) * vertScale
jmp e0898                 ; trunc + FT_Set_Char_Size
```
- `e0898/e08a4`: `cvttss2si` = `trunc`, затем `FT_Set_Char_Size`.

Порт `UiFont::Impl::set_char_size` повторяет:
`points = Size*64`, `sx = trunc(points*horzScale)` при `auto_scaled`,
иначе `trunc(points)`, затем `FT_Set_Char_Size(..., 96, 96)`.

Метрики `face->size->metrics.ascender/height / 64` и растеризация
`FT_Load_Char(FT_LOAD_DEFAULT)` + `FT_Render_Glyph(NORMAL при AntiAlias иначе MONO)`
повторяют режим CEGUI; сам растр зависит от версии FreeType.

## Граница

- Это `library-derived` повторение, не бит-в-бит кадр OGRE/CEGUI.
- Растр глифов зависит от версии FreeType; порядок GL-состояний и полный
  Falagard не заявляются.
- Следующее: `CGameUI::updateIngameUI @0xab8100` (бары `0xab8881..0xab8974`)
  остаётся `inferred`; Ghidra-декомпиляция `00ab8100` падает по timeout,
  нужен адресный ASM-разбор и дифференциальный тест.
