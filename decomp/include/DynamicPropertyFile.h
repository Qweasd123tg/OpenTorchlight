#ifndef DYNAMICPROPERTYFILE_H
#define DYNAMICPROPERTYFILE_H

#include <string>

#include "RunicCore.h"

// Partial: declarations from DynamicPropertyFile.cpp used by recovered TUs.
// The fields after the CRunicCore base are not recovered yet (0x140 bytes in
// total, from the constructor).
class CDynamicPropertyFile : public CRunicCore
{
public:
    virtual ~CDynamicPropertyFile();
    virtual void SaveSettings(const std::wstring& file);
    virtual void LoadSettings(const std::wstring& file);

    int GetInt(unsigned int property);
    const std::wstring& GetString(unsigned int property);
    void SetInt(unsigned int property, int value);
    void SetString(unsigned int property, const std::wstring& value);

private:
    unsigned char m_Unrecovered[0x130];
};

#endif
