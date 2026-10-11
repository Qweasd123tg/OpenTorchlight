#include "EmptyStrings.h"
#include "DataGroup.h"
#include "Descriptor.h"
#include "DescriptorController.h"
#include "FileUtilities.h"
#include "LogicGroupDescriptor.h"
#include "MasterResourceManager.h"
#include "ParticleScene.h"
#include "ParticleTechWrapper.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "Settings.h"
#include "Timeline.h"
extern unsigned int gObjectsCreated __asm__("_ZL15gObjectsCreated");

#include "EditorScene.h"

void CEditorScene::fireEvent(EEDITOR_EVENTS event, long long guid)
{
}

#include <map>
#include <string>
#include "DescriptorManager.h"

void CEditorScene::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
    if (m_pDescriptorManager)
    {
        if (enabled)
            BroadcastEvent(6);
        else
            BroadcastEvent(7);
    }
}

void CEditorScene::update(float elapsed)
{
    if (m_bVisible && getEnabled() && m_pDescriptorManager)
        m_pDescriptorManager->update(elapsed);
}

CEditorBaseObject* CEditorScene::GetObjectInScene(long long guid)
{
    if (guid == -1)
        return NULL;
    std::map<long long, CEditorBaseObject*>::iterator object = m_Objects.find(guid);
    if (object != m_Objects.end())
        return object->second;
    return NULL;
}

void CEditorScene::clearObjectIndex()
{
    gObjectsCreated = 0;
}

unsigned int CEditorScene::GetNumberOfObjectsInScene(bool includeOwner)
{
    if (includeOwner && getSceneOwner()) return getSceneOwner()->GetNumberOfObjectsInScene(true) + m_Objects.size();
    return m_Objects.size();
}

TArrayList<CEditorBaseObject*>* CEditorScene::GetObjectsCreatedByADescriptor(CDescriptor* descriptor)
{
    return descriptor ? &descriptor->m_Objects : NULL;
}

bool CEditorScene::canObjectBeSaved(CResourceManager* manager, CEditorBaseObject* object)
{
    for (;;) {
        if (static_cast<signed char>(object->getDescriptor()->m_iFlags) < 0) return false;
        if (object->HasBaseObjectFlag(EDITOROBJECT_FLAG_DONT_SAVE)) return false;
        long long parent = object->getParentGuid();
        if (parent == -1) return true;
        std::map<long long, CEditorBaseObject*>::iterator found = m_Objects.find(parent);
        if (found == m_Objects.end()) return true;
        object = found->second;
        if (!object) return true;
    }
}

CEditorBaseObject* CEditorScene::CreateObjectByDescriptor(const std::wstring& name, bool load)
{
    if (m_pDescriptorManager) return CreateObjectByDescriptor(m_pDescriptorManager->GetDescriptor(name.c_str(), true), NULL, NULL, load);
    return NULL;
}

CDescriptor* CEditorScene::GetDescriptorInSceneByName(const wchar_t* name, bool create)
{
    if (m_pDescriptorManager) return m_pDescriptorManager->GetDescriptor(name, create);
    return NULL;
}

void CEditorScene::setChildrenVisible(long long parent, bool visible)
{
    for (std::map<long long, CEditorBaseObject*>::iterator i=m_Objects.begin(); i!=m_Objects.end(); ++i) {
        if (i->second->isChildOfObject(parent)) {
            CSceneNodeObject* object = dynamic_cast<CSceneNodeObject*>(i->second);
            if (object) object->setVisible(visible);
        }
    }
}

CEditorBaseObject* CEditorScene::CreateObjectByDescriptor(unsigned int index, CEditorBaseObject* parent, CEditorBaseObject* owner, bool load)
{
    if (m_pDescriptorManager) return CreateObjectByDescriptor(m_pDescriptorManager->GetDescriptor(index), parent, owner, load);
    return NULL;
}

void CEditorScene::AddDescriptor(CDescriptor* descriptor)
{
    if (descriptor && m_pDescriptorManager) m_pDescriptorManager->AddDescriptor(descriptor);
}

void CEditorScene::InitScene(CResourceManager* manager, unsigned int flags)
{
    if (manager && !m_pUnknown178) {
        setResourceManager(manager);
        m_iUnknown188 = flags;
        m_pUnknown170 = CMasterResourceManager::getSingleton()->m_pSettings;
        m_pUnknown178 = getResourceManager()->getSceneManager();
        createDescriptors();
        setVisible(true);
    }
}

