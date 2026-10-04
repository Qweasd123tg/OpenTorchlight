#include "EmptyStrings.h"
#include "Mod.h"

const std::wstring& CMod::getModFile(const std::wstring& path)
{
    std::map<std::wstring, std::wstring>::iterator i = m_mapModFiles.find(path);
    return i != m_mapModFiles.end() ? i->second : EMPTY_WSTRING;
}

const std::wstring& CMod::getModFileAbsolute(const std::wstring& path)
{
    std::map<std::wstring, std::wstring>::iterator i = m_mapModFiles.find(path);
    return i != m_mapModFiles.end() ? i->second : EMPTY_WSTRING;
}

CMod::~CMod()
{
}
