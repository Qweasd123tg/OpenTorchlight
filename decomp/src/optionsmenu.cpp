#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "OptionsMenu.h"

bool COptionsMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton) {
    CGameUI* ui = m_pGameUI;
    ui->m_bExitButtonPressed = true;
    ui->closeAll();
    }
    return true;
}

bool COptionsMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    return CDropdownMenu::handle_CloseButton(event);
}

void COptionsMenu::update(float elapsed)
{
    bool closing = m_bUnknown31;
    CDropdownMenu::update(elapsed);
    if (closing != m_bUnknown31 && m_returnToMainMenu) {
        m_returnToMainMenu = false;
        m_pGameUI->requestSetGameState(static_cast<EGameState>(0), static_cast<EMenu>(0));
    }
}

bool COptionsMenu::onClick(ELayoutFunction function, std::wstring)
{
    if (m_bUnknown30) {
        switch (static_cast<int>(function)) {
        case 6: m_bUnknown32 = true; break;
        case 94: m_pGameUI->toggleSettings(); m_bUnknown32 = true; break;
        case 0: m_returnToMainMenu = true; m_bUnknown32 = true; break;
        }
    }
    return true;
}

#include "StringTranslate.h"
COptionsMenu::COptionsMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 0), m_returnToMainMenu(false)
{
    createMenus();
    static std::wstring g_Options;
    if (g_Options.empty())
        g_Options = CStringTranslate::getSinglton()->getTranslateString(L"Options");
    setTitle(g_Options);
}

#include "FileSystem.h"
#include "EmptyStrings.h"
#include "GameClient.h"
#include "GameVariables.h"
#include <CEGUIWindowManager.h>
void COptionsMenu::createMenus()
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/optionsmenu.layout",info,false,true,false);
    CEGUI::Window* layout = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(info.m_sResourceName),true);
    m_pGameUI->convertToScreenScale(layout,false);
    m_pGameUI->mapToFunctions(layout);
    m_iUnknown50 = layout->recursiveChildSearch("Title");
    mapEventHandlers(layout);
    static_cast<CEGUI::Window*>(m_pUnknown20)->addChildWindow(layout);
    static_cast<CEGUI::Window*>(m_pUnknown18)->setAlwaysOnTop(true);
    static_cast<CEGUI::Window*>(m_pUnknown18)->setZOrderingEnabled(false);
}
void COptionsMenu::setOpen(bool open)
{
    if (m_bUnknown30 && !open) {
        CGameClient* client = m_pGameUI->getGameClient();
        client->getMouseClickUnit(3).setObject(NULL);
        client->getMouseClickUnit(2).setObject(NULL);
        client->getMouseClickUnit(0).setObject(NULL);
        client->getMouseClickUnit(1).setObject(NULL);
        if (m_pGenericModel) {
            m_pSoundBank->playSample(66,NULL,0.0f,0.0f,false);
            m_pGenericModel->blendAnimation("CLOSE",false,0.1f,2.0f,-1.0f);
            m_bUnknown31 = false;
        } else {
            static_cast<CEGUI::Window*>(m_pUnknown10)->removeChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
            m_bUnknown31 = true;
        }
    } else if (!m_bUnknown30 && open) {
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
        if (m_pGenericModel) {
            m_pSoundBank->playSample(22,NULL,0.0f,0.0f,false);
            m_pGenericModel->setVisible(true);
            if (m_pGenericModel->animationPlaying("CLOSE"))
                m_pGenericModel->blendAnimation("OPEN",false,0.1f,2.0f,-1.0f);
            else
                m_pGenericModel->playAnimation("OPEN",false,2.0f,-1.0f);
            m_pGenericModel->queueBlendAnimation("IDLE",true,0.1f,1.0f);
        } else {
            static_cast<CEGUI::Window*>(m_pUnknown20)->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
        }
        static_cast<CEGUI::Window*>(m_pUnknown10)->addChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
        static_cast<CEGUI::Window*>(m_pUnknown18)->moveToFront();
    }
    m_bUnknown30 = open;
}
