
#include "EmptyStrings.h"
#include "DataGroup.h"
#include "DataValue.h"
#include "BinaryStyle.h"
#include "StringUtilities.h"

bool CDataValue::GetValueBool()
{
    return m_Value.boolean;
}

void CDataValue::SetValueBool(bool value)
{
    m_eType = static_cast<EDATAVALUETYPES>(6);
    m_Value.boolean = value;
}

long long CDataValue::GetValueInt64()
{
    return m_Value.signed64;
}

void CDataValue::SetValueInt64(long long value)
{
    m_eType = static_cast<EDATAVALUETYPES>(7);
    m_Value.signed64 = value;
}

int CDataValue::GetValueInt32()
{
    return m_Value.signed32;
}

void CDataValue::SetValueInt32(int value)
{
    m_eType = static_cast<EDATAVALUETYPES>(1);
    m_Value.signed32 = value;
}

unsigned int CDataValue::GetValueUInt32()
{
    return m_Value.unsigned32;
}

void CDataValue::SetValueUInt32(unsigned int value)
{
    m_eType = static_cast<EDATAVALUETYPES>(4);
    m_Value.unsigned32 = value;
}

float CDataValue::GetValueFloat32()
{
    return m_Value.float32;
}

void CDataValue::SetValueFloat32(float value)
{
    m_eType = static_cast<EDATAVALUETYPES>(2);
    m_Value.float32 = value;
}

double CDataValue::GetValueFloat64()
{
    return m_Value.float64;
}

void CDataValue::SetValueFloat64(double value)
{
    m_eType = static_cast<EDATAVALUETYPES>(3);
    m_Value.float64 = value;
}

void CDataValue::SetValueIsTranslate()
{
    if (m_eType == DATAVALUE_STRING || m_eType == DATAVALUE_TRANSLATE)
        m_eType = DATAVALUE_TRANSLATE;
}

void CDataValue::SetValueTranslate(const wchar_t* value)
{
    m_eType = DATAVALUE_TRANSLATE;
    SetValueString(value);
}

std::wstring CDataValue::GetValueTypeAsString()
{
    switch (static_cast<unsigned int>(m_eType)) {
    case 1: return L"INTEGER";
    case 2: return L"FLOAT";
    case 3: return L"DOUBLE";
    case 4: return L"UNSIGNED INT";
    case 5: return L"STRING";
    case 6: return L"BOOL";
    case 7: return L"INTEGER64";
    case 8: return L"TRANSLATE";
    default: return L"Not Set";
    }
}

#include "TRepository.h"
#include "StringTranslate.h"

const std::wstring& CDataValue::GetDataValueName()
{
    const std::wstring* name = &EMPTY_WSTRING;
    if (m_pRepository != NULL && m_iNameID != static_cast<unsigned int>(-1))
    {
        name = &m_pRepository->m_DefaultValue;
        if (!m_pRepository->m_Values.empty())
        {
            std::map<unsigned int, std::wstring>::iterator i = m_pRepository->m_Values.find(m_iNameID);
            if (i != m_pRepository->m_Values.end())
                name = &i->second;
        }
    }
    return *name;
}

const std::wstring& CDataValue::GetValueString(bool translate)
{
    if ((m_eType == DATAVALUE_TRANSLATE || m_eType == DATAVALUE_STRING) &&
        m_pRepository != NULL && m_bStringValue)
    {
        if (translate && m_eType == DATAVALUE_TRANSLATE && CStringTranslate::getSinglton() != NULL)
        {
            const std::wstring* value = &m_pRepository->m_DefaultValue;
            if (m_Value.unsigned32 != static_cast<unsigned int>(-1) && !m_pRepository->m_Values.empty())
            {
                std::map<unsigned int, std::wstring>::iterator i = m_pRepository->m_Values.find(m_Value.unsigned32);
                if (i != m_pRepository->m_Values.end())
                    value = &i->second;
            }
            return CStringTranslate::getSinglton()->getTranslateString(*value);
        }
        if (m_Value.unsigned32 != static_cast<unsigned int>(-1) && !m_pRepository->m_Values.empty())
        {
            std::map<unsigned int, std::wstring>::iterator i = m_pRepository->m_Values.find(m_Value.unsigned32);
            if (i != m_pRepository->m_Values.end())
                return i->second;
        }
        return m_pRepository->m_DefaultValue;
    }
    return EMPTY_WSTRING;
}

