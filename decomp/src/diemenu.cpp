
#include <CEGUIInputEvent.h>
#include "DieMenu.h"
#include "Player.h"
#include "GameClient.h"

void CDieMenu::update(float)
{
    if (!m_bUnknown30 && !m_bUnknown31) {
        m_bUnknown31 = true;
        if (m_returnToMainMenu) {
            m_returnToMainMenu = false;
            m_pGameUI->requestSetGameState(static_cast<EGameState>(0), static_cast<EMenu>(0));
        }
        if (m_returnToTown) {
            CPlayer* player = m_pGameUI->m_gameClient->getPlayer();
            player->giveGold(static_cast<int>(0u - static_cast<unsigned int>(m_goldPenalty)));
            player->awardFame(*player->getLevel(), NULL, static_cast<int>(0u - static_cast<unsigned int>(m_famePenalty)), false);
            player->awardExperience(*player->getLevel(), NULL, static_cast<int>(0u - static_cast<unsigned int>(m_experiencePenalty)), false);
            m_pGameUI->m_returnToTownOption = m_returnToTownOption;
            m_returnToTown = false;
            m_pGameUI->requestSetGameState(static_cast<EGameState>(5), static_cast<EMenu>(0));
        }
    }
}

bool CDieMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton) {
        CGameUI* ui = m_pGameUI;
        ui->m_bExitButtonPressed = true;
        ui->closeAll();
    }
    return true;
}

bool CDieMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton)
        return CDropdownMenu::handle_CloseButton(event);
    return true;
}

#include "StringTranslate.h"
CDieMenu::CDieMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 0), m_returnToMainMenu(false), m_returnToTown(false)
{
    createMenus();
    static std::wstring g_Continue;
    if (g_Continue.empty())
        g_Continue = CStringTranslate::getSinglton()->getTranslateString(L"Continue");
    setTitle(g_Continue + L"?");
}

#include "MasterResourceManager.h"
bool CDieMenu::onClick(ELayoutFunction function, std::wstring)
{
    if (m_bUnknown30) {
        CPlayer* player = m_pGameUI->getGameClient()->getPlayer();
        if (function == static_cast<ELayoutFunction>(0)) {
            m_returnToMainMenu = true; m_bUnknown32 = true;
        } else if (function == static_cast<ELayoutFunction>(14)) {
            m_returnToTownOption = 0; m_bUnknown32 = true; m_returnToTown = true;
            int level = static_cast<int>(player->m_iUnitLevel);
            int gate = CMasterResourceManager::getSingleton()->experienceGate(level);
            level = static_cast<int>(player->m_iUnitLevel - 1u);
            int previous = CMasterResourceManager::getSingleton()->experienceGate(level);
            m_experiencePenalty = static_cast<int>(static_cast<unsigned int>(gate) - static_cast<unsigned int>(previous)) / 10;
            level = player->m_fameLevel;
            gate = CMasterResourceManager::getSingleton()->fameGate(level);
            level = static_cast<int>(static_cast<unsigned int>(player->m_fameLevel) - 1u);
            previous = CMasterResourceManager::getSingleton()->fameGate(level);
            m_famePenalty = static_cast<int>(static_cast<unsigned int>(gate) - static_cast<unsigned int>(previous)) / 10;
            m_goldPenalty = 0;
        } else if (function == static_cast<ELayoutFunction>(15)) {
            m_returnToTownOption = 1; m_bUnknown32 = true; m_returnToTown = true;
            m_experiencePenalty = m_famePenalty = 0;
            m_goldPenalty = player->getGold() / 10;
        } else if (function == static_cast<ELayoutFunction>(16)) {
            m_returnToTownOption = 2; m_bUnknown32 = true; m_returnToTown = true;
            m_experiencePenalty = m_famePenalty = m_goldPenalty = 0;
        }
        setOpen(false);
    }
    return true;
}
