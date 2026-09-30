# Доступные исходники перед следующим производственным пакетом

Проверено 2026-09-30: рабочее дерево, архив игры, официальный upstream и
release-архивы. Это инвентаризация доступности и границ, не новый completion.
Текущие изменения CEGUI в рабочем дереве сохранены; новая игровая логика
в этом аудите не добавлялась.

## Результат

| Подсистема | Подтверждённое состояние | Следующее использование |
|---|---|---|
| CEGUI 0.6.2 + Falagard + Expat | Исходники в `third_party/cegui-0.6.2`, собраны и используются Main/credits/Settings/Options/character create | Load и HUD через ту же библиотеку |
| OGRE 1.6.5 | Точный release source найден, скачан и проверен по version macros | Проверить переиспользование serializers, skeleton/animation, scene/resource ownership; renderer требует отдельного решения |
| FreeImage 3.13.1 | Версия shipped ELF установлена по инструкциям; соответствующий source release скачан | Кандидат для DDS/image codecs вместо нового ручного декодирования |
| LodePNG, candidate 2014 | Два исходных файла скачаны по закреплённому commit; хеши совпали с прежним исследованием | Источник для границы оригинальных PNG-операций; текущий production decoder уже использует libpng |
| ParticleUniverse | Статически в игровом ELF; исследование указывает 1.0/pre-1.01, исходники именно этой версии не найдены | Более новый source — кандидат с обязательной проверкой отличий, не готовая замена |
| FMOD Ex 4.36.21 | Shipped binary/API; публичный source release не найден | Переиспользовать подходящий audio backend, восстанавливать игровые вызовы; source FMOD требует отдельного доступа |
| zlib/libpng/FreeType/PCRE | Уже реальные библиотеки в CMake | Сохранить переиспользование и проверять важные отличия версий |
| zziplib | Публичный исходник существует; локально только shipped `.so` | Оценивать при необходимости замены архивного reader; patch version игры пока не установлена |

## Что действительно лежит локально

`third_party/cegui-0.6.2` — buildable исходники, а не декомпиляция.
Версия/commit/патчи/хеши закреплены в `cegui-source-integration.md`,
`cegui-source-inputs.json` и upstream `PATCHES.md`. В полном snapshot
`/tmp/opentorchlight-cegui-source` есть FreeImageImageCodec, но это **адаптер
к FreeImage**, не реализация этой библиотеки.

Повторная ограниченная проверка repo, `/tmp`, Code, Downloads и cache не
нашла старых checkout OGRE/PU/LodePNG/FreeImage/zzip. Упоминания прежних
`/tmp/lodepng/src` и PU checkout в исторических отчётах больше не описывают
доступные файлы этой среды.

Новые внешние source inputs сохранены в ignored `build-source-cache/`:

- `ogre-v1-6-5.tar.bz2`, SHA-256
  `7fc0e948679c1c1f10751756d267a41d0e3395a6520a23f7853a0ae39a1281f5`;
  source части OgreMain/RenderSystems/PlugIns распакованы в
  `build-source-cache/ogre-1.6.5/ogre/`.
- `FreeImage3131.zip`, SHA-256
  `329bd2036e97d5e527ac2f1fdade4a2029bb06ce4cee0e8bca12e211fd7397c6`;
  распакован в `build-source-cache/freeimage-3.13.1/FreeImage/`.
- `lodepng-bf09e0a.cpp`, SHA-256
  `8f6810a4b848e1e45ec8559df121f90342078b1af3a1c4d0ccbd86d91bc1391d`;
  `lodepng-bf09e0a.h`, SHA-256
  `c44978696b0e2eb40b573d65e3dd16f7fa7f1202cf0cf862802493aeaf861ee0`.
  Это standalone source files, не git checkout для прежнего opt-in harness.

Source cache переживает очистку `/tmp`, но ignored-файлы не переносятся
обычным git clone. Архивы пока не vendored: включать следует только реально
принятую библиотеку/часть с лицензиями и воспроизводимой сборкой.

## Версии и отличия

### OGRE

`original-code`: основной ELF требует `libOgreMain-1.6.5.so` и
`libCEGUIOgreRenderer-1.6.5.so` по DT_NEEDED. В скачанном
`OgreMain/include/OgrePrerequisites.h` major/minor/patch = 1/6/5.

