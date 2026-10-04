#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "CmdLineParser.h"

CCmdLineParser::~CCmdLineParser()
{
    typedef std::map<std::wstring, std::vector<std::wstring> > ParamsMap;

    ParamsMap *params = reinterpret_cast<ParamsMap *>(
        reinterpret_cast<char *>(this) + 0x10);

    params->clear();
    params->~ParamsMap();
}
