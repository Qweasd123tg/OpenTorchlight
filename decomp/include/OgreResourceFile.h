#ifndef OGRERESOURCEFILE_H
#define OGRERESOURCEFILE_H

#include <map>
#include <string>

#include "BinaryStyle.h"
#include "DataGroup.h"

class COgreReader;
class CTimerStatics;

class COgreResourceFile : public iDataFileSaveAndLoad
{
public:
    virtual ~COgreResourceFile();

    virtual void SaveDataGroupToFile(const std::wstring& fileName,
                                      CDataGroup* dataGroup);
    virtual void LoadDataGroupToFile(const std::wstring& fileName,
                                      CDataGroup* dataGroup,
                                      CTimerStatics* timerStatics);

    COgreResourceFile();

    int Get32BitData(COgreReader* reader);
    long long Get64BitData(COgreReader* reader);
    std::wstring GetWChar16ArrayAsString(COgreReader* reader,
                                          unsigned int length);

    void getStringIndexs(
        CDataGroup* dataGroup,
        std::map<unsigned int, bool>& stringIndexes);

    void LoadDataValues(
        COgreReader* reader,
        CDataGroup* dataGroup,
        std::map<unsigned int, unsigned int>& stringIndexes,
        unsigned int reserved,
        CTimerStatics* timerStatics);

    void Load(
        COgreReader* reader,
        CDataGroup* dataGroup,
        std::map<unsigned int, unsigned int>& stringIndexes,
        unsigned int reserved,
        CTimerStatics* timerStatics);
};

#endif
