#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "FishingMenu.h"

bool CFishingMenu::processInput(void*, float, bool capture)
{
    if (capture) return !m_visible;
    return true;
}

void CFishingMenu::setVisible(bool visible)
{
    if (m_window && m_visible != visible) {
        if (visible) {
            m_window->setVisible(true);
            m_window->moveToFront();
        } else m_window->setVisible(false);
        m_visible = visible;
    }
}

CFishingMenu::~CFishingMenu()
{
}

CFishingMenu::CFishingMenu(CGameUI& ui, CSettings&, Ogre::SceneManager*, CEGUI::Window* parent, CResourceManager* resources)
    : CRunicCore(), m_parent(parent), m_window(NULL), m_resources(resources), m_visible(true), m_gameUI(&ui)
{
    createMenus();
}
