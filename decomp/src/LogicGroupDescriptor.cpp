#include "EditorScene.h"
#include "LogicGroup.h"
#include "LogicGroupDescriptor.h"

CEditorBaseObject* CLogicGroupDescriptor::CreateObject(CEditorScene* scene)
{
    return new CLogicGroup(scene->getResourceManager());
}

CLogicGroupDescriptor::~CLogicGroupDescriptor()
{
}
