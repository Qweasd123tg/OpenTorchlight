#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "InteractiveMenu.h"
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
