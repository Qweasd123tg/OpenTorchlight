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
#include <CEGUIWindowManager.h>

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

void CEditorImage::calculatePosHie(CEGUI::UDim& position, CEGUI::UDim& size)
{
    if (m_pParentImage)
        m_pParentImage->calculatePosHie(position, size);
    position.d_scale += m_fPosXPct;
    position.d_offset += m_fPosX;
    size.d_scale += m_fPosYPct;
    size.d_offset += m_fPosY;
}

#include "EditorScene.h"

void CEditorImage::activate()
{
    m_pParentImage = NULL;
    if (getParentGuid() != -1) {
        m_pParentImage = dynamic_cast<CEditorImage*>(getSceneOwner()->GetObjectInScene(getParentGuid()));
        if (m_pParentImage && m_pParentImage->m_pWindow) {
            m_pParentImage->m_pWindow->addChildWindow(m_pWindow);
            return;
        }
    }
    m_pParentWindow->addChildWindow(m_pWindow);
}

void CEditorImage::update(float elapsed)
{
    if (!m_pWindow || !m_pParentWindow)
        return;
    if (m_bVisible) {
        if (!m_bWindowVisible) {
            m_bWindowVisible = true;
            m_pWindow->setVisible(true);
        }
        updatePositionAndSize();
    } else if (m_bWindowVisible) {
        m_bWindowVisible = false;
        m_pWindow->setVisible(false);
    }
}

CEditorImage::~CEditorImage()
{
    setVisible(false);
    if (m_pWindow) {
        if (m_pWindow->getParent())
            m_pWindow->getParent()->removeChildWindow(m_pWindow);
        CEGUI::WindowManager::getSingleton().destroyWindow(m_pWindow);
    }
}
