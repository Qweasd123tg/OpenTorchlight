extern unsigned int gObjectsCreated asm("_ZL15gObjectsCreated");
#include "DataGroup.h"
#include "Descriptor.h"
#include "DescriptorController.h"
#include "DescriptorManager.h"
#include "EditorScene.h"
#include "FileUtilities.h"
#include "LogicGroupDescriptor.h"
#include "MasterResourceManager.h"
#include "ParticleScene.h"
#include "ParticleTechWrapper.h"
#include "ResourceManager.h"
#include "Settings.h"
#include "Timeline.h"
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


// Imported source candidates; historical status is not fresh acceptance.
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
