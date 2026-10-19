#include "Equipment.h"
#include "EquipmentRef.h"
#include <OgreEntity.h>
#include "QuestManager.h"
#include "Quest.h"
#include "MasterResourceManager.h"
#include "Settings.h"
#include "Dungeon.h"
#include "DungeonManager.h"

#include "Achievements.h"
#include "Achievement.h"
#include "EmptyStrings.h"

#include "FileUtilities.h"
#include "Inventory.h"
#include "SkillManager.h"
#include "GameUI.h"

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

void CDungeonTracker::save(FILE* file)
{
    unsigned short length = static_cast<unsigned short>(m_name.length());
    fwrite(&length, 2, 1, file);
    WriteUTF32ToUTF16(file, m_name, length);
    fwrite(&m_rank, 4, 1, file);
    fwrite(&m_value8, 4, 1, file);
    fwrite(&m_value10, 4, 1, file);
    unsigned int count = m_levels.size();
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i)
        fwrite(&m_levels[i], 4, 1, file);
}

void CPlayer::firstTimeSetup()
{
    if (!m_pInventory) return;
    const wchar_t* names[] = {L"Health Potion", L"Health Potion", L"Mana Potion",
        L"Mana Potion", L"Town Portal Scroll", L"Town Portal Scroll",
        L"Identify Scroll", L"Identify Scroll"};
    for (unsigned int i = 0; i < 8; ++i) {
        CEquipment* equipment = m_pResourceManager->createEquipment(names[i], false, true);
        if (equipment) m_pInventory->pickupEquipment(equipment, true);
    }
    m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(9));
}

void CDungeonTracker::load(FILE* file, unsigned int version)
{
    unsigned short length;
    fread(&length, 2, 1, file);
    m_name = FILESYSTEM::ReadWString(file, length);
    fread(&m_rank, 4, 1, file);
    fread(&m_value8, 4, 1, file);
    if (version > 2) {
        fread(&m_value10, 4, 1, file);
        if (version > 5) {
            unsigned int count;
            fread(&count, 4, 1, file);
            for (unsigned int i = 0; i < count; ++i) {
                int level;
                fread(&level, 4, 1, file);
                m_levels.push_back(level);
            }
        }
    }
}

void CPlayer::resetStatPoints()
{
    m_iUnusedStatPoints = 0;
    m_iUnusedSkillPoints = 0;
    m_iMeleeStat = m_pDataGroup->GetDataValue(L"STRENGTH", 10);
    m_rangedStat = m_pDataGroup->GetDataValue(L"DEXTERITY", 10);
    m_magicStat = m_pDataGroup->GetDataValue(L"MAGIC", 10);
    m_defenseStat = m_pDataGroup->GetDataValue(L"DEFENSE", 10);
    m_naturalArmor = m_pDataGroup->GetDataValue(L"ARMOR", 0);
}

void CPlayer::resetSkills()
{
    if (!m_pSkillManager) return;
    int points = m_pSkillManager->getSkillPoints();
    m_pSkillManager->stopAllSkills(true, false, true);
    m_pSkillManager->resetSkillLevels();
    std::vector<CDataGroup*> groups;
    unsigned int count = m_pDataGroup->GetDataGroupsMatchingName(L"SKILL", &groups);
    for (unsigned int i = 0; i < count; ++i) {
        CDataGroup* group = groups[i];
        std::wstring name = STRINGS::StringUpper(group->GetDataValue(L"NAME", L""));
        unsigned int level = group->GetDataValue(L"LEVEL", 0u);
        points -= level;
        m_pSkillManager->setSkillLevel(name, level);
    }
    m_iUnusedSkillPoints += std::max(0, points);
}

void CPlayer::setAIState(EAIState state)
{
    if (m_eAIState >= 32 && m_eAIState <= 34 && state != 32 && state != 33 && state != 34)
        if (m_fishingNode) m_fishingNode->setVisible(false, true);
    m_eAIState = state;
}

void CPlayer::incrementJournalStatistic(EJournalStatistic statistic, int amount)
{
    switch (statistic) {
    case 1:
        CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(13), amount);
        if (m_iGold + amount > 99999)
            CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(35))->forceComplete();
        break;
    case 3: CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(15), amount); break;
    case 4: CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(10), amount); break;
    case 5:
        CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(0), amount);
        if (m_saveOnDeath) CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(18), amount);
        break;
    case 6: CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(4), amount); break;
    case 11: CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(1), amount); break;
    case 12: CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(16), amount); break;
    case 14: CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(6), amount); break;
    case 15: CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(9), amount); break;
    case 16: CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(8), amount); break;
    default: break;
    }
    m_journalStats[statistic] += amount;
}

void CPlayer::die(CCharacter* killer, const Ogre::Vector3* direction, float force, bool silent)
{
    if (alive() && m_pResourceManager->getGameClient()->getGameState() == static_cast<EGameState>(1)) {
        CCharacter::die(killer, direction, force, silent);
        if (m_saveOnDeath) m_pResourceManager->getGameClient()->saveCharacter(true, true);
    }
}

CLevelState* CPlayer::getLevelSavedState(std::wstring dungeon, int level)
{
    for (unsigned int i = 0; i < m_savedLevels.size(); ++i)
        if (m_savedLevels[i]->m_iLevelId == level && m_savedLevels[i]->m_sLevelName == dungeon)
            return m_savedLevels[i];
    return NULL;
}

bool CPlayer::hasLevelSavedState(std::wstring dungeon, int level)
{
    for (unsigned int i = 0; i < m_savedLevels.size(); ++i)
        if (m_savedLevels[i]->m_iLevelId == level && m_savedLevels[i]->m_sLevelName == dungeon)
            return true;
    return false;
}

bool CPlayer::addWaypoint(std::wstring dungeon, int depth)
{
    for (unsigned int i = 0; i < m_dungeonTrackers.size(); ++i) {
        if (m_dungeonTrackers[i]->m_name == dungeon) {
            for (unsigned int j = 0; j < m_dungeonTrackers[i]->m_levels.size(); ++j)
                if (m_dungeonTrackers[i]->m_levels[j] == depth) return false;
            m_dungeonTrackers[i]->m_levels.push_back(depth);
            return true;
        }
    }
    return false;
}

int CPlayer::getMaxDepth(std::wstring dungeon)
{
    dungeon = STRINGS::StringUpper(dungeon);
    for (unsigned int i = 0; i < m_dungeonTrackers.size(); ++i)
        if (m_dungeonTrackers[i]->m_name == dungeon) return m_dungeonTrackers[i]->m_value8;
    return -1;
}

std::wstring CPlayer::getPlayerClassName()
{
    if (m_pDataGroup) return STRINGS::StringUpper(m_pDataGroup->GetDataValue(L"NAME", L"NOT SPECIFIED"));
    return EMPTY_WSTRING;
}

void CPlayer::calculateNaturalArmor()
{
    m_naturalArmor = m_pDataGroup->GetDataValue(L"ARMOR", 0);
    if (m_naturalArmor) {
        CGraph* graph = CGraphManager::getSingleton()->getGraph(L"ARMOR_MONSTER_BYLEVEL");
        if (graph) {
            float value = graph->getValue(float(m_iUnitLevel), 0);
            m_naturalArmor = int(ceilf(value * (float(m_naturalArmor) / 100.0f)));
        }
    }
}

void CPlayer::createPortals(CLevel& level)
{
    Ogre::Vector3 position = level.m_waypointPosition;
    if (position != Ogre::Vector3(-1.0f, -1.0f, -1.0f))
    {
        for (unsigned int i = 0; i < m_dungeonTrackers.size(); ++i)
        {
            if (!m_dungeonTrackers[i]->m_levels.empty())
            {
                CBaseUnit* unit = m_pResourceManager->createUnit(L"PROPS", L"WAYPOINT PORTAL", 0, false);
                if (unit)
                {
                    CItem* portal = dynamic_cast<CItem*>(unit);
                    if (portal)
                        level.addItem(portal, position, false);
                }
                break;
            }
        }
    }
    if (m_hasPortal)
    {
        if ((m_portalDepth != level.getLevelDepth() || level.getDungeonName() != m_portalDungeon) && !level.getLevelTemplateData()->isTown())
            return;
        Ogre::Vector3 returnPosition = m_portalPosition;
        if (level.getLevelTemplateData()->isTown())
            returnPosition = level.m_returnPortalPosition;
        CBaseUnit* unit = m_pResourceManager->createUnit(L"PROPS", level.getLevelTemplateData()->isTown() ? L"RETURN TO DUNGEON" : L"RETURN TO TOWN", 0, false);
        if (unit)
        {
            CItem* portal = dynamic_cast<CItem*>(unit);
            if (portal)
                level.addItem(portal, returnPosition, false);
        }
    }
    level.updateAutomapIcons();
}

