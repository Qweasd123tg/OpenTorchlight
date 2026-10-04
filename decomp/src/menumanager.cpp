#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "MenuManager.h"
#include "ContinueGameMenu.h"
#include "DifficultyMenu.h"
#include "Item.h"
#include "GameUI.h"
#include "KeyManager.h"
#include "MainMenu.h"
#include "MouseManager.h"
#include "NewGameMenu.h"
#include "ResourceManager.h"
#include "RunicCore.h"
#include "Settings.h"
#include "BaseUnit.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"

void CMenuManager::closeMenus()
{
    struct Menu
    {
        void* m_pObject;
        void** m_ppVTable;

        Menu(void* pObject)
            : m_pObject(pObject),
              m_ppVTable(*reinterpret_cast<void***>(pObject))
        {
        }

        void setOpen(bool open)
        {
            reinterpret_cast<void (*)(void*, bool)>(m_ppVTable[7])(m_pObject, open);
        }
    };

    Menu(m_pUnknownDD0).setOpen(false);
    Menu(m_pContinueGameMenu).setOpen(false);
    Menu(m_pUnknownDD8).setOpen(false);
    Menu(m_pUnknownDE0).setOpen(false);
    m_UnknownDF0 = 6;
}

void CMenuManager::flushProcessInput()
{
}

void CMenuManager::captureProcessInput()
{
    reinterpret_cast<CMouseManager*>(&m_UnknownD58)->capture();
    reinterpret_cast<CKeyManager*>(&m_Unknown40)->capture();
}

void CMenuManager::mouseEvent(unsigned int param_1, unsigned int param_2)
{
    reinterpret_cast<CMouseManager *>(reinterpret_cast<char *>(this) + 0xd58)
        ->mouseEvent(param_1, param_2);
}

void CMenuManager::keyEvent(unsigned int param_1, unsigned int param_2, long param_3)
{
    reinterpret_cast<CKeyManager *>(reinterpret_cast<char *>(this) + 0x40)
        ->keyEvent(param_1, param_2);
}

void CMenuManager::canContinue()
{
    m_pContinueGameMenu->canContinue();
}

void CMenuManager::reloadMenuCharacters()
{
    m_pContinueGameMenu->reloadFiles(true);
    m_pContinueGameMenu->selectCharacter(0, true);
}

long long CMenuManager::create()
{
    m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
    m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);

    m_pUnknownDD0 = new CMainMenu(
        *reinterpret_cast<CGameUI*>(m_UnknownDA8),
        *reinterpret_cast<CSettings*>(m_pDynamicPropertyFile),
        static_cast<Ogre::SceneManager*>(m_pUnknown18),
        static_cast<CEGUI::Window*>(m_pUnknownDC8),
        reinterpret_cast<CResourceManager*>(m_iUnknownDC0));

    m_pUnknownDD8 = new CNewGameMenu(
        *reinterpret_cast<CGameUI*>(m_UnknownDA8),
        *reinterpret_cast<CSettings*>(m_pDynamicPropertyFile),
        static_cast<Ogre::SceneManager*>(m_pUnknown18),
        static_cast<CEGUI::Window*>(m_pUnknownDC8),
        reinterpret_cast<CResourceManager*>(m_iUnknownDC0));

    m_pContinueGameMenu = new CContinueGameMenu(
        *reinterpret_cast<CGameUI*>(m_UnknownDA8),
        *reinterpret_cast<CSettings*>(m_pDynamicPropertyFile),
        static_cast<Ogre::SceneManager*>(m_pUnknown18),
        static_cast<CEGUI::Window*>(m_pUnknownDC8),
        reinterpret_cast<CResourceManager*>(m_iUnknownDC0));

    m_pUnknownDE0 = new CDifficultyMenu(
        *reinterpret_cast<CGameUI*>(m_UnknownDA8),
        *reinterpret_cast<CSettings*>(m_pDynamicPropertyFile),
        static_cast<Ogre::SceneManager*>(m_pUnknown18),
        static_cast<CEGUI::Window*>(m_pUnknownDC8),
        reinterpret_cast<CResourceManager*>(m_iUnknownDC0));

    return 1;
}

void CMenuManager::setWindowActive(bool active)
{
    if (!active) {
        reinterpret_cast<CKeyManager *>(&m_Unknown40)->flushAll();
        reinterpret_cast<CMouseManager *>(&m_UnknownD58)->flushAll();
    }
}

CMenuManager::~CMenuManager()
{
    if (m_pUnknownDD0 != NULL) {
        delete static_cast<CRunicCore*>(m_pUnknownDD0);
        m_pUnknownDD0 = NULL;
    }
    if (m_pUnknownDD8 != NULL) {
        delete static_cast<CRunicCore*>(m_pUnknownDD8);
        m_pUnknownDD8 = NULL;
    }
    if (m_pUnknownDE0 != NULL) {
        delete static_cast<CRunicCore*>(m_pUnknownDE0);
        m_pUnknownDE0 = NULL;
    }
    if (m_pContinueGameMenu != NULL) {
        delete m_pContinueGameMenu;
        m_pContinueGameMenu = NULL;
    }

    reinterpret_cast<CMouseManager*>(&m_UnknownD58)->CMouseManager::~CMouseManager();
    reinterpret_cast<CKeyManager*>(&m_Unknown40)->CKeyManager::~CKeyManager();
}
