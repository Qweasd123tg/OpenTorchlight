#include "EmptyStrings.h"
#include "UnitSpawnerDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "UnitSpawner.h"
#include "UnitSpawnerDescriptorNames.h"
#include "Level.h"
#include "ResourceManager.h"

CEditorBaseObject* CUnitSpawnerDescriptor::CreateObject(CEditorScene* scene)
{
    return new CUnitSpawner(scene->getResourceManager());
}

CUnitSpawnerDescriptor::CUnitSpawnerDescriptor()
    : CShapeDescriptor(L"Unit Spawner", L"Spawns units in differnt formations", L"spawn", true, true, true)
{
    AddInputLogic(INPUT_EVENT_SPAWN_UNITS);
    AddInputLogic(INPUT_EVENT_STOP);
    AddInputLogic(INPUT_EVENT_DESTROY_SPAWNED_UNITS);
    AddInputLogic(INPUT_EVENT_HIDE_AND_DISABLE_SPAWNED_UNITS);
    AddInputLogic(INPUT_EVENT_INCREMENT_LEVEL_DELTA);
    AddInputLogic(INPUT_EVENT_DECREMENT_LEVEL_DELTA);
    AddOutputLogic(OUTPUT_EVENT_ALL_UNITS_SPAWNED);
    AddOutputLogic(OUTPUT_EVENT_MONSTER_KILLED);
    AddOutputLogic(OUTPUT_EVENT_ALL_MONSTERS_DEAD);
    AddOutputLogic(OUTPUT_EVENT_ITEM_PICKED_UP);
    AddOutputLogic(OUTPUT_EVENT_ALL_ITEMS_PICKED_UP);
    AddOutputLogic(OUTPUT_EVENT_ITEM_INTERACTED);
    AddOutputLogic(OUTPUT_EVENT_ALL_ITEMS_INTERACTED_WITH);
    AddProperty(L"PROPERTIES", L"COUNT", L"Sets the number of units to spawn.", (void*)Set_setNumberOfUnitsToCreate, (void*)Get_getNumberOfUnitsToCreate, VARIABLE_TYPE_UNSIGNED_INTEGER, 0);
    AddProperty(L"PROPERTIES", L"MAX ALLOWED", L"The maxiumum number of monsters allowed to be alive at a time.", (void*)Set_setMaxNumMonstersAllowedAtATime, (void*)Get_getMaxNumMonstersAllowedAtATime, VARIABLE_TYPE_UNSIGNED_INTEGER, 0);
    AddProperty(L"PROPERTIES", L"UPDATE IN EDITOR", L"The object will visualy update in the editor.", (void*)Set_setUpdateInEditor, (void*)Get_getUpdateInEditor, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"SPAWN ON CREATE", L"Will spawn when the spawner becomes active.", (void*)Set_setSpawnOnCreate, (void*)Get_getSpawnOnCreate, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"TARGET PLAYER", L"Monsters only - will target player on creation.", (void*)Set_setTargetPlayer, (void*)Get_getTargetPlayer, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"DURATION", L"The duration to release the units in", (void*)Set_setSpawnDuration, (void*)Get_getSpawnDuration, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"PULSE RATE", L"The number of pulses that occure. NOTE - this will spawn the number of units per pulse.", (void*)Set_setPulseNumber, (void*)Get_getPulseNumber, VARIABLE_TYPE_UNSIGNED_INTEGER, 0);
    AddProperty(L"PROPERTIES", L"SPAWN IN CENTER", L"Items and monsters only - the first will spawn in the center of the unit spawner.", (void*)Set_setSpawnInCenter, (void*)Get_getSpawnInCenter, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"REQUIRES LOS", L"Unit requires line-of-sight from spawner to be generated", (void*)Set_setRequiresLOS, (void*)Get_getRequiresLOS, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"MUST SPAWN", L"MUST spawn the unit, even if the area is un-pathable", (void*)Set_setMustSpawn, (void*)Get_getMustSpawn, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"PLAY SPAWN ANIM", L"Monsters only - if true the monster will play it's spawn animation if it has one.", (void*)Set_setUseSpawnAnimation, (void*)Get_getUseSpawnAnimation, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"SNAP TO GROUND", L"Items and monsters snap to ground on creation.", (void*)Set_setSnapToGround, (void*)Get_getSnapToGround, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"GIVE XP", L"Monsters give XP", (void*)Set_setUnitsGiveXP, (void*)Get_getUnitsGiveXP, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"GIVE LOOT", L"Monsters give loot", (void*)Set_setUnitsGiveLoot, (void*)Get_getUnitsGiveLoot, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"UNIT LEVEL DELTA", L"Modify the level of resulting units by this amount", (void*)Set_setSpawnLevelOverrideDelta, (void*)Get_getSpawnLevelOverrideDelta, VARIABLE_TYPE_INTEGER, 0);
    AddProperty(L"PROPERTIES", L"DESTROY BODY", L"If true and your spawning Monsters, the monsters mesh will go away on death.", (void*)Set_setDestroyMeshOnDeath, (void*)Get_getDestroyMeshOnDeath, VARIABLE_TYPE_BOOL, 0);
    unsigned int groupProperty = AddPropertyWithInterpreterFunctions(L"RESOURCES", L"GROUP", L"The group to choose from.", (void*)Set_setCategory, (void*)Get_getCategory, GetGroupIDByString, GetGroupStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    unsigned int resourceProperty = AddPropertyWithInterpreterFunctions(L"RESOURCES", L"RESOURCE", L"The resource to spawn.", (void*)Set_setResourceSpawn, (void*)Get_getResourceSpawn, GetResourceIDByString, GetResourceStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    LinkProperty(resourceProperty, groupProperty);
}

CUnitSpawnerDescriptor::~CUnitSpawnerDescriptor()
{
}

void CUnitSpawnerDescriptor::descriptorSceneLoaded(CEditorScene* scene)
{
}


void CUnitSpawnerDescriptor::update(float elapsed)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CUnitSpawner* spawner = dynamic_cast<CUnitSpawner*>(m_Objects[i]);
        if (spawner)
            spawner->update(elapsed);
    }
}

void CUnitSpawnerDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject*)
{
    CUnitSpawner* spawner = dynamic_cast<CUnitSpawner*>(object);
    if (!spawner)
        return;
    switch (event) {
    case 10: spawner->stop(); break;
    case 32: spawner->spawn(); break;
    case 33: spawner->destroyUnits(); break;
    case 34: spawner->hideAndDisableUnits(true); break;
    case 35: ++spawner->m_spawnLevelOverrideDelta; break;
    case 36: --spawner->m_spawnLevelOverrideDelta; break;
    }
}

void CUnitSpawnerDescriptor::descriptorSceneActivated(CEditorScene*)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CUnitSpawner* spawner = dynamic_cast<CUnitSpawner*>(m_Objects[i]);
        if (!spawner)
            continue;
        spawner->createUnitsInMemory();
        if (spawner->m_spawnOnCreate &&
            !(std::wstring(spawner->m_category) != gSPAWN_TYPE_NAMES[4] &&
              std::wstring(spawner->m_category) != gSPAWN_TYPE_NAMES[2] &&
              spawner->getResourceManager()->getLevel()->m_flag258))
            spawner->spawn();
    }
}

std::wstring CUnitSpawnerDescriptor::GetGroupStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index < 1 || index > 6)
        return gSPAWN_TYPE_NAMES[0];
    return gSPAWN_TYPE_NAMES[index];
}

unsigned int CUnitSpawnerDescriptor::GetGroupIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    for (unsigned int index = 0; index < 7; ++index)
    {
        if (gSPAWN_TYPE_NAMES[index] == value)
            return index;
    }
    return 0;
}

unsigned int CUnitSpawnerDescriptor::GetResourceIDByString(CEditorScene*, CEditorBaseObject* object, const std::wstring& value, void*)
{
    CUnitSpawner* spawner = dynamic_cast<CUnitSpawner*>(object);
    if (spawner && spawner->getResourceManager() != NULL)
        return 0;
    return 0xffffffff;
}

