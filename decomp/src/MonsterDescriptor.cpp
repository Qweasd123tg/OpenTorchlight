#include "GenericModel.h"
#include "AnimationSet.h"
#include "StringUtilities.h"
#include "PathController.h"
#include "Monster.h"
#include "UnitResourceList.h"
#include "EmptyStrings.h"
#include "MonsterDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "UnitThemes.h"
#include "Level.h"
#include "Character.h"

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

std::wstring CMonsterDescriptor::getThemeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData)
{
    CUnitThemes* themes = CUnitThemes::getSingleton();
    if (themes->getThemes().size() < index || index == 0) {
        return EMPTY_WSTRING;
    }
    return themes->getThemes()[index - 1]->getName();
}

unsigned int CMonsterDescriptor::getThemeIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring& value, void*)
{
    CUnitThemes* themes = CUnitThemes::getSingleton();
    for (unsigned int index = 0; index < themes->getThemes().size(); ++index) {
        if (themes->getThemes()[index]->getName() == value)
            return index + 1;
    }
    return 0;
}

bool CMonsterDescriptor::DescriptorObjectBeingDeleted(CEditorBaseObject* object)
{
    CLevel* level = getSceneOwner()->getResourceManager()->getLevel();
    if (level != NULL)
        level->removeCharacter(static_cast<CCharacter*>(object), true);
    return true;
}

std::wstring CMonsterDescriptor::getPathStringByID(CEditorScene* scene, CEditorBaseObject*, unsigned int index, void*)
{
    if (index == 0)
        return EMPTY_WSTRING;
    --index;
    TArrayList<CEditorBaseObject*>* paths = scene->GetObjectsCreatedByADescriptor(L"Pathing");
    if (paths != NULL) {
        if (index < paths->size())
            return static_cast<CPathController*>((*paths)[index])->m_pathName;
        if (paths->size() != 0)
            return static_cast<CPathController*>((*paths)[0])->m_pathName;
    }
    return EMPTY_WSTRING;
}
unsigned int CMonsterDescriptor::getPathIDByString(CEditorScene* scene, CEditorBaseObject*, const std::wstring& value, void*)
{
    if (value.empty())
        return 0;
    TArrayList<CEditorBaseObject*>* paths = scene->GetObjectsCreatedByADescriptor(L"Pathing");
    if (paths != NULL) {
        for (unsigned int index = 0; index < paths->size(); ++index) {
            if (static_cast<CPathController*>((*paths)[index])->m_pathName == value)
                return index;
        }
    }
    return 0;
}
unsigned int CMonsterDescriptor::getMonsterIDByString(CEditorScene*, CEditorBaseObject* object, const std::wstring& value, void*)
{
    CMonster* monster = dynamic_cast<CMonster*>(object);
    if (monster == NULL || monster->getResourceManager() == NULL)
        return static_cast<unsigned int>(-1);
    CResourceManager* resources = monster->getResourceManager();
    unsigned int index = 0;
    const std::map<long long, CDataGroup*>* group = resources->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[1]);
    for (std::map<long long, CDataGroup*>::const_iterator it = group->begin(); it != group->end(); ++it, ++index) {
        if (it->second->GetDataValue(L"NAME", EMPTY_WSTRING) == value)
            return index;
    }
    group = resources->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[2]);
    for (std::map<long long, CDataGroup*>::const_iterator it = group->begin(); it != group->end(); ++it, ++index) {
        if (it->second->GetDataValue(L"NAME", EMPTY_WSTRING) == value)
            return index;
    }
    return 0;
}
std::wstring CMonsterDescriptor::getMonsterStringByID(CEditorScene*, CEditorBaseObject* object, unsigned int index, void*)
{
    CMonster* monster = dynamic_cast<CMonster*>(object);
    if (monster == NULL || monster->getResourceManager() == NULL)
        return EMPTY_WSTRING;
    CResourceManager* resources = monster->getResourceManager();
    const std::map<long long, CDataGroup*>* group = resources->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[1]);
    std::wstring fallback = EMPTY_WSTRING;
    std::map<long long, CDataGroup*>::const_iterator it = group->begin();
    if (it != group->end())
        fallback = it->second->GetDataValue(L"NAME", L"");
    for (; it != group->end(); ++it) {
        if (index == 0)
            return it->second->GetDataValue(L"NAME", L"");
        --index;
    }
    group = resources->getMasterResourceList()->getGroupByName(gRESOURCE_GROUP_NAMES[2]);
    it = group->begin();
    if (it != group->end())
        fallback = it->second->GetDataValue(L"NAME", L"");
    for (; it != group->end(); ++it) {
        if (index == 0)
            return it->second->GetDataValue(L"NAME", L"");
        --index;
    }
    return fallback;
}

