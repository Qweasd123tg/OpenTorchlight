#include "OgreResourceFile.h"

COgreResourceFile::COgreResourceFile()
{
}

#include <map>
#include <string>
#include "OgreReader.h"

int COgreResourceFile::Get32BitData(COgreReader* reader)
{
    int value[1] = {0};
    reader->read(value, sizeof(value));
    return value[0];
}

long long COgreResourceFile::Get64BitData(COgreReader* reader)
{
    long long value = 0;
    reader->read(&value, sizeof(value));
    return value;
}

COgreResourceFile::~COgreResourceFile()
{
}

#include "EmptyStrings.h"
#include "UTFConversion.h"

std::wstring COgreResourceFile::GetWChar16ArrayAsString(COgreReader* reader,
                                                      unsigned int length)
{
    static wchar_t output[4024];
    static unsigned char strReadStringArray[8048];
    if (length > 1023)
        return EMPTY_WSTRING;
    if (length == 0)
        return EMPTY_WSTRING;
    unsigned int bytes = length * 2;
    output[length] = 0;
    strReadStringArray[bytes] = 0;
    strReadStringArray[bytes + 1] = 0;
    strReadStringArray[bytes + 2] = 0;
    reader->read(strReadStringArray, bytes);
    ReadUTF16ToUTF32(reinterpret_cast<const unsigned short*>(strReadStringArray), output, length);
    return std::wstring(output);
}

#include "DataGroup.h"
#include "DataValue.h"

void COgreResourceFile::getStringIndexs(CDataGroup* group,
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


#include <OgreLogManager.h>

int COgreResourceFile::SaveDataGroupToFile(const std::wstring&, CDataGroup*)
{
    Ogre::LogManager::getSingleton().logMessage("Unable to save into a OgreResourceFile.", Ogre::LML_CRITICAL, false);
    return 0;
}