void CPlayer::updateAnimation(float elapsed)
{
    if (!m_pUnitModel)
        return;
    if (m_followersEnabled != getEnabled())
    {
        unsigned int count = getFollowerCount();
        for (unsigned int i = 0; i < count; ++i)
        {
            CCharacter* follower = getFollower(i);
            if (follower)
                follower->setEnabled(getEnabled());
        }
    }
    m_followersEnabled = getEnabled();
    CCharacter::updateAnimation(elapsed);
    if (m_fishingParticle && m_fishingLineNode)
    {
        if (m_eAIState >= 0x20 && m_eAIState <= 0x22)
        {
            m_fishingLineNode->setVisible(true, true);
            updateFishingLine(elapsed);
            if (m_fishingParticle->getVisible())
                m_fishingParticle->updateAnimation(elapsed, false);
        }
        else
        {
            m_fishingParticle->setVisible(false);
            m_fishingLineNode->setVisible(false, true);
        }
    }
    if (HP() <= 0 && static_cast<CGenericModel*>(getUnitModel())->animationPlayingSubstring("DIE"))
        m_deathDelay = 0.5f;
}

bool CPlayer::removeItemFromInventoryOrPetsInventoryByGuid(long long guid, bool wholeStack, bool destroy, UNITTYPES::EUNITTYPES type)
{
    bool removed = false;
    CInventory* inventory = m_pInventory;
    if (inventory)
    {
        TArrayList<CEquipmentRef*> items(10);
        // The player-side query uses the original 32-bit unsigned sentinel.
        inventory->getEquipmentsOfQuestID(static_cast<unsigned int>(-1), items);
        if (guid != -1)
        {
            for (unsigned int i = 0; i < items.size(); ++i)
            {
                if (items[i]->m_pEquipment->getUnitGuid() != guid)
                    items.removeAt(i--);
            }
        }
        for (unsigned int i = 0; i < items.size(); ++i)
        {
            CEquipment* equipment = items[i]->m_pEquipment;
            if (!equipment || !equipment->ISA(type))
                continue;
            bool erase = destroy;
            if (!wholeStack)
            {
                equipment->incrementStackBy(-1);
                if (equipment->m_iUnknown238 != 0)
                {
                    removed = true;
                    continue;
                }
                erase = true;
            }
            inventory->removeEquipment(equipment);
            if (erase)
                delete equipment;
            removed = true;
        }
    }
    CCharacter* pet = getFollower(0);
    if (pet)
    {
        inventory = pet->getInventory();
        if (inventory)
        {
            TArrayList<CEquipmentRef*> items(10);
            if (guid == -1)
                inventory->getEquipmentsOfQuestID(guid, items);
            else
                inventory->getEquipmentsOfUnitGuid(guid, items);
            for (unsigned int i = 0; i < items.size(); ++i)
            {
                CEquipment* equipment = items[i]->m_pEquipment;
                if (!equipment || !equipment->ISA(type))
                    continue;
                bool erase = destroy;
                if (!wholeStack)
                {
                    equipment->incrementStackBy(-1);
                    if (equipment->m_iUnknown238 != 0)
                    {
                        removed = true;
                        continue;
                    }
                    erase = true;
                }
                inventory->removeEquipment(equipment);
                if (erase)
                    delete equipment;
                removed = true;
            }
        }
    }
    return removed;
}

bool CPlayer::removeQuestItemFromInventoryOrPetsInventoryByGuid(long long quest, long long guid, bool wholeStack, bool destroy, UNITTYPES::EUNITTYPES type)
{
    bool removed = false;
    CInventory* inventory = m_pInventory;
    if (inventory)
    {
        TArrayList<CEquipmentRef*> items(10);
        if (guid == -1)
            inventory->getEquipmentsOfQuestID(quest, items);
        else if (quest == -1)
            inventory->getEquipmentsOfUnitGuid(guid, items);
        else
        {
            inventory->getEquipmentsOfQuestID(quest, items);
            for (unsigned int i = 0; i < items.size(); ++i)
            {
                if (items[i]->m_pEquipment->getUnitGuid() != guid)
                    items.removeAt(i--);
            }
        }
        for (unsigned int i = 0; i < items.size(); ++i)
        {
            CEquipment* equipment = items[i]->m_pEquipment;
            if (!equipment || !equipment->ISA(type))
                continue;
            bool erase = destroy;
            if (!wholeStack)
            {
                equipment->incrementStackBy(-1);
                if (equipment->m_iUnknown238 != 0)
                {
                    removed = true;
                    continue;
                }
                erase = true;
            }
            inventory->removeEquipment(equipment);
            if (erase)
                delete equipment;
            removed = true;
        }
    }
    CCharacter* pet = getFollower(0);
    if (pet)
    {
        inventory = pet->getInventory();
        if (inventory)
        {
            TArrayList<CEquipmentRef*> items(10);
            if (guid == -1)
                inventory->getEquipmentsOfQuestID(quest, items);
            else if (quest == -1)
                inventory->getEquipmentsOfUnitGuid(guid, items);
            else
            {
                inventory->getEquipmentsOfQuestID(quest, items);
                for (unsigned int i = 0; i < items.size(); ++i)
                {
                    if (items[i]->m_pEquipment->getUnitGuid() != guid)
                        items.removeAt(i--);
                }
            }
            for (unsigned int i = 0; i < items.size(); ++i)
            {
                CEquipment* equipment = items[i]->m_pEquipment;
                if (!equipment || !equipment->ISA(type))
                    continue;
                bool erase = destroy;
                if (!wholeStack)
                {
                    equipment->incrementStackBy(-1);
                    if (equipment->m_iUnknown238 != 0)
                    {
                        removed = true;
                        continue;
                    }
                    erase = true;
                }
                inventory->removeEquipment(equipment);
                if (erase)
                    delete equipment;
                removed = true;
            }
        }
    }
    return removed;
}

void CPlayer::loadModel(std::wstring model, std::wstring skeleton)
{
    if (m_fishingPole)
    {
        Ogre::SceneNode* parent = m_fishingPole->getSceneNode()->getParentSceneNode();
        if (parent)
            parent->removeChild(m_fishingPole->getSceneNode());
        if (m_fishingPole)
        {
            delete m_fishingPole;
            m_fishingPole = NULL;
        }
    }
    if (m_fishingParticle)
    {
        Ogre::SceneNode* parent = m_fishingParticle->getSceneNode()->getParentSceneNode();
        if (parent)
            parent->removeChild(m_fishingParticle->getSceneNode());
        if (m_fishingParticle)
        {
            delete m_fishingParticle;
            m_fishingParticle = NULL;
        }
    }
    CCharacter::loadModel(model, skeleton);
    CResourceManager* resources = m_pResourceManager;
    m_fishingPole = resources->createGenericModel(NULL, L"media/models/fishingpole/fishingpole.mesh", skeleton.c_str(), false, false, true);
    m_fishingPole->getEntity()->setRenderQueueGroup(88);
    m_fishingParticle = resources->createGenericModel(NULL, L"media/models/fish/fish.mesh", skeleton.c_str(), false, false, true);
    m_fishingParticle->playAnimation("IDLE", true, 1.0f, -1.0f);
    m_fishingParticle->setVisible(false);
    m_fishingParticle->setRenderBehind(false);
    m_fishingParticle->getEntity()->setRenderQueueGroup(88);
    Ogre::SceneNode* fishingNode = m_fishingNode;
    if (fishingNode)
    {
        Ogre::SceneNode* parent = m_fishingPole->getSceneNode()->getParentSceneNode();
        if (parent)
            parent->removeChild(m_fishingPole->getSceneNode());
        fishingNode->addChild(m_fishingPole->getSceneNode());
        fishingNode->setVisible(false, true);
    }
}

