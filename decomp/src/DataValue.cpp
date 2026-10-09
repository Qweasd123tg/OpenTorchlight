
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
