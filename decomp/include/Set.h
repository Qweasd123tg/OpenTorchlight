#ifndef SET_H
#define SET_H
#include <string>
#include "TArrayList.h"
class CAffix;
// The 0x18-byte unnamed set-bonus record allocated by CSet::load at 0xe0ea1b.
struct CSetAffix
{
    CAffix* m_pAffix;
    std::wstring m_sAffixName;
    unsigned int m_iLevel;
    int m_iRequiredCount;
};
// Partial. CSet::load writes names at +0x20/+0x28 and bonuses at +0x08.
class CSet
{
public:
    unsigned char m_SetData00[8];
    TArrayList<CSetAffix*> m_Affixes;
    std::wstring m_sName;
    std::wstring m_sDisplayName;
};
#endif
