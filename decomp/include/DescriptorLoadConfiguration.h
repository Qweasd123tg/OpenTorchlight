#ifndef DESCRIPTORLOADCONFIGURATION_H
#define DESCRIPTORLOADCONFIGURATION_H

#include <map>
#include <string>

#include "RunicCore.h"

class CEditorBaseObject;
class CTimerStatics;
template<class T> class TArrayList;

// Partial: DescriptorLoadConfiguration.cpp. Options and the guid remapping
// table passed through the descriptor load routines.
class CDescriptorLoadConfiguration : public CRunicCore
{
public:
    CDescriptorLoadConfiguration();
    virtual ~CDescriptorLoadConfiguration();

    long long getRemappedID(long long id);
    void addRemap(long long id, long long remappedID);

    int m_iVersion;
    bool m_bFlag14;
    int m_iValue18;
    std::wstring m_sFilePath;
    std::wstring m_sFileName;
    long long m_iParentGuid;
    union { long long m_iValue38; TArrayList<CEditorBaseObject*>* m_createdObjects; };
    union { void* m_pValue40; CTimerStatics* m_timers; };
    std::map<long long, long long> m_Remaps;
};

#endif