void CPlayer::openMapPortal(std::wstring name, CLevel& level)
{
    Ogre::Vector3 position = level.randomOpenPosition(getPosition(true), 3.0f, false);
    CBaseUnit* unit = m_pResourceManager->createUnit(L"PROPS", L"MAP PORTAL", 0, false);
    if (!unit)
        return;
    CItem* portal = dynamic_cast<CItem*>(unit);
    if (!portal)
        return;
    level.addItem(portal, position, false);
    CEffect* effect = new CEffect(static_cast<EEFFECT_TYPE>(0x71), false, static_cast<EEFFECT_ACTIVATION>(0), -1000.0f, 0.0f, 0.0f, false);
    effect->m_flag33 = true;
    effect->m_sName = STRINGS::StringUpper(name);
    portal->addNewEffect(effect);
}

void CPlayer::levelResetting()
{
    CCharacter::levelResetting();
    modifyHP(static_cast<float>(maxHP()));
    modifyMana(static_cast<float>(maxMana()));
    if (m_pResourceManager && m_pResourceManager->getLevel() && m_pResourceManager->getGameUI()->m_returnToTownOption == 1)
    {
        setPosition(getLevel()->m_playerStart);
        dropToGround(*getLevel(), 4.0f, false);
        setToward(getLevel()->m_startDirection);
    }
    for (unsigned int i = 0; i < m_Followers.size(); ++i)
    {
        m_Followers[i]->teleportToMaster(static_cast<float>(m_Followers.size()) * 0.25f);
        int maximum = m_Followers[i]->maxHP();
        m_Followers[i]->modifyHP(static_cast<float>(maximum));
    }
    setAIState(static_cast<EAIState>(0));
    m_pUnitModel->playAnimation("IDLE", true, 1.0f, -1.0f);
    setEnabled(true);
    if (m_pEffectManager)
    {
        m_pEffectManager->deleteAffix(L"DAMAGEEFFECTFROZENPLAYER");
        m_pEffectManager->deleteAffix(L"DAMAGEEFFECTONFIRE");
        m_pEffectManager->deleteAffix(L"DAMAGEEFFECTELECTRICITY");
        m_pEffectManager->deleteAffix(L"DAMAGEEFFECTPOISONED");
        if (m_pEffectManager)
            m_pEffectManager->removeNonSavedEffects();
    }
}

void CPlayer::updateDungeonTracking(std::wstring name, int depth)
{
    name = STRINGS::StringUpper(name);
    CDungeon* dungeon = CDungeonManager::getSingleton()->getDungeonByName(name);
    for (unsigned int i = 0; i < m_dungeonTrackers.size(); ++i)
    {
        if (m_dungeonTrackers[i]->m_name == name)
        {
            m_dungeonTrackers[i]->m_value8 = std::max(m_dungeonTrackers[i]->m_value8, depth);
            if (dungeon)
            {
                if (m_dungeonTrackers[i]->m_value10 != dungeon->m_iDungeonIndex)
                    m_dungeonTrackers[i]->m_rank = m_iUnitLevel;
                m_dungeonTrackers[i]->m_value10 = dungeon->m_iDungeonIndex;
            }
            return;
        }
    }
    CDungeonTracker* tracker = new CDungeonTracker;
    tracker->m_name = name;
    tracker->m_value8 = depth;
    tracker->m_rank = m_iUnitLevel;
    tracker->m_value10 = dungeon ? dungeon->m_iDungeonIndex : 0;
    m_dungeonTrackers.add(tracker);
}

void CPlayer::setQuestManager(CQuestManager* manager)
{
    m_questManager = manager;
    if (!m_pDataGroup || !manager)
        return;
    manager->setPlayer(this);
    m_questManager->resetQuestManager(true);
    CDataGroup* quests = m_pDataGroup->GetDataGroupByName(L"QUESTS", false);
    if (quests)
    {
        for (unsigned int i = 0; i < quests->GetNumberOfDataValues(); ++i)
        {
            CDataValue::EDATAVALUETYPES type = quests->GetDataValue(i)->GetValueType();
            if (type == CDataValue::DATAVALUE_TRANSLATE || type == CDataValue::DATAVALUE_STRING)
            {
                CQuest* quest = reinterpret_cast<CQuest*>(m_questManager->getQuestByName(STRINGS::StringUpper(quests->GetDataValue(i)->GetValueString(true))));
                if (quest)
                {
                    m_questManager->giveQuest(quest, NULL, false);
                    quest->setQuestAccepted(true);
                }
            }
        }
    }
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_GAME_COMPLETED_ONCE) == 1)
    {
        CQuest* quest = reinterpret_cast<CQuest*>(m_questManager->getQuestByName(CMasterResourceManager::getSingleton()->m_pSettings->GetString(KSETTINGS_RETIREE_QUEST)));
        if (quest && !m_questManager->getQuestComplete(CMasterResourceManager::getSingleton()->m_pSettings->GetString(KSETTINGS_RETIREE_QUEST)))
        {
            m_questManager->giveQuest(quest, NULL, true);
            m_questManager->completeQuest(quest);
        }
    }
}

void CPlayer::fishingAI(float elapsed, CLevel& level)
{
    m_fishingValue854 += elapsed * 4.0f;
    if (m_fishingTime > 1.0f && m_fishingTime < 2.0f)
        m_fishingDelay += UTILITIES::randomBetweenVolatile(-4.1f, 4.0f) * elapsed;
    else if (m_fishingTime >= 2.0f)
        m_fishingDelay += UTILITIES::randomBetweenVolatile(-8.0f, 0.0f) * elapsed;
    else if (m_fishingTime <= 1.0f)
        m_fishingDelay += UTILITIES::randomBetweenVolatile(0.5f, 10.0f) * elapsed;
    if (m_fishingTime < 1.75f && UTILITIES::randomBetweenVolatile(0.0f, 10000.0f) < 5.0f)
        m_fishingDelay += UTILITIES::randomBetweenVolatile(30.0f, 40.0f);
    if (m_fishingValue860 > 0.0f)
        m_fishingValue860 -= elapsed;
    if (!(m_fishingDelay < 10.0f))
        m_fishingDelay = 10.0f;
    if (m_fishingDelay <= -4.0f)
        m_fishingDelay = -4.0f;
    m_fishingTime = std::min(2.0f, m_fishingTime + m_fishingDelay * elapsed);
    if (m_fishingTime + sinf(m_fishingValue854) * 0.2f <= 1.0f)
    {
        m_fishingTime = 1.0f;
        m_fishingDelay = 1.0f;
        if (!m_pUnitModel->animationPlayingSubstring("FISHING_CAST") &&
            !m_pUnitModel->animationPlayingSubstring("FISHING_BITE"))
        {
            m_fishingValue860 = UTILITIES::randomBetweenVolatile(0.25f, 0.4f);
            fishingSplash();
        }
    }
}

#include "CharacterSaveState.h"
#include "FileSystem.h"

void CPlayer::fillSaveState(CCharacterSaveState& state)
{
    CCharacter::fillSaveState(state);
    state.m_flag34 = m_cheatMarker;
    state.m_value68 = m_levelSaveSerial;
    state.m_playTime = m_playTime;
    TArrayList<std::wstring> mods(10);
    CFileSystem::getSingleton()->getEnabledModNames(&mods);
    for (unsigned int i = 0; i < mods.size(); ++i)
        state.m_strings.add(mods[i]);
}

void CPlayer::applySaveState(CCharacterSaveState& state)
{
    CCharacter::applySaveState(state);
    m_cheatMarker = state.m_flag34;
    m_levelSaveSerial = state.m_value68;
    m_playTime = state.m_playTime;
    m_loadedModNames.clear();
    for (unsigned int i = 0; i < state.m_strings.size(); ++i)
        m_loadedModNames.add(state.m_strings[i]);
    calculateNaturalArmor();
    if (!getEnabled())
        setEnabled(true);
}

