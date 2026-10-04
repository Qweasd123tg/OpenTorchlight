#include "EmptyStrings.h"
#include "GameStateController.h"
#include "OutputEvents.h"
#include "GameUI.h"
#include "CameraControl.h"
#include "GameClient.h"
#include "Player.h"
#include "SkillManager.h"
#include "Level.h"
void CGameStateController::setInitialized()
{
    if (m_bInitialized)
        return;

    m_bInitialized = true;
    if (m_bEnabled)
        performStateControl();
}
void CGameStateController::broadcastPlayerHPThreshholdEvents(float maximum, float oldHP, float change)
{
    static const float eventsByPct[9] = {
        0.9f, 0.8f, 0.7f, 0.6f, 0.5f,
        0.4f, 0.3f, 0.2f, 0.1f
    };
    static const unsigned int eventsBelowBroadCast[9] = {
        67, 68, 69, 70, 71, 72, 73, 74, 75
    };
    static const unsigned int eventsAboveBroadCast[9] = {
        76, 77, 78, 79, 80, 81, 82, 83, 84
    };

    if (!(maximum > 0.0f))
        return;

    const float newHP = oldHP + change;
    const float oldPercentage = oldHP / maximum;
    const float newPercentage = newHP / maximum;

    if (oldPercentage != 0.0f) {
        for (unsigned int i = 0; i < 9; ++i) {
            if (oldPercentage > eventsByPct[i] &&
                newPercentage <= eventsByPct[i]) {
                BroadcastEvent(eventsBelowBroadCast[i]);
            } else if (oldPercentage < eventsByPct[i] &&
                       newPercentage >= eventsByPct[i]) {
                BroadcastEvent(eventsAboveBroadCast[i]);
            }
        }
    }
}
CGameStateController::CGameStateController(CResourceManager* pResourceManager)
    : m_pResourceManager(pResourceManager)
{
    m_bEnabled = false;
    m_bInitialized = false;
    m_iGameState = 1;
    m_bPlayerInvulnerable = false;
    m_iHelpTip = -1;
}

CGameStateController::~CGameStateController()
{
    if (m_bEnabled)
    {
        m_bEnabled = false;
        performStateControl();
    }
}

void CGameStateController::showHelp()
{
    if (m_iHelpTip != -1)
        CGameUI::getSingleton()->queueTip(static_cast<EContextTip>(m_iHelpTip));
}
void CGameStateController::doActualGameState(bool enabled)
{
    if (m_pResourceManager == 0)
        return;

    CGameClient *pGameClient = m_pResourceManager->getGameClient();
    if (pGameClient == 0)
        return;

    CPlayer *pPlayer = pGameClient->getPlayer();
    if (pPlayer == 0)
        return;

    switch (m_iGameState)
    {
    case 0:
        break;

    case 1:
        pPlayer->setEnabled(!enabled);
        pPlayer = m_pResourceManager->getGameClient()->getPlayer();
        pPlayer->stopPathing();
        break;

    case 2:
        pGameClient->setStateControlFlag(enabled);
        pPlayer = m_pResourceManager->getGameClient()->getPlayer();
        pPlayer->setEnabled(!enabled);
        break;

    case 3:
        CGameUI::getSingleton()->setInteractiveMenuVisible(enabled);
        if (!enabled)
        {
            pPlayer = m_pResourceManager->getGameClient()->getPlayer();
            pPlayer->setEnabled(true);
            pPlayer = m_pResourceManager->getGameClient()->getPlayer();
            pPlayer->attemptToStopPlayerSkill(true);
        }
        CCameraControl::getSingleton()->setCinematicMode(enabled);
        m_pResourceManager->getLevel()->updateNPCIcons();
        break;

    case 4:
        pPlayer->setMeshVisible(!enabled, true);
        break;

    case 5:
        CSkillManager::globallyDisableSkills(enabled);
        break;

    case 6:
    {
        CGameUI *pGameUI = CGameUI::getSingleton();
        if (pGameUI == 0)
            return;

        CGameUI::getSingleton()->closeLeft();
        CGameUI::getSingleton()->closeRight();
        CGameUI::getSingleton()->closeMenus();
        CGameUI::getSingleton()->closeAll();
        break;
    }
    }
}

void CGameStateController::healPlayer()
{
    if (m_pResourceManager)
    {
        CGameClient* gameClient = m_pResourceManager->getGameClient();
        if (gameClient)
        {
            CPlayer* player = gameClient->getPlayer();
            if (player)
            {
                const int maximumHP = player->maxHP();
                m_pResourceManager->getGameClient()->getPlayer()->modifyHP(
                    static_cast<float>(maximumHP));
            }
        }
    }
}

void CGameStateController::performStateControl()
{
    if (!m_bInitialized)
        return;

    if (m_bEnabled)
    {
        if (m_bPlayerInvulnerable &&
            m_pResourceManager->getGameClient()->getPlayer())
        {
            m_pResourceManager->getGameClient()->getPlayer()->setInvulnerable(true);
        }

        doActualGameState(true);
        BroadcastEvent(OUTPUT_EVENT_ENABLED);
        return;
    }

    if (m_bPlayerInvulnerable &&
        m_pResourceManager->getGameClient()->getPlayer())
    {
        m_pResourceManager->getGameClient()->getPlayer()->setInvulnerable(false);
    }

    doActualGameState(false);
    BroadcastEvent(OUTPUT_EVENT_DISABLED);
}

void CGameStateController::update(float)
{
    if (m_pResourceManager->getEditorIsRunning())
        return;

    CPlayer* player = m_pResourceManager->getGameClient()->getPlayer();
    if (!player)
        return;

    const float currentHP =
        static_cast<float>(static_cast<unsigned int>(player->HP()));

    if (currentHP == m_fPreviousHP)
        return;

    const float maximumHP =
        static_cast<float>(static_cast<unsigned int>(player->maxHP()));
    const float previousHP = m_fPreviousHP;
    const float hpDifference = currentHP - previousHP;

    broadcastPlayerHPThreshholdEvents(maximumHP, previousHP, hpDifference);
    m_fPreviousHP = currentHP;
}
