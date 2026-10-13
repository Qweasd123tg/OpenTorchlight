#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "QuestUnitData.h"
#include "BaseUnit.h"
#include "DataGroup.h"
#include "Level.h"
#include "Quest.h"
#include "ResourceManager.h"
#include "RunicCore.h"
#include "CollisionList.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"
#include "StringUtilities.h"
#include "UnitTypes.h"

bool CQuestUnitData::isComplete(bool includeChildren)
{
    if (!m_completed)
        return false;

    if (!includeChildren && m_children.size() != 0)
    {
        for (int i = 0; i < m_children.size(); ++i)
        {
            if (!m_children[i]->isComplete(false))
                return false;
        }
    }

    return true;
}

void CQuestUnitData::save(_IO_FILE* file)
{
    bool value = isComplete(false);
    fwrite(&value, sizeof(bool), 1, file);

    value = m_trackUnitEvents;
    fwrite(&value, sizeof(bool), 1, file);

    int spawnFromUnitType = *reinterpret_cast<const int*>(
        reinterpret_cast<const char*>(&m_spawnFromUnitType) - 8);
    fwrite(&spawnFromUnitType, sizeof(int), 1, file);

    fwrite(reinterpret_cast<const void*>(
        reinterpret_cast<const char*>(&m_unitType) - 8), sizeof(int), 1, file);

    int quest = *reinterpret_cast<const int*>(
        reinterpret_cast<const char*>(&m_pQuest) - 8);
    fwrite(&quest, sizeof(int), 1, file);

    fwrite(reinterpret_cast<const void*>(
        reinterpret_cast<const char*>(&m_requiredUnitCount) - 8),
        sizeof(int) * 2, 1, file);

    unsigned int childCount = m_children.size();
    fwrite(&childCount, sizeof(childCount), 1, file);

    if (childCount != 0)
    {
        for (unsigned int i = 0; i < m_children.size(); ++i)
            m_children[i]->save(file);
    }
}

void CQuestUnitData::spawnChildrenUnits(CResourceManager* resourceManager,
                                        Ogre::Vector3 const& position)
{
    CLevel* level = resourceManager != NULL ? resourceManager->getLevel() : NULL;
    if (level == NULL || m_children.size() == 0)
        return;

    for (unsigned int i = 0; i < m_children.size(); ++i)
    {
        float radius = i * 0.5f;
        if (radius < 1.0f)
            radius = 1.0f;

        Ogre::Vector3 spawnPosition =
            level->randomOpenPosition(position, radius, false);
        spawnPosition.y += 1.5f;

        m_children[i]->spawnUnit(resourceManager, spawnPosition);
        m_children[i]->m_trackUnitEvents = true;
    }
}

CQuestUnitData::CQuestUnitData(CQuest* quest)
    : CRunicCore(),
      m_questUnitDataId(m_gQuestUnitDataID++),
      m_pQuest(quest),
      m_pBaseUnitDataGroup(NULL),
      m_pQuestDataGroup(NULL),
      m_baseUnitGuid(-1),
      m_requiredUnitCount(1),
      m_currentUnitCount(0),
      m_spawnFromUnitType(22),
      m_unitType(22),
      m_children(10),
      m_completed(false),
      m_makeChampion(false),
      m_createUnit(true),
      m_removeFromInventory(true),
      m_removeOnlyQuestItems(true),
      m_displayName(),
      m_uniqueUnitName(EMPTY_WSTRING),
      m_spawnClass(),
      m_itemName(),
      m_monsterName(),
      m_unitTypeName(),
      m_spawnFromUnitTypeName(),
      m_relativeFloor(0),
      m_specificFloor(-1),
      m_minCount(1),
      m_maxCount(1),
      m_spawnClassPreset(0),
      m_unitSearchMode(0),
      m_neverDestroy(true),
      m_trackUnitEvents(false),
      m_generatedChampionName()
{
}

bool CQuestUnitData::getIsRandom()
{
    if (m_minCount != m_maxCount || !m_spawnClass.empty())
        return true;

    for (unsigned int i = 0; i < m_children.size(); i++)
        if (m_children[i]->getIsRandom())
            return true;

    return false;
}

