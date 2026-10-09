#include "SpawnClassParser.h"
#include "StringUtilities.h"
#include "SpawnClass.h"
#include "SpawnClassData.h"

static CSpawnClassParser* m_gSpawnClassParser = NULL;

CSpawnClassParser* CSpawnClassParser::getSingleton()
{
    return m_gSpawnClassParser;
}

void CSpawnClassParser::clear()
{
    for (std::map<std::wstring, CSpawnClassData*>::iterator it = m_spawnClassData.begin();
         it != m_spawnClassData.end(); ++it)
    {
        if (it->second)
        {
            delete it->second;
            it->second = NULL;
        }
    }
    m_spawnClassData.clear();
    for (std::map<std::wstring, CSpawnClass*>::iterator it = m_spawnClasses.begin();
         it != m_spawnClasses.end();)
    {
        CSpawnClass* spawnClass = it->second;
        ++it;
        delete spawnClass;
    }
    m_spawnClasses.clear();
}

CSpawnClassParser::~CSpawnClassParser()
{
    clear();
    m_gSpawnClassParser = NULL;
}

CSpawnClassData* CSpawnClassParser::getSpawnClassDataByName(const std::wstring& name)
{
    std::map<std::wstring, CSpawnClassData*>::iterator found = m_spawnClassData.find(STRINGS::StringUpper(name));
    if (found == m_spawnClassData.end())
        return NULL;
    return found->second;
}

CSpawnClass* CSpawnClassParser::getSpawnClass(const std::wstring& name)
{
    std::map<std::wstring, CSpawnClass*>::iterator found = m_spawnClasses.find(STRINGS::StringUpper(name));
    if (found == m_spawnClasses.end())
        return NULL;
    return found->second;
}


