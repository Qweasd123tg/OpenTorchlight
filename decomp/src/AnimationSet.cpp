#include "AnimationSet.h"
#include "Keyframe.h"
#include "EmptyStrings.h"
#include "AnimationSet.h"
#include "RunicCore.h"

CAnimationSet::CAnimationSet()
    : CRunicCore(),
      m_lUnknown28(),
      m_lUnknown40(),
      m_lAnimationGroups()
{
    m_nAnimationCount = 1;
    m_nUnknown = 0;
}


// Imported source candidates; historical status is not fresh acceptance.
void CAnimationSet::clear()
{
    for (unsigned int i = 0; i < m_lAnimationGroups.size(); ++i) {
        for (unsigned int j = 0; j < m_lAnimationGroups[i].size(); ++j) {
            if (m_lAnimationGroups[i][j]) { delete m_lAnimationGroups[i][j]; m_lAnimationGroups[i][j] = NULL; }
        }
        m_lAnimationGroups[i].clear();
    }
    m_lAnimationGroups.clear();
    m_lUnknown28.clear();
    m_lUnknown40.clear();
    m_nUnknown = 0;
}
