#ifndef PAIRSTYLE_H
#define PAIRSTYLE_H

#include <string>

#include "BinaryStyle.h"
#include "DataGroup.h"
#include "FileReader.h"

class CTimerStatics;

class CPairStyle : public iDataFileSaveAndLoad
{
public:
    virtual ~CPairStyle();
    virtual void SaveDataGroupToFile(const std::wstring& fileName, CDataGroup* dataGroup);
    virtual void LoadDataGroupToFile(const std::wstring& fileName, CDataGroup* dataGroup, CTimerStatics* timerStatics);

    CPairStyle();
    void ParseSubGroups(CFileReader* reader, CDataGroup* dataGroup);
};

#endif
