#ifndef BINARYSTYLE_H
#define BINARYSTYLE_H

#include <string>
#include <fstream>
#include <map>

class CDataGroup;
class CTimerStatics;

// Partial: interface of the data file serializers (BinaryStyle.cpp).
class iDataFileSaveAndLoad
{
public:
    virtual ~iDataFileSaveAndLoad() {}
    virtual void SaveDataGroupToFile(const std::wstring& file, CDataGroup* group) = 0;
    virtual void LoadDataGroupToFile(const std::wstring& file, CDataGroup* group, CTimerStatics* timers) = 0;
};

class CBinaryStyle : public iDataFileSaveAndLoad
{
public:
    int Get32BitData(std::basic_ifstream<char, std::char_traits<char> >& stream);
    long long Get64BitData(std::basic_ifstream<char, std::char_traits<char> >& stream);
    std::wstring GetWChar16ArrayAsString(std::basic_ifstream<char, std::char_traits<char> >& stream, unsigned int length);
    void getStringIndexs(CDataGroup* group, std::map<unsigned int, bool>& indexes);

    CBinaryStyle();
    virtual ~CBinaryStyle();
    virtual void SaveDataGroupToFile(const std::wstring& file, CDataGroup* group);
    virtual void LoadDataGroupToFile(const std::wstring& file, CDataGroup* group, CTimerStatics* timers);
};

#endif
