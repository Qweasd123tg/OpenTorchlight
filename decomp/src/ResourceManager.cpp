#include "GameNamespaces.h"
#include "StringUtilities.h"
#include "GraphManager.h"
#include "MasterResourceManager.h"
#include "EmptyStrings.h"
#include "ResourceManager.h"

CResourceManager::~CResourceManager()
{
    m_pSceneManager = NULL;
    m_pLevel = NULL;
    m_pHierarchy = NULL;
}

#include "Editor.h"
#include "MissilePreloader.h"
#include "OgreTextureManager.h"
#include "UnitResourceList.h"
#include <map>
#include <string>
#include "CameraControl.h"
#include "DungeonManager.h"
#include "GameUI.h"
#include "Hierarchy.h"

bool CResourceManager::ISA(UNITTYPES::EUNITTYPES type, UNITTYPES::EUNITTYPES parent)
{
    if (m_pHierarchy)
        return m_pHierarchy->ISA(type, parent);
    return false;
}

UNITTYPES::EUNITTYPES CResourceManager::getUnitTypeByName(const std::wstring& name)
{
    if (m_pHierarchy)
    {
        UNITTYPES::EUNITTYPES type = m_pHierarchy->getTypeIDByName(name);
        if (type != static_cast<UNITTYPES::EUNITTYPES>(-1))
            return type;
    }
    return static_cast<UNITTYPES::EUNITTYPES>(22);
}

CDungeonManager* CResourceManager::getDungeonManager()
{
    return CDungeonManager::getSingleton();
}

CUnitResourceList* CResourceManager::getMasterResourceList()
{
    return CUnitResourceList::getSingleton();
}

CGameUI* CResourceManager::getGameUI()
{
    return CGameUI::getSingleton();
}

CCameraControl* CResourceManager::getCameraControl()
{
    return CCameraControl::getSingleton();
}

CMissilePreloader* CResourceManager::getMissilePreloader()
{
    return CMissilePreloader::getSinglelton();
}

CMissile* CResourceManager::createMissile(const std::wstring& name)
{
    return CMissilePreloader::getSinglelton()->createNewMissileRef(this, name);
}

std::map<long long, CDataGroup*>* CResourceManager::getGroupByName(const std::wstring& name)
{
    if (CUnitResourceList::getSingleton())
        return CUnitResourceList::getSingleton()->getGroupByName(name);
    return NULL;
}

Ogre::TextureManager* CResourceManager::getTextureManager()
{
    return Ogre::TextureManager::getSingletonPtr();
}

bool CResourceManager::getEditorIsRunning()
{
    return ((gEditor->getFlags() >> 1) & 1) ^ 1;
}

CDataGroup* CResourceManager::getUnitDataByGuid(long long guid)
{
    return CUnitResourceList::getSingleton()->getDataGroupByGuid(guid);
}

long long CResourceManager::getUnitGuidByDataGroup(CDataGroup* data, const std::wstring& name)
{
    if (data) {
        const std::wstring& value = data->GetDataValue(name, EMPTY_WSTRING);
        if (!value.empty())
            return STRINGS::GetInt64(value);
    }
    return -1;
}

CGraph* CResourceManager::getGraph(const std::wstring& name)
{
    if (CMasterResourceManager::getSingleton() && CMasterResourceManager::getSingleton()->m_pGraphManager)
        return CMasterResourceManager::getSingleton()->m_pGraphManager->getGraph(name);
    return NULL;
}

CDungeon* CResourceManager::getDungeonByName(const std::wstring& name)
{
    return CDungeonManager::getSingleton()->getDungeonByName(name);
}

CBaseUnit* CResourceManager::createUnit(CDataGroup* data, int level, bool flag1, bool flag2)
{
    if (data) {
        long long guid = getUnitGuidByDataGroup(data, L"UNIT_GUID");
        return createUnit(guid, level, flag1, flag2);
    }
    return NULL;
}

#include "ParticlePreloader.h"
#include "EffectGroupManager.h"
#include "Affix.h"
#include "SpawnClassParser.h"
#include "SpawnClass.h"
#include "Level.h"

CParticle* CResourceManager::createParticle(const wchar_t* name)
{
    if (CMasterResourceManager::getSingleton()->m_pParticlePreloader)
        return CMasterResourceManager::getSingleton()->m_pParticlePreloader->GetParticle(this, name);
    return NULL;
}

