#ifndef DATAGROUP_H
#define DATAGROUP_H

#include <string>
#include <vector>

#include "RunicCore.h"
#include "TArrayList.h"

class CDataValue;
class CTimerStatics;
class iDataFileSaveAndLoad;
template <class T> class TRepository;

// Partial: declarations from DataGroup.cpp used by recovered TUs. Layout from
// the constructor.
class CDataGroup : public CRunicCore
{
public:
    CDataGroup(const std::wstring& name, CDataGroup* parent, unsigned int valuesGrowBy, unsigned int groupsGrowBy,
               TRepository<std::wstring>* repository);
    virtual ~CDataGroup();

    const std::wstring& GetGroupName();
    void SetGroupName(const std::wstring& name);
    CDataGroup* AddDataGroup(const std::wstring& name);
    // No caller reads a result: both overloads end without setting rax.
    void LoadFile(const std::wstring& file, CTimerStatics* timers);
    void LoadFile(const std::wstring& file, iDataFileSaveAndLoad* style, CTimerStatics* timers);
    CDataGroup* GetDataGroupByName(const std::wstring& name, bool recursive);
    void GetDataGroupsMatchingName(const std::wstring& name, std::vector<CDataGroup*>* groups);
    void GetDataValuesMatchingName(const std::wstring& name, std::vector<CDataValue*>* values);
    const std::wstring& GetDataValue(const std::wstring& name, const wchar_t* defaultValue);
    float GetDataValue(const std::wstring& name, float defaultValue);
    bool GetDataValue(const std::wstring& name, bool defaultValue);
    void SaveToFile(const std::wstring& file);
    const std::wstring& GetDataValue(const std::wstring& name, const std::wstring& defaultValue);

    unsigned int GetNumberOfDataGroups() { return m_DataGroups.size(); }
    CDataGroup* GetDataGroup(unsigned int index) { return m_DataGroups[index]; }
    TRepository<std::wstring>* getRepository() { return m_pRepository; }

    int m_iNameID;
    TRepository<std::wstring>* m_pRepository;
    TArrayList<CDataValue*> m_DataValues;
    TArrayList<CDataGroup*> m_DataGroups;
    CDataGroup* m_pParent;
    bool m_b58; // dirty (setDirty)
    bool m_b59; // taken from the CFileSystem cache; values are shared
};

#endif