bool CQuestUnitData::parseDataGroup(CDataGroup* dataGroup, CDataGroup* questDataGroup)
{
    if (dataGroup == NULL)
        return false;

    m_removeFromInventory = dataGroup->GetDataValue(L"REMOVEFROMINVENTORY", true);
    m_relativeFloor = dataGroup->GetDataValue(L"RELATIVEFLOOR", 0);
    m_specificFloor = dataGroup->GetDataValue(L"SPECIFICFLOOR", -1);

    m_pQuestDataGroup = questDataGroup;
    m_pBaseUnitDataGroup = NULL;

    m_spawnClass = STRINGS::StringUpper(
        dataGroup->GetDataValue(L"SPAWNCLASS", EMPTY_WSTRING));
    m_itemName = dataGroup->GetDataValue(L"ITEM", EMPTY_WSTRING);
    m_monsterName = dataGroup->GetDataValue(L"MONSTER", EMPTY_WSTRING);
    m_unitTypeName = dataGroup->GetDataValue(L"UNITTYPE", EMPTY_WSTRING);
    m_neverDestroy = dataGroup->GetDataValue(L"NEVERDESTROY", true);
    m_spawnFromUnitTypeName = dataGroup->GetDataValue(
        L"SPAWNFROMUNITTYPE", EMPTY_WSTRING);
    m_uniqueUnitName = dataGroup->GetDataValue(
        L"UNIQUE_MONSTER_NAME", EMPTY_WSTRING);
    m_removeOnlyQuestItems = dataGroup->GetDataValue(
        L"REMOVE_ONLY_QUESTITEMS", true);

    m_minCount = dataGroup->GetDataValue(L"MINCOUNT", 0);
    if (m_minCount < 1)
        m_minCount = 1;

    m_maxCount = dataGroup->GetDataValue(L"MAXCOUNT", m_minCount);
    if (m_maxCount < m_minCount)
        m_maxCount = m_minCount;

    m_createUnit = dataGroup->GetDataValue(L"CREATE", true);
    m_makeChampion = dataGroup->GetDataValue(L"MAKECHAMPION", m_makeChampion);

    return true;
}

bool CQuestUnitData::unitInteracted(CBaseUnit* unit)
{
    if (unit == NULL || unit->getLevel() == NULL)
        return false;

    if (m_pBaseUnitDataGroup == NULL)
        m_pBaseUnitDataGroup = getBaseUnitDataGroup();

    const UNITTYPES::EUNITTYPES unitType =
        static_cast<UNITTYPES::EUNITTYPES>(m_unitType);

    bool matchesUnit =
        m_pBaseUnitDataGroup == unit->getDataGroup() ||
        unit->ISA(unitType);

    bool belongsToQuest = m_unitType != 22 &&
        unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_unitType));

    if (!belongsToQuest)
    {
        const unsigned long long unitQuestId =
            *reinterpret_cast<const unsigned long long*>(
                reinterpret_cast<const unsigned char*>(unit) + 0x170);
        const unsigned long long questId =
            *reinterpret_cast<const unsigned long long*>(
                reinterpret_cast<const unsigned char*>(m_pQuest) + 0x1c8);
        const unsigned int unitBaseUnitId =
            *reinterpret_cast<const unsigned int*>(
                reinterpret_cast<const unsigned char*>(unit) + 0x178);

        belongsToQuest =
            unitQuestId == questId &&
            unitBaseUnitId == static_cast<unsigned int>(m_questUnitDataId);
    }

    if (!m_completed && matchesUnit)
    {
        m_currentUnitCount = static_cast<int>(
            static_cast<unsigned int>(m_currentUnitCount) + 1u);

        if (static_cast<unsigned int>(m_currentUnitCount) >=
            static_cast<unsigned int>(m_requiredUnitCount))
        {
            spawnChildrenUnits(unit->getResourceManager(),
                               unit->getPosition(true));
            m_completed = true;
            return true;
        }
    }
    else if (m_completed && !belongsToQuest && m_children.size() != 0)
    {
        for (unsigned int i = 0; i < m_children.size(); ++i)
        {
            if (m_children[i]->unitInteracted(unit))
                return true;
        }
    }

    return false;
}

