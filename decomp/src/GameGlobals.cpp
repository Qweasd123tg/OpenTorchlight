
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

CGameGlobals::CGameGlobals(const wchar_t* path)
    : m_globalsPath(path), m_normalItemWeight(0), m_magicItemWeight(0),
      m_uniqueItemWeight(0), m_fRandomEnchantChance(0), m_fRandomSocketChance(0),
      m_fSecondSocketChance(0), m_iMinRandomEnchantSlots(0),
      m_iMaxRandomEnchantSlots(0), m_iMinMagicItemSlots(0), m_iMaxMagicItemSlots(0),
      m_iMinUniqueItemSlots(0), m_iMaxUniqueItemSlots(0), m_retirementAge(20),
      m_magicFindMagicInfluence(0), m_magicFindUniqueInfluence(0),
      m_configStrings(10), m_tipRandomizer(RANDOMIZER_NORMAL), m_maxLevelMemory(6),
      m_levelRespawnTime(1800), m_merchantRespawnTime(60)
{
    reload();
    if (!g_pGameGlobals) g_pGameGlobals = this;
}

CGameGlobals::~CGameGlobals()
{
    g_pGameGlobals = NULL;
}
