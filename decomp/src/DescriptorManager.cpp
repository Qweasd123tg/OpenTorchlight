#include "EmptyStrings.h"
#include "DescriptorManager.h"
#include "DataGroup.h"
#include "Descriptor.h"
#include "DescriptorLoadConfiguration.h"
#include "EditorScene.h"
#include "RunicCore.h"

void CDescriptorManager::update(float fTimeDelta)
{
    for (unsigned int uiIndex = 0;
         uiIndex < static_cast<unsigned int>(
             reinterpret_cast<CDescriptor ***>(&m_descriptors)[1] -
             reinterpret_cast<CDescriptor ***>(&m_descriptors)[0]);
         ++uiIndex)
        reinterpret_cast<CDescriptor ***>(&m_descriptors)[0][uiIndex]->update(fTimeDelta);
}

void CDescriptorManager::postProcessDescriptorObjects(
    CDataGroup* group,
    CDescriptorLoadConfiguration* configuration)
{
    if (group == NULL)
        return;

    struct DescriptorListStorage
    {
        CDescriptor** first;
        long last;
    };

    const volatile DescriptorListStorage* storage =
        reinterpret_cast<const volatile DescriptorListStorage*>(&m_descriptors);

    for (unsigned int i = 0;
         i < static_cast<unsigned long>(
                 (static_cast<long>(
                      static_cast<unsigned long>(storage->last) -
                      reinterpret_cast<unsigned long>(storage->first)) >> 3));
         ++i)
    {
        storage->first[i]->postProcessObjects(group, configuration);
    }
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