std::wstring CMonsterDescriptor::GetAnimationStringByID(CEditorScene*, CEditorBaseObject* object, unsigned int index, void*)
{
    CMonster* monster = dynamic_cast<CMonster*>(object);
    if (monster != NULL) {
        CGenericModel* model = static_cast<CGenericModel*>(monster->getUnitModel());
        if (model != NULL && model->m_animationSet != NULL && index != static_cast<unsigned int>(-1) && index < model->m_animationSet->m_lUnknown28.size())
            return STRINGS::StringConvertToWide(model->m_animationSet->m_lUnknown28[index]);
    }
    return EMPTY_WSTRING;
}
unsigned int CMonsterDescriptor::GetAnimationIDByString(CEditorScene*, CEditorBaseObject* object, const std::wstring& value, void*)
{
    std::string name = STRINGS::StringConvertToNarrow(value.c_str());
    CMonster* monster = dynamic_cast<CMonster*>(object);
    if (monster != NULL) {
        CGenericModel* model = static_cast<CGenericModel*>(monster->getUnitModel());
        if (model != NULL && model->m_animationSet != NULL) {
            const std::vector<std::string>& names = model->m_animationSet->m_lUnknown28;
            for (unsigned int index = 0; index < names.size(); ++index) {
                if (name == names[index])
                    return index;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

#include "ResourceManager.h"

void CMonsterDescriptor::DescriptorObjectHasBeenInited(CEditorBaseObject* object)
{
    CLevel* level = getSceneOwner()->getResourceManager()->getLevel();
    if (level) {
        level->removeCharacter(static_cast<CCharacter*>(object), false);
        getSceneOwner()->getResourceManager()->getLevel()->addCharacter(
            static_cast<CCharacter*>(object), Ogre::Vector3::ZERO, true);
    }
}

CEditorBaseObject* CMonsterDescriptor::CreateObject(CEditorScene* scene)
{
    CResourceManager* resources = scene->getResourceManager();
    int depth = 1;
    if (resources->getLevel())
        depth = resources->getLevel()->getDungeonDepth();
    CEditorBaseObject* object = new CMonster(resources, depth);
    CMonster* monster = dynamic_cast<CMonster*>(object);
    if (monster)
        monster->m_bBaseUnitFlag0 = true;
    return object;
}

void CMonsterDescriptor::ReloadMonsters()
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CCharacter* character = dynamic_cast<CCharacter*>(m_Objects[i]);
        if (character) {
            bool visible = character->getVisible();
            bool enabled = character->getEnabled();
            character->convertCharacter(character->getName(), false);
            character->setVisible(visible);
            character->setEnabled(enabled);
        }
    }
}

#include "AIManager.h"
#include "QuestManager.h"
#include "GameUI.h"
#include "GameClient.h"
#include "Player.h"
#include "SkillManager.h"
#include "LevelTemplateData.h"
#include <OgreSceneManager.h>

void CMonsterDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject*)
{
    CMonster* monster = dynamic_cast<CMonster*>(object);
    if (!monster)
        return;
    switch (event) {
    case 0:
        monster->setMeshVisible(true, false);
        monster->BroadcastEvent(4);
        CQuestManager::getSingleton()->calculateNPCIcon(monster);
        break;
    case 1:
        monster->stopParticles(true);
        monster->setMeshVisible(false, false);
        monster->BroadcastEvent(5);
        CQuestManager::getSingleton()->calculateNPCIcon(monster);
        break;
    case 2:
        monster->setEnabled(true);
        monster->BroadcastEvent(6);
        CQuestManager::getSingleton()->calculateNPCIcon(monster);
        break;
    case 3:
        monster->setEnabled(false);
        monster->BroadcastEvent(7);
        CQuestManager::getSingleton()->calculateNPCIcon(monster);
        break;
    case 48: {
        CPlayer* player = monster->getResourceManager()->getGameClient()->getPlayer();
        player->stopPathing();
        player->setAIState(static_cast<EAIState>(44));
        CGameUI::getSingleton()->forceInteractiveDialog(player, monster, NULL);
        break;
    }
    case 49: monster->m_bInvulnerable = true; monster->BroadcastEvent(96); break;
    case 50: monster->m_bInvulnerable = false; monster->BroadcastEvent(97); break;
    case 64: monster->m_targetLocked = false;
    case 61: {
        CPlayer* player = static_cast<CPlayer*>(monster->getLevel()->getPlayer());
        monster->m_targetLocked = false;
        monster->addAffix(L"MONSTER_HUNT", 1, monster, -1.0f);
        if (monster->m_pAIManager)
            monster->m_pAIManager->addAIFlag(static_cast<EAIFLAG_TYPES>(4), 20.0f);
        monster->setTarget(player);
        break;
    }
    case 62: monster->m_targetLocked = false; break;
    case 63:
        monster->setTarget(NULL);
        monster->removeAffix(L"MONSTER_HUNT");
        monster->m_targetLocked = true;
        break;
    case 65: monster->setAIState(static_cast<EAIState>(4)); break;
    case 70: monster->m_damageShapeEnabled = false; break;
    case 71: monster->m_damageShapeEnabled = true; break;
    case 72: monster->getResourceManager()->getGameClient()->getPlayer()->addPet(monster); break;
    case 73: monster->getResourceManager()->getGameClient()->getPlayer()->removePet(monster); break;
    case 74: monster->modifyHP(-monster->HPFloat()); break;
    case 82:
        if (monster->getSkillManager())
            monster->getSkillManager()->stopAllSkills(true, false, false);
        break;
    case 83:
        for (unsigned int i = 0; i < monster->getFollowerCount(); ++i) {
            if (monster->getFollower(i)) {
                int hp = monster->maxHP();
                monster->getFollower(i)->modifyHP(static_cast<float>(hp));
                monster->getFollower(i)->die(NULL, NULL, 0.0f, false);
            }
        }
        break;
    }
}

void CMonsterDescriptor::descriptorSceneActivated(CEditorScene*)
{
    if (!getSceneOwner()->getResourceManager()->getLevel() ||
        getSceneOwner()->getResourceManager()->getEditorIsRunning())
        return;
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CMonster* monster = dynamic_cast<CMonster*>(m_Objects[i]);
        if (monster) {
            Ogre::Quaternion orientation = monster->getOrientationQuaternionAbsolute();
            getSceneOwner()->getResourceManager()->getLevel()->removeCharacter(monster, false);
            CLevel* level = getSceneOwner()->getResourceManager()->getLevel();
            if (level->m_flag1A1 && !level->getLevelTemplateData()->isTown())
                monster->m_bBaseUnitFlag190 = true;
            monster->m_bSaveFlag191 = true;
            bool hidden = monster->m_forcedHidden;
            monster->setMeshVisible(true, true);
            Ogre::Vector3 position = monster->getPosition(true);
            monster->sceneNodeSetParent(monster->getResourceManager()->getSceneManager()->getRootSceneNode(), false);
            monster->setMeshVisible(!hidden, true);
            level = getSceneOwner()->getResourceManager()->getLevel();
            if (level) {
                level->addCharacter(monster, position, false);
                monster->setOrientation(orientation);
            }
            if (!monster->m_pathName.empty())
                monster->setPathToFollowByName(monster->m_pathName);
        }
    }
}
