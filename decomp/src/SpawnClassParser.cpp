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



#include "EmptyStrings.h"
#include "UnitResourceList.h"
#include <OgreUTFString.h>

void CSpawnClassParser::createEmptySpawnClass(CDataGroup* group)
{
    if (!group)
        return;
    std::wstring name = STRINGS::StringUpper(group->GetDataValue(L"NAME", EMPTY_WSTRING));
    if (name != EMPTY_WSTRING && !group->GetDataValue(L"DONOTSPAWN", false) && !getSpawnClass(name)) {
        CSpawnClass* spawnClass = new CSpawnClass(name.c_str());
        spawnClass->m_iUnknown30 = group->GetDataValue(L"LEVEL_BONUS", 0);
        m_spawnClasses[name] = spawnClass;
    }
}

CSpawnClassData* CSpawnClassParser::createSpawnClassDataRefSpawnClass(const std::wstring& name,
                                                                  CDataGroup* group)
{
    std::wstring key = Ogre::UTFString("SPAWNCLASS:") + Ogre::UTFString(name);
    CSpawnClassData* data = getSpawnClassDataByName(key);
    if (data)
        return data;
    CSpawnClass* spawnClass = getSpawnClass(name);
    if (spawnClass) {
        if (group)
            data = new CSpawnClassData(STRINGS::StringUpper(key));
        data->addSpawnClass(spawnClass);
        m_spawnClassData[data->m_sName] = data;
    }
    return data;
}

CSpawnClassData* CSpawnClassParser::createSpawnClassDataWithUnit(const std::wstring& name,
                                                               CDataGroup* group)
{
    std::wstring key = L"UNIT:" + name;
    CSpawnClassData* data = getSpawnClassDataByName(key);
    if (data)
        return data;
    CDataGroup* unit = CUnitResourceList::getSingleton()->getDataGroupByObjectName(name);
    if (unit) {
        if (group)
            data = new CSpawnClassData(STRINGS::StringUpper(key));
        data->addUnitDataObject(unit);
        m_spawnClassData[data->m_sName] = data;
    }
    return data;
}

CSpawnClassData* CSpawnClassParser::createSpawnClassData(CDataGroup* group)
{
    if (!group)
        return NULL;
    std::wstring type = STRINGS::StringUpper(group->GetDataValue(L"UNITTYPE", EMPTY_WSTRING));
    std::wstring unit = STRINGS::StringUpper(group->GetDataValue(L"UNIT", EMPTY_WSTRING));
    std::wstring spawnClass = STRINGS::StringUpper(group->GetDataValue(L"SPAWNCLASS", EMPTY_WSTRING));
    if (type != EMPTY_WSTRING)
        return createSpawnClassDataByUnitType(type, group);
    if (unit != EMPTY_WSTRING)
        return createSpawnClassDataWithUnit(unit, group);
    if (spawnClass != EMPTY_WSTRING)
        return createSpawnClassDataRefSpawnClass(spawnClass, group);
    return NULL;
}

void CSpawnClassParser::fillEmptySpawnClass(CDataGroup* group)
{
    if (!group)
        return;
    std::wstring name = STRINGS::StringUpper(group->GetDataValue(L"NAME", EMPTY_WSTRING));
    if (name == EMPTY_WSTRING)
        return;
    CSpawnClass* spawnClass = getSpawnClass(name);
    if (spawnClass) {
        for (unsigned int i = 0; i < group->GetNumberOfDataGroups(); ++i) {
            CSpawnClassData* data = createSpawnClassData(group->GetDataGroup(i));
            if (data)
                spawnClass->addSpawnClassData(group->GetDataGroup(i), data);
        }
    }
}
