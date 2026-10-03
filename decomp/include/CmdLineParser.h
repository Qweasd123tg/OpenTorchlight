#ifndef CMDLINEPARSER_H
#define CMDLINEPARSER_H

#include <string>

#include "RunicCore.h"

// Partial: declarations from CmdLineParser.cpp used by recovered TUs; the
// fields are not recovered yet.
class CCmdLineParser : public CRunicCore
{
public:
    virtual ~CCmdLineParser();

    int GetIntParam(const std::wstring& name, int defaultValue);
};

#endif