int CResourceManager::ISA(const std::wstring& unit, const std::wstring& parent)
{
    if (!m_pHierarchy)
        return false;
    UNITTYPES::EUNITTYPES parentType = getUnitTypeByName(parent);
    UNITTYPES::EUNITTYPES unitType = getUnitTypeByName(unit);
    return m_pHierarchy->ISA(unitType, parentType);
}

CSpawnClass* CResourceManager::getSpawnClassByName(const std::wstring& name)
{
    return CMasterResourceManager::getSingleton()->m_pSpawnClassParser->getSpawnClass(name);
}

unsigned int CResourceManager::getCurrentLevelSeed()
{
    if (m_pLevel)
        return m_pLevel->getCurrentLevelSeed();
    return 0;
}

CAffix* CResourceManager::getNewAffixByName(const std::wstring& name, unsigned int level)
{
    CAffix* affix = CMasterResourceManager::getSingleton()->m_effectGroups->getAffix(name);
    if (affix)
        return new CAffix(affix, level);
    return NULL;
}

ERESOURCE_GROUPS CResourceManager::getResourceGroupFromDataGroup(CDataGroup* data)
{
    if (data) {
        unsigned int group = data->GetDataValue(L"RESOURCEGROUP", static_cast<unsigned int>(-1));
        if (group != static_cast<unsigned int>(-1))
            return static_cast<ERESOURCE_GROUPS>(group);
    }
    return static_cast<ERESOURCE_GROUPS>(4);
}

CBaseUnit* CResourceManager::createUnit(const wchar_t* category, const wchar_t* name, int level, bool flag)
{
    if (!name || !category || !CUnitResourceList::getSingleton())
        return NULL;
    CDataGroup* data = CUnitResourceList::getSingleton()->getDataGroupByObjectName(category, name);
    if (data)
        return createUnit(data, level, flag, false);
    return NULL;
}

void CResourceManager::createUnitsBySpawnClass(CSpawnClass* spawn, TArrayList<CBaseUnit*>& units,
    unsigned int count, CCharacter* first, CCharacter* second, int level, int flags)
{
    if (!spawn || !count)
        return;
    TArrayList<CDataGroup*> groups(10);
    TArrayList<bool> choices(10);
    for (unsigned int i = 0; i < count; ++i) {
        groups.clear();
        spawn->rollSpawnClass(groups, &choices, first, second, level, static_cast<unsigned int>(-1), 0, -1, 0, flags);
        for (unsigned int j = 0; j < groups.size(); ++j) {
            CBaseUnit* unit = createUnit(groups[j], level, false, choices[j]);
            if (unit)
                units.add(unit);
        }
    }
}

#include "BaseUnit.h"
#include "Monster.h"
#include "Player.h"
#include "Item.h"
#include "Equipment.h"
#include "GenericModel.h"
#include "GameClient.h"
#include "Settings.h"
#include "CmdLineParser.h"

void CResourceManager::createAffixesForUnit(CBaseUnit* unit, unsigned int level, unsigned int count)
{
    if (!count || !unit)
        return;
    TArrayList<CAffix*> affixes(count);
    CMasterResourceManager::getSingleton()->m_effectGroups->rollAndCreateRandomAffixes(unit->m_eUnitType, level, count, affixes);
    for (unsigned int i = 0; i < affixes.size(); ++i)
        unit->addAffix(affixes[i], level, unit, -1.0f);
}

CGraph* CResourceManager::getGraphDamage()
{
    if (m_GameClients.size() && m_GameClients[0]) {
        switch (m_GameClients[0]->m_startDifficulty) {
        case 0: return CGraphManager::getSingleton()->getGraph(L"DAMAGE_MONSTER_EASY");
        case 1: return CGraphManager::getSingleton()->getGraph(L"DAMAGE_MONSTER");
        case 2: return CGraphManager::getSingleton()->getGraph(L"DAMAGE_MONSTER_HARD");
        case 3: return CGraphManager::getSingleton()->getGraph(L"DAMAGE_MONSTER_VERYHARD");
        }
    }
    return NULL;
}

CMonster* CResourceManager::createMonster(long long guid, int level, bool initialize)
{
    CDataGroup* data = CUnitResourceList::getSingleton()->getDataGroupByGuid(guid);
    if (!data)
        return NULL;
    if (level <= 0)
        level = m_pLevel ? m_pLevel->getDungeonDepth() : 1;
    CMonster* monster = new CMonster(this, level);
    monster->unitInit(data, initialize);
    return monster;
}

