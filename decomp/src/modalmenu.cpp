#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "ModalMenu.h"

void CModalMenu::update(float elapsed)
{
    CDropdownMenu::update(elapsed);
}

void CModalMenu::setOpen(bool open)
{
    CDropdownMenu::setOpen(open);
}

bool CModalMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton) {
    m_bUnknown32 = true;
    m_pGameUI->getCharacter()->setAIState(AISTATE_IDLE);
    }
    return true;
}

bool CModalMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton) {
    m_bUnknown32 = true;
    m_pGameUI->getCharacter()->setAIState(AISTATE_IDLE);
        return CDropdownMenu::handle_CloseButton(event);
    }
    return true;
}

bool CModalMenu::onClick(ELayoutFunction function, std::wstring)
{
    if (m_bUnknown30) {
        if (function == 9 || function == 10) {
            m_pGameUI->getCharacter()->setAIState(AISTATE_IDLE);
            m_bUnknown32 = true;
            if (m_acceptCallback) m_acceptCallback(m_pGameUI->getCharacter(), m_callbackData);
        } else if (function == 8) {
            m_pGameUI->getCharacter()->setAIState(AISTATE_IDLE);
            m_bUnknown32 = true;
            if (m_declineCallback) m_declineCallback(m_pGameUI->getCharacter(), m_callbackData);
        }
    }
    return true;
}

#include "StringTranslate.h"
CModalMenu::CModalMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 0), m_callbackData(NULL), m_promptWindow(NULL), m_acceptWindow(NULL), m_declineWindow(NULL), m_extraWindow(NULL), m_acceptCallback(NULL), m_declineCallback(NULL)
{
    createMenus();
    static std::wstring g_Dialog;
    if (g_Dialog.empty())
        g_Dialog = CStringTranslate::getSinglton()->getTranslateString(L"Dialog");
    setTitle(g_Dialog);
}
