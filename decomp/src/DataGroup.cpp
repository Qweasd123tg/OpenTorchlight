
#include "DataGroup.h"
#include "DataValue.h"
#include "EmptyStrings.h"
#include "BinaryStyle.h"
#include "StringUtilities.h"
static std::wstring gDataGroupString = L"";

bool CDataGroup::GetDataValue(const std::wstring& name, bool defaultValue)
{
    CDataValue* value = GetDataValueByName(name);
    if (value)
        return value->GetValueBool();
    return defaultValue;
}

long long CDataGroup::GetDataValue(const std::wstring& name, long long defaultValue)
{
    CDataValue* value = GetDataValueByName(name);
    if (value)
        return value->GetValueInt64();
    return defaultValue;
}

int CDataGroup::GetDataValue(const std::wstring& name, int defaultValue)
{
    CDataValue* value = GetDataValueByName(name);
    if (value)
        return value->GetValueInt32();
    return defaultValue;
}

unsigned int CDataGroup::GetDataValue(const std::wstring& name, unsigned int defaultValue)
{
    CDataValue* value = GetDataValueByName(name);
    if (value)
        return value->GetValueUInt32();
    return defaultValue;
}

float CDataGroup::GetDataValue(const std::wstring& name, float defaultValue)
{
    CDataValue* value = GetDataValueByName(name);
    if (value)
        return value->GetValueFloat32();
    return defaultValue;
}

double CDataGroup::GetDataValue(const std::wstring& name, double defaultValue)
{
    CDataValue* value = GetDataValueByName(name);
    if (value)
        return value->GetValueFloat64();
    return defaultValue;
}

const std::wstring& CDataGroup::GetDataValue(const std::wstring& name, const std::wstring& defaultValue)
{
    CDataValue* value = GetDataValueByName(name);
    if (value)
        return value->GetValueString(true);
    return defaultValue;
}

CDataValue::EDATAVALUETYPES CDataGroup::GetDataValueType(const std::wstring& name)
{
    CDataValue* value = GetDataValueByName(name);
    if (value)
        return value->GetValueType();
    return static_cast<CDataValue::EDATAVALUETYPES>(0);
}

void CDataGroup::RemoveDataGroup(CDataGroup* group)
{
    if (group)
    {
        m_b58 = true;
        m_DataGroups.remove(group);
        delete group;
    }
}

void CDataGroup::setDirty(bool dirty)
{
    m_b58 = dirty;
    for (unsigned int i = 0; i < m_DataGroups.size(); ++i)
        m_DataGroups[i]->setDirty(dirty);
}

bool CDataGroup::isDirty()
{
    if (m_b58)
        return true;
    for (unsigned int i = 0; i < m_DataGroups.size(); ++i)
        if (m_DataGroups[i]->isDirty())
            return true;
    return false;
}

const std::wstring& CDataGroup::GetDataValue(const std::wstring& name, const wchar_t* defaultValue)
{
    CDataValue* value = GetDataValueByName(name);
    if (value)
        return value->GetValueString(true);
    gDataGroupString = defaultValue;
    return gDataGroupString;
}

bool CDataGroup::SetDataValue(const std::wstring& name, bool value)
{
    CDataValue* data = GetDataValueByName(name);
    if (data)
    {
        data->SetValueBool(value);
        return false;
    }
    AddDataValue(name, value);
    return true;
}

bool CDataGroup::SetDataValue(const std::wstring& name, long long value)
{
    CDataValue* data = GetDataValueByName(name);
    if (data)
    {
        data->SetValueInt64(value);
        return false;
    }
    AddDataValue(name, value);
    return true;
}

bool CDataGroup::SetDataValue(const std::wstring& name, int value)
{
    CDataValue* data = GetDataValueByName(name);
    if (data)
    {
        data->SetValueInt32(value);
        return false;
    }
    AddDataValue(name, value);
    return true;
}

bool CDataGroup::SetDataValue(const std::wstring& name, double value)
{
    CDataValue* data = GetDataValueByName(name);
    if (data)
    {
        data->SetValueFloat64(value);
        return false;
    }
    AddDataValue(name, value);
    return true;
}

bool CDataGroup::SetDataValue(const std::wstring& name, float value)
{
    CDataValue* data = GetDataValueByName(name);
    if (data)
    {
        data->SetValueFloat32(value);
        return false;
    }
    AddDataValue(name, value);
    return true;
}

bool CDataGroup::SetDataValue(const std::wstring& name, unsigned int value)
{
    CDataValue* data = GetDataValueByName(name);
    if (data)
    {
        data->SetValueUInt32(value);
        return false;
    }
    AddDataValue(name, value);
    return true;
}

void CDataGroup::LoadFile(const std::wstring& file, iDataFileSaveAndLoad* style, CTimerStatics* timers)
{
    SetGroupName(EMPTY_WSTRING);
    style->LoadDataGroupToFile(file, this, timers);
    setDirty(false);
}

CDataValue* CDataGroup::AddDataValue(const std::wstring& name, const wchar_t* value, bool translate)
{
    m_b58 = true;
    std::wstring text(value);
    return AddDataValue(name, text, translate);
}

CDataValue* CDataGroup::GetDataValueByName(const std::wstring& name)
{
    for (unsigned int i = 0; i < m_DataValues.size(); ++i)
        if (m_DataValues[i]->GetDataValueName() == name)
            return m_DataValues[i];
    return NULL;
}

unsigned int CDataGroup::GetDataGroupsMatchingName(const std::wstring& name, std::vector<CDataGroup*>* groups)
{
    if (!groups)
        return 0;
    unsigned int i = 0;
    while (i < m_DataGroups.size()) {
        if (m_DataGroups[i]->GetGroupName() == name)
            groups->push_back(m_DataGroups[i]);
        ++i;
    }
    return groups->size();
}

bool CDataGroup::SetDataValue(const std::wstring& name, const wchar_t* value, bool translate)
{
    CDataValue* data = GetDataValueByName(name);
    if (data) {
        data->SetValueString(value);
        if (translate)
            data->SetValueIsTranslate();
        return false;
    }
    AddDataValue(name, value, translate);
    return true;
}

bool CDataGroup::SetDataValue(const std::wstring& name, const std::wstring& value, bool translate)
{
    CDataValue* data = GetDataValueByName(name);
    if (data) {
        data->SetValueString(value.c_str());
        if (translate)
            data->SetValueIsTranslate();
        return false;
    }
    AddDataValue(name, value, translate);
    return true;
}

CDataValue* CDataGroup::AddDataValue(const std::wstring& name, long long value)
{
    m_b58 = true;
    CDataValue* data = new CDataValue(name.c_str(), m_pRepository);
    data->SetValueInt64(value);
    m_DataValues.add(data);
    return data;
}

CDataValue* CDataGroup::AddDataValue(const std::wstring& name, int value)
{
    m_b58 = true;
    CDataValue* data = new CDataValue(name.c_str(), m_pRepository);
    data->SetValueInt32(value);
    m_DataValues.add(data);
    return data;
}

CDataGroup* CDataGroup::GetDataGroupByName(const std::wstring& name, bool createIfMissing)
{
    for (unsigned int i = 0; i < m_DataGroups.size() && m_DataGroups.size() != (unsigned int)-1; ++i)
        if (m_DataGroups[i]->GetGroupName() == name)
            return m_DataGroups[i];
    if (createIfMissing)
        return AddDataGroup(name);
    return NULL;
}
