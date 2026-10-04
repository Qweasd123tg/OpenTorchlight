#include "EmptyStrings.h"
#include "MonsterDescriptor.h"

CMonsterDescriptor::CMonsterDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, true, true, true, false)
{
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"MONSTER", L"The monster you want to spawn in the level.", (void*)Set_createNewCharacter, (void*)Get_getUnitDataName, getMonsterIDByString, getMonsterStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddProperty(L"MESH", L"FILE", L" File containing the model", (void*)Set_setModelPathDummy, (void*)Get_getModelPath, VARIABLE_TYPE_STRING, 1);
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the trigger enabled or disabled.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"NO TARGET", L"Monster starts with 'No Target' on", (void*)Set_setMonsterNoTarget, (void*)Get_getMonsterNoTarget, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"FIRE ALL HP EVENTS", L"if set, all HP events will fire (i.e. one-hitting will fire all HP events)", (void*)Set_setBroadcastAllHPEvents, (void*)Get_getBroadcastAllHPEvents, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"INVINCIBLE", L"If true the monster can't be hurt.", (void*)Set_setInvincible, (void*)Get_getInvincible, VARIABLE_TYPE_BOOL, 0);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"PATH", L"The path in the level to follow.", (void*)Set_setPathToFollowByName, (void*)Get_getPathNameToFollow, getPathIDByString, getPathStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddProperty(L"PROPERTIES", L"PATH LOOPS", L"If true the monster will follow loop around the path.", (void*)Set_setShouldLoopOnPath, (void*)Get_getShouldLoopOnPath, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"VISIBLE", L"If true the monster will disappear. Player can't hurt monster", (void*)Set_setMeshVisible, (void*)Get_getMeshVisible, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"TARGETABLE", L"If true the monster can't be targetable.", (void*)Set_setCanBeTargeted, (void*)Get_getCanBeTargeted, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"SCALE", L"The scale of the monster.", (void*)Set_setScale, (void*)Get_getScaleFloat, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"CANNOT WANDER", L"If true the monster cannot wander.", (void*)Set_setDisableWandering, (void*)Get_getDisableWandering, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"NO GOLD", L"If true the monster WILL NOT drop gold.", (void*)Set_setDontDropGold, (void*)Get_getDontDropGold, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"NO TREASURE", L"If true the monster WILL NOT drop treasure.", (void*)Set_setDontDropTreasure, (void*)Get_getDontDropTreasure, VARIABLE_TYPE_BOOL, 0);
    AddPropertyWithInterpreterFunctions(L"ANIMATION", L"ANIMATION", L"The animation you want to play.", (void*)Set_setAnimationPlaying, (void*)Get_getAnimationPlaying, GetAnimationIDByString, GetAnimationStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"THEME", L"Theme to apply to unit (preview only)", (void*)Set_setEditorThemeID, (void*)Get_getEditorThemeID, getThemeIDByString, getThemeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 260);
    AddProperty(L"ANIMATION", L"SPEED", L"Speed of animation", (void*)Set_setAnimationSpeed, (void*)Get_getAnimationSpeed, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"ANIMATION", L"LOOPS", L"Animation will loop", (void*)Set_setAnimationLoop, (void*)Get_getAnimationLoop, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"WARDROBE", L"CHEST MESH", L"Chest Mesh File", (void*)Set_setWardrobeChestMesh, (void*)Get_getWardrobeChestMesh, VARIABLE_TYPE_STRING, 4352);
    AddProperty(L"WARDROBE", L"BOOTS MESH", L"Boots Mesh File", (void*)Set_setWardrobeBootsMesh, (void*)Get_getWardrobeBootsMesh, VARIABLE_TYPE_STRING, 4352);
    AddProperty(L"WARDROBE", L"GLOVES MESH", L"Gloves Mesh File", (void*)Set_setWardrobeGlovesMesh, (void*)Get_getWardrobeGlovesMesh, VARIABLE_TYPE_STRING, 4352);
    AddProperty(L"WARDROBE", L"HELM MESH", L"Helm Mesh File", (void*)Set_setWardrobeHelmMesh, (void*)Get_getWardrobeHelmMesh, VARIABLE_TYPE_STRING, 4352);
    AddProperty(L"WARDROBE", L"SHOULDER MESH", L"Shoulder Mesh File", (void*)Set_setWardrobeShoulderMesh, (void*)Get_getWardrobeShoulderMesh, VARIABLE_TYPE_STRING, 4352);
    AddProperty(L"WARDROBE", L"CHEST TEXTURE", L"Chest Texture File", (void*)Set_setWardrobeChestTexture, (void*)Get_getWardrobeChestTexture, VARIABLE_TYPE_STRING, 8448);
    AddProperty(L"WARDROBE", L"BOOTS TEXTURE", L"Boots Texture File", (void*)Set_setWardrobeBootsTexture, (void*)Get_getWardrobeBootsTexture, VARIABLE_TYPE_STRING, 8448);
    AddProperty(L"WARDROBE", L"GLOVES TEXTURE", L"Gloves Texture File", (void*)Set_setWardrobeGlovesTexture, (void*)Get_getWardrobeGlovesTexture, VARIABLE_TYPE_STRING, 8448);
    AddInputLogic(INPUT_EVENT_INTERACT);
    AddInputLogic(INPUT_EVENT_MAKE_INVULNERABLE);
    AddInputLogic(INPUT_EVENT_MAKE_VULNERABLE);
    AddInputLogic(INPUT_EVENT_ALERT_MONSTER);
    AddInputLogic(INPUT_EVENT_ENABLE_TARGETING);
    AddInputLogic(INPUT_EVENT_DISABLE_TARGETING);
    AddInputLogic(INPUT_EVENT_ENABLE_TARGETING_AND_ALERT);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddInputLogic(INPUT_EVENT_HUNT);
    AddInputLogic(INPUT_EVENT_SHOW);
    AddInputLogic(INPUT_EVENT_HIDE);
    AddInputLogic(INPUT_EVENT_CANNOT_BE_TARGETED);
    AddInputLogic(INPUT_EVENT_CAN_BE_TARGETED);
    AddInputLogic(INPUT_EVENT_ADD_AS_PET);
    AddInputLogic(INPUT_EVENT_REMOVE_AS_PET);
    AddInputLogic(INPUT_EVENT_KILL_MONSTER);
    AddInputLogic(INPUT_EVENT_STOP_SKILLS);
    AddInputLogic(INPUT_EVENT_KILL_PETS);
    AddOutputLogic(OUTPUT_EVENT_INTERACTING);
    AddOutputLogic(OUTPUT_EVENT_INVULNERABLE);
    AddOutputLogic(OUTPUT_EVENT_VULNERABLE);
    AddOutputLogic(OUTPUT_EVENT_HP_90_PCT);
    AddOutputLogic(OUTPUT_EVENT_HP_80_PCT);
    AddOutputLogic(OUTPUT_EVENT_HP_70_PCT);
    AddOutputLogic(OUTPUT_EVENT_HP_60_PCT);
    AddOutputLogic(OUTPUT_EVENT_HP_50_PCT);
    AddOutputLogic(OUTPUT_EVENT_HP_40_PCT);
    AddOutputLogic(OUTPUT_EVENT_HP_30_PCT);
    AddOutputLogic(OUTPUT_EVENT_HP_20_PCT);
    AddOutputLogic(OUTPUT_EVENT_HP_10_PCT);
    AddOutputLogic(OUTPUT_EVENT_MONSTER_KILLED);
    AddOutputLogic(OUTPUT_EVENT_MONSTER_ALERTED);
    AddOutputLogic(OUTPUT_EVENT_INTERACTED);
    AddOutputLogic(OUTPUT_EVENT_INTERACTED_ACCEPTED);
    AddOutputLogic(OUTPUT_EVENT_INTERACTED_DECLINED);
    AddOutputLogic(OUTPUT_EVENT_INTERACTED_CLOSED);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
    AddOutputLogic(OUTPUT_EVENT_END_OF_PATH_REACHED);
    AddOutputLogic(OUTPUT_EVENT_ON_INVISIBLE);
    AddOutputLogic(OUTPUT_EVENT_ON_VISIBLE);
}

CMonsterDescriptor::~CMonsterDescriptor()
{
}