Официальный [release archive](https://sourceforge.net/projects/ogre/files/ogre/1.6.5/)
доступен. GitHub inventory `OGRECave/ogre` содержит tag `v1-6-0`, но tag
`v1-6-5` там не найден; его нельзя объявлять закреплённым источником.
Использован настоящий архив 1.6.5.

`library-derived`: в этом source release RenderSystems — GL, Direct3D9,
Direct3D10; GLES backend отсутствует. Поэтому прямое включение старого
renderer не соответствует существующему Wayland/EGL/GLES пути порта.
Публичные исходники serializers и scene core доступны; варианты полного
движка, отдельного resource subset и renderer adapter надо оценивать по
конкретному consumer. Точная версия не доказывает отсутствие Runic patch.

Архив `COPYING` — LGPL 2.1 с OGRE exceptions; для OGRE 1.6 нельзя брать
MIT-условия современного релиза. [Официальная страница версий лицензии](https://www.ogre3d.org/licensing).
Сборка и интеграция OGRE в этом аудите не выполнялись.

### FreeImage

`original-code`: shipped `FreeImage_GetVersion @0x32c40` загружает format
`%d.%d.%d` по `0x2176a8`; аргументы sprintf `edx=3`, `ecx=13`, `r8d=1`
устанавливают **3.13.1** без запуска `.so`. Это точнее, чем SONAME `.so.3`.
В source `Source/FreeImage.h` macros major/minor/release = 3/13/1.

[Официальный source release](https://sourceforge.net/projects/freeimage/files/Source%20Distribution/3.13.1/)
сохранён с `license-fi.txt` и `license-gpl.txt`. Для native CEGUI renderer
сейчас используются существующие PNG/DDS декодеры; это потенциальная область
замены, но whole-codec/vendor parity пока не проверена.

### ParticleUniverse и LodePNG

`inferred`: старое PU исследование различает раннюю 1.0 по API markers.
В текущем symbol inventory есть `removeAllParticleSystemTemplates`, но нет
поздних `destroyTemplate/getFastForwardInterval/copyParentAttributeTo`.
Это ограничение версии, а не идентификация точного source archive.
[Публичный репозиторий](https://github.com/OGRECave/particleuniverse) подтверждён;
его единственный найденный tag `v1.10` указывает commit
`1865708d54c9e3eb1e42994f07886a505e5ccb1b`. Требуемого tag 1.0 нет.
Текущий changelog показывает изменения сигнатур/defaults между версиями.

LodePNG source получен с официального `lvandeve/lodepng`, commit
`bf09e0a5f173ba07821b782b8297dbfc139d5fed`. Прежняя доказанная граница двух
функций — `lodepng-source-pilot.md`; её сравнения сегодня не повторялись.
Хеши обоих source files проверены. Exact historical decoder version и
whole-library parity не установлены; PNG уже декодируется реальной libpng.

### Другие зависимости

`original-code`: shipped PCRE содержит version string **7.8 2008-09-05**;
CEGUI сейчас собирается с host PCRE 8.45 и FreeType 2.14.3. Проверка
конкретных font/regex consumers остаётся границей адаптации.

Исходники [zziplib](https://github.com/gdraheim/zziplib) доступны, но
SONAME `.so.13` не определяет patch version. Production `PakArchive` уже
использует zlib; файловый registry/normalization — адаптер приложения.

[FMOD предлагает доступ к engine source через отдельное обращение](https://www.fmod.com/licensing).
SDK/header/example исходники не равны реализации FMOD Ex 4.36.21.
Общий backend не следует восстанавливать целиком по ASM без выбранной
необходимости; игровые SoundBank/request/ownership contracts остаются
предметом восстановления.

## Практический следующий пакет

Первый пакет Settings/Options подключён и проверен: [доказательства](cegui-settings-options.md).
Пакет character create подключил библиотечные Editbox и настоящий consumer
имени/класса: [граница](cegui-character-creation.md). Следующая полезная цепочка —
character load через тот же System и действующий `.otc` store с сохранением
открытой границы `.SVB`/модов/preview. Исторический выбор первого пакета:
окна, controls, focus/capture, текст, Falagard, callback → settings/audio
consumers и Options animation. Следом — создание/загрузка персонажа через
тот же System, если выбранный scope и проверки завершены.

Перед реализацией каждого механизма проверить доступный source и consumer;
новый ручной код нужен для установленного vendor delta или игрового контракта.
Для OGRE/PU нужно отдельное ограниченное исследование build/renderer/version
различий. Ночной пакет должен завершаться подключённой цепочкой, сборкой,
узкими проверками и точным остатком; объём выбирается по этому результату.