CMonster* CResourceManager::createMonster(const wchar_t* name, int level, bool initialize)
{
    CDataGroup* data = CUnitResourceList::getSingleton()->getDataGroupByObjectName(L"MONSTERS", name);
    if (!data)
        return NULL;
    if (level <= 0)
        level = m_pLevel ? m_pLevel->getDungeonDepth() : 1;
    CMonster* monster = new CMonster(this, level);
    monster->unitInit(data, initialize);
    return monster;
}

CPlayer* CResourceManager::createPlayer(const wchar_t* name, bool initialize)
{
    CDataGroup* data = CUnitResourceList::getSingleton()->getDataGroupByObjectName(L"PLAYERS", name);
    if (!data)
        return NULL;
    CPlayer* player = new CPlayer(this);
    player->unitInit(data, initialize);
    return player;
}

CGenericModel* CResourceManager::createGenericModel(Ogre::SceneManager* scene, const wchar_t* mesh, const wchar_t* material, bool first, bool second, bool third)
{
    CGenericModel* model = new CGenericModel(this, scene, EMPTY_WSTRING, EMPTY_WSTRING, first);
    model->loadModel(mesh, material ? std::wstring(material) : EMPTY_WSTRING, second, third, false);
    return model;
}

CItem* CResourceManager::createItem(long long guid, bool initialize, bool flag, bool enchantItem)
{
    CDataGroup* data = CUnitResourceList::getSingleton()->getDataGroupByGuid(guid);
    if (!data)
        return NULL;
    CItem* item = createNewItem(data);
    if (item) {
        item->m_bItemFlag20A = flag;
        item->unitInit(data, initialize);
        CEquipment* equipment = dynamic_cast<CEquipment*>(item);
        if (enchantItem && equipment)
            equipment->enchant(true);
    }
    return item;
}

CItem* CResourceManager::createItem(const wchar_t* name, bool initialize, bool flag)
{
    CDataGroup* data = CUnitResourceList::getSingleton()->getDataGroupByObjectName(L"ITEMS", name);
    if (!data)
        return NULL;
    CItem* item = createNewItem(data);
    if (item) {
        item->m_bItemFlag20A = flag;
        item->unitInit(data, initialize);
    }
    return item;
}

CEquipment* CResourceManager::createEquipment(const wchar_t* name, bool initialize, bool flag)
{
    CItem* item = createItem(name, initialize, flag);
    if (!item)
        return NULL;
    CEquipment* equipment = dynamic_cast<CEquipment*>(item);
    if (!equipment)
        delete item;
    return equipment;
}

CResourceManager::CResourceManager(Ogre::SceneManager* scene)
    : CRunicCore(), m_pSceneManager(scene), m_pLevel(NULL), m_GameClients(10),
      m_bFlag0(false), m_bFlag1(true), m_bFlag2(false), m_bFlag3(false)
{
    if (CMasterResourceManager::getSingleton()) {
        m_pHierarchy = CMasterResourceManager::getSingleton()->m_pHierarchy;
        if (!m_pSceneManager)
            m_pSceneManager = CMasterResourceManager::getSingleton()->m_pDefaultSceneManager;
        if (CMasterResourceManager::getSingleton()->m_pSettings)
            m_bFlag3 = CMasterResourceManager::getSingleton()->m_pSettings->m_pCmdLineParser->GetStringParam(L"COMPRESS", EMPTY_WSTRING) != EMPTY_WSTRING;
    }
}

CBaseUnit* CResourceManager::createUnit(long long guid, int level, bool initialize, bool enchantItem)
{
    if (guid == -1)
        return NULL;
    if (level <= 0)
        level = m_pLevel ? m_pLevel->getDungeonDepth() : 1;
    CDataGroup* data = CUnitResourceList::getSingleton()->getDataGroupByGuid(guid);
    if (!data)
        return NULL;
    unsigned int group = data->GetDataValue(L"RESOURCEGROUP", static_cast<unsigned int>(-1));
    if (group == static_cast<unsigned int>(-1) || group == 2)
        return NULL;
    if (group == 1)
        return createMonster(guid, level, initialize);
    if (group == 0)
        return createItem(guid, initialize, true, enchantItem);
    CItem* item = createItem(guid, initialize, true, false);
    if (item)
        item->setLevel(level);
    return item;
}

void CResourceManager::createUnitsBySpawnClass(const std::wstring& name, TArrayList<CBaseUnit*>& units,
    unsigned int count, CCharacter* first, CCharacter* second, int level, int flags)
{
    units.clear();
    if (!name.empty() && count) {
        CSpawnClass* spawn = getSpawnClassByName(name);
        if (spawn)
            createUnitsBySpawnClass(spawn, units, count, first, second, level, flags);
    }
}
