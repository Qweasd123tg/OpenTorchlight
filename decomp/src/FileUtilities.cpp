#include "FileUtilities.h"
#include "LinuxUtils.h"
#include "EmptyStrings.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "FileUtilities.h"
#include "LinuxUtils.h"

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
