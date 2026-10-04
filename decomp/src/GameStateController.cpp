#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameNamespaces.h"
#include "GameStateController.h"
#include "EditorBaseObject.h"
#include "GameUI.h"
#include "ResourceManager.h"

void CGameStateController::broadcastPlayerHPThreshholdEvents(float maximum, float current, float delta)
{
    static const int eventsBroadCast[] = {67, 68, 69, 70, 71, 72, 73, 74, 75};
    static const int eventsBroadCastUp[] = {76, 77, 78, 79, 80, 81, 82, 83, 84};
    static const float eventsByPct[] = {0.9f, 0.8f, 0.7f, 0.6f, 0.5f,
                                        0.4f, 0.3f, 0.2f, 0.1f};

    if (maximum <= 0.0f)
        return;

    float oldRatio = current / maximum;
    float newRatio = (current + delta) / maximum;
    if (oldRatio == 0.0f)
        return;

    for (int i = 0; i < 9; ++i) {
        if (oldRatio > eventsByPct[i] && newRatio <= eventsByPct[i])
            BroadcastEvent(eventsBroadCast[i]);
        else if (oldRatio < eventsByPct[i] && newRatio >= eventsByPct[i])
            BroadcastEvent(eventsBroadCastUp[i]);
    }
}

void CGameStateController::showHelp()
{
    if (m_iHelpTip != -1)
        CGameUI::getSingleton()->queueTip(static_cast<EContextTip>(m_iHelpTip));
}

void CGameStateController::setInitialized()
{
    if (!m_bInitialized)
    {
        m_bInitialized = true;
        if (m_bEnabled)
            performStateControl();
    }
}

CGameStateController::~CGameStateController()
{
    if (m_bEnabled) {
        m_bEnabled = false;
        performStateControl();
    }
}

CGameStateController::CGameStateController(CResourceManager* resourceManager)
    : CEditorBaseObject(), m_pResourceManager(resourceManager), m_bEnabled(false),
      m_bInitialized(false), m_iGameState(1), m_bPlayerInvulnerable(false), m_iHelpTip(-1)
{
}
