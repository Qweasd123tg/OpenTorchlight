# Материалы и текстуры OGRE

## Исходные данные

`resource-derived`: в установленном `pak.zip` находятся 1 182 файла
`.material`, 2 749 определений материалов и 2 401 директива `texture`. Все 525
submesh контрольной городской сцены разрешают материал и исходную текстуру.

Разбор директив показал, что упрощение всех материалов до одной непрозрачной
текстуры было неверным:

- 763 прохода задают `scene_blend`: 724 `alpha_blend`, 20 `add`, 17 `one one`
  и 2 `modulate`;
- 723 прохода используют `alpha_rejection` с разными функциями и порогами;
- 171 проход задаёт `depth_write off`, 43 — `lighting off`;
- встречаются `colour_op add`, `filtering`, `tex_address_mode clamp`, несколько
  проходов и несколько texture unit.

Например, материал Skeletal Warrior использует `alpha_blend` и
`alpha_rejection greater 5`. `monster_spectral` у Shadow Archer использует
`depth_write off` и additive blend `one one`. У материала золота поздний проход
имеет `lighting off`; это состояние не должно менять первый проход.

## Перенесённое поведение

`resource-derived`: парсер сохраняет функцию и байтовый порог alpha rejection,
режим scene blend, `depth_write`, `lighting`, `colour_op`, clamp и filtering.
Рендерер применяет эти параметры к первому проходу и первой texture unit.
Глобальное отсечение всех пикселей с alpha меньше 0,10 удалено: отсечение теперь
включается только исходной директивой материала.

Парсер продолжает собирать ссылки на текстуры всех проходов для аудита, но
рендерное состояние первого прохода берёт только из его тела. Поэтому поздний
`lighting off` и clamp второй texture unit больше не загрязняют основной
проход. Рендерер использует отдельную ссылку на texture именно первой texture
unit; текстура позднего прохода больше не подставляется в нетекстурированный
первый проход.

`resource-derived`: основные городские текстуры грунта (`dirt001.dds`,
`grass001.dds` и alpha-blend слои) содержат по десять авторских mip-уровней.
Декодер раньше сохранял только верхний уровень, поэтому поверхность под
наклоном рябила. Теперь декодируются и загружаются все заявленные уровни DDS.
`library-derived`: материал без директивы `filtering` использует стандарт OGRE
1.6 `TFO_BILINEAR`: linear min/mag и point между mip-уровнями, то есть
`GL_LINEAR_MIPMAP_NEAREST`. PNG-текстуры получают сгенерированную цепочку,
как автоматические mipmaps OGRE.

## Runtime override уровня

Исследован Linux ELF с SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Точечные экспорты находятся в `research/disassembly/89aef0.asm`,
`950a40.asm` и `977760-material-ambient.asm`; связанный псевдокод — в
`research/decompiled-core/generic_model.c`, `level.c` и
`level_template_data.c`.

`original-code`: `CLevelTemplateData::load @0x009762f0` читает
`MATERIAL AMBIENT RED/GREEN/BLUE`, по умолчанию 92, делит каждую компоненту
на 255 и задаёт alpha 1. `CLevel::updateMaterialAmbient @0x00950a40` проходит
по `CEditorScene`. Если в конкретной сцене отсутствует объект дескриптора
`Scene Object`, функция применяет этот RGBA ко всем её `Room Piece` через
`CGenericModel::setAmbient @0x0089aef0`. ASM последней функции подтверждает,
что один указатель цвета передаётся и `Ogre::Material::setAmbient`, и
`Ogre::Material::setDiffuse` каждого материала модели.

Порт хранит финальный RGBA как override отдельного `SceneMeshInstance` и перед
shader подаёт его одновременно в diffuse и material ambient. Общий каталог
материалов не изменяется. Ресурсный тест проверяет область override отдельно
для фиксированного города и каждого layout сгенерированного этажа.

## Оставшиеся границы

`prototype`: рендерер всё ещё рисует один проход и одну texture unit. Полное
воспроизведение требует сохранить дерево pass/texture unit, выполнить проходы
в исходном порядке и перенести `anim_texture`, `colour_op_ex` и cubemap.

`prototype`: направление света и коэффициенты освещения пока принадлежат
OpenTorchlight. Их нужно заменить значениями и состояниями исходного кадра,
снятыми из оригинального runtime. Сами material-файлы этих параметров сцены не
задают.

`original-code`, граница: восстановлена только ветка `Room Piece` из
`CLevel::updateMaterialAmbient`. Другие вызовы `CGenericModel::setAmbient`,
например добавление предметов с настройками override lighting, требуют
отдельного переноса их условий и источников цвета.
