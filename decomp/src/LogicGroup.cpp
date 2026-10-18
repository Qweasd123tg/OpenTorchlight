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

void CLogicGroup::AddLogicObject(CLogicObject* object)
{
    object->m_iID = m_logicObjects.size();
    m_logicObjects.add(object);
}

bool CLogicGroup::RemoveLogicObjectsRefingObjectID(long long objectID)
{
    if (objectID == -1) return false;
    bool result = true;
    for (unsigned int i = 0; i < m_logicObjects.size(); ++i) {
        if (m_logicObjects[i]) {
            if (m_logicObjects[i]->m_iObjectID == objectID)
                result &= RemoveLogicObjectByIndex(i);
            else
                result &= m_logicObjects[i]->RemoveLogicLinksRefingObjectID(objectID);
        }
    }
    return result;
}

void CLogicGroup::saveLogicGroupToDataGroup(CDataGroup* dataGroup,
    std::ofstream* stream, CDescriptorSaveConfiguration* configuration)
{
    TArrayList<bool> saved(m_logicObjects.size());
    unsigned int count = 0;
    for (unsigned int i = 0; i < m_logicObjects.size(); ++i) {
        if (m_logicObjects[i]) {
            CEditorBaseObject* object = m_logicObjects[i]->GetObject();
            if (object) {
                if (object->getSceneOwner()->canObjectBeSaved(m_pResourceManager, object)) {
                    saved.add(true);
                    ++count;
                } else saved.add(false);
            }
        } else saved.add(false);
    }
    if (dataGroup) {
        CDataGroup* group = dataGroup->AddDataGroup(L"LOGICGROUP");
        for (unsigned int i = 0; i < m_logicObjects.size(); ++i)
            if (m_logicObjects[i] && saved[i])
                m_logicObjects[i]->saveLogicObjectToDataGroup(group);
    } else if (stream) {
        stream->write(reinterpret_cast<const char*>(&count), 4);
        for (unsigned int i = 0; i < m_logicObjects.size(); ++i)
            if (saved[i]) m_logicObjects[i]->saveLogicObjectToBinaryFile(stream);
        for (unsigned int i = 0; i < m_logicObjects.size(); ++i)
            if (saved[i]) m_logicObjects[i]->saveLogicObjectLinksToBinaryFile(stream);
    }
}

#include "StringUtilities.h"
#include <OgreLogManager.h>

void CLogicGroup::loadLogicGroupToDataGroup(CDataGroup* data, COgreReader* reader,
    CDescriptorLoadConfiguration* configuration)
{
    std::map<int, int> remapped;
    if (data) {
        CDataGroup* group = data->GetDataGroupByName(L"LOGICGROUP", false);
        if (!group || group->GetGroupName() != L"LOGICGROUP")
            return;
        std::vector<CDataGroup*> objects;
        group->GetDataGroupsMatchingName(L"LOGICOBJECT", &objects);
        for (unsigned int i = 0; i < objects.size(); ++i) {
            CDataGroup* object = objects[i];
            if (object->GetGroupName() != L"LOGICOBJECT")
                Ogre::LogManager::getSingleton().logMessage("ERROR LEVEL WILL NOT WORK LOGICOBJECT NOT FOUND ", Ogre::LML_CRITICAL, false);
            unsigned int id = object->GetDataValue(L"ID", static_cast<unsigned int>(-1));
            long long originalID = object->GetDataValue(L"OBJECTID", -1LL);
            long long objectID = configuration->getRemappedID(originalID);
            if (objectID == -1 || id == static_cast<unsigned int>(-1))
                Ogre::LogManager::getSingleton().logMessage("ERROR IN GETTING ORIGINAL OBJECT!!" + STRINGS::GetValueAsString(originalID), Ogre::LML_CRITICAL, false);
            remapped[id] = AddLogicObject(objectID);
        }
        for (unsigned int i = 0; i < objects.size(); ++i) {
            CDataGroup* object = objects[i];
            if (object->GetGroupName() == L"LOGICOBJECT") {
                unsigned int id = remapped[object->GetDataValue(L"ID", static_cast<unsigned int>(-1))];
                if (id < m_logicObjects.size() && m_logicObjects[id])
                    m_logicObjects[id]->loadLogicObjectByDataGroup(this, object, configuration, &remapped);
            }
        }
    } else if (reader) {
        unsigned int count = 0;
        reader->read(&count, 4);
        for (unsigned int i = 0; i < count; ++i) {
            CLogicObject* object = new CLogicObject(getSceneOwner(), -1, static_cast<unsigned int>(-1));
            AddLogicObject(object);
            object->loadLogicObjectByBinaryFile(this, reader, configuration, remapped);
        }
        for (unsigned int i = 0; i < m_logicObjects.size(); ++i)
            m_logicObjects[i]->loadAndRelinkObjectInFromBinaryFile(this, reader, configuration, remapped);
    }
}
