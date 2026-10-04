#include "EmptyStrings.h"
#include "GameStateControllerDescriptor.h"

CGameStateControllerDescriptor::CGameStateControllerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"When enabled the state is active. NOTE - if this is enabled on load it will set the state when the level loads.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PLAYER", L"INVULNERABLE", L"When true the player will be invulnerable.", (void*)Set_setPlayerInvulnerable, (void*)Get_getPlayerInvulnerable, VARIABLE_TYPE_BOOL, 0);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"STATE", L"The game state which you wish to enable or disable", (void*)Set_setGameState, (void*)Get_getGameState, getGameStateIDByString, getGameStateStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddPropertyWithInterpreterFunctions(L"HELP", L"TIP", L"The tip you wish to show", (void*)Set_setHelpTip, (void*)Get_getHelpTip, getTipIDByString, getTipStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddInputLogic(INPUT_EVENT_WARP_PETS_TO_PLAYER);
    AddInputLogic(INPUT_EVENT_HEAL_PLAYER);
    AddInputLogic(INPUT_EVENT_SHOW_TIP);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
    AddOutputLogic(OUTPUT_EVENT_PLAYER_HP_BELOW_90_PCT);
    AddOutputLogic(OUTPUT_EVENT_PLAYER_HP_BELOW_80_PCT);
    AddOutputLogic(OUTPUT_EVENT_PLAYER_HP_BELOW_70_PCT);
    AddOutputLogic(OUTPUT_EVENT_PLAYER_HP_BELOW_60_PCT);
    AddOutputLogic(OUTPUT_EVENT_PLAYER_HP_BELOW_50_PCT);
    AddOutputLogic(OUTPUT_EVENT_PLAYER_HP_BELOW_40_PCT);
    AddOutputLogic(OUTPUT_EVENT_PLAYER_HP_BELOW_30_PCT);
    AddOutputLogic(OUTPUT_EVENT_PLAYER_HP_BELOW_20_PCT);
    AddOutputLogic(OUTPUT_EVENT_PLAYER_HP_BELOW_10_PCT);
}

CGameStateControllerDescriptor::~CGameStateControllerDescriptor()
{
}
