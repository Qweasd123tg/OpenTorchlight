#ifndef GAMENAMESPACES_H
#define GAMENAMESPACES_H

// Free functions of game namespaces by symbol, promoted from the generated headers as
// recovered code needs them; return types from Ghidra until a TU defines them.

#include "TArrayList.h"
#include <Ogre.h>
#include <OgreMesh.h>
#include <OgreQuaternion.h>
#include <OgreSubMesh.h>
#include <OgreVector3.h>
#include <memory>
#include <stdio.h>
#include <string>
#include <vector>

namespace FILESYSTEM
{
    char ReadBool(_IO_FILE*);
    int ReadInt(_IO_FILE*);
    short ReadShort(_IO_FILE*);
}

namespace LinuxUtils
{
    void GetDesktopResolution(int&, int&);
    void Init();
}

namespace STRINGS
{
    bool GetBool(const std::string&);
    int GetBool(const std::wstring&);
    void GetFloat64(const std::string&);
    void GetFloat64(const std::wstring&);
    long GetInt64(const std::string&);
    long long GetInt64(const std::wstring&);
    void* StringConvertUTF8ToWide(const std::string&);
    long long StringCopyWCharArray(wchar_t*, unsigned int, const char*);
    long long StringCopyWCharArray(wchar_t*, unsigned int, std::string);
    unsigned int StringCopyWCharArray(wchar_t*, unsigned int, const wchar_t*);
    long long StringIsLower(const std::string&);
    long long StringIsLower(const std::wstring&);
    long long StringIsUpper(const std::string&);
    long long StringIsUpper(const std::wstring&);
    long long firstXCharactersMatch(const std::wstring&, const std::wstring&, unsigned int);
    long long firstXCharactersMatch(const wchar_t*, unsigned int, const wchar_t*, unsigned int);
}

namespace ShellUtils
{
    void LaunchBrowser(const std::string&);
    void LaunchProgram(const std::string&, const std::vector<std::string, std::allocator<std::string > >&);
}

#endif
