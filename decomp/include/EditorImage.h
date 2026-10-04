#ifndef EDITORIMAGE_H
#define EDITORIMAGE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <CEGUIString.h>
#include <CEGUIUDim.h>
#include <string>
#include "EditorBaseObject.h"
#include "ResourceManager.h"
class CGameUI;

class CEditorImage : public CEditorBaseObject
{
public:
    virtual ~CEditorImage();
    void setVisible(bool);
    void calculatePosOffsetHie(CEGUI::UDim&, CEGUI::UDim&);
    void calculatePosHie(CEGUI::UDim&, CEGUI::UDim&);
    char getVisibleHie();
    void activate();
    void setEnabled(bool);
    void updatePositionAndSize();
    void update(float);
    CEditorImage(CResourceManager*, CEGUI::String);
    long getImageByFileOrName(const std::wstring&, unsigned char*);
    void setImageFileName(const std::wstring&);

    // fields
    CGameUI* m_pGameUI;
    CResourceManager* m_pResourceManager;
    long long m_iUnknown68;
    void* m_pUnknown70;
    std::string m_sUnknown78;
    std::wstring m_sImageFileName;
    float m_fPosXPCT;
    float m_fPosX;
    float m_fPosYPCT;
    float m_fPosY;
    long long m_iWidthPCT;
    long long m_iHeightPCT;
    float m_fOffsetXPct;
    float m_fOffsetX;
    float m_fOffsetYPct;
    float m_fOffsetY;
    bool m_bVisible;
    bool m_bUnknownB9;
    unsigned char m_gapBA[0x6];
    CEditorImage* m_pEditorImage;
    bool m_bUnknownC8;
};

#endif
