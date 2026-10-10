#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "MasterResourceManager.h"
#include "Settings.h"
#include "TipMenu.h"

bool CTipMenu::handle_ExitButton(const CEGUI::EventArgs&)
{
    m_bUnknown32 = true;
    return true;
}

bool CTipMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button != CEGUI::LeftButton) return true;
    m_bUnknown32 = true;
    return CDropdownMenu::handle_CloseButton(event);
}

bool CTipMenu::onClick(ELayoutFunction function,std::wstring)
{
    if (m_bUnknown30) {
        if (function == static_cast<ELayoutFunction>(10)) {
            bool show = m_showTipsCheckbox->isSelected();
            unsigned int property = KSETTINGS_SHOW_TIPS;
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(property, show);
            m_bUnknown32 = true;
        }
        setOpen(false);
    }
    return true;
}
