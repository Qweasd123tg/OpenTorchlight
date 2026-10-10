#include "EditorButton.h"

CEditorButton::~CEditorButton()
{
}

bool CEditorButton::handle_Click(const CEGUI::EventArgs&)
{
    if (m_bEnabled) BroadcastEvent(111);
    return true;
}

void CEditorButton::setRolloverImage(const std::wstring& name)
{
    if (m_pWindow && m_pGameUI && name != m_sRolloverImage) {
        m_sRolloverImage = name;
        getImageByFileOrName(name, (unsigned char*)"HoverImage");
    }
}

void CEditorButton::setNormalImage(const std::wstring& name)
{
    if (m_pWindow && m_pGameUI && name != m_sNormalImage) {
        m_sNormalImage = name;
        getImageByFileOrName(name, (unsigned char*)"NormalImage");
    }
}

void CEditorButton::setDisabledImage(const std::wstring& name)
{
    if (m_pWindow && m_pGameUI && name != m_sDisabledImage) {
        m_sDisabledImage = name;
        getImageByFileOrName(name, (unsigned char*)"DisabledImage");
    }
}

void CEditorButton::setClickedImage(const std::wstring& name)
{
    if (m_pWindow && m_pGameUI && name != m_sClickedImage) {
        m_sClickedImage = name;
        getImageByFileOrName(name, (unsigned char*)"PushedImage");
    }
}
