#ifndef ANIMATIONSET_H
#define ANIMATIONSET_H

#include <string>
#include <vector>
class CKeyframe;

#include "RunicCore.h"
#include "TArrayList.h"

class CAnimation;
class CKeyframe;

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
    std::vector<std::string> m_lUnknown28;
    std::vector<std::wstring> m_lUnknown40;
    std::vector<std::vector<CKeyframe*> > m_lAnimationGroups;
};

#endif
