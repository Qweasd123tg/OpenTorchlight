#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "QuestRequirements.h"
#include "DataGroup.h"
#include "DataValue.h"
#include "StringUtilities.h"
#include "TArrayList.h"

long long CQuestRequirements::parseRequirementTag(CDataGroup* dataGroup)
{
    m_pDataGroup = dataGroup;
    if (dataGroup != NULL)
    {
        m_iUnknown20 = m_pDataGroup->GetDataValue(L"MINPLAYERLEVEL", ~0u);
        m_iUnknown24 = m_pDataGroup->GetDataValue(L"MAXPLAYERLEVEL", ~0u);
        m_iUnknown28 = m_pDataGroup->GetDataValue(L"MINDUNGEONDEPTH", ~0u);
        m_iUnknown2C = m_pDataGroup->GetDataValue(L"MAXDUNGEONDEPTH", ~0u);
        m_pUnknown30.assign(STRINGS::StringUpper(m_pDataGroup->GetDataValue(L"RULESET", EMPTY_WSTRING)));
        const std::wstring* requirementNames = reinterpret_cast<const std::wstring*>(gQUEST_REQUIREMENTS);
        for (int i = 0; i < 3; ++i)
        {
            CDataGroup* group = dataGroup->GetDataGroupByName(requirementNames[i], false);
            TArrayList<std::wstring>* requirements = m_Unknown38[i];
            if (group != NULL && requirements != NULL)
                for (unsigned int j = 0; j < group->GetNumberOfDataValues(); ++j)
                {
                    CDataValue::EDATAVALUETYPES type = group->GetDataValue(j)->GetValueType();
                    if (type == CDataValue::DATAVALUE_TRANSLATE || type == CDataValue::DATAVALUE_STRING)
                        requirements->add(STRINGS::StringUpper(group->GetDataValue(j)->GetValueAsString()));
                }
        }
    }
    return 1;
}

#include "Quest.h"
#include "QuestManager.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Dungeon.h"
#include "LevelTemplateData.h"

CQuestRequirements::CQuestRequirements(CQuest* quest)
    : m_pDataGroup(NULL), m_pQuest(quest), m_iUnknown20(0), m_iUnknown24(999999),
      m_iUnknown28(0), m_iUnknown2C(999999), m_pUnknown30(EMPTY_WSTRING), m_Unknown38(1)
{
    for (unsigned int i = 0; i < 3; ++i)
        m_Unknown38.add(new TArrayList<std::wstring>(1));
}

CQuestRequirements::~CQuestRequirements()
{
    m_Unknown38.deleteAll();
    m_pDataGroup = NULL;
}

char CQuestRequirements::questRequirmentsHaveBeenMet()
{
    if (m_pQuest != NULL && m_pQuest->m_pQuestManager->getQuestComplete(m_pQuest->m_sUnknown50))
        return false;
    if (m_pDataGroup == NULL)
        return true;
    if (m_pQuest == NULL)
        return false;
    CPlayer* player = m_pQuest->getPlayer();
    if (player == NULL || m_pQuest->m_pQuestManager == NULL)
        return false;
    CQuestManager* manager = m_pQuest->m_pQuestManager;
    if (m_iUnknown20 != -1 && (player->m_iUnitLevel < static_cast<unsigned int>(m_iUnknown20) ||
                             player->m_iUnitLevel > static_cast<unsigned int>(m_iUnknown24)))
        return false;
    for (unsigned int i = 0; i < m_Unknown38[0]->size(); ++i)
        if (!manager->getQuestComplete((*m_Unknown38[0])[i]) && (*m_Unknown38[0])[i] != m_pQuest->m_sUnknown50)
            return false;
    for (unsigned int i = 0; i < m_Unknown38[1]->size(); ++i)
        if (manager->getQuestComplete((*m_Unknown38[1])[i]) && (*m_Unknown38[1])[i] != m_pQuest->m_sUnknown50)
            return false;
    for (unsigned int i = 0; i < m_Unknown38[2]->size(); ++i)
        if (!manager->getQuestIsActive((*m_Unknown38[2])[i]))
            return false;
    if (player->getResourceManager() == NULL || player->getResourceManager()->getLevel() == NULL)
        return false;
    std::wstring dungeonName = m_pQuest->m_pUnknown30;
    if (dungeonName.empty())
        dungeonName = L"MAIN";
    CDungeon* dungeon = m_pQuest->m_pResourceManager->getDungeonByName(dungeonName);
    if (dungeon == NULL)
        return false;
    int depth = static_cast<int>(static_cast<unsigned int>(player->getMaxDepth(dungeonName)) + 1u);
    if (depth < 0)
        depth = 0;
    CResourceManager* resources = m_pQuest->m_pResourceManager;
    CGameClient* client = resources->getGameClient();
    CLevelTemplateData* levelTemplate = dungeon->getLevelTemplateDataForDepth(client, depth);
    if (levelTemplate == NULL || (!m_pUnknown30.empty() && m_pUnknown30 != levelTemplate->m_name))
        return false;
    if (m_iUnknown28 != -1 && (depth < m_iUnknown28 || depth > m_iUnknown2C))
        return false;
    return true;
}