void CEditorScene::deleteUnusedDescriptors()
{
    if (m_pDescriptorManager) m_pDescriptorManager->deleteUnusedDescriptors();
}

void CEditorScene::setFileLoaded(const std::wstring& path)
{
    m_sFileLoaded = FILESYSTEM::CleanPath(path);
}

unsigned int CEditorScene::saveObjectsHavingParent(long long parent, CDataGroup* group, CDescriptorSaveConfiguration* configuration)
{
    unsigned int count=0;
    for (std::map<long long, CEditorBaseObject*>::iterator it=m_Objects.begin(); it!=m_Objects.end(); ++it) {
        if (it->second->getParentGuid()==parent && it->second->getDescriptor())
            count += saveObjectAndChildren(it->second, group, configuration);
    }
    return count;
}

TArrayList<CEditorBaseObject*>* CEditorScene::GetObjectsCreatedByADescriptor(const std::wstring& name)
{
    if (!m_pDescriptorManager) return NULL;
    CDescriptor* descriptor = m_pDescriptorManager->GetDescriptor(name.c_str(),false);
    if (!descriptor) return NULL;
    return &descriptor->m_Objects;
}

void CEditorScene::AddDescriptor(const wchar_t* name)
{
    if (!m_pDescriptorManager->GetDescriptor(name,true)) {
        CDescriptor* descriptor = CDescriptorController::getNewDescriptorByName(name);
        AddDescriptor(descriptor);
    }
}

unsigned int CEditorScene::getNumberOfParticlesUpdating()
{
    CDescriptor* descriptor = GetDescriptorInSceneByName(L"Particle", false);
    unsigned int count = 0;
    if (descriptor) {
        for (unsigned int i = 0; i < descriptor->getObjectCount(); ++i)
            if (static_cast<CParticleWrapper*>(descriptor->getObject(i))->isPlaying()) ++count;
    }
    else {
        descriptor = GetDescriptorInSceneByName(L"Layout Link Particle", false);
        if (descriptor) {
            for (unsigned int i = 0; i < descriptor->getObjectCount(); ++i)
                count += static_cast<CEditorScene*>(descriptor->getObject(i))->getNumberOfParticlesUpdating();
        }
    }
    return count;
}

unsigned int CEditorScene::getNumberOfTimelinesUpdating(bool excludeLooping)
{
    CDescriptor* descriptor = GetDescriptorInSceneByName(L"Timeline", false);
    unsigned int count = 0;
    if (descriptor) {
        for (unsigned int i = 0; i < descriptor->getObjectCount(); ++i) {
            CTimeline* timeline = static_cast<CTimeline*>(descriptor->getObject(i));
            if (timeline->m_bEnabled && (!excludeLooping || !timeline->m_bTimelineLoops)) ++count;
        }
    }
    return count;
}

unsigned int CEditorScene::getNumberOfTimelinesThatDoLoop()
{
    CDescriptor* descriptor = GetDescriptorInSceneByName(L"Timeline", false);
    unsigned int count = 0;
    if (descriptor) {
        for (unsigned int i = 0; i < descriptor->getObjectCount(); ++i)
            if (static_cast<CTimeline*>(descriptor->getObject(i))->m_bTimelineLoops) ++count;
    }
    return count;
}

void CEditorScene::setActivated(bool activated)
{
    if (m_bActivated == activated) return;
    m_bActivated = activated;
    if (!m_pDescriptorManager) return;
    if (!activated) {
        m_pDescriptorManager->deactivateDescriptors(this);
        return;
    }
    m_pDescriptorManager->activateDescriptors(this);
    CDescriptor* descriptor = GetDescriptorInSceneByName(L"Logic Group", false);
    CLogicGroupDescriptor* logic = dynamic_cast<CLogicGroupDescriptor*>(descriptor);
    if (logic) logic->levelActivated(this);
}

#include <fstream>
#include "RandomGroup.h"

void CEditorScene::EditorBaseObjectChangedID(CEditorBaseObject* object, long long oldGuid, long long newGuid)
{
    std::map<long long, CEditorBaseObject*>::iterator found = m_Objects.find(oldGuid);
    if (found == m_Objects.end()) return;
    m_Objects.erase(found);
    if (m_Objects.find(newGuid) == m_Objects.end()) m_Objects[newGuid] = object;
}

