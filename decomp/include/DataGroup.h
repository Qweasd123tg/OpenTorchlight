#ifndef DATAGROUP_H
#define DATAGROUP_H

#include <string>
#include <vector>

#include "RunicCore.h"
#include "DataValue.h"
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
    void setDirty(bool dirty);
    bool isDirty();
    void RemoveDataGroup(CDataGroup* group);
    CDataValue* AddDataValue(const std::wstring& name, int value);
    CDataValue* AddDataValue(const std::wstring& name, double value);
    CDataValue* AddDataValue(const std::wstring& name, const wchar_t* value, bool translate);
    bool SetDataValue(const std::wstring& name, bool value);
    bool SetDataValue(const std::wstring& name, long long value);
    bool SetDataValue(const std::wstring& name, int value);
    bool SetDataValue(const std::wstring& name, unsigned int value);
    bool SetDataValue(const std::wstring& name, float value);
    bool SetDataValue(const std::wstring& name, double value);
    bool SetDataValue(const std::wstring& name, const wchar_t* value, bool translate);
    bool SetDataValue(const std::wstring& name, const std::wstring& value, bool translate);

    CDataValue* GetDataValueByName(const std::wstring& name);
    CDataValue::EDATAVALUETYPES GetDataValueType(const std::wstring& name);
    double GetDataValue(const std::wstring& name, double defaultValue);
    unsigned int GetDataValue(const std::wstring& name, unsigned int defaultValue);
    const std::wstring& GetGroupName();
    void SetGroupName(const std::wstring& name);
    CDataGroup* AddDataGroup(const std::wstring& name);
    // No caller reads a result: both overloads end without setting rax.
    void LoadFile(const std::wstring& file, CTimerStatics* timers);
    void LoadFile(const std::wstring& file, iDataFileSaveAndLoad* style, CTimerStatics* timers);
    CDataGroup* GetDataGroupByName(const std::wstring& name, bool createIfMissing);
    unsigned int GetDataGroupsMatchingName(const std::wstring& name, std::vector<CDataGroup*>* groups);
    void GetDataValuesMatchingName(const std::wstring& name, std::vector<CDataValue*>* values);
    const std::wstring& GetDataValue(const std::wstring& name, const wchar_t* defaultValue);
    int GetDataValue(const std::wstring& name,int defaultValue);
    float GetDataValue(const std::wstring& name, float defaultValue);
    bool GetDataValue(const std::wstring& name, bool defaultValue);
    void SaveToFile(const std::wstring& file);
    const std::wstring& GetDataValue(const std::wstring& name, const std::wstring& defaultValue);

    unsigned int GetNumberOfDataValues() { return m_DataValues.size(); }
    CDataValue* GetDataValue(unsigned int index) { return m_DataValues[index]; }
    unsigned int GetNumberOfDataGroups() { return m_DataGroups.size(); }
    CDataGroup* GetDataGroup(unsigned int index) { return m_DataGroups[index]; }
    TRepository<std::wstring>* getRepository() { return m_pRepository; }

    CDataValue* AddDataValue(const std::wstring& name, const std::wstring& value, bool translate);
    CDataValue* AddDataValue(const std::wstring& name, bool value);
    CDataValue* AddDataValue(const std::wstring& name, float value);
    CDataValue* AddDataValue(const std::wstring& name, unsigned int value);
    CDataValue* AddDataValue(const std::wstring& name, long long value);
    long long GetDataValue(const std::wstring& name, long long defaultValue);

    int m_iNameID;
    TRepository<std::wstring>* m_pRepository;
    TArrayList<CDataValue*> m_DataValues;
    TArrayList<CDataGroup*> m_DataGroups;
    CDataGroup* m_pParent;
    bool m_b58; // dirty (setDirty)
    bool m_b59; // taken from the CFileSystem cache; values are shared
};

#endif
