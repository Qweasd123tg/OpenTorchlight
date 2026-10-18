#include "EmptyStrings.h"
#include "DescriptorManager.h"
#include "DataGroup.h"
#include "Descriptor.h"
#include "DescriptorLoadConfiguration.h"
#include "EditorScene.h"
#include "RunicCore.h"

void CDescriptorManager::update(float fTimeDelta)
{
    for (unsigned int i = 0; i < getDescriptorVector().size(); ++i)
        getDescriptorVector()[i]->update(fTimeDelta);
}

void CDescriptorManager::postProcessDescriptorObjects(
    CDataGroup* group,
    CDescriptorLoadConfiguration* configuration)
{
    if (group == NULL)
        return;
    for (unsigned int i = 0; i < getDescriptorVector().size(); ++i)
        getDescriptorVector()[i]->postProcessObjects(group, configuration);
}

CDescriptorManager::CDescriptorManager(CEditorScene* pEditorScene)
    : CRunicCore(), m_descriptors(), m_pEditorScene(pEditorScene)
{
}

unsigned int CDescriptorManager::AddDescriptor(CDescriptor* pDescriptor)
{
    if (pDescriptor == NULL)
        return -1;

    pDescriptor->SetSceneOwner(m_pEditorScene);

    unsigned int uiIndex = m_descriptors.size();
    m_descriptorIndices[pDescriptor->m_sName] = uiIndex;
    m_descriptors.push_back(pDescriptor);

    return uiIndex;
}

CDescriptor* CDescriptorManager::GetDescriptor(unsigned int index)
{
    if (index < getDescriptorVector().size())
        return getDescriptorVector()[index];
    return NULL;
}

void CDescriptorManager::notifyDescriptorsSceneLoaded(CEditorScene* scene)
{
    if (scene == NULL)
        return;
    for (unsigned int i = 0; i < getDescriptorVector().size(); ++i)
        getDescriptorVector()[i]->descriptorSceneLoaded(scene);
}

void CDescriptorManager::deactivateDescriptors(CEditorScene* scene)
{
    if (scene == NULL)
        return;
    for (unsigned int i = 0; i < getDescriptorVector().size(); ++i)
        getDescriptorVector()[i]->descriptorSceneDeactivated(scene);
}

int CDescriptorManager::loadDescriptorObjects(CDataGroup* group, CDescriptorLoadConfiguration* configuration)
{
    int count = 0;
    if (group == NULL)
        return count;
    for (unsigned int i = 0; i < getDescriptorVector().size(); ++i)
        count += getDescriptorVector()[i]->loadObjects(group, configuration);
    return count;
}

#include "DescriptorController.h"

CDescriptor* CDescriptorManager::GetDescriptor(const wchar_t* name, bool createIfMissing)
{
    std::map<std::wstring, unsigned int>::iterator i = m_descriptorIndices.find(name);
    if (i != m_descriptorIndices.end())
        return GetDescriptor(i->second);
    if (createIfMissing)
    {
        CDescriptor* descriptor = CDescriptorController::getNewDescriptorByName(name);
        if (descriptor != NULL)
            AddDescriptor(descriptor);
        return descriptor;
    }
    return NULL;
}

CDescriptor* CDescriptorManager::GetDescriptorByCreated(unsigned int index, bool createIfMissing)
{
    for (unsigned int i = 0; i < getDescriptorVector().size(); ++i)
        if (getDescriptorVector()[i]->m_iID == index)
            return getDescriptorVector()[i];
    if (createIfMissing) {
        CDescriptor* descriptor = CDescriptorController::getNewDescriptorByCreatedIndex(index);
        if (descriptor)
            AddDescriptor(descriptor);
        return descriptor;
    }
    return NULL;
}

void CDescriptorManager::activateDescriptors(CEditorScene* scene)
{
    if (!scene)
        return;
    for (unsigned int i = 0; i < getDescriptorVector().size(); ++i) {
        CDescriptor* descriptor = getDescriptorVector()[i];
        if (descriptor->m_iFlags & 0x4000)
            for (unsigned int j = 0; j < descriptor->m_Objects.size(); ++j)
                descriptor->m_Objects[j]->calculateParentHierarchyHashCode();
    }
    for (unsigned int i = 0; i < getDescriptorVector().size(); ++i)
        getDescriptorVector()[i]->descriptorSceneActivated(scene);
}

void CDescriptorManager::SerializeDescriptors(CDataGroup* data)
{
    if (!data)
        return;
    CDataGroup* group = data->AddDataGroup(L"OBJECT GROUP");
    for (unsigned int i = 0; i < getDescriptorVector().size(); ++i)
        getDescriptorVector()[i]->SerializeDescriptor(group, i);
}

#include "ResourceManager.h"

CDescriptorManager::~CDescriptorManager()
{
    for (unsigned int i = 0; i < m_descriptors.size(); ++i) {
        m_descriptors[i]->deleteNotification();
        if (m_descriptors[i]) {
            delete m_descriptors[i];
            m_descriptors[i] = NULL;
        }
    }
    m_descriptors.clear();
    m_descriptorIndices.clear();
    m_pEditorScene = NULL;
}

void CDescriptorManager::deleteUnusedDescriptors()
{
    if (m_pEditorScene && m_pEditorScene->getResourceManager()->getEditorIsRunning())
        return;
    for (unsigned int i = 0; i < m_descriptors.size(); ++i) {
        CDescriptor* descriptor = m_descriptors[i];
        if (descriptor->m_Objects.size() == 0) {
            std::map<std::wstring, unsigned int>::iterator entry = m_descriptorIndices.find(descriptor->m_sName);
            if (entry != m_descriptorIndices.end()) {
                m_descriptorIndices.erase(entry);
                m_descriptors[i] = m_descriptors[m_descriptors.size() - 1];
                m_descriptors.pop_back();
                delete descriptor;
                --i;
            }
        } else
            m_descriptorIndices[descriptor->m_sName] = i;
    }
}
