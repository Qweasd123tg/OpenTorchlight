# Автоматическая проверка по настоящему pak (large-6)

## Происхождение и граница

Это **инструменты порта**, не декомпилированный scheduler или новый эталон игры.
Вход: настоящий read-only pak SHA-256
`8650ad752a81e7289e94e7b1bd3c86404ff2b0c74d7abab34fb8fc4d515064d8`.
Во всех машинных прогонах вычисляется хеш самого входа. Оригинальный Linux ELF с закреплённым SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`
в этой среде отсутствует. Не выполнялся новый полный original-процесс.

Исполняется тот же `run_application`, которым пользуется оконный адаптер,
настоящие загрузчики, контроллеры и GLES-renderer. Сценарный host заменяет
системное окно/доставку ввода/часы; он не создаёт PlayerSession напрямую и не
переписывает координаты игрока. Источники реализации:
`src/application.cpp`, `include/torchlight/application.hpp`,
`tests/application_scenario_probe.cpp`, `tools/run_scenario.py`.

## Независимые группы

| Группа | Входы / смысл | Чего не доказывает |
|---|---|---|
| core | авторские данные, bounded export probes; исторический UI probe | совместимость всех игровых ресурсов |
| assets | TORCHLIGHT_GAME_DIR/pak.zip, не требует ELF | исполнение исходных функций |
| reference | закреплённый ELF, прежние original comparison tests | остальные непрослеженные функции |
| render | настоящий EGL/GLES и pak; общий игровой цикл | настоящий Wayland-ввод и original visual parity |
| desktop | полный executable + отдельный compositor/input harness | даже успешный прогон порта не равен исходной игре |

`tools/check.py` печатает таблицу и атомарно пишет JSON с пятью группами,
requested/status/reason, именами тестов, результатами и хешами входов.
Незапрошенная группа тоже видна как NOT RUN. Отсутствующий обязательный вход,
пустая группа и CTest skip не дают успешного результата запрошенной группе.
Старый JUnit удаляется перед запуском. `--core` очищает ресурсные параметры
старого CMake cache. `--assets DIR` не ищет ELF по соседству.

`original_data_bootstrap --pak` проверяет только pak; обычный запуск bootstrap
с каталогом по-прежнему строго требует внешний `resources.cfg`. При наличии
этого файла добавляется `original_resource_configuration`, а не скрывается
проверка полной установки.

GLES-цели отделены от Wayland SDK. При отсутствии development SDK два
тестовых probes собираются с ограниченным существовавшим C API header и
**настоящим libGL dispatch**, а EGL-контекст создаётся через ctypes. Это не
mock, но и не доказательство сборки production desktop. UI probe имеет две
метки `core;render`, поэтому сумму групп нельзя выдавать за число уникальных
тестов. Полный Weston/input harness в этом патче НЕ реализован: `--desktop`
даёт NOT RUN даже при наличии pak, пока соответствующий тест не добавлен.

Примеры (DIR содержит pak.zip; путь может быть каталогом текущего репозитория):

```bash
bash tools/check.sh --portable
bash tools/check.sh --core --assets DIR --render --jobs 2 --report build/verification.json
bash tools/check.sh --all --game-dir DIR --reference DIR/Torchlight.bin.x86_64 \
  --report build/full-verification.json
