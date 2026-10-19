
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

#include "FileSystem.h"
#include "EmptyStrings.h"
#include <CEGUIWindowManager.h>
void CDieMenu::createMenus()
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/diemenu.layout",info,false,true,false);
    CEGUI::Window* layout = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(info.m_sResourceName),true);
    m_pGameUI->convertToScreenScale(layout,false);
    m_pGameUI->mapToFunctions(layout);
    mapEventHandlers(layout);
    m_windowC8 = layout->recursiveChildSearch("Resurrect1");
    m_windowD0 = layout->recursiveChildSearch("Resurrect2");
    m_windowD8 = layout->recursiveChildSearch("Resurrect3");
    m_windowE0 = layout->recursiveChildSearch("Choice1");
    m_windowE8 = layout->recursiveChildSearch("Choice2");
    m_windowF0 = layout->recursiveChildSearch("Choice3");
    static_cast<CEGUI::Window*>(m_pUnknown20)->addChildWindow(layout);
    m_iUnknown50 = layout->recursiveChildSearch("Title");
}

#include "StringUtilities.h"
#include "GameVariables.h"
void CDieMenu::setOpen(bool open)
{
    if (m_bUnknown30 != open) m_pGameUI->setInteractiveMenuVisible(open);
    if (m_bUnknown30 && !open) {
        static_cast<CEGUI::Window*>(m_pUnknown10)->removeChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
        m_bUnknown31 = false;
    } else if (!m_bUnknown30 && open) {
        m_bUnknown31 = false;
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
        static_cast<CEGUI::Window*>(m_pUnknown20)->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
        static_cast<CEGUI::Window*>(m_pUnknown10)->addChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
        static_cast<CEGUI::Window*>(m_pUnknown18)->moveToBack();
    }
    m_bUnknown30 = open;
    if (!open) return;
    CPlayer* player = m_pGameUI->getGameClient()->getPlayer();
    if (player->m_saveOnDeath) {
        static std::wstring g_Death;
        if (g_Death.empty()) g_Death = CStringTranslate::getSinglton()->getTranslateString(L"Death");
        setTitle(g_Death);
        m_windowC8->setVisible(false);
        m_windowD0->setVisible(false);
        m_windowD8->setVisible(false);
        m_windowE0->setVisible(false);
        m_windowE8->setVisible(false);
        m_windowF0->setVisible(false);
        return;
    }
    static std::wstring g_Resurrect;
    if (g_Resurrect.empty()) g_Resurrect = CStringTranslate::getSinglton()->getTranslateString(L"Resurrect");
    setTitle(g_Resurrect);
    m_windowC8->setVisible(true);
    m_windowD0->setVisible(true);
    m_windowD8->setVisible(true);
    m_windowE0->setVisible(true);
    m_windowE8->setVisible(true);
    m_windowF0->setVisible(true);
    player = m_pGameUI->getGameClient()->getPlayer();
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
    m_goldPenalty = player->getGold() / 10;
    static std::wstring g_ResTown;
    if (g_ResTown.empty()) g_ResTown = CStringTranslate::getSinglton()->getTranslateString(L"Resurrect in town and lose nothing.");
    static std::wstring g_LoseGold;
    if (g_LoseGold.empty()) g_LoseGold = CStringTranslate::getSinglton()->getTranslateString(L"Resurrect at the entrance to this floor, but lose [GOLD] Gold.");
    static std::wstring g_LoseXPFame;
    if (g_LoseXPFame.empty()) g_LoseXPFame = CStringTranslate::getSinglton()->getTranslateString(L"Resurrect here, but lose [XP] Experience and [FAME] Fame.");
    std::wstring xpText = STRINGS::replaceWString(std::wstring(g_LoseXPFame.c_str()),L"[XP]",STRINGS::GetValueAsWString(m_experiencePenalty));
    xpText = STRINGS::replaceWString(std::wstring(xpText.c_str()),L"[FAME]",STRINGS::GetValueAsWString(m_famePenalty));
    std::string label = STRINGS::StringConvertToUTF8(std::wstring(xpText.c_str()));
    m_windowE0->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(label.c_str())));
    std::wstring goldText = STRINGS::replaceWString(std::wstring(g_LoseGold.c_str()),L"[GOLD]",STRINGS::GetValueAsWString(m_goldPenalty));
    label = STRINGS::StringConvertToUTF8(std::wstring(goldText.c_str()));
    m_windowE8->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(label.c_str())));
    label = STRINGS::StringConvertToUTF8(std::wstring(g_ResTown.c_str()));
    m_windowF0->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(label.c_str())));
}
