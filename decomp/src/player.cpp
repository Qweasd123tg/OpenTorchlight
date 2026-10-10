#include <cmath>
#include "DataGroup.h"
#include "DungeonTracker.h"
#include "GameClient.h"
#include "GenericModel.h"
#include "Graph.h"
#include "GraphManager.h"
#include "Level.h"
#include "LevelState.h"
#include "LevelTemplateData.h"
#include "OgreSceneNode.h"
#include "Particle.h"
#include "ResourceManager.h"
#include "Skill.h"
#include "SteamStats.h"
#include "StringUtilities.h"
#include "Utilities.h"
#include "cmath"
void WriteUTF32ToUTF16(FILE*, const std::wstring&, unsigned long);

#include "Character.h"
#include "Player.h"

void CPlayer::levelLoaded(CLevel* value)
{
    CCharacter::levelLoaded(value);
}

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

int CPlayer::getDungeonRank(std::wstring dungeon)
{
    for (unsigned int i = 0; i < m_dungeonTrackers.size(); ++i) {
        if (m_dungeonTrackers[i]->m_name == dungeon) return m_dungeonTrackers[i]->m_rank;
    }
    return 0;
}

void CPlayer::clearDungeonHistory(std::wstring dungeon)
{
    dungeon = STRINGS::StringUpper(dungeon);
    for (int i = 0; i < int(m_savedLevels.size()); ++i) {
        CLevelState* state = m_savedLevels[i];
        if (state->m_sLevelName == dungeon) state->m_iStateVersion = -1.0f;
    }
}

bool CPlayer::hasDungeonHistory(std::wstring dungeon)
{
    dungeon = STRINGS::StringUpper(dungeon);
    for (int i = 0; i < int(m_savedLevels.size()); ++i)
        if (m_savedLevels[i]->m_sLevelName == dungeon) return true;
    return false;
}

void CPlayer::startFishing()
{
    CCharacter::startFishing();
    m_fishingParticle->setVisible(false);
    m_fishingFlag = false;
    m_fishingDelay = UTILITIES::randomBetweenVolatile(1.0f,3.0f);
    m_fishingTime = 2.0f;
    m_fishingValue860 = 0.0f;
    m_fishingValue854 = 0.0f;
}

void CPlayer::openPortal(CLevel& level)
{
    if (level.getLevelTemplateData()->permitsPortal())
    {
        level.deleteOpenPortals();
        m_hasPortal = true;
        m_portalDepth = level.getLevelDepth();
        m_portalDungeon = level.getDungeonName();
        m_portalPosition = level.randomOpenPosition(getPosition(true), 3, false);
        createPortals(level);
    }
}

void CPlayer::attemptToStopPlayerSkill(bool force)
{
    if (m_activeSkill)
    {
        int animation = m_activeSkill->getAnimationIndexLoopEnd();
        attemptStopOfActiveSkill();
        if (!performingSkill())
        {
            if (animation != -1)
            {
                blendAnimation(animation, true, 0.2f, 1, -1);
                queueBlendAnimation("IDLE", true, 0.2f, 1);
            }
            if (m_activeSkill && m_activeSkill->stopsPathingOnCompletion() && force)
                stopPathing();
        }
    }
}

void CPlayer::catchFish()
{
    if (m_eAIState == 34)
        return;
    m_fishingFlag = false;
    if (m_fishingValue860 > 0)
        m_fishingFlag = true;
    setAIState(static_cast<EAIState>(34));
    blendAnimation("FISHING_CATCH", false, 0.2f, 1, -1);
    m_pUnitModel->queueBlendAnimation("IDLE", true, 0.2f, 1);
}
