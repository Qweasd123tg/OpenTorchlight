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

#include "FileUtilities.h"
#include "StringUtilities.h"
#include "TRepository.h"
#include "TimerStatics.h"

int CBinaryStyle::SaveDataGroupToFile(const std::wstring& file, CDataGroup* group)
{
    if (file == EMPTY_WSTRING || !group)
        return 0;
    std::wstring clean = FILESYSTEM::CleanPath(file);
    std::wstring path(clean);
    std::wstring directory = FILESYSTEM::GetDirectory(path);
    std::string utf8 = STRINGS::StringConvertToUTF8(path);
    std::ofstream stream(utf8.c_str(), std::ios::binary);
    if (!stream.is_open())
        return 0;
    SaveUInt32BitDataValue(stream, 1);
    std::map<unsigned int, bool> indexes;
    getStringIndexs(group, indexes);
    SaveUInt32BitDataValue(stream, indexes.size());
    for (std::map<unsigned int, bool>::iterator i = indexes.begin(); i != indexes.end(); ++i) {
        SaveUInt32BitDataValue(stream, i->first);
        std::wstring text = group->m_pRepository->m_DefaultValue;
        if (i->first != static_cast<unsigned int>(-1) && !group->m_pRepository->m_Values.empty()) {
            std::map<unsigned int, std::wstring>::iterator value = group->m_pRepository->m_Values.find(i->first);
            if (value != group->m_pRepository->m_Values.end())
                text = value->second;
        }
        SaveStringData(stream, text);
    }
    Save(stream, group);
    stream.close();
    return 1;
}

void CBinaryStyle::LoadDataValues(std::ifstream& stream, CDataGroup* group,
                                std::map<unsigned int, unsigned int>& names,
                                unsigned int version, CTimerStatics* timers)
{
    if (timers)
        timers->m_times.add(static_cast<unsigned int>(timers->m_timer.getMicroseconds()));
    unsigned int count = Get32BitData(stream);
    for (unsigned int i = 0; i < count; ++i) {
        unsigned int name = names[static_cast<unsigned int>(Get32BitData(stream))];
        CDataValue::EDATAVALUETYPES type = static_cast<CDataValue::EDATAVALUETYPES>(Get32BitData(stream));
        UNIONDATA64BIT value;
        if (type == 7 || type == 3)
            value.signed64 = Get64BitData(stream);
        else {
            value.signed64 = static_cast<unsigned int>(Get32BitData(stream));
            if (type == CDataValue::DATAVALUE_STRING || type == CDataValue::DATAVALUE_TRANSLATE)
                value.signed64 = names[value.unsigned32];
        }
        group->AddDataValue(name, value, type);
    }
    if (timers)
        timers->popTime(L"CHILD DATAVALUES");
}

void CBinaryStyle::Load(std::ifstream& stream, CDataGroup* group,
                        std::map<unsigned int, unsigned int>& names,
                        unsigned int version, CTimerStatics* timers)
{
    group->SetGroupNameID(names[static_cast<unsigned int>(Get32BitData(stream))]);
    if (timers)
        timers->popTime(L"DATA GROUPS");
    LoadDataValues(stream, group, names, version, timers);
    unsigned int count = Get32BitData(stream);
    for (unsigned int i = 0; i < count; ++i) {
        if (timers)
            timers->m_times.add(static_cast<unsigned int>(timers->m_timer.getMicroseconds()));
        CDataGroup* child = group->AddDataGroup(EMPTY_WSTRING);
        Load(stream, child, names, version, timers);
    }
}

#include "FileSystem.h"

int CBinaryStyle::LoadDataGroupToFile(const std::wstring& fileName, CDataGroup* dataGroup,
                                      CTimerStatics* timers)
{
    if (fileName == EMPTY_WSTRING || !dataGroup)
        return 0;
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(fileName, info, false, true, false);
    if (timers)
        timers->m_times.add(static_cast<unsigned int>(timers->m_timer.getMicroseconds()));
    std::string path = STRINGS::StringConvertToUTF8(info.m_sPath);
    std::ifstream stream(path.c_str(), std::ios::binary);
    if (timers)
        timers->popTime(L"TIME TO LOAD OFF DISK");
    if (!stream.is_open())
        return 0;
    unsigned int version = Get32BitData(stream);
    TRepository<std::wstring>* repository = dataGroup->m_pRepository;
    std::map<unsigned int, unsigned int> names;
    if (!repository)
        return 0;
    unsigned int count = Get32BitData(stream);
    if (timers)
        timers->m_times.add(static_cast<unsigned int>(timers->m_timer.getMicroseconds()));
    for (unsigned int i = 0; i < count; ++i) {
        unsigned int id = Get32BitData(stream);
        unsigned int length = Get32BitData(stream);
        std::wstring value = GetWChar16ArrayAsString(stream, length);
        names[id] = repository->addItem(value);
    }
    if (timers) {
        timers->popTime(L"TIME TO PARSE STRINGS");
        timers->m_times.add(static_cast<unsigned int>(timers->m_timer.getMicroseconds()));
        timers->m_times.add(static_cast<unsigned int>(timers->m_timer.getMicroseconds()));
    }
    Load(stream, dataGroup, names, version, timers);
    if (timers)
        timers->popTime(L"TIME TO PARSE DATAGROUP");
    stream.close();
    return 1;
}
