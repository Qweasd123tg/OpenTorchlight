#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "CmdLineParser.h"

CCmdLineParser::~CCmdLineParser()
{
    m_params.clear();
}

#include "StringUtilities.h"

bool CCmdLineParser::HasCommand(const std::wstring& name)
{
    return m_params.find(name) != m_params.end();
}

std::wstring CCmdLineParser::GetStringParam(const std::wstring& name, std::wstring defaultValue)
{
    if (m_params.find(name) != m_params.end() && m_params[name].size() > 0)
        return m_params[name][0];
    return defaultValue;
}

int CCmdLineParser::GetIntParam(const std::wstring& name, int defaultValue)
{
    if (m_params.find(name) != m_params.end() && m_params[name].size() > 0)
        return STRINGS::GetInt(m_params[name][0]);
    return defaultValue;
}

float CCmdLineParser::GetFloatParam(const std::wstring& name, float defaultValue)
{
    if (m_params.find(name) != m_params.end() && m_params[name].size() > 0)
        return STRINGS::GetFloat(m_params[name][0]);
    return defaultValue;
}
