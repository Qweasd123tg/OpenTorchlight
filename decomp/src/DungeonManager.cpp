#include "EmptyStrings.h"
#include "GameVariables.h"
#include "DungeonManager.h"
#include "RunicCore.h"
#include "FileUtilities.h"
#include "StringUtilities.h"

CDungeonManager* CDungeonManager::getSingleton()
{
    return reinterpret_cast<CDungeonManager*>(g_pDungeonManager);
}

CDungeonManager::~CDungeonManager()
{
    clear();
    g_pDungeonManager = NULL;
}

CDungeonManager::CDungeonManager(std::wstring path)
    : CRunicCore(),
      m_szDungeonPath(path),
      m_lDungeons(10)
{
    m_szDungeonPath = FILESYSTEM::CleanPath(STRINGS::StringUpper(m_szDungeonPath));
    g_pDungeonManager = this;
    reload();
}

#include "StringUtilities.h"
#include "Dungeon.h"

CDungeon* CDungeonManager::getDungeonByName(std::wstring name)
{
    name = STRINGS::StringUpper(name);
    for (unsigned int i = 0; i < m_lDungeons.size(); ++i)
        if (m_lDungeons[i]->m_sName == name)
            return m_lDungeons[i];
    return NULL;
}
