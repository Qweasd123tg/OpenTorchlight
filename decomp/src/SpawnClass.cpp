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
