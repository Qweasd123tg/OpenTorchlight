#include "Item.h"
#include "Character.h"
#include "DropdownMenu.h"
#include "iMenuListener.h"


CDropdownMenu::~CDropdownMenu()
{
    if (m_pGenericModel)
    {
        delete m_pGenericModel;
        m_pGenericModel = NULL;
    }
    if (m_pSoundBank)
    {
        delete m_pSoundBank;
        m_pSoundBank = NULL;
    }
    m_menuListeners.clear();
    m_pendingMenuListeners.clear();
}

template TArrayList<iMenuListener*>::~TArrayList();

bool CDropdownMenu::processInput(void*, float, bool capture)
{
    if (capture && m_bUnknown32) {
        setOpen(false);
        m_bUnknown32 = false;
        return false;
    }
    return true;
}

#include <CEGUIInputEvent.h>
#include "GameClient.h"

void CDropdownMenu::addMenuListener(iMenuListener* listener)
{
    if (m_menuListeners.find(listener) != -1) return;
    m_pendingMenuListeners.remove(listener);
    m_menuListeners.add(listener);
}

void CDropdownMenu::removeMenuListener(iMenuListener* listener)
{
    m_pendingMenuListeners.add(listener);
}

void CDropdownMenu::broadcastEvent(EMENU_TYPE menu, EMENU_EVENT event)
{
    for (unsigned int i = 0; i < m_pendingMenuListeners.size(); ++i)
        m_menuListeners.remove(m_pendingMenuListeners[i]);
    m_pendingMenuListeners.clear();
    for (unsigned int i = 0; i < m_menuListeners.size(); ++i)
        m_menuListeners[i]->menuEventOccured(this, menu, event);
}

bool CDropdownMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton) {
        m_bUnknown32 = true;
        CGameClient* client = m_pGameUI->m_gameClient;
        client->m_selectedItem.setObject(NULL);
        client->m_targetItem.setObject(NULL);
        client->m_selectedCharacter.setObject(NULL);
        client->m_targetCharacter.setObject(NULL);
    }
    return true;
}

#include "StringUtilities.h"
bool CDropdownMenu::handle_onDoubleClick(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = static_cast<const CEGUI::WindowEventArgs&>(event).window;
    if (!window) return true;
    ELayoutFunction function = *static_cast<ELayoutFunction*>(window->getUserData());
    // These event controls store the payload string and prefix length in the
    // extended layout at +0x520/+0x680, beyond Window's ordinary text/ID.
    const CEGUI::String& payload = *reinterpret_cast<const CEGUI::String*>(reinterpret_cast<const char*>(window) + 0x520);
    std::wstring text = STRINGS::StringConvertToWide(reinterpret_cast<const char*>(payload.c_str()), 5000);
    std::wstring::size_type prefix = *reinterpret_cast<const int*>(reinterpret_cast<const char*>(window) + 0x680);
    text = text.substr(prefix, text.length() - prefix);
    return onDoubleClick(function, text);
}
bool CDropdownMenu::handle_onClick(const CEGUI::EventArgs& event)
{
    const CEGUI::MouseEventArgs& mouse = static_cast<const CEGUI::MouseEventArgs&>(event);
    CEGUI::Window* window = mouse.window;
    if (mouse.button != CEGUI::LeftButton || !window) return true;
    // These event controls store the payload string and prefix length in the
    // extended layout at +0x520/+0x680, beyond Window's ordinary text/ID.
    const CEGUI::String& payload = *reinterpret_cast<const CEGUI::String*>(reinterpret_cast<const char*>(window) + 0x520);
    std::wstring text = STRINGS::StringConvertToWide(reinterpret_cast<const char*>(payload.c_str()), 5000);
    std::wstring::size_type prefix = *reinterpret_cast<const int*>(reinterpret_cast<const char*>(window) + 0x680);
    text = text.substr(prefix, text.length() - prefix);
    return onClick(*static_cast<ELayoutFunction*>(window->getUserData()), text);
}
