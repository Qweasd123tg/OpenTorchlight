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

bool CFishingMenu::handle_onClick(const CEGUI::EventArgs& event)
{
    const CEGUI::MouseEventArgs& mouse = static_cast<const CEGUI::MouseEventArgs&>(event);
    CEGUI::Window* window = mouse.window;
    if (mouse.button == CEGUI::LeftButton && window)
        return onClick(*static_cast<ELayoutFunction*>(window->getUserData()));
    return true;
}

bool CFishingMenu::onClick(ELayoutFunction function)
{
    if (m_visible) {
        if (function == 6) {
            if (m_gameUI->getCharacter()->getAIState() != static_cast<EAIState>(34)) {
                m_gameUI->getCharacter()->setTargetItem(NULL);
                m_gameUI->getCharacter()->setAIState(AISTATE_IDLE);
            }
        } else if (function == 14) m_gameUI->getCharacter()->catchFish();
    }
    return true;
}
