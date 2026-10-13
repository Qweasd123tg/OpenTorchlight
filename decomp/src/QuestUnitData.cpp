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
