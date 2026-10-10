#ifndef FILEUTILITIES_H
#define FILEUTILITIES_H

#include <string>
#include <cstdio>

// Partial: declarations from FileUtilities.cpp used by recovered TUs.
namespace FILESYSTEM
{
    bool FileExists(const wchar_t*);
    std::wstring GetLocalPath();
    std::wstring GetApplicationPath();
    std::wstring GetAppDataPath();
    std::wstring AssembleAbsolutePath(const std::wstring& base, const std::wstring& path);
    std::wstring CleanPath(const std::wstring& path);
    std::string RemoveFileName(const std::string& path);
    bool FileExists(const std::wstring& path);
    bool CreateAppDataDirectory(const std::wstring& path);
    long long GetFileTime(const wchar_t* path);
}


// Signatures retained from the supplied pass10 source, verified against the original at import.
namespace FILESYSTEM {
float ReadFloat(FILE* file);
std::wstring GetWindowsTempPath();
std::wstring GetLocalPath();
bool FileExists(const std::wstring& path);
}

#endif
