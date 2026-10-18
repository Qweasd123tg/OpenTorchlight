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