std::wstring CQuestUnitData::getUnitName()
{
    m_pBaseUnitDataGroup = getBaseUnitDataGroup();

    if (!m_generatedChampionName.empty())
        return m_generatedChampionName;

    if (m_unitType != 22 || m_pBaseUnitDataGroup == NULL)
        return m_displayName;

    std::wstring name = m_pBaseUnitDataGroup->GetDataValue(L"DISPLAYNAME", EMPTY_WSTRING);
    if (name.empty())
        name = m_pBaseUnitDataGroup->GetDataValue(L"NAME", EMPTY_WSTRING);

    int begin = name.find(L"{");
    int end = name.find(L"}", begin);
    if (begin != -1 && end != -1 && end > begin + 1)
        name.replace(begin, end - begin + 1, L"");

    return name;
}

#include "GameClient.h"
#include "GameUI.h"

bool CQuestUnitData::unitDefeated(CBaseUnit* unit)
{
    if (!m_trackUnitEvents)
        return false;

    if (m_pBaseUnitDataGroup == NULL)
        m_pBaseUnitDataGroup = getBaseUnitDataGroup();

    const UNITTYPES::EUNITTYPES type =
        static_cast<UNITTYPES::EUNITTYPES>(m_unitType);
    bool matches = m_pBaseUnitDataGroup == unit->getDataGroup() || unit->ISA(type);
    bool belongsToQuest;
    if (m_unitType != 22 &&
        unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_unitType)))
        belongsToQuest = true;
    else
        belongsToQuest = unit->getQuestGuid() == m_pQuest->m_iUnknown1C8 &&
            unit->m_iQuestState == m_questUnitDataId;

    if (m_spawnFromUnitType == 22 && m_createUnit)
        matches = belongsToQuest;

    if (!m_completed && matches)
    {
        // The original uses a wrapping 32-bit count and unsigned completion test.
        m_currentUnitCount = static_cast<int>(
            static_cast<unsigned int>(m_currentUnitCount) + 1u);

        CResourceManager* resources = unit->getResourceManager();
        CLevel* level = resources != NULL ? resources->getLevel() : NULL;
        if (level != NULL && m_pQuest != NULL &&
            unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(25)))
        {
            CCharacter* character = dynamic_cast<CCharacter*>(unit);
            if (character != NULL)
            {
                level->m_pGameClient->getGameUI()->setBigText(
                    m_pQuest->replaceStringTags(m_pQuest->m_sUnknown58), 1.0f);
                level->m_pGameClient->getGameUI()->setSmallText(
                    character->m_characterDisplayName + L" - " +
                    STRINGS::GetValueAsWString(static_cast<unsigned int>(m_currentUnitCount)) +
                    L"/" +
                    STRINGS::GetValueAsWString(static_cast<unsigned int>(m_requiredUnitCount)) +
                    L" Defeated", 1.0f);
            }
        }

        if (static_cast<unsigned int>(m_currentUnitCount) >=
            static_cast<unsigned int>(m_requiredUnitCount))
        {
            spawnChildrenUnits(unit->getResourceManager(), unit->getPosition(true));
            m_completed = true;
            return true;
        }
    }
    else if (m_completed && !matches && m_children.size() != 0)
    {
        for (unsigned int i = 0; i < m_children.size(); ++i)
            if (m_children[i]->unitDefeated(unit))
                return true;
    }

    return false;
}

#include "Equipment.h"
#include "StringTranslate.h"

