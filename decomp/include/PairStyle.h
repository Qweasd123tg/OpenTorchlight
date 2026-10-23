#ifndef PAIRSTYLE_H
#define PAIRSTYLE_H

#include <string>
#include <cstdio>

#include "BinaryStyle.h"
#include "DataGroup.h"
#include "FileReader.h"

class CTimerStatics;

class CPairStyle : public iDataFileSaveAndLoad
{
public:
    virtual ~CPairStyle();
    virtual int SaveDataGroupToFile(const std::wstring& fileName, CDataGroup* dataGroup);
    virtual int LoadDataGroupToFile(const std::wstring& fileName, CDataGroup* dataGroup, CTimerStatics* timerStatics);

    CPairStyle();
    void Save(FILE* file, CDataGroup* dataGroup);
    void ParseSubGroups(CFileReader* reader, CDataGroup* dataGroup);
};

#endif
