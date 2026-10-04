#ifndef DESCRIPTORMANAGER_H
#define DESCRIPTORMANAGER_H

// Partial: layout of DescriptorManager.cpp; only the methods used so far.

#include <map>
#include <string>

#include "RunicCore.h"
#include "TArrayList.h"

class CDescriptor;
class CEditorScene;

class CDescriptorManager : public CRunicCore
{
public:
    CDescriptorManager(CEditorScene* scene);
    virtual ~CDescriptorManager();

    CDescriptor* GetDescriptor(const wchar_t* name, bool createIfMissing);

protected:
    std::map<std::wstring, unsigned int> m_DescriptorIDs;
    TArrayList<CDescriptor*> m_Descriptors;
    CEditorScene* m_pScene;
};

#endif
