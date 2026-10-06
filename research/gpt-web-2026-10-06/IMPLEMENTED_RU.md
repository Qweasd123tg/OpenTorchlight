# Ремонт инструментов по трём пакетам, 7 октября 2026

Обе версии утреннего исследования и OpenTorchlight_complete_audit.zip учтены. У нового ZIP проверены 33 manifest записи; 25 файлов сохранены читаемо, 177 файлов девяти вложенных исследований сопоставлены по SHA256, 16 новых сохранены отдельно. [Точная карта импорта](complete-audit/ARCHIVE_IMPORT.json). Архивные патчи адаптированы к текущей ветке.

## Внедрено

- Stage изолирует исходники, заголовки и generated inputs. Публикация после конечной сборки и полного headless-прогона проверяет baseline, сериализует запись и откатывает частичную ошибку. llm_loop больше не экспериментирует в live src.
- candidate.py проверяет полный TU без модели и trial-флагов. no_llm_loop.py подключает существующие генераторы дескрипторов/свойств, сохраняет отказы и пропускает их повтор на одинаковых входах. Новые property definitions принадлежат исходному TU, а не weak header code.
- Исправлены direct calls, numeric != false, литералы/комментарии, cv, перегрузки, namespace и подтверждённый static/member. Непроверенная lifetime/dead-store очистка выключена по умолчанию.
- Ghidra получает COMPLETE/TIMEOUT/TYPE_ERROR/NO_BODY, raw SHA и полный versioned types fingerprint. IO/logs отдельные, project flock, ограниченные retries и выбор адресов. Неподдерживаемый соседний тип не обрывает весь job.
- DWARF сохраняет qualified identities и конфликты. Сохранены все 1099 vtable groups, включая 222 secondary с непроверенным ABI. Исправлен LP64; экспортированы 31876 SDK declarations, покрывающие 481/1004 PLT imports. Живой Ghidra применил 48 exact scalar/pointer signatures; aggregate/variadic не угадываются.
- Сохранены точные pointer-only шаблоны RunicCore. Known incomplete pointee сохраняет identity и 8-байтовый pointer ABI без использования его непроверенных полей/by-value layout. Неизвестный 24-байтовый span остаётся undefined24.
- Кэш заново разрешает includes препроцессором и учитывает compiler contents. Добавление shadow header меняет объект. objdiff индексирует каждую секцию один раз. Очередь включает частичные/крупные TU; claim атомарен и возвращается после отказа запуска.
- Приёмка защищена от обрезанных литералов/capture, непроверенной LSDA, старой mutation evidence, нулевого исполнения и аварийных stats. TL_ORIGINAL declaration теперь только навигация. Для strong mutation result нужны минимум три валидных мутации двух категорий и изолированные kills.
- Рантайм blob/loader разделён immutable content identities внутри checkout. CPU/wall budgets раздельны; timeout — incomplete. Есть timing каждого теста и диагностика неполного процесса.
- standalone.py делает обычный link-only без originals.ld, redirects и заглушек. Manifest также перечисляет оригинальные imports/data/RTTI/vtables/omitted initializers.

## Проверка

Проверки инструментов: **108 тестов, 0 ошибок**. Полный check.py: **103 самотеста, 0 ошибок**. Строгий результат **895/5247, 52558 байт**. Прежние 144 зачёта по declarations больше автоматически не принимаются; исходники и ручные регрессионные оснастки сохранены.

На Equipment/FileSystem/ParticleTechWrapper полные object-function records идентичны; этот этап ускорился **17.92/2.98/5.86x**. 1000 пустых fork/capture случаев: 0.209 секунды раньше, 0.207 с раздельными таймерами. Общего ускорения восстановления не измерено.

В staged AnimationPlayerDescriptor получены **11 новых MATCH definitions**, пока без публикации в игру. Неполный Affector descriptor — BLOCKED; Equipment.cpp с DIFF отвергнут. Оба крупных setPetSlotIcon (6229 исходных байт каждый) прошли от TYPE_ERROR до COMPLETE: merchantmenu.cpp:0xb6ab50 и stashmenu.cpp:0xbf7cc0. Черновик не считается принятым исходником.

Полная link-only проба не замкнута: 972 game function imports, 33 RTTI, 34 vtables, 222 library imports, 46 unknown. Библиотеки в этой пробе не добавлялись. Самостоятельная игра не доказана.

**Новых опубликованных игровых функций 0; model calls 0; GUI не открывалось.** [Все 56 решений](implementation-decisions.json), [результаты проверок](local-check/tools-integration/validation.json). Не внедрённые гипотезы перечислены отдельно: нужен конкретный donor/ABI/CFG/observer, архивный прототип не является готовым правилом переноса.

## Использование

`python3 tools/decomp/candidate.py TU.cpp --input path/TU.cpp`

`python3 tools/decomp/no_llm_loop.py TUDescriptor.cpp --provider properties`

`--publish` запускает полную проверку перед записью. Старые helpers вызываются общим runner только внутри Stage. Это законченный безопасный маршрут проверки имеющихся генераторов; автоматический синтез всех крупных функций ещё не реализован.
