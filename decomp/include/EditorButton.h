#ifndef EDITORBUTTON_H
#define EDITORBUTTON_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <CEGUIEventArgs.h>
#include <string>
#include "EditorImage.h"
#include "ResourceManager.h"

class CEditorButton : public CEditorImage
{
public:
    virtual ~CEditorButton();
    long long handle_Click(const CEGUI::EventArgs&);
    void setRolloverImage(const std::wstring&);
    void setNormalImage(const std::wstring&);
    void setDisabledImage(const std::wstring&);
    void setClickedImage(const std::wstring&);
    CEditorButton(CResourceManager*);

    // fields
    std::wstring m_sNormalImage;
    std::wstring m_sRolloverImage;
    std::wstring m_sClickedImage;
    std::wstring m_sDisabledImage;
};

#endif