void CPlayer::update(Ogre::Camera* camera, const Ogre::Vector3& position, float elapsed)
{
    CCharacter::update(camera, position, elapsed);
    if (m_questManager)
        m_questManager->update(elapsed);
    if (m_pathToFollow.getObject())
        updatePathFollowing(true);
    if (m_isPathing)
        m_returningToTown = true;
    else
    {
        m_returningToTown = false;
        if ((m_eAIState == 0 || m_eAIState == 2) && !performingSkill() && !performingAttack() &&
            m_fidgetTime > 10.0f && UTILITIES::randomIntegerBetweenVolatile(0, 1000) <= 2 &&
            animationPlaying("IDLE") && m_pUnitModel->animationExistsSubstring("FIDGET"))
        {
            m_fidgetTime = 0.0f;
            unsigned int animation = m_pUnitModel->findRandomAnimation("FIDGET");
            m_pUnitModel->blendAnimation(animation, false, 0.2f, 1.0f, -1.0f);
            queueBlendAnimation("IDLE", true, 0.2f, 1.0f);
        }
    }
    if (m_pResourceManager->getGameClient()->getGameState() == 1 && m_pResourceManager->getGameUI())
    {
        int hp = HP();
        if (static_cast<float>(maxHP()) * 0.35f >= static_cast<float>(hp))
            m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(3));
        int mp = mana();
        if (static_cast<float>(maxMana()) * 0.2f >= static_cast<float>(mp))
            m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(4));
        if (m_Followers.size() && m_Followers[0]->isPetNearDeath())
            m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(11));
    }
    if (HP() <= 0 && m_pResourceManager->getGameUI())
    {
        if (m_pResourceManager->getGameClient()->getGameState() == 1)
        {
            m_deathDelay -= elapsed;
            if (m_deathDelay <= 0.0f)
            {
                m_pResourceManager->getGameUI()->toggleDeath();
                m_deathDelay = 999999.0f;
            }
            return;
        }
        m_currentOpacity = 0.4f;
        updateOpacity(0.0f, true);
        return;
    }
    if (m_playerTranslucent)
    {
        m_currentOpacity = 0.4f;
        updateOpacity(0.0f, true);
    }
}

#include "DynamicLine.h"
#include "Path.h"
#include <OgreSceneManager.h>
#include <cstring>

CPlayer::CPlayer(CResourceManager* resources)
    : CCharacter(resources), m_levelUpParticle(NULL), m_godMode(false), m_cheatMarker('N'),
      m_hasPortal(false), m_portalDepth(1), m_portalDungeon(EMPTY_WSTRING), m_returnDepth(0),
      m_returnDungeon(EMPTY_WSTRING), m_levelSaveSerial(0), m_playerTranslucent(false),
      m_saveOnDeath(false), m_followersEnabled(false), m_dungeonTrackers(5), m_loadedModNames(10)
{
    typedef char PlayerOpaqueExtents[(sizeof(m_Padding864) == 4 && sizeof(m_Padding870) == 20 &&
        sizeof(m_PaddingA10) == 4 && sizeof(m_PaddingA17) == 41 && sizeof(m_turnRate288) == 4) ? 1 : -1];
    m_fishingPole = NULL;
    m_fishingParticle = NULL;
    m_fishingPath = NULL;
    m_fishingLine = NULL;
    m_fishingLineNode = NULL;
    m_fishingTime = 2.0f;
    m_fishingValue854 = 0.0f;
    m_fishingDelay = 0.0f;
    m_fishingFlag = false;
    m_questManager = NULL;
    m_deathDelay = 10.0f;
    // These otherwise unused spans have exact zero stores in the original constructor.
    std::memset(m_Padding864, 0, sizeof(m_Padding864));
    std::memset(m_Padding870, 0, sizeof(m_Padding870));
    std::memset(m_PaddingA10, 0, sizeof(m_PaddingA10));
    std::memset(m_PaddingA17, 0, 34);
    m_maxHPBase = 2000;
    m_fHPFloat = 2000.0f;
    m_turnRate288 = 20.0f;
    m_iMeleeStat = 10;
    m_rangedStat = 0;
    m_magicStat = 3;
    m_defenseStat = 10;
    m_naturalArmor = 4;
    clearItemLinkMap();
    clearSkillMap();
    clearSkillFunctionMap();
    m_fishingPath = new CPath(EMPTY_STRING, false, Ogre::Vector3::ZERO);
    m_fishingLine = new CDynamicLine(static_cast<Ogre::RenderOperation::OperationType>(2));
    m_fishingPath->AddPoint(Ogre::Vector3::ZERO, -60.0f, 60.0f);
    m_fishingPath->AddPoint(Ogre::Vector3::ZERO, -60.0f, 60.0f);
    m_fishingPath->AddPoint(Ogre::Vector3::ZERO, -60.0f, 60.0f);
    for (unsigned int i = 0; i < 16; ++i)
        m_fishingLine->addPoint(0.0f, 0.0f, 0.0f);
    m_fishingLineNode = m_pResourceManager->getSceneManager()->getRootSceneNode()->createChildSceneNode(STRINGS::uniqueName("line_"));
    m_fishingLineNode->attachObject(m_fishingLine);
    m_fishingLineNode->setVisible(false, true);
    CCharacter::setAlignment(static_cast<EAlignment>(1));
    for (unsigned int i = 0; i < 18; ++i)
        m_journalPrefix[i] = 0;
    CFileSystem::getSingleton()->getEnabledModNames(&m_loadedModNames);
}

void CPlayer::applyAchievementsForKilledCharacter(CCharacter* character)
{
    if (character->HP() > 0)
        return;
    int difficulty = 1;
    if (m_pResourceManager && m_pResourceManager->getGameClientCount() && m_pResourceManager->getGameClient())
        difficulty = m_pResourceManager->getGameClient()->m_startDifficulty;
    bool hardcore = m_saveOnDeath;
    int deaths = m_journalStats[5];
    float played = m_playTime;
    int achievement = -1;
    if (STRINGS::StringUpper(character->getName()) == L"EMBERCOLOSSUS")
        achievement = 10;
    else if (STRINGS::StringUpper(character->getName()) == L"ALRIC_EVIL")
        achievement = 13;
    else if (STRINGS::StringUpper(character->getName()) != L"FIRSTHENCHMEN")
    {
        if (STRINGS::StringUpper(character->getName()) == L"LICH")
            achievement = 8;
        else if (STRINGS::StringUpper(character->getName()) == L"MEDEA")
            achievement = 12;
        else if (STRINGS::StringUpper(character->getName()) == L"BOSS1")
            achievement = 7;
        else if (STRINGS::StringUpper(character->getName()) == L"ROOTGOLEMBOSS")
            achievement = 9;
        else if (STRINGS::StringUpper(character->getName()) == L"LAVATROLLBOSS")
            achievement = 11;
    }
    if (achievement >= 0 && CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(achievement)))
    {
        CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(achievement))->forceComplete();
        return;
    }
    if (STRINGS::StringUpper(character->getName()) != L"ORDRAK")
        return;
    if (!deaths)
        CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(34))->forceComplete();
    switch (difficulty)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(14))->forceComplete();
        if (difficulty >= 2)
            CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(15))->forceComplete();
        if (difficulty >= 3)
            CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(16))->forceComplete();
        if (hardcore)
            CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(17 + difficulty))->forceComplete();
        break;
    }
    float hours = played / 3600.0f;
    if (hours <= 8.0f)
        CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(21))->forceComplete();
    if (hours <= 5.0f)
        CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(22))->forceComplete();
}

