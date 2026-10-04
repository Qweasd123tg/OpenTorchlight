#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Affix.h"
#include "Effect.h"

void CAffix::effectDeleted(CEffect *pEffect)
{
    m_Effects.remove(pEffect);
}

void CAffix::setLevel(unsigned int uiLevel)
{
    m_uiLevel = std::max((float)uiLevel, (float)m_iMinSpawnRange);
    m_uiLevel = std::min((float)m_uiLevel, (float)m_iMaxSpawnRange);

    float fLevelPercent =
        ((float)(m_uiLevel - m_iMinSpawnRange) /
         (float)(m_iMaxSpawnRange - m_iMinSpawnRange)) * 100.0f;

    m_cLevelPercent = 100;
    if (fLevelPercent < 100.0f)
        m_cLevelPercent = (char)(fLevelPercent + 0.5f);

    setPercent(m_cLevelPercent);
}
