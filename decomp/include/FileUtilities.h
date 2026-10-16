#ifndef FILEUTILITIES_H
#define FILEUTILITIES_H

#include <string>
#include <cstdio>
#include <vector>
#include "TArrayList.h"
#include "LinuxFileCompat.h"

// Partial: declarations from FileUtilities.cpp used by recovered TUs.
namespace FILESYSTEM
{
    bool FileIsOlder(const std::wstring& first, const std::wstring& second);
    std::string AssembleAbsolutePath(const std::string& base, const std::string& path);
    bool CreateLocalDirectory(const std::wstring& path);
    void GetFileListSorted(const std::wstring& path, TArrayList<std::wstring>& files, std::wstring pattern);
    _WIN32_FIND_DATA GetFileData(const std::wstring& path);
    unsigned char ReadByte(FILE* file);
    std::string ReadString(FILE* file, unsigned int length);
    std::string ReadString(FILE* file);
    std::wstring ReadWString(FILE* file);
    std::wstring GetFileName(const std::wstring& path);
    std::string GetFileName(const std::string& path);
    std::wstring GetDirectory(const std::wstring& path);
    bool FileExists(const std::string& path);
    long long GetFileCreationTime(const wchar_t* path);
    void GetDirectoryList(const std::wstring& path, std::vector<std::wstring>& directories);
    std::wstring FindFullDirectoryName(const std::wstring& path, const std::wstring& name);
    void GetFileList(const std::wstring& path, TArrayList<std::wstring>& files, std::wstring pattern);
    void GetFileListRecursive(const std::wstring& path, TArrayList<std::wstring>& files, const std::wstring& pattern);
    std::wstring FindFullFileName(const std::wstring& path, const std::wstring& name, const std::wstring& extension);
    std::wstring ReadWString(_IO_FILE*, unsigned int);
    bool FileExists(const wchar_t*);
    std::wstring GetLocalPath();
    std::wstring GetApplicationPath();
    std::wstring GetAppDataPath();
    std::wstring GetSaveDataPath();
    std::wstring AssembleAbsolutePath(const std::wstring& base, const std::wstring& path);
    std::wstring CleanPath(const std::wstring& path);
    std::wstring GetFileName(const std::wstring& path);
    std::string RemoveFileName(const std::string& path);
    std::wstring RemoveFileName(const std::wstring& path);
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
