#include "EmptyStrings.h"
#include "UnitSpawnerDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "UnitSpawner.h"

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

void CUnitSpawnerDescriptor::update(float param_1)
{
    (void)param_1;

    for (unsigned int i = 0; i < m_Objects.size(); ++i)
    {
        CUnitSpawner* unitSpawner = dynamic_cast<CUnitSpawner*>(m_Objects[i]);
        if (unitSpawner != NULL)
        {
            (void)unitSpawner;
        }
    }
}

void CUnitSpawnerDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject*)
{
    if (dynamic_cast<CUnitSpawner*>(object) != NULL) {
        switch (event) {
        case 10:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
            break;
        default:
            break;
        }
    }
}
