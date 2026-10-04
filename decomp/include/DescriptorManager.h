#ifndef DESCRIPTORMANAGER_H
#define DESCRIPTORMANAGER_H

#include "DataGroup.h"
#include "Descriptor.h"
#include "DescriptorLoadConfiguration.h"
#include "EditorScene.h"
#include "RunicCore.h"
#include "TArrayList.h"

#include <map>
#include <string>

class CDescriptorManager : public CRunicCore
{
public:
    virtual ~CDescriptorManager();

    void update(float fTimeDelta);
    CDescriptor* GetDescriptor(unsigned int uiIndex);
    void notifyDescriptorsSceneLoaded(CEditorScene* pScene);
    void deactivateDescriptors(CEditorScene* pScene);
    void activateDescriptors(CEditorScene* pScene);
    void postProcessDescriptorObjects(CDataGroup* pDataGroup,
                                      CDescriptorLoadConfiguration* pLoadConfiguration);
    int loadDescriptorObjects(CDataGroup* pDataGroup,
                              CDescriptorLoadConfiguration* pLoadConfiguration);

    CDescriptorManager(CEditorScene* pEditorScene);

    void SerializeDescriptors(CDataGroup* pDataGroup);
    unsigned int AddDescriptor(CDescriptor* pDescriptor);
    CDescriptor* GetDescriptor(const wchar_t* pName, bool bCreateIfMissing);
    CDescriptor* GetDescriptorByCreated(unsigned int uiCreatedIndex,
                                        bool bCreateIfMissing);
    void deleteUnusedDescriptors();

    std::map<std::wstring, unsigned int> m_descriptorIndices;
    TArrayList<CDescriptor*> m_descriptors;
    CEditorScene* m_pEditorScene;
};

#endif
