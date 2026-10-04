#ifndef MOD_H
#define MOD_H

#include <map>
#include <string>

#include "RunicCore.h"

class CMod : public CRunicCore
{
public:
    virtual ~CMod();

    const std::wstring& getModFile(const std::wstring& path);
    const std::wstring& getModFileAbsolute(const std::wstring& path);

    void reloadModFiles();

    CMod(const std::wstring& path, int priority);

    std::string m_sUnknown10;
    std::map<std::wstring, std::wstring> m_mapModFiles;
    std::string m_sUnknown48;
    std::wstring m_wUnknown50;
    std::wstring m_wUnknown58;
    std::wstring m_wUnknown60;
    std::wstring m_wUnknown68;
    bool m_bUnknown70;
    bool m_bUnknown71;
    int m_iUnknown74;
};

#endif
