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

CBaseObjectDescriptor::CBaseObjectDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CDescriptor(0)
{
    m_sName = std::wstring(name);
    m_sIcon = std::wstring(description);
    m_sDescription = std::wstring(group);
}
