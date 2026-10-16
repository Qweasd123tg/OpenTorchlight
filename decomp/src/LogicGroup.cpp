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
    int index = -1;
    if (objectID != -1 && getSceneOwner() != NULL) {
        CLogicObject* logicObject = new CLogicObject(
            getSceneOwner(), objectID, m_logicObjects.size());
        AddLogicObject(logicObject);
        index = m_logicObjects.size() - 1;
    }
    return index;
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

bool CLogicGroup::RemoveLogicObjectByIndex(unsigned int index)
{
    if (index < m_logicObjects.size() && m_logicObjects[index] != NULL) {
        for (unsigned int i = 0; i < m_logicObjects.size(); ++i)
            if (i != index && m_logicObjects[i] != NULL)
                m_logicObjects[i]->RemoveLinksToLogicObject(m_logicObjects[index]);
        if (m_logicObjects[index] != NULL) {
            delete m_logicObjects[index];
            m_logicObjects[index] = NULL;
        }
        m_logicObjects[index] = NULL;
        return true;
    }
    return false;
}

CLogicGroup::~CLogicGroup()
{
    m_logicObjects.deleteAll();
}