#include "OgreUtilities.h"
CPlayer::~CPlayer()
{
    if (m_fishingLineNode)
    {
        m_fishingLineNode->detachObject(m_fishingLine);
        OGRE_UTILITIES::removeChildFromParentNode(m_fishingLineNode);
    }
    if (m_fishingLine)
    {
        delete m_fishingLine;
        m_fishingLine = NULL;
    }
    if (m_fishingLineNode)
    {
        m_fishingLineNode->removeAllChildren();
        m_pResourceManager->getSceneManager()->destroySceneNode(m_fishingLineNode);
        m_fishingLineNode = NULL;
    }
    if (m_questManager)
        m_questManager->setPlayer(NULL);
    m_questManager = NULL;
    if (m_fishingPole)
    {
        Ogre::SceneNode* parent = m_fishingPole->getSceneNode()->getParentSceneNode();
        if (parent)
            parent->removeChild(m_fishingPole->getSceneNode());
    }
    if (m_fishingParticle)
        m_fishingParticle->setVisible(false);
    for (unsigned int i = 0; i < m_savedLevels.size(); ++i)
    {
        if (m_savedLevels[i])
        {
            delete m_savedLevels[i];
            m_savedLevels[i] = NULL;
        }
    }
    m_savedLevels.clear();
    m_dungeonTrackers.deleteAll();
    m_loadedModNames.clear();
    if (m_levelUpParticle)
    {
        delete m_levelUpParticle;
        m_levelUpParticle = NULL;
    }
    if (m_fishingPole)
    {
        delete m_fishingPole;
        m_fishingPole = NULL;
    }
    if (m_fishingParticle)
    {
        delete m_fishingParticle;
        m_fishingParticle = NULL;
    }
    if (m_fishingPath)
    {
        delete m_fishingPath;
        m_fishingPath = NULL;
    }
}

#include "StringTranslate.h"
void CPlayer::levelUp()
{
    CCharacter::levelUp();
    if (m_levelUpParticle)
    {
        Ogre::SceneNode* node = m_levelUpParticle->getSceneNode();
        Ogre::SceneNode* parent = node->getParentSceneNode();
        if (parent)
            parent->removeChild(m_levelUpParticle->getSceneNode());
        getSceneNode()->addChild(m_levelUpParticle->getSceneNode());
        m_levelUpParticle->setPosition(0.0f, -0.95f * m_fBaseUnitValue194, 0.0f);
        if (m_levelSound && !m_levelSound->bankPlaying(25))
            m_levelSound->playSample(25, getSceneNode(), 0.0f, 0.0f, false);
        m_levelUpParticle->Start();
        static std::wstring g_LevelUp;
        static std::wstring g_Level;
        static std::wstring g_Reached;
        if (g_LevelUp.empty())
            g_LevelUp = CStringTranslate::getSinglton()->getTranslateString(L"Level Up");
        if (g_Level.empty())
            g_Level = CStringTranslate::getSinglton()->getTranslateString(L"Level");
        if (g_Reached.empty())
            g_Reached = CStringTranslate::getSinglton()->getTranslateString(L"reached");
        m_pResourceManager->getGameUI()->setBigText(g_LevelUp + L"!", 2.0f);
        std::wstring level = STRINGS::GetValueAsWString(static_cast<int>(m_iUnitLevel));
        m_pResourceManager->getGameUI()->setSmallText(g_Level + L" " + level + L" " + g_Reached, 2.0f);
    }
    if (m_levelSound)
        m_levelSound->queueGlobalSample(60, 1.0f, 1.0f);
    if (m_pInventory)
        m_pInventory->refreshEquipped();
    m_pResourceManager->getGameUI()->queueTip(static_cast<EContextTip>(6));
    calculateMaxHP();
    calculateMaxMana();
    calculateNaturalArmor();
    m_fHPFloat = static_cast<float>(maxHP());
    m_fManaFloat = static_cast<float>(maxMana());
    if (m_pInventory)
        m_pInventory->forceRecalculationOfEquipmentStats();
    if (m_iUnitLevel > 64)
    {
        CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(24))->forceComplete();
        if (m_iUnitLevel > 99)
            CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(25))->forceComplete();
    }
}

#include "GameGlobals.h"
void CPlayer::updateStoredLevels(CLevel& level)
{
    if (static_cast<int>(m_savedLevels.size()) > CGameGlobals::getSingleton()->m_maxLevelMemory)
    {
        float oldestTime = 1000000.0f;
        int oldest = -1;
        for (unsigned int i = 0; i < m_savedLevels.size(); ++i)
        {
            bool questLevel = false;
            if (m_questManager)
            {
                for (int q = 0; q < static_cast<int>(m_questManager->m_Unknown18.size()); ++q)
                {
                    if (m_questManager->m_Unknown18[q]->getQuestDetails() != EMPTY_WSTRING &&
                        STRINGS::StringUpper(m_questManager->m_Unknown18[q]->m_pUnknown30) == m_savedLevels[i]->m_sLevelName &&
                        m_questManager->m_Unknown18[q]->m_iUnknown20 == m_savedLevels[i]->m_iLevelId)
                        questLevel = true;
                }
            }
            CLevelState* state = m_savedLevels[i];
            if (state->m_bUnknownB1 || questLevel || state->m_bUnknownB0)
                continue;
            if (state->m_iLevelId == level.getLevelDepth() && state->m_sLevelName == level.getDungeonName())
                continue;
            if (m_returnDepth == state->m_iLevelId && state->m_sLevelName == m_returnDungeon)
                continue;
            if (m_portalDepth == state->m_iLevelId && state->m_sLevelName == m_portalDungeon && m_hasPortal)
                continue;
            if (oldestTime > state->m_iStateVersion)
            {
                oldest = i;
                oldestTime = state->m_iStateVersion;
            }
        }
        if (oldest != -1)
            removeLevelSavedState(oldest);
    }
    for (int i = 0; i < static_cast<int>(m_savedLevels.size()); ++i)
    {
        CLevelState* state = m_savedLevels[i];
        bool returning = m_returnDepth == state->m_iLevelId && state->m_sLevelName == m_returnDungeon;
        returning = returning && state->m_iStateVersion != -1.0f;
        bool questLevel = false;
        if (m_questManager)
        {
            for (int q = 0; q < static_cast<int>(m_questManager->m_Unknown18.size()); ++q)
            {
                if (m_questManager->m_Unknown18[q]->getQuestDetails() != EMPTY_WSTRING &&
                    STRINGS::StringUpper(m_questManager->m_Unknown18[q]->m_pUnknown30) == m_savedLevels[i]->m_sLevelName &&
                    m_questManager->m_Unknown18[q]->m_iUnknown20 == m_savedLevels[i]->m_iLevelId)
                    questLevel = true;
            }
        }
        state = m_savedLevels[i];
        if (state->m_bUnknownB1)
            continue;
        if (!(m_playTime > state->m_iStateVersion + static_cast<float>(CGameGlobals::getSingleton()->m_levelRespawnTime)) &&
            state->m_iStateVersion != -1.0f)
            continue;
        if (state->m_iLevelId == level.getLevelDepth() && state->m_sLevelName == level.getDungeonName())
            continue;
        if (returning)
            continue;
        if (m_portalDepth == state->m_iLevelId && state->m_sLevelName == m_portalDungeon && m_hasPortal)
            continue;
        if (questLevel || state->m_bUnknownB0)
            continue;
        removeLevelSavedState(i);
        --i;
    }
}

#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
void CPlayer::updateFishingLine(float)
{
    m_fishingPath->Clear();
    Ogre::SkeletonInstance* skeleton = m_pUnitModel->m_pSkeleton;
    Ogre::Bone* bones[4];
    bones[0] = skeleton->getBone("tag_zfishpoleend");
    bones[1] = skeleton->getBone("tag_zfishcenter");
    bones[2] = skeleton->getBone("tag_zfishlure");
    bones[3] = skeleton->getBone("tag_zfishlureend");
    Ogre::Vector3 points[4];
    for (unsigned int i = 0; i < 4; ++i)
    {
        points[i] = m_pUnitModel->getPosition(false);
        points[i] += bones[i]->_getDerivedPosition();
        points[i] = getOrientation() * points[i];
        points[i] += getPosition(true);
    }
    if (m_targetItem.getObject())
        points[2].y = std::max(m_targetItem.getObject()->getPosition(true).y, points[2].y);
    for (unsigned int i = 0; i < 4; ++i)
        m_fishingPath->AddPoint(points[i], -60.0f, 60.0f);
    float step = m_fishingPath->m_fPathLength * 0.125f;
    for (unsigned int i = 0; i < 8; ++i)
    {
        m_fishingLine->setPoint(i * 2, m_fishingPath->GetSplinePositionAtDistance(static_cast<float>(i) * step));
        m_fishingLine->setPoint(i * 2 + 1, m_fishingPath->GetSplinePositionAtDistance(static_cast<float>(i + 1) * step));
    }
    m_fishingLine->update();
    m_fishingLineNode->needUpdate(false);
    if (m_fishingFlag)
    {
        m_fishingParticle->setVisible(true);
        m_fishingParticle->setPosition(points[3]);
        Ogre::Vector3 end = m_fishingPath->GetSplinePositionAtDistance(m_fishingPath->m_fPathLength);
        Ogre::Vector3 prior = m_fishingPath->GetSplinePositionAtDistance(m_fishingPath->m_fPathLength - 0.05f);
        Ogre::Vector3 direction = prior - end;
        direction.normalise();
        Ogre::Vector3 forward = getForward();
        Ogre::Vector3 right = forward.crossProduct(direction);
        forward = direction.crossProduct(right);
        m_fishingParticle->setOrientation(forward, direction);
    }
}

