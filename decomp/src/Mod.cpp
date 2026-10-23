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

#include "FileUtilities.h"
#include "StringUtilities.h"
#include "MasterResourceManager.h"
#include "DataGroup.h"
#include <OgreResourceGroupManager.h>
#include <queue>

void CMod::reloadModFiles()
{
    if (m_iUnknown74 < 0)
        return;
    if (m_bUnknown71)
        Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup(m_sUnknown48, true);
    m_bUnknown71 = true;
    TArrayList<std::wstring> files(25);
    m_mapModFiles.clear();
    FILESYSTEM::GetFileListRecursive(m_wUnknown68, files, L"*.*");
    unsigned int initialCount = files.size();
    bool wasEnabled = m_bUnknown70;
    for (unsigned int i = 0; i < files.size(); ++i) {
        std::wstring path = files[i];
        std::wstring relative = path;
        relative = relative.substr(m_wUnknown68.length(), relative.length() - m_wUnknown68.length());
        std::string remaining = STRINGS::StringConvertToUTF8(path);
        _WIN32_FIND_DATA data;
        std::string resolved;
        while (FindFirstFile(remaining.c_str(), &data)) {
            std::string name(data.fileName);
            resolved = "/" + name + resolved;
            remaining = remaining.substr(0, remaining.length() - name.length() - 1);
        }
        resolved = "/Users" + resolved;
        path = STRINGS::StringConvertToWide(resolved);
        path = path.substr(m_wUnknown68.length(), files[i].length() - m_wUnknown68.length());
        m_mapModFiles[relative] = path;
    }
    m_bUnknown70 = !m_mapModFiles.empty() && (initialCount == 0 || wasEnabled);
    CMasterResourceManager::getSingleton()->addResourceLocation(m_wUnknown68, m_sUnknown48, true);
    Ogre::ResourceGroupManager::getSingleton().setResourceGroupAllowedToAccessFileSystemOnSearch(m_sUnknown48, false);
}

CMod::CMod(const std::wstring& path, int priority)
    : m_sUnknown48("MOD"), m_wUnknown50(L"MOD"), m_wUnknown58(EMPTY_WSTRING),
      m_wUnknown60(EMPTY_WSTRING), m_wUnknown68(path), m_bUnknown70(true),
      m_bUnknown71(false), m_iUnknown74(priority)
{
    if (!m_wUnknown68.empty() && m_wUnknown68[m_wUnknown68.length() - 1] != L'/')
        m_wUnknown68 = m_wUnknown68 + L"/";
    m_wUnknown68 = FILESYSTEM::CleanPath(m_wUnknown68);
    CDataGroup metadata(EMPTY_WSTRING, NULL, 20, 10, NULL);
    if (FILESYSTEM::FileExists(m_wUnknown68 + L"mod.dat"))
        metadata.LoadFile(m_wUnknown68 + L"mod.dat", static_cast<CTimerStatics*>(NULL));
    std::queue<std::wstring> parts;
    STRINGS::TokenizeString(&parts, m_wUnknown68, L"/");
    while (!parts.empty()) {
        m_wUnknown50 = parts.front();
        parts.pop();
    }
    m_sUnknown10 = STRINGS::StringConvertToUTF8(m_wUnknown68);
    m_wUnknown50 = metadata.GetDataValue(L"NAME", m_wUnknown50);
    m_sUnknown48 = STRINGS::StringConvertToUTF8(m_wUnknown50);
    m_wUnknown58 = metadata.GetDataValue(L"AUTHOR", m_wUnknown50);
    m_wUnknown60 = metadata.GetDataValue(L"DESCRIPTION", m_wUnknown60);
    reloadModFiles();
}