void CEditorScene::DeleteAllObjectsFromScene()
{
    editorObjectsAboutToBeDelete();
    if (!m_Objects.empty()) {
        for (std::map<long long, CEditorBaseObject*>::iterator i = m_Objects.begin(); i != m_Objects.end(); ++i) {
            CPositionableObject* node = dynamic_cast<CPositionableObject*>(i->second);
            if (node) node->sceneNodeSetParent(NULL, true);
        }
        for (std::map<long long, CEditorBaseObject*>::iterator i = m_Objects.begin(); i != m_Objects.end();) {
            CEditorBaseObject* object = i->second;
            ++i;
            object->getDescriptor()->DescriptorObjectBeingDeleted(object);
            editorObjectDelete(object);
            delete object;
        }
        for (unsigned int i = 0; i < m_pDescriptorManager->getDescriptorVector().size(); ++i)
            m_pDescriptorManager->getDescriptorVector()[i]->cleanForQuickShutDown();
    }
    m_Objects.clear();
    m_ObjectList0.clear();
}

void CEditorScene::RemoveObjectInScene(CEditorBaseObject* object)
{
    if (!object || object->getSceneOwner() != this || !object->getDescriptor()) return;
    for (std::map<long long, CEditorBaseObject*>::iterator i = m_Objects.begin(); i != m_Objects.end();) {
        CEditorBaseObject* child = i->second;
        ++i;
        if (child->getParentGuid() == object->getGuid()) child->setParentGuid(object->getParentGuid());
    }
    std::map<long long, CEditorBaseObject*>::iterator found = m_Objects.find(object->getGuid());
    if (found == m_Objects.end()) return;
    m_Objects.erase(found);
    m_ObjectList0.remove(object);
    object->getDescriptor()->EditorSceneRemovingObject(object);
    object->SetSceneOwner(NULL);
    object->m_pDescriptor = NULL;
}

void CEditorScene::getChildren(long long parent, TArrayList<CEditorBaseObject*>& objects, CDescriptor* exclude)
{
    objects.setGrowBy(static_cast<unsigned int>(m_Objects.size()));
    for (std::map<long long, CEditorBaseObject*>::iterator i = m_Objects.begin(); i != m_Objects.end(); ++i) {
        CEditorBaseObject* object = i->second;
        if (object->getParentGuid() == parent && object->getDescriptor() != exclude && canObjectBeSaved(getResourceManager(), object))
            objects.add(object);
    }
}

void saveBinaryGroup(CEditorScene*, std::ofstream& file, CRandomGroup* group, CDescriptor* descriptor, CDescriptorSaveConfiguration* configuration)
{
    if (!descriptor || !group) return;
    descriptor->saveObjectInBinaryFile(file, group, configuration);
    unsigned int count = 0, begin = 0, end = 0;
    group->m_iChildSelectionLimit = static_cast<int>(file.tellp());
    file.write(reinterpret_cast<const char*>(&count), 4);
    file.write(reinterpret_cast<const char*>(&begin), 4);
    file.write(reinterpret_cast<const char*>(&end), 4);
}

void saveBinaryObjects(CEditorScene* scene, std::ofstream& file, TArrayList<CEditorBaseObject*>& objects, CDescriptorSaveConfiguration* configuration)
{
    for (unsigned int i = 0; i < objects.size(); ++i) {
        CEditorBaseObject* object = objects[i];
        object->getDescriptor()->saveObjectInBinaryFile(file, object, configuration);
        TArrayList<CEditorBaseObject*> children(10);
        CDescriptor* group = scene->GetDescriptorInSceneByName(L"Group", false);
        scene->getChildren(object->getGuid(), children, group);
        unsigned int count = children.size();
        file.write(reinterpret_cast<const char*>(&count), 4);
        saveBinaryObjects(scene, file, children, configuration);
    }
}

