# Музыка: файлы, маппинг, бэкенд

## Файлы (read-only `music/`, 15 OGG, 99М)

`TITLE/TOWN/TOWNFIGHT/MINES/CAVERN/CRYPT/FORTRESS/LAVA/PALACE/RUINS,
BOSSANTICIPATION/BOSSFIGHT/BOSSRESOLUTION, ORDRAAKFIGHT/ORDRAAKRESOLUTION`
— все stereo 44100, декодируются штатным vorbisfile
(`original_music_tracks`, только имена/потоки, без маппинга).

## Маппинг (статусы!)

- Механизм: `CGameClient::loadMenuLevel @0x584b80` (меню) и `loadLevel`
  (`StringUpper` перед `playMusic`) — имя файла строится из имени
  уровня/долины верхним регистром. Переключение — жёсткое stop+play,
  кроссфейда в вызовах нет.
- `TOWN.OGG` для данжа Town — сильное (имя совпадает 1:1).
- `TITLE.OGG` для меню, `MINES.OGG` для `mine/` и т.д. — inferred
  (плюральный фолбэк `MINE→MINES` тоже inferred). Порт: кандидаты
  `THEME.OGG → THEMES.OGG → TOWN.OGG` только из файлов на диске.
- Босс/бой (`BOSS*/TOWNFIGHT/ORDRAAK*`) — открыто (состояния боссов открыты).

## Бэкенд (`music.hpp/cpp`)

- vorbisfile → ALSA `default`, s16le stereo, отдельный поток; громкость —
  линейный gain из настроек (кривая открыта), mute — нули; фейды linear
  (форма оригинала открыта), API есть, автовызовов нет.
- Без vorbisfile/ALSA — null-бэкенд (трек запоминается, тишина), сборка не
  падает. Без аудиоустройства — первый декодированный буфер доказывает файл,
  поток завершается без ошибки.
- Проверки: `music` (core: маппинг/гейн/миксер/автомат без железа),
  `original_music_tracks` (assets: 15 файлов декодируются).
- Открыто: страница настроек громкостей (пишет неизвестно куда в оригинале),
  точный маппинг тем, босс/бой-хуки, shape фейдов.
