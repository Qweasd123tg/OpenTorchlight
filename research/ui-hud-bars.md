# UI HUD бары: ASM-разбор updateIngameUI (inferred → original-code, в работе)

Статус: `inferred`. Ниже — точные адреса и скелет формулы для перевода в `original-code`.

## Вход

- ELF SHA-256 `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
- `CGameUI::updateIngameUI(float, CGameClient*, Ogre::RenderWindow*) @0xab8100`
  (Ghidra `research/decompiled-core/game_ui.c:16737` падает по timeout — нужен ASM).
- Полоска mana: `0xab8881..0xab8ac8`; полоска HP: `0xab842e..0xab8596`; обе идут через
  `CEGUI::Window::setPosition @0x5548a8` / `setSize @0x555178`.

## Разбор mana (пример, HP аналогично)

```
ab8881: call CCharacter::manaFloat      ; xmm0 = manaFloat
ab888e: movss [rsp+0xa8],xmm0
ab8897: call CCharacter::maxMana        ; eax
ab889c: cvtsi2ss xmm0,eax               ; (float)maxMana
ab88a0: movss xmm4,[rsp+0xa8]           ; manaFloat
ab88a9: movss xmm2,[rsp+0x98]           ; 0.0 (см. ab8456: xorps+movss)
ab88b2: movss xmm3,[r15+0x1734]
ab88c3: divss xmm4,xmm0                 ; fraction = manaFloat / maxMana
ab88c7..ab88e5: max(fraction, 0.0) через cmpnltss/andps/andnps/orps
ab88f1: movss [rsp+0xa8],xmm0           ; clamped fraction
ab88fa..ab8914: UDim-вычисление с trunc:
  cmpltss/andps/andnps/orps (выбор scale/offset),
  addss, cvttss2si, cvtsi2ss, addss [r15+0x16e8]
ab892f..ab895a: второе UDim-вычисление с [r15+0x1738], [r15+0x16e4]...
ab8974..ab89f8: сборка UVector2 в [rsp+0x3f40..] и call setPosition
ab89fd..ab8ac8: сборка UVector2 размера, mulss [rsp+0xa8] (fraction),
  subss/mulss и call setSize
```

Ключевые константы стека (инициализация в HP-пути, переиспользуется в mana):
- `[rsp+0x98] = 0.0` (`ab8456: xorps xmm4 + movss`).
- `[rsp+0xa0] = 0.5` (`ab8488: movss xmm2,[fa4810]` где `fa4810 = 0.5f`).
- `[rsp+0xa8] = clamped fraction` (0.0 low-clamp доказан; high-clamp 1.0 — проверить:
  `fa86f4 = -0.5f`, `fa47fc = 1.0f`, `fa4810 = 0.5f`, `fa8780 = -0.0f`).

Поля `CGameUI` (`r15`): `0x16d0/0x16d4/0x16d8`, `0x16e0/0x16e4/0x16e8`,
`0x1720/0x1724/0x1728/0x1730/0x1734/0x1738`, `0x140/0x158/0x168` (окна баров).
Это layout-база/масштаб для UVector2, а не просто доля.

## Что не совпадает с портом

`src/ui_hud.cpp::frame` сейчас делает только `clamp_fraction` 0..1 и отдаёт долю
рендереру (`vertical anchor bottom`, `horizontal XP`). Оригинал считает полный
`UVector2(position) + UVector2(size)` с `trunc` (cvttss2si) на каждом UDim,
умножением размера на fraction и вычитанием (`subss`) для якоря снизу.

## Следующий шаг к original-code

1. Выгрузить полный HP-участок `0xab842e..0xab8596` + mana `0xab8881..0xab8ac8`
   в `research/disassembly/` (адресный экспорт, не коммитить полный дамп).
2. Построить минимальный стенд: подать HP/maxHP, mana/maxMana, поля `r15+...`
   (снять с реального `bottomhud.layout` resolve) и сравнить UVector2 с портом.
3. Заменить `inferred` в `ui_hud.cpp` на точную формулу с `trunc` и `setPosition/setSize`.
