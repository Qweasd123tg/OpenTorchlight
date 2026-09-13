# Карта команд оригинальной Torchlight

SHA-256 бинарника: `91b41ae9dfea30aab6bc14dbbfcceaee096d600f39635b8507f5a88b5d41724b`.

Проверено 35 XML-окон, 1298 элементов Window, 115 привязок событий. Из них 2 перекрыты повторным свойством в том же элементе. Из таблицы бинарника извлечено 97 идентификаторов команд, в XML встречается 49 различных команд.

Идентификаторы восстановлены из инициализации KLayoutFunctionNames. Вызовы ниже получены анализом ветвей CGameUI::onClick; это возможные вызовы, а не подтверждённая трасса выполнения. Специализированные меню переопределяют onClick. Динамически создаваемые слоты, клавиатурные команды и жесты эта таблица не исчерпывает.

| ID | Команда | Привязок XML | Вызовы основного HUD |
| --- | --- | ---: | --- |
| 0 | `GUIEXITGAME` | 2 | Контекстный обработчик / см. JSON |
| 1 | `GUIEXITAPPLICATION` | 1 | Контекстный обработчик / см. JSON |
| 2 | `GUINEWGAME` | 1 | Контекстный обработчик / см. JSON |
| 3 | `GUICONTINUEGAME` | 3 | Контекстный обработчик / см. JSON |
| 4 | `GUINEWGAMEMENU` | 1 | Контекстный обработчик / см. JSON |
| 5 | `GUICONTINUEGAMEMENU` | 1 | Контекстный обработчик / см. JSON |
| 6 | `GUICLOSEMENU` | 2 | Контекстный обработчик / см. JSON |
| 7 | `GUIBACK` | 4 | Контекстный обработчик / см. JSON |
| 8 | `GUIDECLINE` | 9 | Контекстный обработчик / см. JSON |
| 9 | `GUIACCEPT` | 7 | Контекстный обработчик / см. JSON |
| 10 | `GUIOK` | 4 | Контекстный обработчик / см. JSON |
| 11 | `GUIPAUSE` | 2 | `CGameUI::togglePause()` |
| 12 | `GUISCROLLUP` | 1 | Контекстный обработчик / см. JSON |
| 13 | `GUISCROLLDOWN` | 1 | Контекстный обработчик / см. JSON |
| 14 | `GUISELECT1` | 12 | Контекстный обработчик / см. JSON |
| 15 | `GUISELECT2` | 8 | Контекстный обработчик / см. JSON |
| 16 | `GUISELECT3` | 8 | Контекстный обработчик / см. JSON |
| 17 | `GUISELECT4` | 3 | Контекстный обработчик / см. JSON |
| 18 | `GUISELECT5` | 2 | Контекстный обработчик / см. JSON |
| 19 | `GUISELECT6` | 1 | Контекстный обработчик / см. JSON |
| 20 | `GUISELECT7` | 1 | Контекстный обработчик / см. JSON |
| 21 | `GUISELECT8` | 1 | Контекстный обработчик / см. JSON |
| 22 | `GUISELECT9` | 1 | Контекстный обработчик / см. JSON |
| 23 | `GUISELECT10` | 1 | Контекстный обработчик / см. JSON |
| 24 | `GUISELECT11` | 0 | Контекстный обработчик / см. JSON |
| 25 | `GUISELECT12` | 0 | Контекстный обработчик / см. JSON |
| 26 | `GUISELECT13` | 0 | Контекстный обработчик / см. JSON |
| 27 | `GUISELECT14` | 0 | Контекстный обработчик / см. JSON |
| 28 | `GUISELECT15` | 0 | Контекстный обработчик / см. JSON |
| 29 | `GUISELECT16` | 0 | Контекстный обработчик / см. JSON |
| 30 | `GUISELECT17` | 0 | Контекстный обработчик / см. JSON |
| 31 | `GUISELECT18` | 0 | Контекстный обработчик / см. JSON |
| 32 | `GUISELECT19` | 0 | Контекстный обработчик / см. JSON |
| 33 | `GUISELECT20` | 0 | Контекстный обработчик / см. JSON |
| 34 | `GUISELECT21` | 0 | Контекстный обработчик / см. JSON |
| 35 | `GUISELECT22` | 0 | Контекстный обработчик / см. JSON |
| 36 | `GUISELECT23` | 0 | Контекстный обработчик / см. JSON |
| 37 | `GUISELECT24` | 0 | Контекстный обработчик / см. JSON |
| 38 | `GUISELECT25` | 0 | Контекстный обработчик / см. JSON |
| 39 | `GUISELECT26` | 0 | Контекстный обработчик / см. JSON |
| 40 | `GUISELECT27` | 0 | Контекстный обработчик / см. JSON |
| 41 | `GUISELECT28` | 0 | Контекстный обработчик / см. JSON |
| 42 | `GUISELECT29` | 0 | Контекстный обработчик / см. JSON |
| 43 | `GUISELECT30` | 0 | Контекстный обработчик / см. JSON |
| 44 | `GUISELECT31` | 0 | Контекстный обработчик / см. JSON |
| 45 | `GUISELECT32` | 0 | Контекстный обработчик / см. JSON |
| 46 | `GUISELECT33` | 0 | Контекстный обработчик / см. JSON |
| 47 | `GUISELECT34` | 0 | Контекстный обработчик / см. JSON |
| 48 | `GUISELECT35` | 0 | Контекстный обработчик / см. JSON |
| 49 | `GUISELECT36` | 0 | Контекстный обработчик / см. JSON |
| 50 | `GUISELECT37` | 0 | Контекстный обработчик / см. JSON |
| 51 | `GUISELECT38` | 0 | Контекстный обработчик / см. JSON |
| 52 | `GUISELECT39` | 0 | Контекстный обработчик / см. JSON |
| 53 | `GUISELECT40` | 0 | Контекстный обработчик / см. JSON |
| 54 | `GUISELECT41` | 0 | Контекстный обработчик / см. JSON |
| 55 | `GUISELECT42` | 0 | Контекстный обработчик / см. JSON |
| 56 | `GUISELECT43` | 0 | Контекстный обработчик / см. JSON |
| 57 | `GUISELECT44` | 0 | Контекстный обработчик / см. JSON |
| 58 | `GUISELECT45` | 0 | Контекстный обработчик / см. JSON |
| 59 | `GUISELECT46` | 0 | Контекстный обработчик / см. JSON |
| 60 | `GUISELECT47` | 0 | Контекстный обработчик / см. JSON |
| 61 | `GUISELECT48` | 0 | Контекстный обработчик / см. JSON |
| 62 | `GUISELECT49` | 0 | Контекстный обработчик / см. JSON |
| 63 | `GUISELECT50` | 0 | Контекстный обработчик / см. JSON |
| 64 | `GUISELECTA` | 3 | Контекстный обработчик / см. JSON |
| 65 | `GUISELECTB` | 4 | Контекстный обработчик / см. JSON |
| 66 | `GUISELECTC` | 3 | Контекстный обработчик / см. JSON |
| 67 | `GUISELECTD` | 2 | Контекстный обработчик / см. JSON |
| 68 | `GUIFEEDPET` | 1 | `CGameUI::performItemUse(CLevel&, CEquipment*, CCharacter*, CCharacter*, CCharacter*)`; `CGameUI::returnDraggedItem()`; `CGameUI::togglePet()` |
| 69 | `GUIPETPASSIVE` | 1 | `CCharacter::setTarget(CCharacter*)` |
| 70 | `GUIPETAGGRESSIVE` | 1 | `CCharacter::setTarget(CCharacter*)` |
| 71 | `GUIPETDEFENSIVE` | 1 | `CCharacter::setTarget(CCharacter*)` |
| 72 | `GUITOGGLEINVENTORY` | 1 | `CGameUI::toggleInventory()` |
| 73 | `GUITOGGLEQUESTS` | 1 | `CGameUI::toggleQuest()` |
| 74 | `GUITOGGLESTATS` | 1 | `CGameUI::toggleStats()` |
| 75 | `GUITOGGLESKILLS` | 1 | `CGameUI::toggleSkill()` |
| 76 | `GUITOGGLEPERKS` | 0 | Контекстный обработчик / см. JSON |
| 77 | `GUITOGGLEJOURNAL` | 1 | `CGameUI::toggleJournal()` |
| 78 | `GUITOGGLEPET` | 1 | `CGameUI::togglePet()` |
| 79 | `GUITOGGLEAUTOMAP` | 1 | Контекстный обработчик / см. JSON |
| 80 | `GUITOGGLEOPTIONS` | 1 | `CGameUI::toggleOptions()` |
| 81 | `GUITOGGLEITEMNAMES` | 1 | Контекстный обработчик / см. JSON |
| 82 | `GUIAUTOMAPZOOMIN` | 1 | Контекстный обработчик / см. JSON |
| 83 | `GUIAUTOMAPZOOMOUT` | 1 | Контекстный обработчик / см. JSON |
| 84 | `GUILEVELUP` | 0 | `CGameUI::closeLeft()`; `CGameUI::closeRight()`; `CGameUI::modalDialogOpenPartial()` |
| 85 | `GUISTATSUP` | 1 | `CGameUI::closeLeft()`; `CGameUI::closeRight()`; `CGameUI::modalDialogOpenPartial()` |
| 86 | `GUISKILLUP` | 1 | `CGameUI::closeLeft()`; `CGameUI::closeRight()`; `CGameUI::modalDialogOpenPartial()` |
| 87 | `GUIPET1` | 3 | Контекстный обработчик / см. JSON |
| 88 | `GUIPET2` | 0 | Контекстный обработчик / см. JSON |
| 89 | `GUIPET3` | 0 | Контекстный обработчик / см. JSON |
| 90 | `GUIDELETE1` | 1 | Контекстный обработчик / см. JSON |
| 91 | `GUIDELETE2` | 0 | Контекстный обработчик / см. JSON |
| 92 | `GUIDELETE3` | 0 | Контекстный обработчик / см. JSON |
| 93 | `GUIDELETE4` | 0 | Контекстный обработчик / см. JSON |
| 94 | `GUISETTINGSMENU` | 2 | Контекстный обработчик / см. JSON |
| 95 | `GUIPETSELL` | 1 | `CCharacter::alive()`; `CCharacter::isPetNearDeath()`; `CCharacter::sendToTown(CLevel&)`; `CGameUI::openModalDialog(std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >, bool)` |
| 96 | `NONE` | 0 | Контекстный обработчик / см. JSON |

