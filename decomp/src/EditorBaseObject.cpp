#include "EmptyStrings.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "ResourceManager.h"
#include "Descriptor.h"
#include "Editor.h"
#include "EditorDLL.h"
#include "EditorObjectManager.h"
#include "Utilities.h"

CEditorBaseObject::CEditorBaseObject()
    : m_iGuid(UTILITIES::createUniqueGuid()), m_iParentGuid(-1), m_iOriginalGuid(m_iGuid),
      m_iParentHierarchyHashCode(0), m_bHashFromOriginalGuid(false), m_pDescriptor(NULL), m_pSceneOwner(NULL),
      m_pParentPositionableObject(NULL)
{
}

CEditorBaseObject::~CEditorBaseObject()
{
}

void CEditorBaseObject::AddBaseObjectFlag(EEDITOROBJECT_FLAG flag)
{
}

void CEditorBaseObject::RemoveBaseObjectFlag(EEDITOROBJECT_FLAG flag)
{
}

bool CEditorBaseObject::HasBaseObjectFlag(EEDITOROBJECT_FLAG flag)
{
    return false;
}

bool CEditorBaseObject::isChildOfObject(long long guid)
{
    if (guid == -1)
        return false;

    if (m_iParentGuid == -1)
        return false;
    if (m_iParentGuid == guid)
        return true;
    if (m_pSceneOwner == NULL)
        return false;
    CEditorBaseObject* parent = m_pSceneOwner->GetObjectInScene(m_iParentGuid);
    if (parent == NULL)
        return false;
    return parent->isChildOfObject(guid);
}

void CEditorBaseObject::setGuid(long long guid)
{
    long long oldGuid = m_iGuid;
    m_iGuid = guid;
    if (m_pSceneOwner)
        m_pSceneOwner->EditorBaseObjectChangedID(this, oldGuid, guid);
    if (m_iOriginalGuid == -1)
        m_iOriginalGuid = guid;
}

void CEditorBaseObject::BroadcastEvent(unsigned int event)
{
    if (m_pDescriptor)
        m_pDescriptor->BroadcastEventFromObject(this, event);
}

void CEditorBaseObject::calculateParentHierarchyHashCode()
{
    if (m_pSceneOwner == NULL)
    {
        m_iParentHierarchyHashCode = 0;
        return;
    }

    m_iParentHierarchyHashCode = m_bHashFromOriginalGuid ? m_iOriginalGuid : 0;
    if (m_iParentGuid != -1)
    {
        CEditorBaseObject* parent = m_pSceneOwner->GetObjectInScene(m_iParentGuid);
        if (parent)
        {
            m_iParentHierarchyHashCode = m_iParentHierarchyHashCode | parent->getParentHierarchyHashCode();
            return;
        }
    }
    m_iParentHierarchyHashCode = m_iParentHierarchyHashCode | m_pSceneOwner->getParentHierarchyHashCode();
}

CEditorBaseObject* GetObjectInScene(long long guid)
{
    if (guid == -1)
        return NULL;
    CEditorObjectManager* manager = gEditor->getObjectManager();
    if (manager == NULL)
        return NULL;
    CEditorObjectManager::ObjectMap::iterator found = manager->getObjects()->find(guid);
    if (found == manager->getObjects()->end())
        return NULL;
    return found->second;
}

int EditorGetEdtiorLevelDepth()
{
    if (gEditor->isActive())
        return gEditor->getLevelDepth();
    return -1;
}

void EditorSetEditorLevelDepth(int depth)
{
    if (gEditor->isActive())
        gEditor->setLevelDepth(depth);
}

void EditorSetEditorCharacterLevel(int level)
{
    if (gEditor->isActive())
        gEditor->setCharacterLevel(level);
}

void EditorSetEditorRunGodded(bool godded)
{
    if (gEditor->isActive())
        gEditor->setRunGodded(godded);
}

void EditorSetEditorAiFreeze(bool freeze)
{
    if (gEditor->isActive())
        gEditor->setAiFreeze(freeze);
}

void EditorSetEditorLevelPopulate(bool populate)
{
    if (gEditor->isActive())
        gEditor->setLevelPopulate(populate);
}

void EditorSetEditorLevelPopulateChampions(bool populate)
{
    if (gEditor->isActive())
        gEditor->setLevelPopulateChampions(populate);
}

void EditorSetEditorLevelCreatePet(bool create)
{
    if (gEditor->isActive())
        gEditor->setLevelCreatePet(create);
}

void EditorSetUseTempStartPos(bool use)
{
    if (gEditor->isActive())
        gEditor->setUseTempStartPos(use);
}

void EditorSetTempStartPos(float x, float y, float z)
{
    if (gEditor->isActive())
        gEditor->setTempStartPos(x, y, z);
}

bool EditorObjectExists(long long guid)
{
    if (!gEditor->isActive() || guid == -1)
        return false;
    CEditorObjectManager::ObjectMap* objects = gEditor->getObjectManager()->getObjects();
    if (objects == NULL)
        return false;
    return objects->find(guid) != objects->end();
}

void EditorFlyToObject(long long guid)
{
    // The lookup is all that is left of this function in the shipped build.
    if (gEditor->isActive())
        GetObjectInScene(guid);
}

long long EditorGetObjectSelectedByIndex(unsigned int index)
{
    if (gEditor->isActive())
    {
        TArrayList<CEditorBaseObject*>* selected = gEditor->getObjectManager()->getSelectedObjects();
        if (selected)
        {
            if (selected->size() != 0 && index < selected->size())
                return (*selected)[index]->getGuid();
        }
    }
    return -1;
}

void EditorSetObjectParent(long long guid, long long parentGuid)
{
    if (gEditor->isActive())
    {
        CEditorBaseObject* object = GetObjectInScene(guid);
        if (object)
            object->setParentGuid(parentGuid);
    }
}

long long EditorGetObjectParent(long long guid)
{
    if (gEditor->isActive())
    {
        CEditorBaseObject* object = GetObjectInScene(guid);
        if (object)
            return object->getParentGuid();
    }
    return -1;
}

int EditorGetObjectDescriptorID(long long guid)
{
    if (gEditor->isActive())
    {
        CEditorBaseObject* object = GetObjectInScene(guid);
        if (object && object->getSceneOwner() && object->getSceneOwner()->getDescriptorManager() &&
            object->getDescriptor())
            return 0;
    }
    return -1;
}

bool EditorGetFlagState(unsigned int flag)
{
    if (gEditor->isActive())
        return (gEditor->getFlags() >> flag) & 1;
    return false;
}

void EditorParticleMovementConfig(float& a, float& b, bool set)
{
    if (gEditor->isActive())
    {
        if (set)
        {
            gEditor->m_fParticleMovementB = b;
            gEditor->m_fParticleMovementA = a;
        }
        else
        {
            b = gEditor->m_fParticleMovementB;
            a = gEditor->m_fParticleMovementA;
        }
    }
}

void EditorMakeGuid()
{
}

void EditorSetModPriority(const wchar_t* mod, int priority)
{
}
