#ifndef EDITORIMAGE_H
#define EDITORIMAGE_H

#include <CEGUIString.h>
#include <CEGUIUDim.h>
#include <string>

#include "EditorBaseObject.h"
#include "ResourceManager.h"

class CGameUI;

namespace CEGUI
{
class Window;
}

class CEditorImage : public CEditorBaseObject
{
public:
    virtual ~CEditorImage();

    void setVisible(bool visible);
    void calculatePosOffsetHie(CEGUI::UDim& position,
                               CEGUI::UDim& size);
    void calculatePosHie(CEGUI::UDim& position,
                         CEGUI::UDim& size);
    bool getVisibleHie();
    void activate();
    void setEnabled(bool enabled);
    void updatePositionAndSize();
    void update(float deltaTime);

    CEditorImage(CResourceManager* resourceManager,
                 CEGUI::String windowType);

    long getImageByFileOrName(const std::wstring& imageFileName,
                              unsigned char* propertyName);
    void setImageFileName(const std::wstring& imageFileName);

    CGameUI* m_pGameUI;
    CResourceManager* m_pResourceManager;
    CEGUI::Window* m_pParentWindow;
    CEGUI::Window* m_pWindow;
    std::string m_sImageSetName;
    std::wstring m_sImageFileName;
    float m_fPosXPct;
    float m_fPosX;
    float m_fPosYPct;
    float m_fPosY;
    CEGUI::UDim m_sizeWidth;
    CEGUI::UDim m_sizeHeight;
    float m_fOffsetXPct;
    float m_fOffsetX;
    float m_fOffsetYPct;
    float m_fOffsetY;
    bool m_bVisible;
    bool m_bEnabled;
    unsigned char m_gapBA[0x6];
    CEditorImage* m_pParentImage;
    bool m_bWindowVisible;
};

#endif
