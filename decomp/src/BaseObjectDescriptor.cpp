#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"

CEditorBaseObject* CBaseObjectDescriptor::CreateObject(CEditorScene* scene)
{
    return new CEditorBaseObject();
}

CBaseObjectDescriptor::~CBaseObjectDescriptor()
{
}

void CBaseObjectDescriptor::SetIcon(const wchar_t* icon)
{
    m_sIcon = std::wstring(icon);
}
