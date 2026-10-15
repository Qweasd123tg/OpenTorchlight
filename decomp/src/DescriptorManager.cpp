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
    : CRunicCore(), m_descriptors(0), m_pEditorScene(pEditorScene)
{
}

unsigned int CDescriptorManager::AddDescriptor(CDescriptor* pDescriptor)
{
    if (pDescriptor == NULL)
        return -1;

    pDescriptor->SetSceneOwner(m_pEditorScene);

    unsigned int uiIndex = m_descriptors.size();
    m_descriptorIndices[pDescriptor->getName()] = uiIndex;
    m_descriptors.add(pDescriptor);

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