## Все привязки интерфейса

Проверка сенсорного управления для каждой строки пока ожидается.

| Файл | Элемент | Событие | Команда | ID | Объявление |
| --- | --- | --- | --- | ---: | --- |
| `bottomhud.layout` | `AutomapPlus` | onClick | `guiAutomapZoomIn` | 82 | Последнее свойство |
| `bottomhud.layout` | `AutomapMinus` | onClick | `guiAutomapZoomOut` | 83 | Последнее свойство |
| `bottomhud.layout` | `PlayButton` | onClick | `guiPause` | 11 | Последнее свойство |
| `bottomhud.layout` | `StatsUp` | onClick | `guiStatsUp` | 85 | Последнее свойство |
| `bottomhud.layout` | `SkillUp` | onClick | `guiSkillUp` | 86 | Последнее свойство |
| `bottomhud.layout` | `InventoryButton` | onClick | `guiToggleInventory` | 72 | Последнее свойство |
| `bottomhud.layout` | `StatsButton` | onClick | `guiToggleStats` | 74 | Последнее свойство |
| `bottomhud.layout` | `SkillsButton` | onClick | `guiToggleSkills` | 75 | Последнее свойство |
| `bottomhud.layout` | `JournalButton` | onClick | `guiToggleJournal` | 77 | Последнее свойство |
| `bottomhud.layout` | `PetButton` | onClick | `guiTogglePet` | 78 | Последнее свойство |
| `bottomhud.layout` | `QuestButton` | onClick | `guiToggleQuests` | 73 | Последнее свойство |
| `bottomhud.layout` | `PerksButton` | onClick | `guiToggleAutoMap` | 79 | Последнее свойство |
| `bottomhud.layout` | `OptionsButton` | onClick | `guiToggleOptions` | 80 | Последнее свойство |
| `bottomhud.layout` | `MagnifyButton` | onClick | `guiToggleItemNames` | 81 | Последнее свойство |
| `bottomhud.layout` | `PauseButton` | onClick | `guiPause` | 11 | Последнее свойство |
| `charactercreate.layout` | `Back` | onClick | `guiBack` | 7 | Последнее свойство |
| `charactercreate.layout` | `CreatePlayer` | onClick | `guiNewGame` | 2 | Последнее свойство |
| `charactercreate.layout` | `Destroyer` | onClick | `guiSelect1` | 14 | Последнее свойство |
| `charactercreate.layout` | `Vanquisher` | onClick | `guiSelect1` | 14 | Последнее свойство |
| `charactercreate.layout` | `Alchemist` | onClick | `guiSelect1` | 14 | Последнее свойство |
| `charactercreate.layout` | `Dog` | onClick | `guiPet1` | 87 | Последнее свойство |
| `charactercreate.layout` | `Cat` | onClick | `guiPet1` | 87 | Последнее свойство |
| `charactercreate.layout` | `Ferret` | onClick | `guiPet1` | 87 | Последнее свойство |
| `characterload.layout` | `Back` | onClick | `guiBack` | 7 | Последнее свойство |
| `characterload.layout` | `Continue` | onClick | `guiContinueGame` | 3 | Последнее свойство |
| `characterload.layout` | `DeleteConfirmButton` | onClick | `guiAccept` | 9 | Последнее свойство |
| `characterload.layout` | `Cancel` | onClick | `guiDecline` | 8 | Последнее свойство |
| `characterload.layout` | `ScrollUp` | onClick | `guiExitApplication` | 1 | Перекрыто следующим свойством |
| `characterload.layout` | `ScrollUp` | onClick | `guiScrollUp` | 12 | Последнее свойство |
| `characterload.layout` | `ScrollDown` | onClick | `guiExitApplication` | 1 | Перекрыто следующим свойством |
| `characterload.layout` | `ScrollDown` | onClick | `guiScrollDown` | 13 | Последнее свойство |
| `characterload.layout` | `Player1` | onClick | `guiSelect1` | 14 | Последнее свойство |
| `characterload.layout` | `Player2` | onClick | `guiSelect2` | 15 | Последнее свойство |
| `characterload.layout` | `Player3` | onClick | `guiSelect3` | 16 | Последнее свойство |
| `characterload.layout` | `Player4` | onClick | `guiSelect4` | 17 | Последнее свойство |
| `characterload.layout` | `Player5` | onClick | `guiSelect5` | 18 | Последнее свойство |
| `characterload.layout` | `Delete` | onClick | `guiDelete1` | 90 | Последнее свойство |
| `cinematicmenu.layout` | `Skip` | onClick | `guiContinueGame` | 3 | Последнее свойство |
| `combinemenu.layout` | `Decline` | onClick | `guiDecline` | 8 | Последнее свойство |
| `combinemenu.layout` | `Accept` | onClick | `guiAccept` | 9 | Последнее свойство |
| `dialogmenu.layout` | `Decline` | onClick | `guiDecline` | 8 | Последнее свойство |
| `dialogmenu.layout` | `Accept` | onClick | `guiAccept` | 9 | Последнее свойство |
| `dialogmenu.layout` | `Ok` | onClick | `guiOk` | 10 | Последнее свойство |
| `diemenu.layout` | `ExitGame` | onClick | `guiExitGame` | 0 | Последнее свойство |
| `diemenu.layout` | `Resurrect1` | onClick | `guiSelect1` | 14 | Последнее свойство |
| `diemenu.layout` | `Resurrect2` | onClick | `guiSelect2` | 15 | Последнее свойство |
| `diemenu.layout` | `Resurrect3` | onClick | `guiSelect3` | 16 | Последнее свойство |
| `difficulty.layout` | `Back` | onClick | `guiBack` | 7 | Последнее свойство |
| `difficulty.layout` | `Easy` | onClick | `guiSelect1` | 14 | Последнее свойство |
| `difficulty.layout` | `Normal` | onClick | `guiSelect2` | 15 | Последнее свойство |
| `difficulty.layout` | `Hard` | onClick | `guiSelect3` | 16 | Последнее свойство |
| `difficulty.layout` | `VeryHard` | onClick | `guiSelect4` | 17 | Последнее свойство |
| `difficultymenu.layout` | `Back` | onClick | `guiBack` | 7 | Последнее свойство |
| `enchantmenu.layout` | `Decline` | onClick | `guiDecline` | 8 | Последнее свойство |
| `enchantmenu.layout` | `Accept` | onClick | `guiAccept` | 9 | Последнее свойство |
| `fishingmenu.layout` | `Base` | onClick | `guiCloseMenu` | 6 | Последнее свойство |
| `fishingmenu.layout` | `FishingButton` | onClick | `guiSelect1` | 14 | Последнее свойство |
| `inventorymenu.layout` | `TabBackpack` | onClick | `guiSelect1` | 14 | Последнее свойство |
| `inventorymenu.layout` | `TabSpell` | onClick | `guiSelect2` | 15 | Последнее свойство |
| `inventorymenu.layout` | `TabFish` | onClick | `guiSelect3` | 16 | Последнее свойство |
| `mainmenuframe.layout` | `ContinueLast` | onClick | `guiContinueGame` | 3 | Последнее свойство |
| `mainmenuframe.layout` | `NewGame` | onClick | `guiNewGameMenu` | 4 | Последнее свойство |
| `mainmenuframe.layout` | `ContinueGame` | onClick | `guiContinueGameMenu` | 5 | Последнее свойство |
| `mainmenuframe.layout` | `Settings` | onClick | `guiSettingsMenu` | 94 | Последнее свойство |
| `mainmenuframe.layout` | `ExitGame` | onClick | `guiExitApplication` | 1 | Последнее свойство |
| `mainmenuframe.layout` | `TabA` | onClick | `guiSelectA` | 64 | Последнее свойство |
| `mainmenuframe.layout` | `TabB` | onClick | `guiSelectC` | 66 | Последнее свойство |
| `mainmenuframe.layout` | `CreditFrame` | onClick | `guiSelectB` | 65 | Последнее свойство |
| `mainmenuframe.layout` | `Credits` | onClick | `guiSelectB` | 65 | Последнее свойство |
| `mainmenuframe.layout` | `CreditFrameB` | onClick | `guiSelectD` | 67 | Последнее свойство |
| `mainmenuframe.layout` | `CreditsB` | onClick | `guiSelectD` | 67 | Последнее свойство |
| `merchantmenu.layout` | `TabMisc` | onClick | `guiSelectA` | 64 | Последнее свойство |
| `merchantmenu.layout` | `TabWeapon` | onClick | `guiSelectB` | 65 | Последнее свойство |
| `merchantmenu.layout` | `TabArmor` | onClick | `guiSelectC` | 66 | Последнее свойство |
| `merchantmenu.layout` | `TabBackpack` | onClick | `guiSelect1` | 14 | Последнее свойство |
| `merchantmenu.layout` | `TabSpell` | onClick | `guiSelect2` | 15 | Последнее свойство |
| `merchantmenu.layout` | `TabFish` | onClick | `guiSelect3` | 16 | Последнее свойство |
| `modalmenu.layout` | `Decline` | onClick | `guiDecline` | 8 | Последнее свойство |
| `modalmenu.layout` | `Accept` | onClick | `guiAccept` | 9 | Последнее свойство |
| `modalmenu.layout` | `Ok` | onClick | `guiOk` | 10 | Последнее свойство |
| `optionsmenu.layout` | `Settings` | onClick | `guiSettingsMenu` | 94 | Последнее свойство |
| `optionsmenu.layout` | `ExitGame` | onClick | `guiExitGame` | 0 | Последнее свойство |
| `optionsmenu.layout` | `ReturnToGame` | onClick | `guiCloseMenu` | 6 | Последнее свойство |
| `pethud.layout` | `PetSell` | onClick | `guiPetSell` | 95 | Последнее свойство |
| `pethud.layout` | `PetAggressive` | onClick | `guiPetAggressive` | 70 | Последнее свойство |
| `pethud.layout` | `PetDefensive` | onClick | `guiPetDefensive` | 71 | Последнее свойство |
| `pethud.layout` | `PetPassive` | onClick | `guiPetPassive` | 69 | Последнее свойство |
| `pethud.layout` | `PetFeedButton` | onClick | `guiFeedPet` | 68 | Последнее свойство |
| `petmenu.layout` | `TabBackpack` | onClick | `guiSelect1` | 14 | Последнее свойство |
| `petmenu.layout` | `TabSpell` | onClick | `guiSelect2` | 15 | Последнее свойство |
| `petmenu.layout` | `TabFish` | onClick | `guiSelect3` | 16 | Последнее свойство |
| `questdialogmenu.layout` | `Decline` | onClick | `guiDecline` | 8 | Последнее свойство |
| `questdialogmenu.layout` | `Accept` | onClick | `guiAccept` | 9 | Последнее свойство |
| `questdialogmenu.layout` | `Ok` | onClick | `guiOk` | 10 | Последнее свойство |
| `questmenu.layout` | `Abandon` | onClick | `guiDecline` | 8 | Последнее свойство |
| `settingsmenu.layout` | `Cancel` | onClick | `guiDecline` | 8 | Последнее свойство |
| `settingsmenu.layout` | `Apply` | onClick | `guiAccept` | 9 | Последнее свойство |
| `skillmenu.layout` | `TabA` | onClick | `guiSelectA` | 64 | Последнее свойство |
| `skillmenu.layout` | `TabB` | onClick | `guiSelectB` | 65 | Последнее свойство |
| `skillmenu.layout` | `TabC` | onClick | `guiSelectC` | 66 | Последнее свойство |
| `stashmenu.layout` | `TabBackpack` | onClick | `guiSelect1` | 14 | Последнее свойство |
| `stashmenu.layout` | `TabSpell` | onClick | `guiSelect2` | 15 | Последнее свойство |
| `stashmenu.layout` | `TabFish` | onClick | `guiSelect3` | 16 | Последнее свойство |
| `tipmenu.layout` | `Ok` | onClick | `guiOk` | 10 | Последнее свойство |
| `waypointmenu.layout` | `Cancel` | onClick | `guiDecline` | 8 | Последнее свойство |
| `waypointmenu.layout` | `Button1` | onClick | `guiSelect1` | 14 | Последнее свойство |
| `waypointmenu.layout` | `Button2` | onClick | `guiSelect2` | 15 | Последнее свойство |
| `waypointmenu.layout` | `Button3` | onClick | `guiSelect3` | 16 | Последнее свойство |
| `waypointmenu.layout` | `Button4` | onClick | `guiSelect4` | 17 | Последнее свойство |
| `waypointmenu.layout` | `Button5` | onClick | `guiSelect5` | 18 | Последнее свойство |
| `waypointmenu.layout` | `Button6` | onClick | `guiSelect6` | 19 | Последнее свойство |
| `waypointmenu.layout` | `Button7` | onClick | `guiSelect7` | 20 | Последнее свойство |
| `waypointmenu.layout` | `Button8` | onClick | `guiSelect8` | 21 | Последнее свойство |
| `waypointmenu.layout` | `Button9` | onClick | `guiSelect9` | 22 | Последнее свойство |
| `waypointmenu.layout` | `Button10` | onClick | `guiSelect10` | 23 | Последнее свойство |