std::wstring CDataValue::GetValueAsString()
{
    switch (static_cast<unsigned int>(m_eType))
    {
    case 1: return STRINGS::GetValueAsWString(m_Value.signed32);
    case 2: return STRINGS::GetValueAsWString(m_Value.float32);
    case 3: return STRINGS::GetValueAsWString(m_Value.float64);
    case 4: return STRINGS::GetValueAsWString(m_Value.unsigned32);
    case 5: return GetValueString(false);
    case 6: return STRINGS::GetValueAsWString(m_Value.boolean);
    case 7: return STRINGS::GetValueAsWString(m_Value.signed64);
    case 8: return GetValueString(false);
    default: return L"";
    }
}



#include "GameNamespaces.h"

CDataValue::CDataValue(const wchar_t* name, TRepository<std::wstring>* repository)
    : m_bStringValue(false), m_iNameID(static_cast<unsigned int>(-1)),
      m_pRepository(repository), m_eType(static_cast<EDATAVALUETYPES>(0))
{
    m_Value.signed64 = 0;
    std::wstring text(name);
    SetDataValueName(text);
}

CDataValue::CDataValue(CDataValue* source, TRepository<std::wstring>* repository)
    : m_bStringValue(false), m_iNameID(static_cast<unsigned int>(-1)),
      m_pRepository(repository), m_eType(static_cast<EDATAVALUETYPES>(0))
{
    m_Value.signed64 = 0;
    Copy(source, repository);
}

void CDataValue::Copy(CDataValue* source, TRepository<std::wstring>* repository)
{
    if (source)
    {
        m_pRepository = repository;
        SetDataValueName(const_cast<std::wstring&>(source->GetDataValueName()));
        m_eType = source->m_eType;
        if (source->m_bStringValue)
        {
            m_Value.unsigned32 = static_cast<unsigned int>(-1);
            SetValueString(source->GetValueString(true).c_str());
        }
        else
            m_Value.signed64 = source->m_Value.signed64;
    }
}

void CDataValue::SetValueByString(const std::wstring& type, std::wstring& value)
{
    if (type == L"INTEGER")
        SetValueInt32(STRINGS::GetInt(value));
    else if (type == L"INTEGER64")
        SetValueInt64(STRINGS::GetInt64(value));
    else if (type == L"FLOAT")
        SetValueFloat32(STRINGS::GetFloat(value));
    else if (type == L"DOUBLE")
        SetValueFloat64(STRINGS::GetFloat64(value));
    else if (type == L"UNSIGNED INT")
        SetValueUInt32(STRINGS::GetInt(value));
    else if (type == L"BOOL")
        SetValueBool(STRINGS::GetBool(value));
    else
    {
        m_Value.unsigned32 = static_cast<unsigned int>(-1);
        SetValueString(value.c_str());
        if (type == L"TRANSLATE" || type == L"DIALOG")
            m_eType = DATAVALUE_TRANSLATE;
    }
}

CDataValue::CDataValue(unsigned int name, UNIONDATA64BIT value, EDATAVALUETYPES type,
                     TRepository<std::wstring>* repository)
    : m_bStringValue(type == DATAVALUE_STRING || type == DATAVALUE_TRANSLATE),
      m_iNameID(name), m_pRepository(repository), m_eType(type)
{
    m_Value.signed64 = value.signed64;
    if (name != static_cast<unsigned int>(-1))
    {
        std::wstring text = m_pRepository->m_DefaultValue;
        if (!m_pRepository->m_Values.empty())
        {
            std::map<unsigned int, std::wstring>::iterator i = m_pRepository->m_Values.find(name);
            if (i != m_pRepository->m_Values.end())
                text = i->second;
        }
        if (text != m_pRepository->m_DefaultValue)
        {
            std::map<unsigned int, unsigned short>::iterator i = m_pRepository->m_RefCounts.find(name);
            if (i != m_pRepository->m_RefCounts.end())
                ++i->second;
            else
                m_pRepository->m_RefCounts[name] = 1;
        }
    }
    if (m_pRepository && m_bStringValue && m_Value.unsigned32 != static_cast<unsigned int>(-1))
    {
        unsigned int id = m_Value.unsigned32;
        std::wstring text = m_pRepository->m_DefaultValue;
        if (!m_pRepository->m_Values.empty())
        {
            std::map<unsigned int, std::wstring>::iterator i = m_pRepository->m_Values.find(id);
            if (i != m_pRepository->m_Values.end())
                text = i->second;
        }
        if (text != m_pRepository->m_DefaultValue)
        {
            std::map<unsigned int, unsigned short>::iterator i = m_pRepository->m_RefCounts.find(id);
            if (i != m_pRepository->m_RefCounts.end())
                ++i->second;
            else
                m_pRepository->m_RefCounts[id] = 1;
        }
    }
}
