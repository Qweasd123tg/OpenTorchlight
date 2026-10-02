# Ресурсы замороженного checkpoint-v1

`checkpoint-v1-resources.zip` — авторские тестовые UNIT/layout/model ресурсы,
соответствующие уже существующему неизменённому `checkpoint-v1.hex`. Это не
бинарник, ресурсы или save format оригинальной Torchlight.

Восстановление: четыре `tests/make_{frontend,attack,item_cycle,ai_cooldown}_fixture.py`
из commit `63c0962bb160f4eed081d7cfa694846232695962`, запуск исторического
make_frontend_fixture в отдельном временном каталоге, затем перепаковка entry
bytes в сортированном порядке с ZIP timestamp 1980-01-01, deflate level 9,
create_system 3 / regular-file mode 0644. Entry paths/sizes/CRCs сохранены;
они определяют resource identity. Source и итоговый archive SHA-256 записаны
в `checkpoint-v1-resources.json`; legacy_reward_save_test проверяет pinned SHA
и реальное восстановление состояния до и после upgrade в новых процессах.

Текущая frontend fixture развивается вместе с UI и больше не имеет старую
resource identity. Frozen companion сохраняет старую проверку без изменения
save bytes, обхода identity guard или подмены нынешних fixtures.