bool CQuestUnitData::unitPickedUp(CBaseUnit* unit)
{
    if (!m_trackUnitEvents)
        return false;

    if (m_unitSearchMode == 0)
    {
        if (m_completed && unit->getQuestGuid() == m_pQuest->m_iUnknown1C8)
            for (unsigned int i = 0; i < m_children.size(); ++i)
                if (m_children[i]->unitPickedUp(unit))
                    return true;
        return false;
    }

    if (m_pBaseUnitDataGroup == NULL)
        m_pBaseUnitDataGroup = getBaseUnitDataGroup();
    if (unit->getQuestGuid() != -1 &&
        unit->getQuestGuid() != m_pQuest->m_iUnknown1C8)
        return false;

    const bool matches = m_pBaseUnitDataGroup == unit->getDataGroup();
    bool belongsToQuest;
    if (m_unitType != 22 &&
        unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_unitType)))
        belongsToQuest = true;
    else
        belongsToQuest = unit->getQuestGuid() == m_pQuest->m_iUnknown1C8 &&
            unit->m_iQuestState == m_questUnitDataId;

    const bool wasCompleted = m_completed;
    bool pickedUp = false;
    if ((!m_createUnit || (!wasCompleted && belongsToQuest)) && matches)
    {
        unit->m_iQuestGuid = m_pQuest->m_iUnknown1C8;
        m_currentUnitCount = static_cast<int>(
            static_cast<unsigned int>(m_currentUnitCount) + 1u);
        pickedUp = true;
    }

    if (!wasCompleted && static_cast<unsigned int>(m_currentUnitCount) >=
        static_cast<unsigned int>(m_requiredUnitCount))
        m_completed = true;
    if (static_cast<unsigned int>(m_currentUnitCount) >
        static_cast<unsigned int>(m_requiredUnitCount))
        m_currentUnitCount = m_requiredUnitCount;

    if (!wasCompleted && pickedUp)
    {
        CResourceManager* resources = unit->getResourceManager();
        CLevel* level = resources != NULL ? resources->getLevel() : NULL;
        if (level != NULL && m_pQuest != NULL &&
            unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(2)))
        {
            CEquipment* item = dynamic_cast<CEquipment*>(unit);
            if (item != NULL && !m_pQuest->m_bUnknown209)
            {
                static std::wstring g_Found;
                if (g_Found.empty())
                    g_Found = CStringTranslate::getSinglton()->getTranslateString(L"Found");
                level->m_pGameClient->getGameUI()->setBigText(
                    m_pQuest->replaceStringTags(m_pQuest->m_sUnknown58), 1.0f);
                level->m_pGameClient->getGameUI()->setSmallText(
                    item->getItemName() + L" - " +
                    STRINGS::GetValueAsWString(static_cast<unsigned int>(m_currentUnitCount)) +
                    L"/" +
                    STRINGS::GetValueAsWString(static_cast<unsigned int>(m_requiredUnitCount)) +
                    L" " + g_Found, 1.0f);
            }
        }
    }

    if (m_completed)
    {
        if (!pickedUp && unit->getQuestGuid() == m_pQuest->m_iUnknown1C8 &&
            m_children.size() != 0)
        {
            for (unsigned int i = 0; i < m_children.size(); ++i)
                if (m_children[i]->unitPickedUp(unit))
                    return true;
            // Child callbacks may empty the list or clear completion.
            if (m_children.size() != 0 || !m_completed)
                return pickedUp;
        }
        if (!wasCompleted)
            spawnChildrenUnits(unit->getResourceManager(), unit->getPosition(true));
    }
    return pickedUp;
}

#include "PropertyNode.h"
#include "Utilities.h"

CPositionableObject* CQuestUnitData::createUnit(CLevel* level)
{
    if (!m_createUnit || level == NULL)
        return NULL;

    TArrayList<CPropertyNode*>* nodes = NULL;
    if (m_unitSearchMode == 0)
        nodes = &level->m_propertyNodesF0;
    else if (m_unitSearchMode == 1)
        nodes = &level->m_propertyNodes108;

    if (nodes != NULL && nodes->size() != 0)
    {
        const unsigned int index = static_cast<unsigned int>(
            UTILITIES::randomBetween(1.0f, static_cast<float>(nodes->size())) - 1.0f);
        CBaseUnit* unit = spawnUnit(m_pQuest->m_pResourceManager,
                                    (*nodes)[index]->getPosition(true));
        if (unit != NULL)
        {
            unit->setOrientation((*nodes)[index]->getOrientationQuaternion());
            CCharacter* character = dynamic_cast<CCharacter*>(unit);
            if (character != NULL)
            {
                m_pQuest->m_pQuestManager->calculateNPCIcon(character);
                if (m_uniqueUnitName != EMPTY_WSTRING)
                    character->m_characterDisplayName = std::wstring(m_uniqueUnitName);
                character->dropToGround(*level, 4.0f, false);
            }
            else
            {
                CItem* item = dynamic_cast<CItem*>(unit);
                if (item != NULL)
                    item->snapToGround();
            }
        }
        return unit;
    }

    TArrayList<CBaseUnit*> units(10);
    level->getUnitsByUnitType(static_cast<UNITTYPES::EUNITTYPES>(0), units);
    CBaseUnit* unit = units[UTILITIES::randomIntegerBetween(0, units.size() - 1)];
    if (unit != NULL)
    {
        Ogre::Vector3 position = unit->getLevel()->randomOpenPosition(
            unit->getPosition(true), 10.0f, false);
        int attempts = 0;
        float radius = 10.0f;
        while (unit->getLevel()->isInNoSpawnRegion(position, 0.0f) && attempts != 41)
        {
            unit = units[UTILITIES::randomIntegerBetween(0, units.size() - 1)];
            position = unit->getLevel()->randomOpenPosition(
                unit->getPosition(true), radius, false);
            ++attempts;
            radius += 0.25f;
        }
        spawnUnit(unit->getResourceManager(), position);
    }
    return unit;
}