void CUnitSpawnerDescriptor::DescriptorObjectHasBeenInited(CEditorBaseObject* object)
{
    CUnitSpawner* spawner = dynamic_cast<CUnitSpawner*>(object);
    if (spawner) spawner->reset();
}

#include "SpawnClassParser.h"
#include "MasterResourceManager.h"
#include "Hierarchy.h"
#include "MissilePreloader.h"
#include "FileSystem.h"
#include "UnitResourceList.h"

std::wstring CUnitSpawnerDescriptor::GetResourceStringByID(
    CEditorScene*, CEditorBaseObject* object, unsigned int index, void*)
{
    if (index == 0 || object == NULL)
        return EMPTY_WSTRING;
    CUnitSpawner* spawner = dynamic_cast<CUnitSpawner*>(object);
    if (spawner == NULL)
        return EMPTY_WSTRING;
    CResourceManager* resources = spawner->getResourceManager();
    if (resources == NULL)
        return EMPTY_WSTRING;

    --index;
    if (std::wstring(spawner->m_category) == gSPAWN_TYPE_NAMES[3]) {
        std::map<std::wstring, CSpawnClass*>& classes =
            CSpawnClassParser::getSingleton()->m_spawnClasses;
        for (std::map<std::wstring, CSpawnClass*>::iterator it = classes.begin();
             it != classes.end(); ++it) {
            if (index == 0)
                return it->first;
            --index;
        }
        return EMPTY_WSTRING;
    }

    CHierarchy* hierarchy = CMasterResourceManager::getSingleton()->m_pHierarchy;
    if (std::wstring(spawner->m_category) == gSPAWN_TYPE_NAMES[5]) {
        unsigned int type = index < hierarchy->m_types.size()
            ? hierarchy->m_types[index] : 0;
        if (type == static_cast<unsigned int>(-1))
            type = 0;
        return hierarchy->getTypeName(type);
    }
    if (std::wstring(spawner->m_category) == gSPAWN_TYPE_NAMES[4]) {
        if (gMissileFiles.size() == 0)
            CMissilePreloader::getSinglelton()->getMissileNames(gMissileFiles);
        if (index > 0 && index < gMissileFiles.size())
            return gMissileFiles[index];
        if (gMissileFiles.size() != 0) {
            std::wstring first = gMissileFiles[0];
            gMissileFiles.clear();
            return first;
        }
        return EMPTY_WSTRING;
    }
    if (std::wstring(spawner->m_category) == gSPAWN_TYPE_NAMES[2]) {
        const std::wstring directory(L"media/particles/");
        if (gParticleFiles.size() == 0)
            CFileSystem::getSingleton()->getFileList(
                directory, gParticleFiles, L"*.layout", true, true, false, false);
        if (gParticleFiles.size() == 0)
            return EMPTY_WSTRING;
        if (index > 0 && index < gParticleFiles.size())
            return gParticleFiles[index].substr(directory.length(),
                gParticleFiles[index].length() - directory.length());
        return gParticleFiles[0].substr(directory.length(),
            gParticleFiles[0].length() - directory.length());
    }

    std::map<long long, CDataGroup*>* groups;
    if (std::wstring(spawner->m_category) == gSPAWN_TYPE_NAMES[0])
        groups = resources->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[1]);
    else if (std::wstring(spawner->m_category) == gSPAWN_TYPE_NAMES[6])
        groups = resources->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[3]);
    else if (std::wstring(spawner->m_category) == gSPAWN_TYPE_NAMES[1])
        groups = resources->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[0]);
    else
        return EMPTY_WSTRING;
    for (std::map<long long, CDataGroup*>::iterator it = groups->begin();
         it != groups->end(); ++it) {
        if (index == 0)
            return it->second->GetDataValue(L"NAME", EMPTY_WSTRING);
        --index;
    }
    return EMPTY_WSTRING;
}
