#ifndef DYNAMICPROPERTYFILE_H
#define DYNAMICPROPERTYFILE_H

#include <string>
#include <vector>
#include <map>

#include "RunicCore.h"

// Partial 0x140 layout: container offsets follow the original accessors;
// untouched members remain opaque.
class CDynamicPropertyFile : public CRunicCore
{
public:
    bool SetFloat(unsigned int,float);

    CDynamicPropertyFile(std::wstring directory, std::wstring file, std::wstring section);
    unsigned int GetStringPropertyIndex(const std::wstring& name, std::wstring value, bool flag);
    unsigned int GetFloatPropertyIndex(const std::wstring& name, float value, bool flag);
    unsigned int GetIntPropertyIndex(const std::wstring& name, int value, bool flag);
    virtual ~CDynamicPropertyFile();
    virtual bool SaveSettings(const std::wstring& file);
    virtual bool LoadSettings(const std::wstring& file);

    int GetInt(unsigned int property);
    float GetFloat(unsigned int property);
    const std::wstring& GetString(unsigned int property);
    bool SetInt(unsigned int property, int value);
    bool SetString(unsigned int property, const std::wstring& value);
    bool isNonLocalVariable(const std::wstring& name);
    void SetStatChangeCallback(unsigned int property, void (*)(unsigned int));
    bool saveSettings(const std::wstring& file, bool flag);
    bool loadSettings(const std::wstring& file);

private:
    typedef void (*StatChangeCallback)(unsigned int);
    unsigned char m_Unrecovered10[0x10];
    std::wstring m_secondaryFile; // +0x20
    std::vector<std::vector<StatChangeCallback> > m_callbacks; // +0x28
    std::vector<int> m_intValues; // +0x40
    std::vector<float> m_floatValues; // +0x58
    std::vector<std::wstring> m_stringValues; // +0x70
    std::vector<std::wstring> m_nonLocalVariables; // +0x88
    std::map<std::wstring, unsigned int> m_intIndices; // +0xa0
    std::map<std::wstring, unsigned int> m_floatIndices; // +0xd0
    std::map<std::wstring, unsigned int> m_stringIndices; // +0x100
    unsigned char m_Unrecovered130[8];
    std::wstring m_missingString; // +0x138
};

#endif
