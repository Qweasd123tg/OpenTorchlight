#ifndef EFFECTGROUPMANAGER_H
#define EFFECTGROUPMANAGER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <string>
#include "Affix.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CEffectGroupManager : public CRunicCore
{
public:
    virtual ~CEffectGroupManager();
    void getAffixNames(TArrayList<std::wstring >&);
    void clean();
    long long getAffix(const std::wstring&);
    void rollAndCreateRandomAffixes(unsigned int, unsigned int, unsigned int, TArrayList<CAffix*>&);
    void reload();
    CEffectGroupManager(const wchar_t*);

    // fields
    void* m_pUnknown10;
    long long m_Unknown18;
    int m_iUnknown20;
    unsigned char m_gap24[0x4] __attribute__((aligned(4)));
    void* m_pUnknown28;
    void* m_pUnknown30;
    long long m_iUnknown38;
    long long m_iUnknown40;
    long long m_Unknown48;
    int m_iUnknown50;
    unsigned char m_gap54[0x4] __attribute__((aligned(4)));
    void* m_pUnknown58;
    void* m_pUnknown60;
    long long m_iUnknown68;
    long long m_iUnknown70;
};

#endif
