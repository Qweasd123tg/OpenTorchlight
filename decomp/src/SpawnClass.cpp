#include "SpawnClass.h"
#include "SpawnClassData.h"

CSpawnClass::CSpawnClass(const wchar_t* name)
    : m_entries(2), m_name(name), m_iUnknown30(0)
{
}

int CSpawnClass::calculateNumberOfChoices(CCharacter* character, int minimumLevel, int levelOffset, int rarityOverride, int flags)
{
    int count = 0;
    for (unsigned int i = 0; i < m_entries.size(); ++i)
        count += m_entries[i]->spawnClassData->calculateChoices(character, minimumLevel, levelOffset, rarityOverride, flags);
    return count;
}

CSpawnClass::~CSpawnClass()
{
    for (unsigned int i = 0; i < m_entries.size(); ++i)
    {
        if (m_entries[i]->data)
        {
            delete m_entries[i]->data;
            m_entries[i]->data = NULL;
        }
        m_entries[i]->spawnClassData = NULL;
        delete m_entries[i];
    }
    m_entries.clear();
}

#include "Utilities.h"
#include <algorithm>

void CSpawnClass::addSpawnClassData(CDataGroup* group, CSpawnClassData* spawnData)
{
    if (!spawnData || !group) return;
    CSpawningData* info = new CSpawningData;
    info->m_odds = 0;
    info->m_rarityOverride = 0;
    info->m_flags = 0;
    info->m_minCount = 0;
    info->m_maxCount = 0;
    info->m_levelBonus = 0;
    info->m_magicFind = 0.0f;
    info->m_minCount = group->GetDataValue(L"MINCOUNT", 1);
    info->m_maxCount = group->GetDataValue(L"MAXCOUNT", 1);
    info->m_odds = group->GetDataValue(L"WEIGHT", static_cast<unsigned int>(-1));
    info->m_rarityOverride = group->GetDataValue(L"RARITY_OVERRIDE", static_cast<unsigned int>(-1));
    info->m_levelBonus = group->GetDataValue(L"LEVEL_BONUS", 0);
    info->m_magicFind = static_cast<float>(static_cast<unsigned int>(std::max(group->GetDataValue(L"MAGICFIND", 0), 0)));
    if (info->m_odds == 0) info->m_odds = -1;
    int flags = group->GetDataValue(L"FORCEENCHANT", false) ? 1 : 0;
    if (group->GetDataValue(L"NO_MAGIC_ITEMS", false)) flags |= 4;
    if (group->GetDataValue(L"NO_UNIQUE_ITEMS", false)) flags |= 2;
    if (group->GetDataValue(L"IGNORE_RANGE", false)) flags |= 16;
    info->m_flags = flags;
    SpawnClassEntry* entry = new SpawnClassEntry;
    entry->data = info;
    entry->spawnClassData = spawnData;
    m_entries.add(entry);
}

int CSpawnClass::rollSpawnClass(TArrayList<CDataGroup*>& groups,
    TArrayList<bool>* primaryChoices, CCharacter* character, CCharacter* rollingCharacter,
    int minimumLevel, unsigned int seed, int levelBonus, int rarityOverride,
    int magicFind, int flags)
{
    CRandomizer choices(RANDOMIZER_NORMAL);
    for (unsigned int i = 0; i < m_entries.size(); ++i) {
        if (m_entries[i]->data->m_odds == -1) {
            int count = std::max(UTILITIES::randomIntegerBetween(m_entries[i]->data->m_minCount,
                m_entries[i]->data->m_maxCount), 1);
            int entryFlags = flags | m_entries[i]->data->m_flags;
            for (unsigned int j = 0; j < static_cast<unsigned int>(count); ++j) {
                CSpawnClassData* data = m_entries[i]->spawnClassData;
                if (!data->m_pSpawnClass && data->m_lUnitDataObjects.size() == 1) {
                    for (unsigned int k = 0; k < data->m_lUnitDataObjects.size(); ++k) {
                        groups.add(data->m_lUnitDataObjects[k]);
                        if (primaryChoices) primaryChoices->add((flags & 1) != 0);
                    }
                } else {
                    CSpawningData* info = m_entries[i]->data;
                    data->rollSpawnClassData(groups, primaryChoices, character, rollingCharacter,
                        minimumLevel, std::max(levelBonus, info->m_levelBonus),
                        std::max(rarityOverride, info->m_rarityOverride),
                        std::max(magicFind, static_cast<int>(info->m_magicFind)), entryFlags);
                }
            }
        } else {
            choices.addChoice(i, m_entries[i]->data->m_odds);
        }
    }
    if (choices.hasChoices()) {
        if (seed != static_cast<unsigned int>(-1)) choices.setRandomSeed(seed);
        while (choices.hasChoices()) {
            unsigned int selected = choices.getRandom();
            choices.removeChoice(selected);
            CSpawnClassData* data = m_entries[selected]->spawnClassData;
            CSpawningData* info = m_entries[selected]->data;
            if (data->calculateChoices(character, minimumLevel, info->m_levelBonus,
                                       info->m_rarityOverride, flags)) {
                if (!data) break;
                int count = std::max(UTILITIES::randomIntegerBetween(info->m_minCount, info->m_maxCount), 1);
                int entryFlags = flags | info->m_flags;
                for (unsigned int j = 0; j < static_cast<unsigned int>(count); ++j)
                    data->rollSpawnClassData(groups, primaryChoices, character, rollingCharacter,
                        minimumLevel, std::max(levelBonus, info->m_levelBonus),
                        std::max(rarityOverride, info->m_rarityOverride),
                        std::max(magicFind, static_cast<int>(info->m_magicFind)), entryFlags);
                break;
            }
            if (data->m_bIsInitialized) break;
        }
    }
    return groups.size();
}
