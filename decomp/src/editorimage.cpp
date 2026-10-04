#include "EmptyStrings.h"
#include "GameVariables.h"
#include "EditorImage.h"
#include "Item.h"

void CEditorImage::setVisible(bool visible)
{
    if (m_pParentWindow != NULL && m_pWindow != NULL && m_bVisible != visible)
    {
        m_bVisible = visible;
        if (visible)
            BroadcastEvent(4);
        else
            BroadcastEvent(5);
    }
}

void CEditorImage::calculatePosOffsetHie(CEGUI::UDim& position,
                                        CEGUI::UDim& size)
{
    if (m_pParentImage != NULL) {
        m_pParentImage->calculatePosOffsetHie(position, size);
    }

    reinterpret_cast<float*>(&position)[0] += m_fOffsetXPct;
    reinterpret_cast<float*>(&position)[1] += m_fOffsetX;
    reinterpret_cast<float*>(&size)[0] += m_fOffsetYPct;
    reinterpret_cast<float*>(&size)[1] += m_fOffsetY;
}

bool CEditorImage::getVisibleHie()
{
    if (m_pParentImage)
    {
        if (!m_bVisible)
        {
            return false;
        }
        return m_pParentImage->getVisibleHie();
    }
    return m_bVisible;
}

#include <CEGUIWindow.h>

void CEditorImage::setEnabled(bool enabled)
{
    m_bEnabled = enabled;

    if (m_pWindow != NULL)
        m_pWindow->setEnabled(enabled);

    if (enabled)
        BroadcastEvent(6);
    else
        BroadcastEvent(7);
}

void CEditorImage::updatePositionAndSize()
{
    if (m_pWindow != NULL)
    {
        CEGUI::UVector2 position(
            CEGUI::UDim(m_fPosXPct - m_fOffsetXPct,
                        m_fPosX - m_fOffsetX),
            CEGUI::UDim(m_fPosYPct - m_fOffsetYPct,
                        m_fPosY - m_fOffsetY));
        m_pWindow->setPosition(position);

        CEGUI::UVector2 size(m_sizeWidth, m_sizeHeight);
        m_pWindow->setSize(size);
    }
}

void CEditorImage::setImageFileName(const std::wstring& imageFileName)
{
    if (m_pWindow != NULL && m_pGameUI != NULL) {
        if (m_sImageFileName != imageFileName) {
            m_sImageFileName = imageFileName;
            getImageByFileOrName(imageFileName, (unsigned char*)"Image");
        }
    }
}
