#include "EmptyStrings.h"
#include "AnimationSet.h"
#include "RunicCore.h"

CAnimationSet::CAnimationSet()
    : CRunicCore(),
      m_lUnknown28(0),
      m_lUnknown40(0),
      m_lAnimationGroups(0)
{
    m_nAnimationCount = 1;
    m_nUnknown = 0;
}
