#include "FileUtilities.h"
#include "LinuxUtils.h"
#include "EmptyStrings.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "FileUtilities.h"
#include "LinuxUtils.h"
#include <sys/stat.h>
#include "StringUtilities.h"

short FILESYSTEM::ReadShort(FILE* file)
{
    short value;
    return fread(&value, sizeof(value), 1, file) == 1 ? value : 0;
}

int FILESYSTEM::ReadInt(FILE* file)
{
    int value;
    return fread(&value, sizeof(value), 1, file) == 1 ? value : 0;
}

char FILESYSTEM::ReadBool(_IO_FILE* file)
{
    unsigned char value;
    return fread(&value, 1, 1, file) == 1 ? static_cast<char>(value) : 0;
}

std::wstring FILESYSTEM::CleanPath(const std::wstring& path)
{
    std::wstring result(path);

    while (result.find(L"\\") != std::wstring::npos)
        result.replace(result.find(L"\\"), 1, L"/");

    while (result.find(L"//") != std::wstring::npos)
        result.replace(result.find(L"//"), 2, L"/");

    return result;
}

namespace FILESYSTEM
{
    std::string CleanPath(const std::string& path)
    {
        std::string cleanPath(path);

        while (cleanPath.find("\\") != std::string::npos)
            cleanPath.replace(cleanPath.find("\\"), 1, "/");

        while (cleanPath.find("//") != std::string::npos)
            cleanPath.replace(cleanPath.find("//"), 2, "/");

        return cleanPath;
    }
}

std::string FILESYSTEM::RemoveFileName(const std::string& path)
{
    std::string result(path);
    std::string::size_type pos = path.rfind("/", std::string::npos, 1);

    if (pos != std::string::npos)
        result = path.substr(0, pos + 1);

    if (result.length() == path.length())
    {
        pos = path.rfind("\\", std::string::npos, 1);
        if (pos != std::string::npos)
            result = path.substr(0, pos + 1);
    }

    return result;
}

std::wstring FILESYSTEM::GetAppDataPath()
{
    return LinuxUtils::GetHomeDir() + L".runicgames/Torchlight/";
}


// Imported source candidates; historical status is not fresh acceptance.
float FILESYSTEM::ReadFloat(FILE* file)
{
    float value;
    if(fread(&value,sizeof(value),1,file)==1)return value;
    return 0.0f;
}

std::wstring FILESYSTEM::GetWindowsTempPath()
{
    return LinuxUtils::GetTempDir();
}

std::wstring FILESYSTEM::GetLocalPath()
{
    return LinuxUtils::GetAppDir();
}

bool FILESYSTEM::FileExists(const std::wstring& path)
{
    return FileExists(path.c_str());
}

std::wstring FILESYSTEM::GetApplicationPath()
{
    static std::wstring absolutePath(L"");
    if (absolutePath.empty())
        return LinuxUtils::GetAppDir();
    return absolutePath;
}

std::wstring FILESYSTEM::AssembleAbsolutePath(const std::wstring& base,
                                               const std::wstring& path)
{
    std::wstring result(path);
    if (!path.empty() && path.find(L"/") != 0)
        result = base + path;
    return result;
}

bool FILESYSTEM::FileExists(const wchar_t* path)
{
    std::string narrow = STRINGS::StringConvertToUTF8(std::wstring(path));
    struct stat info;
    return stat(narrow.c_str(), &info) == 0;
}

long long FILESYSTEM::GetFileTime(const wchar_t* path)
{
    std::wstring wide(path);
    std::string narrow = STRINGS::StringConvertToUTF8(wide);
    struct stat info;
    return stat(narrow.c_str(), &info) == 0 ? info.st_mtime : -1;
}

std::wstring FILESYSTEM::ReadWString(FILE* file, unsigned int length)
{
    std::wstring result;
    for (unsigned int i = 0; i < length; ++i) {
        unsigned short value;
        fread(&value, 2, 1, file);
        result = result + static_cast<wchar_t>(value);
    }
    return result;
}

std::wstring FILESYSTEM::GetSaveDataPath()
{
    std::wstring result = EMPTY_WSTRING;
    result = GetAppDataPath() + L"Save/";
    return result;
}

std::wstring FILESYSTEM::GetFileName(const std::wstring& path)
{
    std::wstring result(path);
    std::wstring::size_type pos = path.rfind(L"/");
    if (pos != std::wstring::npos)
        result = path.substr(pos + 1, path.length() - pos);
    pos = path.rfind(L"\\");
    if (pos != std::wstring::npos)
        result = path.substr(pos + 1, path.length() - pos);
    return result;
}

std::string FILESYSTEM::GetFileName(const std::string& path)
{
    std::string result(path);
    std::string::size_type pos = path.rfind("/");
    if (pos != std::string::npos)
        result = path.substr(pos + 1, path.length() - pos);
    if (result.length() == path.length())
    {
        pos = path.rfind("\\");
        if (pos != std::string::npos)
            result = path.substr(pos + 1, path.length() - pos);
    }
    return result;
}

bool FILESYSTEM::FileExists(const std::string& path)
{
    return FileExists(STRINGS::StringConvertToWide(path).c_str());
}

std::wstring FILESYSTEM::GetDirectory(const std::wstring& path)
{
    std::wstring result(path);
    result = STRINGS::replaceWString(result, GetFileName(result), L"");
    return result;
}

long long FILESYSTEM::GetFileCreationTime(const wchar_t* path)
{
    std::string narrow = STRINGS::StringConvertToUTF8(std::wstring(path));
    struct stat info;
    return stat(narrow.c_str(), &info) == 0 ? info.st_ctime : -1;
}