#include "UnitResourceList.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "SharedStash.h"
void CPlayer::unitInit(CDataGroup* data, bool initialize)
{
    CCharacter::unitInit(data, initialize);
    m_pInventory->addSection(static_cast<EINVENTORY_PANES>(1), 21);
    m_pInventory->addSection(static_cast<EINVENTORY_PANES>(2), 21);
    m_iMeleeStat = m_pDataGroup->GetDataValue(L"STRENGTH", 10);
    m_rangedStat = m_pDataGroup->GetDataValue(L"DEXTERITY", 10);
    m_magicStat = m_pDataGroup->GetDataValue(L"MAGIC", 10);
    m_defenseStat = m_pDataGroup->GetDataValue(L"DEFENSE", 10);
    m_manaGraph = m_pDataGroup->GetDataValue(L"MANA_GRAPH", L"MANA_PLAYER_DESTROYER");
    m_hpGraph = m_pDataGroup->GetDataValue(L"HEALTH_GRAPH", L"HEALTH_PLAYER_DESTROYER");
    m_statPointsGraph = m_pDataGroup->GetDataValue(L"STAT_POINTS_PER_LEVEL", L"STAT_POINTS_PER_LEVEL");
    m_skillPointsGraph = m_pDataGroup->GetDataValue(L"SKILL_POINTS_PER_LEVEL", L"SKILL_POINTS_PER_LEVEL");
    m_famePointsGraph = m_pDataGroup->GetDataValue(L"SKILL_POINTS_PER_FAME_LEVEL", L"SKILL_POINTS_PER_FAME_LEVEL");
    calculateMaxHP();
    m_fHPFloat = static_cast<float>(m_maxHPBase);
    calculateMaxMana();
    m_fManaFloat = static_cast<float>(m_maxManaBase);
    calculateNaturalArmor();
    m_levelUpParticle = m_pResourceManager->createParticle(L"PLAYER_LEVELUP");
    if (m_levelUpParticle)
    {
        m_levelUpParticle->sceneNodeSetParent(getSceneNode(), false);
        m_levelUpParticle->setPosition(Ogre::Vector3::ZERO);
    }
    if (m_pSkillManager)
    {
        m_activeSkill = m_pSkillManager->getSkillByIndex(0);
        if (m_activeSkill)
        {
            m_activeSkillGuid = m_activeSkill->getGuid();
            if (!m_activeSkill->getLevel() || m_activeSkill->getActivationType() == static_cast<ESKILL_ACTIVATION_TYPE>(4) ||
                !m_activeSkill->enabledWithoutProperty())
                cycleSkill(1);
        }
        else
            m_activeSkillGuid = -1;
        m_skillMap[2] = m_activeSkill ? m_activeSkill->getGuid() : -1;
        if (m_skillMap[2] != -1)
            m_leftSkillMap[2] = -1;
        m_leftSkillGuid = m_activeSkillGuid;
        for (int i = 0; i < m_pSkillManager->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0)); ++i)
        {
            CSkill* skill = m_pSkillManager->getSkillByIndex(i);
            if (skill && skill != m_activeSkill && skill->getActivationType() != static_cast<ESKILL_ACTIVATION_TYPE>(4) &&
                skill->enabledWithoutProperty() && skill->getLevel())
                m_leftSkillGuid = skill->getGuid();
        }
    }
    if (m_levelSound)
    {
        CSoundData* sound = CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation->getSoundDataObject(L"LEVELUP");
        if (sound)
            m_levelSound->addSample(25, sound->m_iGuid);
        CDataGroup* group = m_pResourceManager->getMasterResourceList()->getDataGroupByObjectName(L"ITEMS", L"Health Potion");
        if (group)
        {
            m_itemLinks[0] = m_pResourceManager->getUnitGuidByDataGroup(group, L"UNIT_GUID");
            m_leftSkillMap[0] = m_pResourceManager->getUnitGuidByDataGroup(group, L"UNIT_GUID");
            if (m_leftSkillMap[0] != -1)
                m_skillMap[0] = -1;
        }
        group = m_pResourceManager->getMasterResourceList()->getDataGroupByObjectName(L"ITEMS", L"Mana Potion");
        if (group)
        {
            m_itemLinks[1] = m_pResourceManager->getUnitGuidByDataGroup(group, L"UNIT_GUID");
            m_leftSkillMap[1] = m_pResourceManager->getUnitGuidByDataGroup(group, L"UNIT_GUID");
            if (m_leftSkillMap[1] != -1)
                m_skillMap[1] = -1;
        }
        group = m_pResourceManager->getMasterResourceList()->getDataGroupByObjectName(L"ITEMS", L"Town Portal Scroll");
        if (group)
        {
            m_leftSkillMap[9] = m_pResourceManager->getUnitGuidByDataGroup(group, L"UNIT_GUID");
            if (m_leftSkillMap[9] != -1)
                m_skillMap[9] = -1;
        }
        group = m_pResourceManager->getMasterResourceList()->getDataGroupByObjectName(L"ITEMS", L"Identify Scroll");
        if (group)
        {
            m_leftSkillMap[8] = m_pResourceManager->getUnitGuidByDataGroup(group, L"UNIT_GUID");
            if (m_leftSkillMap[8] != -1)
                m_skillMap[8] = -1;
        }
    }
    if (getUnitModel())
        static_cast<CGenericModel*>(getUnitModel())->m_animationStep = 0.01f;
    setQuestManager(CQuestManager::getSingleton());
    CSharedStash::getSingleton()->setPlayer(this);
}

void CPlayer::fishingAICatch(float, CLevel& level)
{
    if (m_pUnitModel->animationPlayingSubstring("FISHING_CATCH"))
        return;
    static std::wstring g_Fishing;
    static std::wstring g_CaughtNothing;
    static std::wstring g_Caught;
    static std::wstring g_CaughtContaining;
    if (g_Fishing.empty())
        g_Fishing = CStringTranslate::getSinglton()->getTranslateString(L"Fishing");
    if (g_CaughtNothing.empty())
        g_CaughtNothing = CStringTranslate::getSinglton()->getTranslateString(L"You caught nothing");
    if (g_Caught.empty())
        g_Caught = CStringTranslate::getSinglton()->getTranslateString(L"You caught a");
    if (g_CaughtContaining.empty())
        g_CaughtContaining = CStringTranslate::getSinglton()->getTranslateString(L"You caught a fish containing");
    if (m_fishingFlag)
    {
        std::wstring spawnName = level.getLevelTemplateData() ? level.getLevelTemplateData()->m_selectedUnitSpawners[6] : L"FISH_SPAWN";
        CSpawnClass* spawn = m_pResourceManager->getSpawnClassByName(spawnName);
        TArrayList<CBaseUnit*> units(10);
        m_pResourceManager->createUnitsBySpawnClass(spawn, units, 1, this, this, -1, 0);
        std::wstring name;
        bool fish = false;
        for (unsigned int i = 0; i < units.size(); ++i)
        {
            CEquipment* equipment = dynamic_cast<CEquipment*>(units[i]);
            if (!equipment)
                continue;
            name = equipment->getItemName();
            if (equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(124)))
                fish = true;
            if (m_pInventory && !m_pInventory->pickupEquipment(equipment, true))
            {
                level.addItem(equipment, m_vPosition, true);
                equipment->setPosition(m_vPosition);
                equipment->drop();
            }
        }
        if (fish)
            m_pResourceManager->getGameUI()->openModalDialog(g_Fishing, g_Caught + L" " + name + L"!", false);
        else
            m_pResourceManager->getGameUI()->openModalDialog(g_Fishing, g_CaughtContaining + L":\n" + name + L"!", false);
        incrementJournalStatistic(static_cast<EJournalStatistic>(14), 1);
    }
    else
        m_pResourceManager->getGameUI()->openModalDialog(g_Fishing, g_CaughtNothing + L"!", false);
    setAIState(static_cast<EAIState>(2));
    if (m_weaponsHidden)
    {
        m_weaponsHidden = false;
        if (m_pRightHandNode)
            m_pRightHandNode->setVisible(true, true);
        if (m_pLeftHandNode)
            m_pLeftHandNode->setVisible(true, true);
    }
}

