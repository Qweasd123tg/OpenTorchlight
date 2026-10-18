#ifndef SOUNDDATA_H
#define SOUNDDATA_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "RunicCore.h"
#include "TArrayList.h"
#include "FmodInterface.h"
#include <string>

class CSoundData : public CRunicCore
{
public:
    virtual ~CSoundData();

    // fields
    std::wstring m_name; // +0x10
    std::wstring m_category; // +0x18
    long long m_iGuid;
    float m_float28;
    bool m_flag2c;
    unsigned char m_gap2d[3];
    float m_float30;
    float m_float34;
    float m_float38;
    int m_probability; // +0x3c, passed to the named addSample overload
    TArrayList<std::wstring> m_files; // +0x40
    FMOD::SoundGroup* m_group; // +0x58
};

#endif
