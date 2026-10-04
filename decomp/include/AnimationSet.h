#ifndef ANIMATIONSET_H
#define ANIMATIONSET_H

#include <string>

#include "RunicCore.h"
#include "TArrayList.h"

class CAnimation;

class CAnimationSet : public CRunicCore
{
public:
    virtual ~CAnimationSet();
    CAnimationSet();
    void clear();

    int m_nAnimationCount;
    unsigned char m_alignment14[4] __attribute__((aligned(4)));
    std::wstring m_wsName;
    int m_nUnknown;
    unsigned char m_alignment24[4] __attribute__((aligned(4)));
    TArrayList<CAnimation *> m_lUnknown28;
    TArrayList<CAnimation *> m_lUnknown40;
    TArrayList<TArrayList<CAnimation *> > m_lAnimationGroups;
};

#endif
