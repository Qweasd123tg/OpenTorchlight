#include "EmptyStrings.h"
#include "GameStateControllerDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "GameStateController.h"
#include "Player.h"
#include "GameClient.h"
#include "GameStateControllerDescriptorNames.h"

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

unsigned int CGameStateControllerDescriptor::getGameStateIDByString(
    CEditorScene *scene,
    CEditorBaseObject *object,
    const std::wstring &value,
    void *userData)
{
    const std::wstring *names =
        reinterpret_cast<const std::wstring *>(gGAMESTATE_NAMES);

    for (unsigned int i = 0; i < 7; ++i)
    {
        if (names[i] == value)
            return i;
    }

    return 0;
}

void CGameStateControllerDescriptor::descriptorSceneActivated(CEditorScene* scene)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CGameStateController* controller =
            dynamic_cast<CGameStateController*>(m_Objects[i]);

        if (controller != 0 &&
            !scene->getResourceManager()->getEditorIsRunning()) {
            controller->setInitialized();
        }
    }
}

void CGameStateControllerDescriptor::update(float timeDelta)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i)
    {
        CGameStateController *controller =
            dynamic_cast<CGameStateController *>(m_Objects[i]);
        if (controller != NULL)
        {
            controller->update(timeDelta);
        }
    }
}

CEditorBaseObject* CGameStateControllerDescriptor::CreateObject(CEditorScene* scene)
{
    return new CGameStateController(scene->getResourceManager());
}

std::wstring CGameStateControllerDescriptor::getTipStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 33)
        return KContextTipNames[0];
    return KContextTipNames[index];
}

std::wstring CGameStateControllerDescriptor::getGameStateStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 6)
        return gGAMESTATE_NAMES[1];
    return gGAMESTATE_NAMES[index];
}

unsigned int CGameStateControllerDescriptor::getTipIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    for (unsigned int index = 0; index < 34; ++index)
    {
        if (KContextTipNames[index] == value)
            return index;
    }
    return 0;
}

void CGameStateControllerDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject*)
{
    CGameStateController* control = dynamic_cast<CGameStateController*>(object);
    if (!control)
        return;
    switch (event) {
    case 2:
        if (control->m_bEnabled != true) {
            control->m_bEnabled = true;
            control->performStateControl();
        }
        break;
    case 3:
        if (control->m_bEnabled != false) {
            control->m_bEnabled = false;
            control->performStateControl();
        }
        break;
    case 75: {
        CPlayer* player = getSceneOwner()->getResourceManager()->getGameClient()->getPlayer();
        if (player)
            for (unsigned int i = 0; i < player->getFollowerCount(); ++i)
                player->getFollower(i)->teleportToMaster(1.0f);
        break;
    }
    case 76:
        control->healPlayer();
        break;
    case 80:
        control->showHelp();
        break;
    }
}
