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
