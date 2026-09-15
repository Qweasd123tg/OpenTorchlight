# Происхождение адресных экспортов этого прохода

Новые ограниченные ASM-фрагменты извлечены потоковым чтением ранее предоставленного
`OpenTorchlight-gpt-pro(2).zip`, SHA-256
`395ab77c07e5a3ea9bcd02285bd7a87974221acc9ac50f64452381d1e8d79ecd`.
Внутренний источник: `OpenTorchlight/original-analysis/full-intel-disassembly.asm`.
В полном выходном ZIP **этого дампа нет**. Отобраны только функции смерти,
восстановления, числовых параметров и конкретных исследованных blockers.

Дамп заявлен для Linux ELF SHA-256
`91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.
Здесь ELF отсутствовал: эти файлы — свидетельство из входных материалов, не
свежая независимая проверка его хеша. Read-only native comparison при наличии
ELF проверяет его SHA и точные используемые byte spans до исполнения.

Ограниченные функции могут содержать ещё неподключённые ветки; сам факт их
экспорта не означает, что эти ветки реализованы. Native adapter использует только
три именованных числовых spans, с явными синтетическими зависимостями.

| Файл | Байты текста | SHA-256 текста |
|---|---:|---|
| `606a20-missile-max-velocity.asm` | 511 | `8d52c82a78923685a9aeb60fe43b3f6e796aa210e1c417261a9e8aa7c593c6e1` |
| `606a30-missile-friction.asm` | 781 | `bf069aada3e5bdf2f9154b30964004862ca3104740ee04504c2286394f69ad0b` |
| `65c410-spawner-descriptor.asm` | 129266 | `10eb1087e6c2bff9deee25a9f5f390c644b07ed3c96df375341654e75fe84527` |
| `65ec30-spawner-give-loot.asm` | 484 | `f893a607fb970f3834233f930104020fdb7dd0c01e85153a5a3a1ff0ecfc1bf0` |
| `7f6ae0-base-level-resetting.asm` | 696 | `d7551482e8f250e1c3956e023611482c628f00ade881bec60f991c5b759afc0e` |
| `811a70-give-gold.asm` | 2221 | `0239d4a572d94bf2e03d4bcc2a3e30dec4d7fb0acda0d49678309f475aee20e7` |
| `813a10-max-mana.asm` | 1871 | `31dcfd491191d052c9a1a80c382294767441560867d2f68f5bb399637a165c70` |
| `82a4e0-interrupt-ai.asm` | 3382 | `ca3a73575868ba6e28687927ced7f3574556c263ca888d3061c4b5ea5491bd82` |
| `83b1a0-get-item.asm` | 28161 | `16f595c0515849e9f4c8d4581278d11ba1e8ebe16ca62bc74ffb2bc67ef16891` |
| `847280-perform-attack.asm` | 70727 | `21ab6e496e6c84290174fdd8fc155439a136a0d596d6e2d13e3daab99532461d` |
| `87f120-weapon-missiles.asm` | 26561 | `fb727d6870cd8444df33b4540288f0a3442b7df155e2ce63cf10ad650e701211` |
| `8c9ec0-gold-constructor.asm` | 37127 | `b1f764dd9f8086326e277259daf5c2b1ec1b03b035bf14c461314dcfa88b8193` |
| `8ca940-gold-unit-init.asm` | 29028 | `abafb90c09829519f7b0d8c608f027681412598dc342bda9e5bc37f1b74ff1b5` |
| `8e3f90-player-reset.asm` | 1101 | `e4095928c4ad074c3f009e3f3f5c5ed95d7e65cea6bb6a3d93bff68c72916b32` |
| `8e47d0-player-die.asm` | 3449 | `584f37bfdf2a29d89c352c4e38c5e4908602d54fbaa677e1cc9886b5b2691e61` |
| `8f5810-player-level-resetting.asm` | 18432 | `3bcb20894899a808c7eee6424ac47b4318d8f9fa3e2f14e9029ef72e6aba5b74` |
| `936300-level-restart.asm` | 881 | `7e515e0d3c3f164e0fc5dc3b6fa01bcbeec5fa16aa309dd02cd6ba901dc67e6c` |
| `b05ec0-death-menu-click.asm` | 7870 | `c5bf14b85d4d84712841b9657f54d71fbfa42c630dcfd79c03b860b7b60c4bdc` |
| `b06110-death-menu-update.asm` | 4101 | `f9cec90f2adac1f5b9e842a20f9159eeeecdf6857cb6f3924e3182dfde62bfee` |
| `d05fb0-missile-constructor.asm` | 7195 | `660a2f7c836a307425fccd1e15ba1c1df12e4cf62df86b60c980faae5a2f9db8` |
| `d4a1d0-add-flag.asm` | 3620 | `0dd3be1798f4b87a1e239d849f4dad4e1a655215866b883b6ac4a6d8d6504f3d` |
| `d4a280-tick-flags.asm` | 3934 | `168522d104898b34b4cb665b1f2a9826b7330f2dbe21c3bfd7e48b16ee04f178` |
| `d50c10-add-ai-flag.asm` | 325 | `82dfcc9906f394dae45014b08d78e52558ed69c233ac6000763c68c26238e90d` |
| `d50c40-has-ai-flag.asm` | 311 | `c767f9c9c4ae4eb7a5374c2071587c491e4c6b1fb4820a35ce74be5b535d3d45` |
| `d50c60-remove-ai-flag.asm` | 317 | `d02127393708091ad2082035802386771762954bf2be9eb14b321b9e1b6b601a` |
| `d50c70-update-ai.asm` | 2142 | `1d0c5223f9d6299ed9b89ba5b0c9e0843204657b8cc3af0bfc998a36fa0f752d` |

Функции:

- `606a20-missile-max-velocity.asm` — `0000000000606a20 <CMissileDescriptor::Set_setMaxVelocity(CEditorBaseObject*, UNIONDATA8BIT const*, unsigned int)>:`
- `606a30-missile-friction.asm` — `0000000000606a30 <CMissileDescriptor::Set_setFriction(CEditorBaseObject*, UNIONDATA8BIT const*, unsigned int)>:`
- `65c410-spawner-descriptor.asm` — `000000000065c410 <CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()>:`
- `65ec30-spawner-give-loot.asm` — `000000000065ec30 <CUnitSpawnerDescriptor::Set_setUnitsGiveLoot(CEditorBaseObject*, UNIONDATA8BIT const*, unsigned int)>:`
- `7f6ae0-base-level-resetting.asm` — `00000000007f6ae0 <CBaseUnit::levelResetting()>:`
- `811a70-give-gold.asm` — `0000000000811a70 <CCharacter::giveGold(int)>:`
- `813a10-max-mana.asm` — `0000000000813a10 <CCharacter::maxMana()>:`
- `82a4e0-interrupt-ai.asm` — `000000000082a4e0 <CCharacter::interruptAI(float, CLevel&)>:`
- `83b1a0-get-item.asm` — `000000000083b1a0 <CCharacter::getItem(CItem*, CLevel&)>:`
- `847280-perform-attack.asm` — `0000000000847280 <CCharacter::performAttack(CEquipment*, unsigned int, float, float, EDAMAGE_TYPES)>:`
- `87f120-weapon-missiles.asm` — `000000000087f120 <CEquipment::fireMissiles(CCharacter*, CCharacter*)>:`
- `8c9ec0-gold-constructor.asm` — `00000000008c9ec0 <CItemGold::CItemGold(CResourceManager*, int)>:`
- `8ca940-gold-unit-init.asm` — `00000000008ca940 <CItemGold::unitInit(CDataGroup*, bool)>:`
- `8e3f90-player-reset.asm` — `00000000008e3f90 <CPlayer::resetLevel()>:`
- `8e47d0-player-die.asm` — `00000000008e47d0 <CPlayer::die(CCharacter*, Ogre::Vector3 const*, float, bool)>:`
- `8f5810-player-level-resetting.asm` — `00000000008f5810 <CPlayer::levelResetting()>:`
- `936300-level-restart.asm` — `0000000000936300 <CLevel::restartLevel()>:`
- `b05ec0-death-menu-click.asm` — `0000000000b05ec0 <CDieMenu::onClick(ELayoutFunction, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >)>:`
- `b06110-death-menu-update.asm` — `0000000000b06110 <CDieMenu::update(float)>:`
- `d05fb0-missile-constructor.asm` — `0000000000d05fb0 <CMissile::CMissile(CResourceManager*)>:`
- `d4a1d0-add-flag.asm` — `0000000000d4a1d0 <CAIFlagManager::addAIFlag(EAIFLAG_TYPES, float)>:`
- `d4a280-tick-flags.asm` — `0000000000d4a280 <CAIFlagManager::updateAIFlags(float)>:`
- `d50c10-add-ai-flag.asm` — `0000000000d50c10 <CAIManager::addAIFlag(EAIFLAG_TYPES, float)>:`
- `d50c40-has-ai-flag.asm` — `0000000000d50c40 <CAIManager::hasAIFlag(EAIFLAG_TYPES)>:`
- `d50c60-remove-ai-flag.asm` — `0000000000d50c60 <CAIManager::removeAIFlag(EAIFLAG_TYPES)>:`
- `d50c70-update-ai.asm` — `0000000000d50c70 <CAIManager::update(float)>:`
