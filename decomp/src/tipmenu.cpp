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

#include "StringTranslate.h"
void CTipMenu::update(float)
{
    if (!m_bUnknown30 && !m_bUnknown31) {
        unsigned int property = KSETTINGS_SHOW_TIPS;
        bool show = m_showTipsCheckbox->isSelected();
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(property, show);
        m_bUnknown31 = true;
    }
}

void CTipMenu::setOpen(bool open)
{
    if (m_bUnknown30) {
        if (!open) {
            unsigned int property = KSETTINGS_SHOW_TIPS;
            bool show = m_showTipsCheckbox->isSelected();
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(property, show);
            static_cast<CEGUI::Window*>(m_pUnknown10)->removeChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
            m_bUnknown31 = false;
        }
    } else if (open) {
        m_bUnknown31 = false;
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
        static_cast<CEGUI::Window*>(m_pUnknown20)->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, 0)));
        static_cast<CEGUI::Window*>(m_pUnknown18)->setZOrderingEnabled(true);
        static_cast<CEGUI::Window*>(m_pUnknown10)->addChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
        static_cast<CEGUI::Window*>(m_pUnknown18)->setAlwaysOnTop(true);
        static_cast<CEGUI::Window*>(m_pUnknown18)->moveToFront();
    }
    m_bUnknown30 = open;
}

CTipMenu::CTipMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 0), m_tipText(NULL), m_tipImage(NULL)
{
    createMenus();
    static std::wstring g_Tip;
    if (g_Tip.empty())
        g_Tip = CStringTranslate::getSinglton()->getTranslateString(L"Tip");
    setTitle(g_Tip);
}

#include "FileSystem.h"
#include "StringUtilities.h"
#include <CEGUIWindowManager.h>
void CTipMenu::setContents(std::wstring& text)
{
    if (!m_tipText) return;
    std::string label = STRINGS::StringConvertToUTF8(text);
    m_tipImage->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(label.c_str())));
}
void CTipMenu::createMenus()
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/tipmenu.layout",info,false,true,false);
    CEGUI::Window* layout = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(info.m_sResourceName),true);
    m_tipText = layout->recursiveChildSearch("Ok");
    m_tipImage = layout->recursiveChildSearch("Dialog");
    m_iUnknown50 = layout->recursiveChildSearch("Title");
    m_showTipsCheckbox = static_cast<CEGUI::Checkbox*>(layout->recursiveChildSearch("ShowTips"));
    m_showTipsCheckbox->setSelected(true);
    m_pGameUI->convertToScreenScale(layout,false);
    m_pGameUI->mapToFunctions(layout);
    mapEventHandlers(layout);
    static_cast<CEGUI::Window*>(m_pUnknown20)->addChildWindow(layout);
    static_cast<CEGUI::Window*>(m_pUnknown20)->setAlwaysOnTop(true);
}
