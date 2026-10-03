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
    CDataGroup* GetDataGroupByName(const std::wstring& name, bool recursive);
    void GetDataGroupsMatchingName(const std::wstring& name, std::vector<CDataGroup*>* groups);
    void GetDataValuesMatchingName(const std::wstring& name, std::vector<CDataValue*>* values);
    const std::wstring& GetDataValue(const std::wstring& name, const std::wstring& defaultValue);
    const std::wstring& GetDataValue(const std::wstring& name, const wchar_t* defaultValue);
    float GetDataValue(const std::wstring& name, float defaultValue);
    bool GetDataValue(const std::wstring& name, bool defaultValue);
    bool LoadFile(const std::wstring& file, CTimerStatics* timers);
    bool LoadFile(const std::wstring& file, iDataFileSaveAndLoad* style, CTimerStatics* timers);
    void SaveToFile(const std::wstring& file);

    int m_iNameID;
    TRepository<std::wstring>* m_pRepository;
    TArrayList<CDataValue*> m_DataValues;
    TArrayList<CDataGroup*> m_DataGroups;
    CDataGroup* m_pParent;
    bool m_b58;
    bool m_b59;
};

#endif
