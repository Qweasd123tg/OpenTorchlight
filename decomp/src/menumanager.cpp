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

}

bool CMenuManager::canLoad()
{
    return static_cast<int>(m_pContinueGameMenu->m_savePaths.size()) > 0;
}

void CMenuManager::update(float elapsed, CGameClient*, Ogre::RenderWindow*)
{
    CDropdownMenu* menu = static_cast<CMainMenu*>(m_pUnknownDD0);
    if (menu->m_bUnknown30 || !menu->m_bUnknown31)
        menu->update(elapsed);
    menu = static_cast<CNewGameMenu*>(m_pUnknownDD8);
    if (menu->m_bUnknown30 || !menu->m_bUnknown31)
        menu->update(elapsed);
    menu = m_pContinueGameMenu;
    if (menu->m_bUnknown30 || !menu->m_bUnknown31)
        menu->update(elapsed);
    menu = static_cast<CDifficultyMenu*>(m_pUnknownDE0);
    if (menu->m_bUnknown30 || !menu->m_bUnknown31)
        menu->update(elapsed);
}

bool CMenuManager::processInput(void* window, float elapsed, bool active)
{
    if (!active)
        return true;
    reinterpret_cast<CMouseManager*>(&m_UnknownD58)->update(window);
    CDropdownMenu* menu = static_cast<CMainMenu*>(m_pUnknownDD0);
    if ((menu->m_bUnknown30 || !menu->m_bUnknown31) && !menu->processInput(window, elapsed, true))
        return false;
    menu = static_cast<CNewGameMenu*>(m_pUnknownDD8);
    if ((menu->m_bUnknown30 || !menu->m_bUnknown31) && !menu->processInput(window, elapsed, true))
        return false;
    menu = static_cast<CDifficultyMenu*>(m_pUnknownDE0);
    if ((menu->m_bUnknown30 || !menu->m_bUnknown31) && !menu->processInput(window, elapsed, true))
        return false;
    menu = m_pContinueGameMenu;
    if (menu->m_bUnknown30 || !menu->m_bUnknown31)
        return menu->processInput(window, elapsed, true);
    return true;
}

void CMenuManager::setActiveMenu(EMenu menu)
{
    if (m_UnknownDF0 == menu)
        return;
    switch (menu) {
    case 0:
        if (m_pContinueGameMenu->canContinue())
            m_pContinueGameMenu->selectCharacter(0, true);
        static_cast<CDifficultyMenu*>(m_pUnknownDE0)->setOpen(false);
        static_cast<CMainMenu*>(m_pUnknownDD0)->setOpen(true);
        static_cast<CNewGameMenu*>(m_pUnknownDD8)->setOpen(false);
        m_pContinueGameMenu->setOpen(false);
        break;
    case 1:
    case 2:
        static_cast<CDifficultyMenu*>(m_pUnknownDE0)->setOpen(false);
        static_cast<CNewGameMenu*>(m_pUnknownDD8)->m_bUnknownF8 = menu == 2;
        static_cast<CNewGameMenu*>(m_pUnknownDD8)->setOpen(true);
        static_cast<CMainMenu*>(m_pUnknownDD0)->setOpen(false);
        m_pContinueGameMenu->setOpen(false);
        break;
    case 3:
        static_cast<CDifficultyMenu*>(m_pUnknownDE0)->setOpen(false);
        m_pContinueGameMenu->setOpen(true);
        static_cast<CMainMenu*>(m_pUnknownDD0)->setOpen(false);
        static_cast<CNewGameMenu*>(m_pUnknownDD8)->setOpen(false);
        break;
    case 4:
    case 5:
        static_cast<CDifficultyMenu*>(m_pUnknownDE0)->m_bUnknownD0 = menu == 5;
        static_cast<CDifficultyMenu*>(m_pUnknownDE0)->setOpen(true);
        static_cast<CNewGameMenu*>(m_pUnknownDD8)->setOpen(false);
        static_cast<CMainMenu*>(m_pUnknownDD0)->setOpen(false);
        m_pContinueGameMenu->setOpen(false);
        break;
    }
    m_UnknownDF0 = menu;
}

#include "MasterResourceManager.h"

CMenuManager::CMenuManager(CGameUI& ui, CSettings& settings, Ogre::Camera* camera, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CRunicCore(), m_pUnknown10(camera), m_pUnknown18(scene),
      m_iUnknown20(reinterpret_cast<long long>(CMasterResourceManager::getSingleton()->m_pSoundManager)),
      m_iUnknown28(0), m_iUnknown30(0), m_pDynamicPropertyFile(&settings),
      m_Unknown40(), m_UnknownD58(), m_UnknownDA8(reinterpret_cast<long long>(&ui)),
      m_bUnknownDB0(false), m_iUnknownDC0(reinterpret_cast<long long>(resources)),
      m_pUnknownDC8(parent), m_pUnknownDD0(NULL), m_pUnknownDD8(NULL), m_pUnknownDE0(NULL), m_pContinueGameMenu(NULL), m_UnknownDF0(static_cast<int>(6))
{
    create();
}
