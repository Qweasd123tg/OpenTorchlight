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

#include "FileSystem.h"
#include "Player.h"
#include <CEGUIWindowManager.h>
#include <CEGUIPropertyHelper.h>
#include <cmath>
void CFishingMenu::mapEventHandlers(CEGUI::Window* window)
{
    int count = window->getChildCount();
    for (int i = 0; i < count; ++i) mapEventHandlers(window->getChildAtIdx(i));
    try {
        if (window->isPropertyPresent("onClick") && !window->getProperty("onClick").empty())
            window->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::Event::Subscriber(&CFishingMenu::handle_onClick,this));
    } catch (...) {
    }
}
void CFishingMenu::createMenus()
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/fishingmenu.layout",info,false,true,false);
    m_window = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(info.m_sResourceName),true);
    m_gameUI->convertToScreenScale(m_window,false);
    m_ring = m_window->getChild("FishingRing");
    m_gameUI->mapToFunctions(m_window);
    mapEventHandlers(m_window);
    m_parent->addChildWindow(m_window);
    setVisible(false);
}
void CFishingMenu::update(float)
{
    if (!m_visible) return;
    CPlayer* player = static_cast<CPlayer*>(m_gameUI->getCharacter());
    if (!player) return;
    float time = player->m_fishingTime;
    float sine = sinf(player->m_fishingValue854);
    float size = player->m_fishingValue860 > 0.0f ? 1.0f : time + sine * .2f;
    size = m_gameUI->scaledY(size * 128.0f);
    m_ring->setSize(CEGUI::UVector2(CEGUI::UDim(0,size),CEGUI::UDim(0,size)));
    CEGUI::UVector2 position = m_ring->getPosition();
    position.d_x.d_offset = size * -.5f;
    position.d_y.d_offset = size * -.5f;
    m_ring->setPosition(position);
    CEGUI::colour color = static_cast<CPlayer*>(m_gameUI->getCharacter())->m_fishingValue860 > 0.0f ? CEGUI::colour(1,.3f,.3f,1) : CEGUI::colour(1,1,1,1);
    m_ring->setProperty("ImageColours", "tl:" + CEGUI::PropertyHelper::colourToString(color) + "tr:" + CEGUI::PropertyHelper::colourToString(color) + "bl:" + CEGUI::PropertyHelper::colourToString(color) + "br:" + CEGUI::PropertyHelper::colourToString(color));
}