#include "LogicNodeState.h"
#include "TriggerSphere.h"
#include "TriggerBox.h"
#include "PropertyNode.h"
#include "RandomGroup.h"
#include "Timeline.h"
#include "Counter.h"
#include "LogicTimer.h"
#include "OutputIncrementor.h"
#include "Teleport.h"
#include "AnimationPlayer.h"
#include "PuzzleRandomizer.h"
#include "UnitSpawner.h"

void CPlayer::storeLevelSavedState(CLevel& level)
{
    std::wstring name = level.m_sDungeonName;
    updateDungeonTracking(name, level.m_iLevelDepth);
    m_levelSaveSerial = std::max(m_levelSaveSerial, level.m_iLevelDepth);
    m_journalStats[2] = std::max(m_journalStats[2], m_levelSaveSerial);
    float previousTime = -1.0f;
    if (hasLevelSavedState(name, level.m_iLevelDepth))
        for (unsigned int i = 0; i < m_savedLevels.size(); ++i)
            if (m_savedLevels[i]->m_iLevelId == level.m_iLevelDepth &&
                m_savedLevels[i]->m_sLevelName == name)
            {
                previousTime = m_savedLevels[i]->m_iStateVersion;
                removeLevelSavedState(i);
                break;
            }
    CLevelState* saved = new CLevelState(level.m_iLevelDepth);
    saved->m_sLevelName = level.m_sDungeonName;
    saved->m_bUnknownB0 = level.m_pLevelTemplateData->isTown();
    m_savedLevels.push_back(saved);
    if (level.m_pLevelTemplateData && level.m_pLevelTemplateData->m_dontStore)
        saved->m_iStateVersion = -1.0f;
    else
        saved->m_iStateVersion = previousTime == -1.0f ? m_playTime : previousTime;
    saved->addFormations(&m_pResourceManager->getLevel()->m_formations, level);
    for (TLinkedListNode<CItem*>* node = level.m_items->getHead(); node; node = node->m_pNext)
    {
        CItem* item = node->m_Data;
        if (item->ISA(static_cast<UNITTYPES::EUNITTYPES>(29)) && item->m_bItemFlag218) continue;
        if (item->m_bBaseUnitFlag190) continue;
        if (item->getIsQuestUnit()) saved->m_bUnknownB1 = true;
        saved->addItem(*item);
    }
    for (int pass = 0; pass < 2; ++pass)
        for (TLinkedListNode<CCharacter*>* node = level.m_pCharacters->getHead(); node; node = node->m_pNext)
        {
            CCharacter* character = node->m_Data;
            if (character == this || character->m_pMaster == this || !character->alive() ||
                character->m_bBaseUnitFlag190) continue;
            if ((character->m_pMaster != NULL) == (pass != 0))
                saved->addCharacter(*character, level);
        }
    std::vector<CChunk*> chunks = level.m_chunks;
    for (unsigned int i = 0; i < chunks.size(); ++i)
        saved->m_lLevelStrings.push_back(chunks[i]->m_filename);
    if (level.m_automap) saved->addAutomap(level.m_automap);
    unsigned int roomCount = level.m_RoomScenes.size();
    for (unsigned int roomIndex = 0; roomIndex < roomCount; ++roomIndex)
    {
        CEditorScene* scene = level.m_RoomScenes[roomIndex];
        {
            TArrayList<CEditorBaseObject*> objects(10);
            scene->GetObjectsCreatedByADescriptor(L"Player Sphere Trigger", &objects);
            unsigned int count = objects.size();
            for (unsigned int i = 0; i < count; ++i)
            {
                CTriggerSphere* object = dynamic_cast<CTriggerSphere*>(objects[i]);
                if (!object) continue;
                CLogicNodeState* state = new CLogicNodeState();
                state->m_bActive = object->getEnabled();
                state->m_bEnabled = object->m_bActive;
                state->m_bFinished = object->m_bHasActivated;
                state->m_bFailed = object->m_bHasDeactivated;
                state->m_parentHierarchyHash = object->getParentHierarchyHashCode();
                state->m_wstrName = L"Player Sphere Trigger";
                state->m_position = object->getPosition(false);
                state->m_nCurrentState = roomIndex;
                state->m_guid = object->getOriginalGuid();
                CPositionableObject* parent = object->getParentPositionableObject();
                state->m_parentGuid = parent ? parent->getOriginalGuid() : -1;
                saved->addLogicState(state, level);
            }
        }
        {
            TArrayList<CEditorBaseObject*> objects(10);
            scene->GetObjectsCreatedByADescriptor(L"Player Box Trigger", &objects);
            unsigned int count = objects.size();
            for (unsigned int i = 0; i < count; ++i)
            {
                CTriggerBox* object = dynamic_cast<CTriggerBox*>(objects[i]);
                if (!object) continue;
                CLogicNodeState* state = new CLogicNodeState();
                state->m_bActive = object->getEnabled();
                state->m_bEnabled = object->m_bActive;
                state->m_bFinished = object->m_bHasActivated;
                state->m_bFailed = object->m_bHasDeactivated;
                state->m_parentHierarchyHash = object->getParentHierarchyHashCode();
                state->m_wstrName = L"Player Box Trigger";
                state->m_position = object->getPosition(false);
                state->m_nCurrentState = roomIndex;
                state->m_guid = object->getOriginalGuid();
                CPositionableObject* parent = object->getParentPositionableObject();
                state->m_parentGuid = parent ? parent->getOriginalGuid() : -1;
                saved->addLogicState(state, level);
            }
        }
        {
            TArrayList<CEditorBaseObject*> objects(10);
            scene->GetObjectsCreatedByADescriptor(L"Property Node", &objects);
            unsigned int count = objects.size();
            for (unsigned int i = 0; i < count; ++i)
            {
                CPropertyNode* object = dynamic_cast<CPropertyNode*>(objects[i]);
                if (!object) continue;
                CLogicNodeState* state = new CLogicNodeState();
                state->m_bActive = object->getEnabled();
                state->m_parentHierarchyHash = object->getParentHierarchyHashCode();
                state->m_wstrName = L"Property Node";
                state->m_position = object->getPosition(false);
                state->m_nCurrentState = roomIndex;
                state->m_guid = object->getOriginalGuid();
                CPositionableObject* parent = object->getParentPositionableObject();
                state->m_parentGuid = parent ? parent->getOriginalGuid() : -1;
                saved->addLogicState(state, level);
            }
        }
        {
            TArrayList<CEditorBaseObject*> objects(10);
            scene->GetObjectsCreatedByADescriptor(L"Group", &objects);
            unsigned int count = objects.size();
            for (unsigned int i = 0; i < count; ++i)
            {
                CRandomGroup* object = dynamic_cast<CRandomGroup*>(objects[i]);
                if (!object) continue;
                CLogicNodeState* state = new CLogicNodeState();
                state->m_bActive = object->getEnabled();
                state->m_bEnabled = object->getVisible();
                state->m_position = object->getPosition(false);
                state->m_parentHierarchyHash = object->getParentHierarchyHashCode();
                state->m_wstrName = L"Group";
                state->m_nCurrentState = roomIndex;
                state->m_guid = object->getOriginalGuid();
                CPositionableObject* parent = object->getParentPositionableObject();
                state->m_parentGuid = parent ? parent->getOriginalGuid() : -1;
                saved->addLogicState(state, level);
            }
        }
        {
            TArrayList<CEditorBaseObject*> objects(10);
            scene->GetObjectsCreatedByADescriptor(L"Timeline", &objects);
            unsigned int count = objects.size();
            for (unsigned int i = 0; i < count; ++i)
            {
                CTimeline* object = dynamic_cast<CTimeline*>(objects[i]);
                if (!object) continue;
                CLogicNodeState* state = new CLogicNodeState();
                state->m_value20 = object->m_fSetTimelineDuration <= 0.0f ? 1.0f : object->m_fTimelinePosition / object->m_fSetTimelineDuration;
                state->m_wstrName = L"Timeline";
                state->m_parentHierarchyHash = object->getParentHierarchyHashCode();
                state->m_bActive = object->m_bEnabled;
                state->m_nCurrentState = roomIndex;
                state->m_nStateFlags = object->m_bIsPlayingBackwards ? 0x3f800000u : 0;
                state->m_guid = object->getOriginalGuid();
                CPositionableObject* parent = object->getParentPositionableObject();
                state->m_parentGuid = parent ? parent->getOriginalGuid() : -1;
                state->m_bPersistent = !object->m_bTimelineWasStopped;
                saved->addLogicState(state, level);
            }
        }
        {
            TArrayList<CEditorBaseObject*> objects(10);
            scene->GetObjectsCreatedByADescriptor(L"Counter", &objects);
            unsigned int count = objects.size();
            for (unsigned int i = 0; i < count; ++i)
            {
                CCounter* object = dynamic_cast<CCounter*>(objects[i]);
                if (!object) continue;
                CLogicNodeState* state = new CLogicNodeState();
                state->m_value20 = static_cast<float>(object->m_iValue);
                state->m_bActive = object->getEnabled();
                state->m_parentHierarchyHash = object->getParentHierarchyHashCode();
                state->m_wstrName = L"Counter";
                state->m_nCurrentState = roomIndex;
                state->m_guid = object->getOriginalGuid();
                CPositionableObject* parent = object->getParentPositionableObject();
                state->m_parentGuid = parent ? parent->getOriginalGuid() : -1;
                saved->addLogicState(state, level);
            }
        }
        {
            TArrayList<CEditorBaseObject*> objects(10);
            scene->GetObjectsCreatedByADescriptor(L"Timer", &objects);
            unsigned int count = objects.size();
            for (unsigned int i = 0; i < count; ++i)
            {
                CLogicTimer* object = dynamic_cast<CLogicTimer*>(objects[i]);
                if (!object) continue;
                CLogicNodeState* state = new CLogicNodeState();
                state->m_nNodeId = object->m_iRepeatsLeft;
                state->m_value20 = object->getTimer();
                state->m_bActive = object->getEnabled();
                state->m_parentHierarchyHash = object->getParentHierarchyHashCode();
                state->m_wstrName = L"Timer";
                state->m_nCurrentState = roomIndex;
                state->m_guid = object->getOriginalGuid();
                CPositionableObject* parent = object->getParentPositionableObject();
                state->m_parentGuid = parent ? parent->getOriginalGuid() : -1;
                saved->addLogicState(state, level);
            }
        }
        {
            TArrayList<CEditorBaseObject*> objects(10);
            scene->GetObjectsCreatedByADescriptor(L"Output Incrementor", &objects);
            unsigned int count = objects.size();
            for (unsigned int i = 0; i < count; ++i)
            {
                COutputIncrementor* object = dynamic_cast<COutputIncrementor*>(objects[i]);
                if (!object) continue;
                CLogicNodeState* state = new CLogicNodeState();
                state->m_nNodeId = object->m_iCount;
                state->m_value20 = static_cast<float>(object->m_iRepeatsLeft);
                state->m_bActive = object->getEnabled();
                state->m_parentHierarchyHash = object->getParentHierarchyHashCode();
                state->m_wstrName = L"Output Incrementor";
                state->m_nCurrentState = roomIndex;
                state->m_guid = object->getOriginalGuid();
                CPositionableObject* parent = object->getParentPositionableObject();
                state->m_parentGuid = parent ? parent->getOriginalGuid() : -1;
                saved->addLogicState(state, level);
            }
        }
        {
            TArrayList<CEditorBaseObject*> objects(10);
            scene->GetObjectsCreatedByADescriptor(L"Teleport", &objects);
            unsigned int count = objects.size();
            for (unsigned int i = 0; i < count; ++i)
            {
                CTeleport* object = dynamic_cast<CTeleport*>(objects[i]);
                if (!object) continue;
                CLogicNodeState* state = new CLogicNodeState();
                state->m_bActive = object->getEnabled();
                state->m_parentHierarchyHash = object->getParentHierarchyHashCode();
                state->m_wstrName = L"Teleport";
                state->m_nCurrentState = roomIndex;
                state->m_guid = object->getOriginalGuid();
                CPositionableObject* parent = object->getParentPositionableObject();
                state->m_parentGuid = parent ? parent->getOriginalGuid() : -1;
                saved->addLogicState(state, level);
            }
        }
        {
            TArrayList<CEditorBaseObject*> objects(10);
            scene->GetObjectsCreatedByADescriptor(L"Animation Controller", &objects);
            unsigned int count = objects.size();
            for (unsigned int i = 0; i < count; ++i)
            {
                CAnimationPlayer* object = dynamic_cast<CAnimationPlayer*>(objects[i]);
                if (!object) continue;
                CLogicNodeState* state = new CLogicNodeState();
                state->m_nCurrentState = roomIndex;
                state->m_bActive = object->m_bAnimationPlaying;
                state->m_parentHierarchyHash = object->getParentHierarchyHashCode();
                state->m_wstrName = L"Animation Controller";
                state->m_guid = object->getOriginalGuid();
                CPositionableObject* parent = object->getParentPositionableObject();
                state->m_parentGuid = parent ? parent->getOriginalGuid() : -1;
                state->m_bPersistent = object->m_bLoop;
                std::memcpy(&state->m_nStateVersion, &object->m_fForceDuration, sizeof(state->m_nStateVersion));
                saved->addLogicState(state, level);
            }
        }
        {
            TArrayList<CEditorBaseObject*> objects(10);
            scene->GetObjectsCreatedByADescriptor(L"Puzzle Input", &objects);
            unsigned int count = objects.size();
            for (unsigned int i = 0; i < count; ++i)
            {
                CPuzzleRandomizer* object = dynamic_cast<CPuzzleRandomizer*>(objects[i]);
                if (!object) continue;
                CLogicNodeState* state = new CLogicNodeState();
                state->m_bActive = object->getEnabled();
                state->m_parentHierarchyHash = object->getParentHierarchyHashCode();
                state->m_wstrName = L"Puzzle Input";
                state->m_nCurrentState = roomIndex;
                state->m_guid = object->getOriginalGuid();
                CPositionableObject* parent = object->getParentPositionableObject();
                state->m_parentGuid = parent ? parent->getOriginalGuid() : -1;
                saved->addLogicState(state, level);
            }
        }
        {
            TArrayList<CEditorBaseObject*> objects(10);
            scene->GetObjectsCreatedByADescriptor(L"Unit Spawner", &objects);
            unsigned int count = objects.size();
            for (unsigned int i = 0; i < count; ++i)
            {
                CUnitSpawner* object = dynamic_cast<CUnitSpawner*>(objects[i]);
                if (!object) continue;
                CLogicNodeState* state = new CLogicNodeState();
                state->m_bActive = object->m_spawning;
                state->m_value20 = static_cast<float>(static_cast<unsigned int>(object->m_reset18c));
                state->m_nStateFlags = object->m_reset188;
                state->m_parentHierarchyHash = object->getParentHierarchyHashCode();
                state->m_wstrName = L"Unit Spawner";
                state->m_nCurrentState = roomIndex;
                state->m_guid = object->getOriginalGuid();
                CPositionableObject* parent = object->getParentPositionableObject();
                state->m_parentGuid = parent ? parent->getOriginalGuid() : -1;
                saved->addLogicState(state, level);
            }
        }
    }
    updateStoredLevels(level);
}
