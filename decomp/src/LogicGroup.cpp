#include "EmptyStrings.h"
#include "GameEnums.h"
#include "LogicGroup.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "LogicObject.h"
#include "ResourceManager.h"

CLogicObject* CLogicGroup::GetLogicObjectByIndex(unsigned int index)
{
    return index < m_logicObjects.size() ? m_logicObjects[index] : 0;
}

unsigned int CLogicGroup::GetLogicObjectIndex(CLogicObject* pLogicObject)
{
    if (pLogicObject == NULL)
        return static_cast<unsigned int>(-1);

    return *reinterpret_cast<const unsigned int*>(
        reinterpret_cast<const char*>(pLogicObject) + 0x58);
}

int CLogicGroup::AddLogicObject(long long objectID)
{
    CEditorScene* scene = getSceneOwner();
    if (objectID == -1 || scene == NULL)
        return -1;

    CLogicObject* logicObject = new CLogicObject(
        scene, objectID, m_logicObjects.size());
    AddLogicObject(logicObject);
    return m_logicObjects.size() - 1;
}

bool CLogicGroup::RemoveLogicObjectsLink(unsigned int logicObjectIndex,
                                          unsigned int linkIndex)
{
    if (linkIndex != (unsigned int)-1 &&
        logicObjectIndex != (unsigned int)-1 &&
        logicObjectIndex < m_logicObjects.size()) {
        CLogicObject* pLogicObject = m_logicObjects[logicObjectIndex];
        if (pLogicObject != NULL)
            return pLogicObject->RemoveLinkByIndex(linkIndex);
    }

    return false;
}

CLogicGroup::CLogicGroup(CResourceManager* resourceManager)
    : CEditorBaseObject(),
      m_pResourceManager(resourceManager),
      m_logicObjects(10),
      m_fEnabled(1.0f)
{
}
