#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "InteractiveMenu.h"
#include "FileSystem.h"
#include <CEGUIWindow.h>
#include <CEGUIWindowManager.h>
#include "Item.h"
#include "GameUI.h"
#include "ResourceManager.h"
#include "RunicCore.h"
#include "Settings.h"
#include "BaseUnit.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"

CInteractiveMenu::~CInteractiveMenu()
{
}

CInteractiveMenu::CInteractiveMenu(CGameUI& gameUI, CSettings& settings,
                                   Ogre::SceneManager* sceneManager,
                                   CEGUI::Window* parentWindow,
                                   CResourceManager* resourceManager)
    : CRunicCore(),
      m_pParentWindow(parentWindow),
      m_pMenuWindow(NULL),
      m_pMenuButtons(NULL),
      m_pResourceManager(resourceManager),
      m_bVisible(true),
      m_fAnimationTime(0.0f)
{
    createMenus();
}

void CInteractiveMenu::setVisible(bool visible)
{
    if (!m_pMenuWindow || m_bVisible == visible)
        return;
    if (visible) {
        m_pMenuWindow->setVisible(true);
        m_pMenuWindow->activate();
        m_pMenuWindow->moveToFront();
        m_pMenuContent->setYPosition(CEGUI::UDim(-0.1f, 0.0f));
        m_pMenuButtons->setYPosition(CEGUI::UDim(1.1f, 0.0f));
        m_fAnimationTime = 0.2f;
    } else if (m_pResourceManager->getEditorIsRunning()) {
        m_pMenuWindow->setVisible(false);
        m_pMenuWindow->deactivate();
    } else {
        m_fAnimationTime = m_pMenuContent->getHeight().d_scale * 0.2f / 0.1f;
    }
    m_bVisible = visible;
}

void CInteractiveMenu::update(float elapsed)
{
    if (m_fAnimationTime < 0.0f && !m_bVisible)
        return;
    m_fAnimationTime -= elapsed;
    float percent = m_fAnimationTime / 0.2f;
    percent = percent > 0.0f ? percent : 0.0f;
    if (m_bVisible) {
        m_pMenuContent->setYPosition(CEGUI::UDim(percent * -0.1f, 0.0f));
        m_pMenuButtons->setYPosition(CEGUI::UDim((1.0f - percent) * -0.1f + 1.0f, 0.0f));
    } else {
        float offset = 1.0f - percent;
        m_pMenuContent->setYPosition(CEGUI::UDim(offset * -0.1f, 0.0f));
        m_pMenuButtons->setYPosition(CEGUI::UDim(offset * 0.1f + 0.9f, 0.0f));
        if (percent <= 0.0f) {
            m_pMenuWindow->setVisible(false);
            m_pMenuWindow->deactivate();
        }
    }
}

void CInteractiveMenu::createMenus()
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/interactivemenu.layout", info, false, true, false);
    m_pMenuWindow = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(info.m_sResourceName), true);
    m_pMenuContent = m_pMenuWindow->getChild(CEGUI::String("TopBar"));
    m_pMenuButtons = m_pMenuWindow->getChild(CEGUI::String("BottomBar"));
    m_pParentWindow->addChildWindow(m_pMenuWindow);
    m_pMenuWindow->setVisible(false);
    setVisible(false);
}
