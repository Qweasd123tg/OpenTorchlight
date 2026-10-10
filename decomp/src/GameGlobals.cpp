#include "GameGlobals.h"
static CGameGlobals* g_pGameGlobals __attribute__((used));


CGameGlobals* CGameGlobals::getSingleton()
{
    return g_pGameGlobals;
}

const std::wstring& CGameGlobals::getContextTip(EContextTip tip)
{
    return m_contextTips[tip];
}

const std::wstring& CGameGlobals::getRandomTip()
{
    return m_tips[m_tipRandomizer.getRandom()];
}