python3 tools/coverage_map.py --check --verification-report build/verification.json
```

Полная последняя команда проверки `--all` не станет зелёной только из-за
наличия ELF: отсутствие оконного harness отдельно отражается в отчёте.
Coverage join читает все пять статусов, но **не меняет reviewed fidelity**.

## Один цикл и управляемый ввод

Из `linux_desktop_main.cpp` извлечены startup/frontend/load/save, порядок
world/logic/AI/animation, player session, renderer и переходы. Оконный main
теперь адаптирует реальное время, Wayland callbacks, размеры и swap buffers.
HUD inventory/death общий с тестовым host; его state не рисуется другой
упрощённой реализацией ради теста.

Host задаёт время монотонно; сценарий использует исходную обработку дельты
приложением. Шаг 1/60 и начальный seed 491 — **prototype test schedule**, не
восстановленный оригинальный планировщик. `dt 0` применяется только для
проверки state/pixels UI → world без движения времени. Повторяются не только
seed, но последовательность RNG-вызовов, границы и результаты. Observer
не меняет алгоритм RNG и вложенно восстанавливает предыдущий observer.

Сценарии ограничены по длине/числу команд/тикам и wall-clock таймаутам.
Ожидания проверяют состояние без sleep. `walk` вычисляет экранный клик через
реальную камеру, затем исполняется обычный unprojection/path/input. Маршрут
к ближайшему Unit Trigger использует доступные navigation waypoints и тот
же selection/approach/LogicRuntime, без прямого вызова Warper.
Клавиши — физические US коды; это не XKB/IME тест. Нельзя запускать host для
управления рабочим столом пользователя: у него нет такой реализации.

## Настоящие процессы / сцены

`application_scenario_render` запускает семь отдельных процессов:

1. New Game через меню, второй класс, имя, настоящий Town, ходьба, снятие и
   возврат реального оружия, resize, Save, продолжение и Save & Quit.
2. Continue, сравнение класса/имени/seed/позиции/якоря/HP/mana/gold/экземпляров/
   слотов/урона/брони; pause/resume при остановленном времени.
3. Повтор первого сценария с пустым отдельным save store; точное сравнение.
4–5. Первый и третий классы, настоящие skeleton/weapon/клипы/Town и сохранение.
6. Continue → настоящий городской Unit Trigger → Main:1 → входная лестница →
   Town → Save & Quit. Последовательность перехода не инжектируется в мир.
7. Новый Continue после roundtrip; сохранённые экземпляры предметов проверены.

Реальные комплекты: Destroyer/Rusty Blade, Alchemist/Moldy Staff,
Vanquisher/Loose Shortbow. Это **не тест ranged-выстрела**: эта ветка остаётся
недоступной. Смена оружия в основном сценическом тесте — снять/вернуть
стартовую вещь, не полный набор rarity/affixes. Авторские tests и отдельные
pak-only combat/item tests остаются; одного сквозного реального бой/loot
сценария в новом renderer test нет. Он не объявлен автоматически выполненным.

## Дампы и сравнение

Каждый capture содержит:
- state.json: session/items/world/logic/AI, поза героя, IDs без сырых указателей;
- render.json: реальные camera/view/projection, world transforms, material/
  texture selection, RGB uniforms, blend/depth/cull/alpha, порядок instance/pass;
- RGBA8 bottom-left + image metadata; actor contribution mask;
- ordered events.jsonl и rng.jsonl; environment.json с входными хешами,
  Mesa/EGL/GL строками, prototype clock и признаком window_test=false.

Render dump описывает данные и состояния, подготавливаемые текущим renderer,
а не полную apitrace-запись всех команд драйвера. Свет/contact shadows явно
prototype. Маска измеряет изменение кадра при диагностическом удалении
героя+оружия (включая связанный shadow contribution). Затем прежняя видимость
восстанавливается и исходный framebuffer обязан совпасть точно. Это не
геометрический ID/depth buffer и не полноценный occlusion oracle.

`tools/compare_scenarios.py` сообщает первое различие: поле/индекс/bone,
texture/material, RNG-вызов или pixel/channel. Проверяются наборы файлов,
metadata и status. Пустые/неуспешные снимки не могут совпасть «успешно».
Никакого глобального 99% порога или автоматически увеличиваемого допуска нет.
Негативные тесты намеренно меняют пиксель/кость/текстуру/RNG и удаляют файл.

**Собственные кадры — regression only.** Даже точный повтор 33 файлов между
двумя процессами не подтверждает оригинальные цвета/камеру/skins/occlusion.
Оригинального скриншота в новый репозиторий как эталон не добавлено.

## Каталог зависимостей

`torchlight_asset_catalog pak.zip output.json` перечисляет файлы и виртуальные
узлы UNIT/material/piece; отношения BASEFILE, модель/skeleton/manifest/выбранные
idle/run/attack, материал/текстура, room/layout/parent, эффекты/интерфейс.
Используются production decoders, не regex вместо бинарного парсера.

`SUPPORTED` относится только к названной parser capability, не всему runtime.
`UNSUPPORTED` — формат/семантика неизвестны либо decoder отказал без независимого
доказательства порчи. `MISSING` — зависимость не разрешилась текущим resolver;
в том числе возможны старые authoring пути, не обязательно дефект игры.
`CORRUPT` зарезервирован для независимо установленной integrity ошибки
(например, CRC). Bare symbolic имена не притворяются отсутствующим файлом.
Глобальные resource/timeline/effect/UI ограничения — явные unsupported nodes.
Загрузка «поддержанного material script» не утверждает поддержку каждого pass.

Негативная авторская фикстура имеет валидный PNG, специально испорченный
stored PNG с неверным CRC, неизвестное расширение и отсутствующую текстуру.
Оригинальный pak не изменяется и не извлекается в выходной проект.

## Ограниченное численное сравнение / незакрытые границы

`compare_attack_speed.py --scenario-dir` дополняет прежние SHA-проверяемые
неизменённые ASM spans фактическими SPEED трёх стартовых предметов, снятыми
сценическим host. Эффекты для этого численного сравнения **явно нулевые**;
не подменять это записью всей атаки до HIT. Сам ELF здесь не исполняется и
отсутствующие страницы ELF не выдаются за прочитанные. Новые original-process
traces для атаки/warp/UI ещё НЕ получены.

Следующий этап: полный isolated compositor + настоящий window input;
ограниченные original traces с хешем ELF; реальный staged melee/loot scenario;
исправление thin-wall fixture и дальнейшие механики только после своих
исходных свидетельств. Программный renderer не измеряет FPS целевой GPU.

### Sanitizer budget

Для обычного Debug `TORCHLIGHT_TEST_TIMEOUT_SCALE=1`. Инструментированная
сборка может явно задавать `-DTORCHLIGHT_TEST_TIMEOUT_SCALE=4`: меняются только
wall-clock пределы CTest, subprocess сценариев и каталога, не входные сцены/seed/dt,
число уровней/команд, утверждения или допуски сравнения. Значение попадает в
machine run report. Первый совмещённый ASan прогон упёрся в 240-секундный лимит
`original_random_levels`; его не следует выдавать за успешный тест. Повтор с
отдельным обозначенным instrumentation budget остаётся тем же тестовым
содержимым. После этого полный прогон дал 61/62 из-за оставшегося вложенного
240-секундного лимита каталога. Его согласовали с тем же явно заданным budget;
каталог повторён отдельно с неизменённым содержимым проверок и прошёл. В
агрегате остаются исходный неуспешный XML и успешный retry; это не один
изначально зелёный запуск CTest. Обычный Debug лимит не увеличен.
