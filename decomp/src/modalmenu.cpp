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

#include "FileSystem.h"
#include "StringUtilities.h"
#include <CEGUIWindowManager.h>
void CModalMenu::setContents(std::wstring& text,bool paired,bool (*accept)(CBaseUnit*,CBaseUnit*),bool (*decline)(CBaseUnit*,CBaseUnit*))
{
    m_acceptCallback = accept;
    m_declineCallback = decline;
    if (!m_acceptWindow || !m_declineWindow || !m_promptWindow) return;
    m_acceptWindow->setVisible(false);
    m_declineWindow->setVisible(false);
    m_promptWindow->setVisible(false);
    if (paired) {
        m_declineWindow->setVisible(true);
        m_acceptWindow->setVisible(true);
    } else m_promptWindow->setVisible(true);
    std::string label = STRINGS::StringConvertToUTF8(text);
    m_extraWindow->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(label.c_str())));
}
void CModalMenu::createMenus()
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/modalmenu.layout",info,false,true,false);
    CEGUI::Window* layout = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(info.m_sResourceName),true);
    m_declineWindow = layout->recursiveChildSearch("Decline");
    m_acceptWindow = layout->recursiveChildSearch("Accept");
    m_promptWindow = layout->recursiveChildSearch("Ok");
    m_extraWindow = layout->recursiveChildSearch("Dialog");
    m_iUnknown50 = layout->recursiveChildSearch("Title");
    m_pGameUI->convertToScreenScale(layout,false);
    m_pGameUI->mapToFunctions(layout);
    mapEventHandlers(layout);
    static_cast<CEGUI::Window*>(m_pUnknown20)->addChildWindow(layout);
    static_cast<CEGUI::Window*>(m_pUnknown18)->setAlwaysOnTop(true);
    static_cast<CEGUI::Window*>(m_pUnknown18)->setZOrderingEnabled(false);
}
