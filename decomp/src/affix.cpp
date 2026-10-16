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

bool CAffix::effectHasDuration(EEFFECT_TYPE type)
{
    for (unsigned int i = 0; i < m_Effects.size(); ++i) {
        if (m_Effects[i]->m_fValue24 > 0.0f) {
            if (type != m_Effects[i]->m_eType)
                continue;
            return true;
        }
    }
    return false;
}

bool CAffix::effectExists(EEFFECT_TYPE type)
{
    for (unsigned int i = 0; i < m_Effects.size(); ++i) {
        if (type != m_Effects[i]->m_eType)
            continue;
        return true;
    }
    return false;
}

std::wstring CAffix::getDisplayStats(unsigned int level)
{
    std::wstring result(L"");
    for (unsigned int i = 0; i < m_Effects.size(); ++i) {
        std::wstring text = m_Effects[i]->getDisplayStats(level, false);
        if (result != EMPTY_WSTRING && text != EMPTY_WSTRING)
            result += L"\n";
        result += text;
    }
    return result;
}