void saveBinaryGroupChildren(CEditorScene* scene, std::ofstream& file, CRandomGroup* group, CDescriptor* descriptor, CDescriptorSaveConfiguration* configuration)
{
    if (!descriptor || !group) return;
    unsigned int begin = static_cast<unsigned int>(file.tellp());
    TArrayList<CEditorBaseObject*> children(10);
    scene->getChildren(group->getGuid(), children, descriptor);
    saveBinaryObjects(scene, file, children, configuration);
    unsigned int end = static_cast<unsigned int>(file.tellp());
    file.seekp(std::streampos(static_cast<unsigned int>(group->m_iChildSelectionLimit)));
    unsigned int count = children.size();
    file.write(reinterpret_cast<const char*>(&count), 4);
    file.write(reinterpret_cast<const char*>(&begin), 4);
    file.write(reinterpret_cast<const char*>(&end), 4);
    file.seekp(0, std::ios::end);
}

void CEditorScene::configureGroupsToParse(CEditorBaseObject*, CDataGroup& data, TArrayList<CDataGroup*>& groups, CDescriptorLoadConfiguration*)
{
    CDataGroup* children = data.GetDataGroupByName(L"CHILDREN", false);
    if (children) {
        groups.setGrowBy(children->GetNumberOfDataGroups() + 1);
        for (unsigned int i = 0; i < children->GetNumberOfDataGroups(); ++i)
            groups.add(children->GetDataGroup(i));
    }
}

int CEditorScene::loadObjects(CEditorBaseObject* parent, CDataGroup* data, CDescriptorLoadConfiguration* configuration)
{
    if (!configuration || !data) return 0;
    TArrayList<CDataGroup*> groups(10);
    configureGroupsToParse(parent, *data, groups, configuration);
    unsigned int result = 0;
    for (unsigned int i = 0; i < groups.size(); ++i) result += static_cast<unsigned int>(loadObject(groups[i], configuration));
    return static_cast<int>(result);
}

unsigned int CEditorScene::saveObjectAndChildren(CEditorBaseObject* object, CDataGroup* data, CDescriptorSaveConfiguration* configuration)
{
    if (!data || !object || !object->getDescriptor() || object->HasBaseObjectFlag(EDITOROBJECT_FLAG_DONT_SAVE)) return 0;
    long long guid = object->getGuid();
    if (guid == -1) return 0;
    CDescriptor* descriptor = object->getDescriptor();
    CDataGroup* saved = data->AddDataGroup(L"BASEOBJECT");
    descriptor->saveObject(object, saved, configuration);
    CDataGroup* children = saved->AddDataGroup(L"CHILDREN");
    return saveObjectsHavingParent(guid, children, configuration) + 1;
}

CEditorScene::CEditorScene(const wchar_t* name)
    : CPositionableObject(NULL, NULL), m_pDescriptorManager(NULL), m_ObjectList0(10), m_ObjectList1(10),
      m_sFileLoaded(EMPTY_WSTRING), m_pUnknown170(NULL), m_pUnknown178(NULL), m_pUnknown180(NULL),
      m_iUnknown188(0), m_bActivated(false), m_bUnknown18D(false)
{
    if (name) m_sName = std::wstring(name);
    m_pDescriptorManager = new CDescriptorManager(this);
    CEditorScene::setEnabled(true);
    m_bHashFromOriginalGuid = true;
}

CEditorScene::~CEditorScene()
{
    if (m_pUnknown180) {
        delete m_pUnknown180;
        m_pUnknown180 = NULL;
    }
    m_pUnknown180 = NULL;
    DeleteAllObjectsFromScene();
    m_pUnknown170 = NULL;
    m_ObjectList0.clear();
    if (m_pDescriptorManager) delete m_pDescriptorManager;
}

unsigned int CEditorScene::clone(CEditorScene* scene, TArrayList<CEditorBaseObject*>* objects, CTimerStatics* timers)
{
    if (!scene) return 0;
    if (scene->GetDescriptorInSceneByName(L"Timeline", false) || scene->GetDescriptorInSceneByName(L"Logic Group", false))
        return loadScene(scene->m_sFileLoaded, false, NULL, -1, true, timers);
    cloneLayout(scene, objects, timers);
    return static_cast<unsigned int>(m_Objects.size());
}

unsigned int CEditorScene::merge(CEditorScene* scene, TArrayList<CEditorBaseObject*>* objects, long long guid, CTimerStatics* timers)
{
    if (!scene || !scene->m_pUnknown180) return 0;
    std::wstring oldFile(m_sFileLoaded);
    unsigned int result = loadScene(scene->m_sFileLoaded, *scene->m_pUnknown180, objects, guid, timers);
    m_sFileLoaded = oldFile;
    return result;
}
