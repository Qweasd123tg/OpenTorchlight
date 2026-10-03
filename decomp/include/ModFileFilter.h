#ifndef MODFILEFILTER_H
#define MODFILEFILTER_H

#include <string>

#include "RunicCore.h"
#include "TArrayList.h"

class CFileInfo;
class CMod;

// Partial: declarations from ModFileFilter.cpp used by recovered TUs.
class CModFileFilter : public CRunicCore
{
public:
    CModFileFilter();
    virtual ~CModFileFilter();

    unsigned int getNumberOfActiveMods();
    void refreshAllMods();
    std::wstring getFilePath(const std::wstring& path, std::string& resourceGroup, CFileInfo& info);
    void getEnabledModNames(TArrayList<std::wstring>* names);
    void getModNames(TArrayList<std::wstring>* names);
    void getFiles(const std::wstring& directory, TArrayList<std::wstring>& files, std::wstring pattern,
                  bool bRecursive);

private:
    std::wstring m_sModsFile;
    TArrayList<CMod*> m_Mods;
    bool m_b30;

public:
    bool m_bNeedsToRecompressEverything;
};

#endif
