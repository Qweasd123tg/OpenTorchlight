#ifndef FILEUTILITIES_H
#define FILEUTILITIES_H

#include <string>

// Partial: declarations from FileUtilities.cpp used by recovered TUs.
namespace FILESYSTEM
{
    std::wstring GetLocalPath();
    std::wstring GetApplicationPath();
    std::wstring GetAppDataPath();
    std::wstring AssembleAbsolutePath(const std::wstring& base, const std::wstring& path);
    std::wstring CleanPath(const std::wstring& path);
    std::string RemoveFileName(const std::string& path);
    bool FileExists(const std::wstring& path);
    long long GetFileTime(const wchar_t* path);
}

#endif
