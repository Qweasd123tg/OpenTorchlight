#ifndef CMDLINEPARSER_H
#define CMDLINEPARSER_H

#include <string>
#include <map>
#include <vector>

#include "RunicCore.h"

// Command parameters, stored as a list of values for each name.
class CCmdLineParser : public CRunicCore
{
public:
    CCmdLineParser(const std::wstring&);
    virtual ~CCmdLineParser();

    bool HasCommand(const std::wstring& name);
    std::wstring GetStringParam(const std::wstring& name, std::wstring defaultValue);
    float GetFloatParam(const std::wstring& name, float defaultValue);
    int GetIntParam(const std::wstring& name, int defaultValue);
    std::map<std::wstring, std::vector<std::wstring> > m_params;
};

#endif
