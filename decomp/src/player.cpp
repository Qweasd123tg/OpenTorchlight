#include "Graph.h"
#include "GraphManager.h"
#include "LevelState.h"
#include <OgreSceneNode.h>
#include "Player.h"
#include "SteamStats.h"
#include <cmath>
#include "Character.h"
#include "Player.h"

void CPlayer::levelLoaded(CLevel* value)
{
    CCharacter::levelLoaded(value);
}


// Imported source candidates; historical status is not fresh acceptance.
void CPlayer::clearSkillMap()
{
    for (int i = 0; i < 10; ++i) { m_skillMap[i] = -1; m_leftSkillMap[i] = -1; }
}

void CPlayer::clearSkillFunctionMap()
{
    for (int i = 0; i < 12; ++i) { m_functionSkills[i] = -1; m_leftFunctionSkills[i] = -1; }
}

void CPlayer::setMappedFunctionSkill(unsigned int index, long long guid)
{
    for (int i = 0; i < 12; ++i) if (m_functionSkills[i] == guid) m_functionSkills[i] = -1;
    m_functionSkills[index] = guid;
    if (guid != -1) m_leftFunctionSkills[index] = -1;
}

void CPlayer::setLeftMappedFunctionSkill(unsigned int index, long long guid)
{
    for (int i = 0; i < 12; ++i) if (m_leftFunctionSkills[i] == guid) m_leftFunctionSkills[i] = -1;
    m_leftFunctionSkills[index] = guid;
    if (guid != -1) m_functionSkills[index] = -1;
}

void CPlayer::clearItemLinkMap()
{
    m_itemLinks[0] = -1; m_itemLinks[1] = -1;
}

void CPlayer::resetLevel()
{
    m_iUnitLevel = 1; m_experience = 0; m_fame = 0;
    calculateMaxHP();
    m_fHPFloat = static_cast<float>(m_maxHPBase);
    calculateMaxMana();
    m_fManaFloat = static_cast<float>(m_maxManaBase);
}

void CPlayer::removeLevelSavedState(unsigned int index)
{
    if (static_cast<int>(index) < static_cast<int>(m_savedLevels.size())) {
        if (m_savedLevels[static_cast<int>(index)]) { delete m_savedLevels[static_cast<int>(index)]; m_savedLevels[static_cast<int>(index)] = NULL; }
        m_savedLevels[static_cast<int>(index)] = m_savedLevels[m_savedLevels.size() - 1];
    }
    m_savedLevels.pop_back();
}

void CPlayer::clearLevelHistory()
{
    for (int i = 0; i < static_cast<int>(m_savedLevels.size()); ++i)
        if (!m_savedLevels[i]->m_bUnknownB0) { removeLevelSavedState(i); --i; }
}

void CPlayer::setJournalStatistic(EJournalStatistic statistic, int amount)
{
    m_journalStats[statistic] = amount;
}

void CPlayer::soldItem(CEquipment* equipment)
{
    CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(17), 1);
}

int CPlayer::getSkillPointsAwardedForFameLevel(unsigned int level)
{
    if (!m_famePointsGraph.empty()) {
        CGraph* graph = CGraphManager::getSingleton()->getGraph(m_famePointsGraph);
        if (graph) return static_cast<int>(ceilf(graph->getValue(static_cast<float>(level), 0)));
    }
    return 0;
}

int CPlayer::getSkillPointsAwardedForLevel(unsigned int level)
{
    if (!m_skillPointsGraph.empty()) {
        CGraph* graph = CGraphManager::getSingleton()->getGraph(m_skillPointsGraph);
        if (graph) return static_cast<int>(ceilf(graph->getValue(static_cast<float>(level), 0)));
    }
    return 0;
}

int CPlayer::getStatsPointsAwardedForLevel(unsigned int level)
{
    if (!m_statPointsGraph.empty()) {
        CGraph* graph = CGraphManager::getSingleton()->getGraph(m_statPointsGraph);
        if (graph) return static_cast<int>(ceilf(graph->getValue(static_cast<float>(level), 0)));
    }
    return 0;
}

void CPlayer::calculateMaxHP()
{
    if (!m_hpGraph.empty()) {
        CGraph* graph = CGraphManager::getSingleton()->getGraph(m_hpGraph);
        if (graph) {
            m_maxHPBase = static_cast<int>(ceilf(graph->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)), 0)));
            if (m_fHPFloat > maxHP()) m_fHPFloat = maxHP();
        }
    }
}

void CPlayer::calculateMaxMana()
{
    if (!m_manaGraph.empty()) {
        CGraph* graph = CGraphManager::getSingleton()->getGraph(m_manaGraph);
        if (graph) {
            m_maxManaBase = static_cast<int>(ceilf(graph->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)), 0)));
            if (m_fManaFloat > maxMana()) m_fManaFloat = maxMana();
        }
    }
}
