#ifndef BINARYSTYLE_H
#define BINARYSTYLE_H

#include <string>
#include <fstream>
#include <map>

class CDataGroup;
class CTimerStatics;
union UNIONDATA64BIT;

// Partial: interface of the data file serializers (BinaryStyle.cpp).
class iDataFileSaveAndLoad
{
public:
    virtual ~iDataFileSaveAndLoad() {}
    virtual int SaveDataGroupToFile(const std::wstring& file, CDataGroup* group) = 0;
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
    virtual int SaveDataGroupToFile(const std::wstring& file, CDataGroup* group);
    virtual void LoadDataGroupToFile(const std::wstring& file, CDataGroup* group, CTimerStatics* timers);
    void Save64BitDataValue(std::basic_ofstream<char, std::char_traits<char> >& stream, const UNIONDATA64BIT& value);
    void SaveUInt32BitDataValue(std::basic_ofstream<char, std::char_traits<char> >& stream, unsigned int value);
    void SaveDataValues(std::basic_ofstream<char, std::char_traits<char> >& stream, CDataGroup* group);
    void Save(std::basic_ofstream<char, std::char_traits<char> >& stream, CDataGroup* group);
    void SaveStringData(std::basic_ofstream<char, std::char_traits<char> >& stream, const std::wstring& value);
    void LoadDataValues(std::basic_ifstream<char, std::char_traits<char> >& stream, CDataGroup* group,
                        std::map<unsigned int, unsigned int>& names, unsigned int version,
                        CTimerStatics* timers);
    void Load(std::basic_ifstream<char, std::char_traits<char> >& stream, CDataGroup* group,
              std::map<unsigned int, unsigned int>& names, unsigned int version,
              CTimerStatics* timers);
};

#endif