#include <OgreLogManager.h>

void CQuestUnitData::populate(CLevel* level)
{
    if (level == NULL)
        return;

    CQuest* quest = m_pQuest;
    if (quest->m_pUnknown30 == EMPTY_WSTRING)
        m_createUnit = false;

    int floor = m_specificFloor;
    if (m_relativeFloor != 0)
    {
        // The original adds in 32 bits and falls back on a negative result.
        floor = static_cast<int>(static_cast<unsigned int>(quest->m_iUnknown20) +
                                 static_cast<unsigned int>(m_relativeFloor));
        if (floor < 0)
            floor = quest->m_iUnknown20;
    }
    else if (floor == -1)
        floor = quest->m_iUnknown20;

    if (!(level->m_iLevelDepth == floor &&
          level->m_sDungeonName == quest->m_pUnknown30))
    {
        if (m_createUnit || m_relativeFloor != 0 || m_specificFloor > 0 ||
            !(quest->m_pUnknown30 == EMPTY_WSTRING ||
              level->m_sDungeonName == m_pQuest->m_pUnknown30))
            return;
    }

    if (m_pBaseUnitDataGroup == NULL)
    {
        for (unsigned int attempt = 0; attempt < 5; ++attempt)
        {
            m_pBaseUnitDataGroup = getBaseUnitDataGroup();
            if (m_pBaseUnitDataGroup != NULL)
                break;
        }
        if (m_pBaseUnitDataGroup == NULL)
        {
            std::string message = "Unable to spawn unit for quest " +
                STRINGS::StringConvertToNarrow(m_pQuest->m_sUnknown50.c_str());
            Ogre::LogManager::getSingleton().logMessage(
                std::string(message.c_str()), Ogre::LML_CRITICAL, false);
            m_completed = true;
            m_trackUnitEvents = true;
            return;
        }
    }

    if (!m_pQuest->m_questAccepted &&
        m_pQuest->m_pQuestManager->getQuestComplete(m_pQuest->m_sUnknown50) &&
        !m_neverDestroy)
    {
        CBaseUnit* unit = level->getBaseUnitByDataGroup(m_pBaseUnitDataGroup);
        if (unit != NULL)
        {
            level->removeUnit(unit, true);
            delete unit;
        }
    }

    if (m_completed || !m_pQuest->m_questAccepted || m_trackUnitEvents)
        return;
    m_trackUnitEvents = true;
    if (m_unitType != 22)
        return;

    if (m_spawnFromUnitType == 22)
    {
        unsigned int count = 0;
        while (count < static_cast<unsigned int>(m_requiredUnitCount))
        {
            ++count;
            createUnit(level);
        }
        return;
    }

    TArrayList<CBaseUnit*> units(10);
    level->getUnitsByUnitType(static_cast<UNITTYPES::EUNITTYPES>(m_spawnFromUnitType), units);
    if (units.size() == 0)
    {
        std::string message = "No units found for quest : \n" +
            STRINGS::StringConvertToNarrow(m_pQuest->m_sUnknown50.c_str());
        Ogre::LogManager::getSingleton().logMessage(
            std::string(message.c_str()), Ogre::LML_CRITICAL, false);
        return;
    }

    while (units.size() != 0)
    {
        const unsigned int index = UTILITIES::randomIntegerBetween(0, units.size() - 1);
        CBaseUnit* unit = units[index];
        units.removeAt(index);
        if (unit->m_iQuestGuid == -1)
            continue;

        unit->m_iQuestGuid = m_pQuest->m_iUnknown1C8;
        unit->m_iQuestState = m_questUnitDataId;
        CCharacter* character = dynamic_cast<CCharacter*>(unit);
        if (character != NULL)
            m_pQuest->m_pQuestManager->calculateNPCIcon(character);
        CEquipment* equipment = dynamic_cast<CEquipment*>(unit);
        if (equipment != NULL)
        {
            equipment->m_bUnknown348 = true;
            equipment->destroyItemText();
            equipment->destroyItemText();
        }
        break;
    }
}
