#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "BinaryStyle.h"

CBinaryStyle::CBinaryStyle()
{
}

CBinaryStyle::~CBinaryStyle()
{
}

#include "UTFConversion.h"


int CBinaryStyle::Get32BitData(std::ifstream& stream)
{
    int value[1] = {0};
    stream.read(reinterpret_cast<char*>(value), sizeof(value));
    return value[0];
}

long long CBinaryStyle::Get64BitData(std::ifstream& stream)
{
    long long value[1] = {0};
    stream.read(reinterpret_cast<char*>(value), sizeof(value));
    return value[0];
}

std::wstring CBinaryStyle::GetWChar16ArrayAsString(std::ifstream& stream,
                                                 unsigned int length)
{
    static char strReadStringArray[8048];
    if (length > 1023)
        return EMPTY_WSTRING;
    if (length == 0)
        return EMPTY_WSTRING;
    unsigned int bytes = length * 2;
    strReadStringArray[bytes] = 0;
    strReadStringArray[bytes + 1] = 0;
    strReadStringArray[bytes + 2] = 0;
    stream.read(strReadStringArray, bytes);
    std::wstring text = UTF16ToUTF32(utf16string(
        reinterpret_cast<const unsigned short*>(strReadStringArray)));
    return text;
}

#include "DataGroup.h"
#include "DataValue.h"

void CBinaryStyle::getStringIndexs(CDataGroup* group,
                          std::map<unsigned int, bool>& indexes)
{
    indexes[group->m_iNameID] = true;
    for (unsigned int i = 0; i < group->m_DataValues.size(); ++i) {
        indexes[group->m_DataValues[i]->m_iNameID] = true;
        if (group->m_DataValues[i]->m_eType == CDataValue::DATAVALUE_TRANSLATE ||
            group->m_DataValues[i]->m_eType == CDataValue::DATAVALUE_STRING)
            indexes[group->m_DataValues[i]->m_Value.unsigned32] = true;
    }
    for (unsigned int i = 0; i < group->m_DataGroups.size(); ++i)
        getStringIndexs(group->m_DataGroups[i], indexes);
}


void CBinaryStyle::Save64BitDataValue(std::ofstream& stream, const UNIONDATA64BIT& value)
{
    stream.write(reinterpret_cast<const char*>(&value), 8);
}

void CBinaryStyle::SaveUInt32BitDataValue(std::ofstream& stream, unsigned int value)
{
    stream.write(reinterpret_cast<const char*>(&value), 4);
}

void CBinaryStyle::SaveDataValues(std::ofstream& stream, CDataGroup* group)
{
    SaveUInt32BitDataValue(stream, group->m_DataValues.size());
    for (unsigned int i = 0; i < group->m_DataValues.size(); ++i)
    {
        CDataValue* value = group->m_DataValues[i];
        SaveUInt32BitDataValue(stream, value->m_iNameID);
        unsigned int type = value->m_eType;
        SaveUInt32BitDataValue(stream, type);
        if (type == 7 || type == 3)
        {
            UNIONDATA64BIT data;
            data.signed64 = group->m_DataValues[i]->m_Value.signed64;
            Save64BitDataValue(stream, data);
        }
        else
            SaveUInt32BitDataValue(stream, group->m_DataValues[i]->m_Value.unsigned32);
    }
}

void CBinaryStyle::Save(std::ofstream& stream, CDataGroup* group)
{
    SaveUInt32BitDataValue(stream, group->m_iNameID);
    SaveDataValues(stream, group);
    SaveUInt32BitDataValue(stream, group->m_DataGroups.size());
    for (unsigned int i = 0; i < group->m_DataGroups.size(); ++i)
        Save(stream, group->m_DataGroups[i]);
}

void CBinaryStyle::SaveStringData(std::ofstream& stream, const std::wstring& value)
{
    SaveUInt32BitDataValue(stream, value.size());
    utf16string text = UTF32ToUTF16(value);
    stream.write(reinterpret_cast<const char*>(text.c_str()), text.size() * 2);
}
