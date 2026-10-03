#ifndef BINARYSTYLE_H
#define BINARYSTYLE_H

#include <string>

class CDataGroup;
class CTimerStatics;

// Partial: interface of the data file serializers (BinaryStyle.cpp).
class iDataFileSaveAndLoad
{
public:
    virtual ~iDataFileSaveAndLoad();
    virtual void SaveDataGroupToFile(const std::wstring& file, CDataGroup* group) = 0;
    virtual void LoadDataGroupToFile(const std::wstring& file, CDataGroup* group, CTimerStatics* timers) = 0;
};

class CBinaryStyle : public iDataFileSaveAndLoad
{
public:
    CBinaryStyle();
    virtual ~CBinaryStyle();
    virtual void SaveDataGroupToFile(const std::wstring& file, CDataGroup* group);
    virtual void LoadDataGroupToFile(const std::wstring& file, CDataGroup* group, CTimerStatics* timers);
};

#endif
