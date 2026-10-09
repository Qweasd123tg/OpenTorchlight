
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
