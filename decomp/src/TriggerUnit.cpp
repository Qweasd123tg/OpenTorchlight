#include "TriggerUnit.h"
#include "GenericModel.h"
#include "Layout.h"
#include "MasterResourceManager.h"
#include "SoundBank.h"
#include "EmptyStrings.h"

CTriggerUnit::CTriggerUnit(CResourceManager* resource)
    : CItem(resource), m_unitModel(NULL), m_unitCollisionModel(NULL),
      m_layout(NULL), m_state(0), m_minState(0), m_maxState(1),
      m_cycleMode(0), m_cycleDirection(0), m_flag25C(false),
      m_pendingStateEvent(false), m_modelName(), m_animations(1),
      m_looping(10), m_altAnimations(10), m_stateLayouts(1),
      m_layout2C8(NULL), m_treasureClass(EMPTY_WSTRING),
      m_minTreasure(1), m_maxTreasure(1), m_flag2E0(true),
      m_requiredItem(EMPTY_WSTRING), m_value2F0(0), m_flag2F4(false),
      m_requiredQuest(EMPTY_WSTRING)
{
}

CTriggerUnit::~CTriggerUnit()
{
    if (m_layout2C8) {
        delete m_layout2C8;
        m_layout2C8 = NULL;
    }
    m_pEntity = NULL;
    m_stateLayouts.deleteAll();
    if (m_layout) {
        delete m_layout;
        m_layout = NULL;
    }
    if (m_unitModel) {
        delete m_unitModel;
        m_unitModel = NULL;
    }
    CMasterResourceManager::getSingleton()->removeCollisionModel(m_unitCollisionModel);
    m_unitCollisionModel = NULL;
    if (m_pSoundBank) {
        delete m_pSoundBank;
        m_pSoundBank = NULL;
    }
}

void CTriggerUnit::setVisible(bool visible, bool immediate)
{
    if (m_layout && m_bVisible) {
        if (visible)
            m_layout->setVisible(true);
    } else {
        CItem::setVisible(visible, immediate);
    }
}

#include "DataGroup.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "StringUtilities.h"
void CTriggerUnit::addSoundsToState(ETRIGGER_STATES state, const wchar_t* key)
{
    if (!m_pDataGroup) return;
    CSoundBankDataInformation* information =
        CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
    std::wstring name = m_pDataGroup->GetDataValue(key, EMPTY_WSTRING);
    if (name.empty())
        name = m_pDataGroup->GetDataValue(L"INTERACT_SOUND", EMPTY_WSTRING);
    CSoundData* data = information->getSoundDataObject(STRINGS::StringUpper(name));
    if (data)
        m_pSoundBank->addSample(state, data->m_iGuid);
}

#include "UnitResourceList.h"
#include "Level.h"
void CTriggerUnit::setUnitModelName(std::wstring name)
{
    if (name.empty() || name == m_modelName) return;
    m_modelName = name;
    CDataGroup* data = m_pResourceManager->getMasterResourceList()->getDataGroupByObjectName(L"PROPS", name);
    if (!data) return;
    unitInit(data, false);
    if (!m_pResourceManager->getEditorIsRunning()) {
        m_bItemFlag1F0 = true;
        if (m_bBlocksPath)
            m_bPathingFlag19C = true;
        if (m_pResourceManager && m_pResourceManager->getLevel()) {
            m_pResourceManager->getLevel()->removeItem(this, true);
            Ogre::Vector3 position = getPosition(false);
            CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            level->addItem(this, position, true);
        }
    }
}

void CTriggerUnit::setActiveInLevel(bool active)
{
    if (!m_flag25C && active) {
        m_flag25C = true;
        m_state = m_minState;
        updateCullingBounds();
    }
    if (active) {
        setVisible(true, true);
        m_bInActiveRange = false;
        if (!m_pResourceManager || !m_pResourceManager->getLevel() ||
            !m_pResourceManager->getLevel()->m_collisionList)
            return;
        snapToGround();
        updateCullingBounds();
        CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
        addToAvoidanceMap(*level);
    } else {
        setVisible(false, true);
        if (m_pResourceManager && m_pResourceManager->getLevel())
            removeFromAvoidanceMap(*m_pResourceManager->getLevel());
    }
}

void CTriggerUnit::setTriggerState(ETRIGGER_STATES requested, bool notify, bool force, bool animate)
{
    if (!force && m_state != m_maxState && m_state == requested)
        return;
    int state = requested;
    if (state < m_minState) state = m_minState;
    if (m_maxState < state) state = m_maxState;
    m_state = state;
    if (m_pResourceManager && m_pResourceManager->getLevel() && notify)
        m_pendingStateEvent = m_pResourceManager->getLevel()->m_automapRoomPieces;
    if (animate && static_cast<unsigned int>(m_state) < m_animations.size() && getUnitModel()) {
        int alternate = m_altAnimations[m_state];
        float length = static_cast<CGenericModel*>(getUnitModel())->getAnimationLengthSeconds(alternate);
        m_fForcedActiveTime = length + 0.3f;
        if (alternate == -1) {
            bool loop = m_looping[m_state];
            unsigned int animation = m_animations[m_state];
            static_cast<CGenericModel*>(getUnitModel())->blendAnimation(animation, loop, 0.1f, 1.0f, -1.0f);
        } else {
            unsigned int animation = m_altAnimations[m_state];
            static_cast<CGenericModel*>(getUnitModel())->blendAnimation(animation, false, 0.1f, 1.0f, -1.0f);
            animation = m_animations[m_state];
            static_cast<CGenericModel*>(getUnitModel())->queueBlendAnimation(animation, true, 0.01f, 1.0f);
        }
    }
    for (unsigned int i = 0; i < m_stateLayouts.size(); ++i) {
        if (!m_stateLayouts[i]) continue;
        if (i != static_cast<unsigned int>(m_state)) {
            m_stateLayouts[i]->setVisible(false);
            m_stateLayouts[i]->stop(false);
        } else {
            m_stateLayouts[i]->setVisible(true);
            m_stateLayouts[i]->start();
        }
    }
    if (m_pResourceManager && m_pResourceManager->getLevel() &&
        m_pResourceManager->getLevel()->m_automapRoomPieces)
        m_pSoundBank->playSample(m_state, m_pSceneNode, 0.0f, 0.0f, false);
}

void CTriggerUnit::resetTrigger()
{
    m_bItemFlag1F0 = true;
    setTriggerState(static_cast<ETRIGGER_STATES>(m_minState), false, true, true);
    if (m_pResourceManager && m_pResourceManager->getLevel() &&
        m_pResourceManager->getLevel()->m_automapRoomPieces)
        BroadcastEvent(9);
}

void CTriggerUnit::spawnTreasureClass(CCharacter* owner, const std::wstring& name, unsigned int count)
{
    if (m_flag2E0 && m_pResourceManager && m_pResourceManager->getLevel()) {
        CLevel* level = m_pResourceManager->getLevel();
        Ogre::Vector3 position = getPosition(true);
        CSpawnClass* spawn = m_pResourceManager->getSpawnClassByName(name);
        m_pResourceManager->createUnitsBySpawnClassAtPositionInLevel(spawn, count, position, level, owner, NULL, -1);
    }
}

#include "ItemSaveState.h"
#include "EditorScene.h"
#include "EffectManager.h"
#include "Effect.h"
#include "CameraControl.h"
void CTriggerUnit::fillSaveState(CItemSaveState& save, int index, bool flag)
{
    CItem::fillSaveState(save, index, flag);
    // The shared item save payload stores a trigger's state in the stack-size slot.
    save.m_iStackSize = m_state;
    save.m_iOriginalGuid = getOriginalGuid();
    save.m_iStateValue38 = getSceneOwner() ? getSceneOwner()->getOriginalGuid() : -1;
    if (!m_pEffectManager) return;
    for (unsigned int group = 0; group < 3; ++group) {
        TArrayList<CEffect*>& effects = m_pEffectManager->getActiveEffects(group);
        for (unsigned int i = 0; i < effects.size(); ++i) {
            CEffect* effect = new CEffect(effects[i]);
            effect->setOwner(NULL, true);
            effect->setSkillOwner(NULL);
            effect->m_fValueC0 = effects[i]->m_fValueC0;
            save.m_Effects[group].push_back(effect);
        }
    }
}

void CTriggerUnit::applySaveState(CItemSaveState& save)
{
    CItem::applySaveState(save);
    setTriggerState(static_cast<ETRIGGER_STATES>(save.m_iStackSize), false, true, false);
    if (static_cast<unsigned int>(m_state) < m_animations.size() && getUnitModel()) {
        m_bInActiveRange = true;
        bool loop = m_looping[m_state];
        unsigned int animation = m_animations[m_state];
        static_cast<CGenericModel*>(getUnitModel())->playAnimation(animation, loop, 1.0f, -1.0f);
        updateAnimation(1000.0f);
        update(m_pResourceManager->getCameraControl()->m_cameras[0], save.m_vLocalPosition, 1000.0f);
        static_cast<CGenericModel*>(getUnitModel())->clearAnimations();
        loop = m_looping[m_state];
        animation = m_animations[m_state];
        static_cast<CGenericModel*>(getUnitModel())->playAnimation(animation, loop, 1.0f, -1.0f);
        int selected = m_animations[m_state];
        float length = static_cast<CGenericModel*>(getUnitModel())->getAnimationLengthSeconds(selected);
        static_cast<CGenericModel*>(getUnitModel())->setAnimationTime(length - 0.01f);
    }
    if (m_cycleMode == 0 && m_state >= m_maxState) {
        m_bItemFlag1F0 = false;
    } else {
        m_bItemFlag1F0 = true;
        setEnabled(save.m_bEnabled);
    }
    if (m_state != m_minState) m_flag25C = true;
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(0xad)) && !getEnabled()) {
        setVisible(false, true);
        m_bItemFlag218 = true;
        if (m_layout) m_layout->setVisible(false);
    }
    for (unsigned int group = 0; group < 3; ++group) {
        for (unsigned int i = 0; i < save.m_Effects[group].size(); ++i) {
            CEffect* saved = save.m_Effects[group][i];
            float duration = saved->m_fValueC0;
            CEffect* effect = addNewEffect(saved);
            if (effect) {
                effect->m_fValueC0 = duration;
                activateEffect(effect);
            }
        }
        save.m_Effects[group].clear();
    }
    if (m_pEffectManager) m_pEffectManager->calculateEffectValues();
    m_pendingStateEvent = false;
}

void CTriggerUnit::update(Ogre::Camera* camera, const Ogre::Vector3& position, float elapsed)
{
    if (camera) CItem::update(camera, position, elapsed);
    if (m_layout2C8) m_layout2C8->update(elapsed);
    if (m_bBlocksPath) m_bPathingFlag19C = m_bInActiveRange && !m_bItemFlag218;
    if (m_layout) m_layout->update(elapsed);
    if (static_cast<unsigned int>(m_state) < m_stateLayouts.size() && m_stateLayouts[m_state])
        m_stateLayouts[m_state]->update(elapsed);
    updateCullingBounds();
    CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
    addToAvoidanceMap(*level);
    if (m_pendingStateEvent) {
        if (m_unitModel && m_unitModel->m_animationPlaying != ~0u &&
            m_unitModel->animationPlaying(m_unitModel->m_animationPlaying))
            return;
        BroadcastEvent(0);
        if (m_state == 0) BroadcastEvent(0x2e);
        else if (m_state == 1) BroadcastEvent(0x2f);
        m_pendingStateEvent = false;
    }
}

#include "Character.h"
#include "Player.h"
#include "Inventory.h"
#include "Equipment.h"
#include "QuestManager.h"
#include "SteamStats.h"
#include "Skill.h"
#include "SkillManager.h"
#include "GameClient.h"
#include "GameUI.h"
#include "Utilities.h"
bool CTriggerUnit::interact(CCharacter* actor)
{
    if (!getEnabled() || !m_bItemFlag1F0 || !actor ||
        (m_unitModel && m_unitModel->animationPlaying()))
        return false;
    CPlayer* player = dynamic_cast<CPlayer*>(actor);
    if (!player) return false;
    if (m_requiredQuest != EMPTY_WSTRING && !player->getQuestManager()->getQuestIsActive(m_requiredQuest)) {
        BroadcastEvent(0x30);
        return false;
    }
    if (m_requiredItem != EMPTY_WSTRING) {
        if (!m_pResourceManager) return false;
        CDataGroup* data = m_pResourceManager->getMasterResourceList()->getDataGroupByObjectName(m_requiredItem);
        if (!data) return false;
        long long guid = m_pResourceManager->getUnitGuidByDataGroup(data, L"UNIT_GUID");
        TArrayList<CEquipmentRef*> items(10), petItems(10);
        actor->getInventory()->getEquipmentsOfUnitGuid(guid, items);
        CCharacter* pet = actor->getFollower(0);
        if (pet && pet->getAIState() != static_cast<EAIState>(42))
            pet->getInventory()->getEquipmentsOfUnitGuid(guid, petItems);
        unsigned int count = 0;
        for (unsigned int i = 0; i < items.size(); ++i)
            count += items[i]->m_pEquipment->m_iUnknown238;
        for (unsigned int i = 0; i < petItems.size(); ++i)
            count += petItems[i]->m_pEquipment->m_iUnknown238;
        if (count < static_cast<unsigned int>(m_value2F0)) {
            BroadcastEvent(0x30);
            return false;
        }
        if (m_flag2F4 && m_value2F0 != 0) {
            unsigned int removed = 0;
            while (removed < items.size() && removed < static_cast<unsigned int>(m_value2F0)) {
                actor->getInventory()->removeEquipment(items[removed]->m_pEquipment);
                ++removed;
            }
            if (removed != static_cast<unsigned int>(m_value2F0)) {
                unsigned int i = 0;
                while (i < petItems.size() && i < static_cast<unsigned int>(m_value2F0) - removed) {
                    pet->getInventory()->removeEquipment(petItems[i]->m_pEquipment);
                    ++i;
                }
            }
        }
    }
    if (m_treasureClass.empty() && m_maxState == 1)
        CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(14), 1);
    return trigger(actor);
}

bool CTriggerUnit::trigger(CCharacter* actor)
{
    if (!m_bItemFlag1F0) return false;
    int next = m_state;
    if (m_cycleDirection == 0) ++next;
    else if (m_cycleDirection == 1) --next;
    bool useSkill = false;
    const int cycleMode = m_cycleMode;
    if (cycleMode == 1) {
        if (next > m_maxState) next = m_minState;
        useSkill = true;
    } else if (cycleMode == 2) {
        if (next >= m_maxState) m_cycleDirection = 1;
        else if (next <= m_minState) m_cycleDirection = 0;
    } else if (cycleMode == 0) {
        if (next >= m_maxState) {
            m_bItemFlag1F0 = false;
            if (m_treasureClass != EMPTY_WSTRING) {
                if (actor) actor->incrementJournalStatistic(static_cast<EJournalStatistic>(9), 1);
                unsigned int count = UTILITIES::randomIntegerBetweenVolatile(m_minTreasure, m_maxTreasure);
                spawnTreasureClass(actor, m_treasureClass, count);
            }
            useSkill = true;
        }
    } else return false;
    if (useSkill) {
        unsigned int selected = selectRandomSkill();
        CSkill* skill = selected == ~0u ? NULL : m_pSkillManager->getSkillByIndex(selected);
        if (skill) {
            CPositionableObject* target = actor ? static_cast<CPositionableObject*>(actor) : this;
            Ogre::Vector3 targetPosition = target->getPosition(true);
            const Ogre::Quaternion& orientation = m_pSceneNode->_getDerivedOrientation();
            Ogre::Vector3 position = getPosition(true) + Ogre::Vector3(0.0f, -m_fBaseUnitValue194, 0.0f);
            CSkill* executed = m_pSkillManager->executeSkill(skill, this, static_cast<ESKILL_ACTIVATION_TYPE>(0),
                position, orientation, targetPosition, actor);
            if (executed && actor && actor->ISA(UNITTYPES::PLAYER) && skill->m_skillType != 2) {
                if (actor->m_levelSound) {
                    if (cycleMode == 1) actor->m_levelSound->queueGlobalSample(0x36, 0.0f, 0.1f);
                    else actor->m_levelSound->queueGlobalSample(0x36, 1.0f, 1.0f);
                }
                actor->incrementJournalStatistic(static_cast<EJournalStatistic>(10), 1);
            }
        }
    }
    setTriggerState(static_cast<ETRIGGER_STATES>(next), true, false, true);
    CItem::interact(actor);
    if (ISA(static_cast<UNITTYPES::EUNITTYPES>(0x2b))) {
        TArrayList<CGameClient*>* clients = m_pResourceManager->getGameClients();
        for (unsigned int i = 0; i < clients->size(); ++i)
            if ((*clients)[i]->getPlayer())
                (*clients)[i]->warpLevels(L"Town", -99, 0, false, EMPTY_WSTRING, false);
    } else if (ISA(static_cast<UNITTYPES::EUNITTYPES>(0xad))) {
        std::wstring destination = EMPTY_WSTRING;
        if (m_pEffectManager && m_pEffectManager->hasEffect(static_cast<EEFFECT_TYPE>(0x71))) {
            TArrayList<CEffect*>& effects = m_pEffectManager->getActiveEffects(0);
            for (unsigned int i = 0; i < effects.size(); ++i) {
                if (effects[i]->m_eType == static_cast<EEFFECT_TYPE>(0x71)) {
                    destination = effects[i]->m_sName;
                    break;
                }
            }
            if (destination != EMPTY_WSTRING) {
                setEnabled(false);
                TArrayList<CGameClient*>* clients = m_pResourceManager->getGameClients();
                for (unsigned int i = 0; i < clients->size(); ++i)
                    if ((*clients)[i]->getPlayer())
                        (*clients)[i]->warpLevels(destination, 0, 0, false, EMPTY_WSTRING, false);
            }
        }
    } else if (ISA(static_cast<UNITTYPES::EUNITTYPES>(0xab))) {
        m_pResourceManager->getGameUI()->toggleWaypointMenu();
    }
    if (m_pDataGroup->GetDataValue(L"DESTROY_ON_DEATH", false))
        m_bBaseUnitFlag190 = true;
    return true;
}

#include "AnimationSet.h"
void CTriggerUnit::addAnimations()
{
    if (!getUnitModel()) return;
    m_animations.clear();
    CAnimationSet* animations = static_cast<CGenericModel*>(getUnitModel())->m_animationSet;
    if (!animations || animations->m_lUnknown28.empty()) return;
    std::string name = animations->m_lUnknown28[0];
    unsigned int state = 0;
    do {
        m_animations.add(0);
        m_altAnimations.add(~0u);
        unsigned int next = state + 1;
        std::wstring loopKey = L"ANIMATION_STATE_LOOP_" + STRINGS::StringConvertToWide(STRINGS::GetValueAsString(next));
        name = STRINGS::StringConvertToNarrow(m_pDataGroup->GetDataValue(loopKey, EMPTY_WSTRING).c_str());
        if (name.empty()) {
            m_looping.add(false);
            std::string key = "ANIMATION_STATE_" + STRINGS::GetValueAsString(next);
            name = STRINGS::StringConvertToNarrow(m_pDataGroup->GetDataValue(STRINGS::StringConvertToWide(key), EMPTY_WSTRING).c_str());
        } else m_looping.add(true);
        if (name != "") {
            for (unsigned int i = 0; i < animations->m_lUnknown28.size(); ++i)
                if (animations->m_lUnknown28[i] == name) {m_animations[state] = i; break;}
            std::string key = "ANIMATION_TRANSITION_STATE_" + STRINGS::GetValueAsString(next);
            name = STRINGS::StringConvertToNarrow(m_pDataGroup->GetDataValue(STRINGS::StringConvertToWide(key), EMPTY_WSTRING).c_str());
            for (unsigned int i = 0; i < animations->m_lUnknown28.size(); ++i)
                if (animations->m_lUnknown28[i] == name) {m_altAnimations[state] = i; break;}
        }
        state = next;
    } while (state <= static_cast<unsigned int>(m_maxState));
}

#include "CollisionModel.h"
#include "CollisionList.h"
#include "CullingBounds.h"
#include "FileUtilities.h"
#include "LevelTemplateData.h"
#include "UnitTriggerDescriptorNames.h"
#include <OgreEntity.h>
#include <OgreMesh.h>
void CTriggerUnit::unitInit(CDataGroup* data, bool initialize)
{
    if (!data) return;
    sceneNodeAttachEntity(NULL);
    m_stateLayouts.deleteAll();
    if (m_layout) {delete m_layout; m_layout = NULL;}
    if (m_unitModel) {delete m_unitModel; m_unitModel = NULL;}
    CMasterResourceManager::getSingleton()->removeCollisionModel(m_unitCollisionModel);
    m_unitCollisionModel = NULL;
    if (!m_pSoundBank)
        m_pSoundBank = new CSoundBank(*CMasterResourceManager::getSingleton()->m_pSoundManager, false);
    m_animations.clear();
    m_altAnimations.clear();
    CItem::unitInit(data, initialize);
    m_minState = 0;
    m_maxState = data->GetDataValue(L"MAXSTATES", 2) - 1;
    std::wstring directory = data->GetDataValue(L"RESOURCEDIRECTORY", EMPTY_WSTRING);
    std::wstring mesh = data->GetDataValue(L"MESHFILE", EMPTY_WSTRING);
    std::wstring layout = data->GetDataValue(L"LAYOUTFILE", EMPTY_WSTRING);
    std::wstring collision = data->GetDataValue(L"COLLISIONFILE", EMPTY_WSTRING);
    if (collision == EMPTY_WSTRING) collision = L"media/models/collider.mesh";
    else collision = FILESYSTEM::CleanPath(directory + L"/" + collision + L".mesh");
    std::wstring loop = STRINGS::StringUpper(data->GetDataValue(L"LOOPTYPE", EMPTY_WSTRING));
    for (unsigned int i = 0; i < 3; ++i)
        if (STRINGS::StringUpper(gTRIGGER_LOOP_TYPE_NAMES[i]) == loop) {m_cycleMode = i; break;}
    m_fBaseUnitValue194 = data->GetDataValue(L"COLLISION_RADIUS", m_fBaseUnitValue194);
    if (layout != EMPTY_WSTRING) {
        m_layout = new CLayout(m_pResourceManager, static_cast<ELAYOUT_TYPES>(0));
        m_layout->loadLayoutFile(FILESYSTEM::CleanPath(directory + L"/" + layout + L".layout"), false, NULL, false, false, 0);
        m_layout->setActivated(true);
        m_layout->sceneNodeSetParent(m_pSceneNode, false);
        m_layout->setVisible(true);
        m_layout->setEnabled(true);
        m_layout->fireEvent(static_cast<EEDITOR_EVENTS>(0), 0);
    }
    bool hardwareSkinning = m_pDataGroup->GetDataValue(L"ALLOW_HWSKINNING", true);
    if (m_bLevelLighting) hardwareSkinning = false;
    if (mesh != EMPTY_WSTRING) {
        mesh = FILESYSTEM::CleanPath(directory + L"/" + mesh + L".mesh");
        Ogre::SceneManager* scene = m_pResourceManager ? m_pResourceManager->getSceneManager() : NULL;
        m_unitModel = m_pResourceManager->createGenericModel(scene, mesh.c_str(), L"", hardwareSkinning, false, true);
        if (!m_unitModel) return;
        m_unitModel->setQueryMask(static_cast<OGRE_UTILITIES::EQUERYMASK>(2));
        m_unitModel->getEntity()->setRenderQueueGroup(0x32);
        m_unitModel->sceneNodeDetachEntity();
        m_unitModel->m_animationLoop = false;
        if (m_unitModel->m_animationSet && !m_unitModel->m_animationSet->m_lUnknown28.empty()) {
            if (m_unitModel->m_animationPlaying >= m_unitModel->m_animationSet->m_lUnknown28.size()) {
                m_unitModel->clearAnimations();
                m_unitModel->m_animationPlaying = 0;
            }
            m_unitModel->playAnimation(m_unitModel->m_animationPlaying, m_unitModel->m_animationLoop,
                m_unitModel->m_animationSpeed, -1.0f);
        }
        sceneNodeAttachEntity(m_unitModel->getEntity());
        if (!m_bLevelLighting) {
            CLevel* level = m_pResourceManager ? m_pResourceManager->getLevel() : NULL;
            if (level && level->getLevelTemplateData())
                m_unitModel->setRimLighting(level->getLevelTemplateData()->m_sRimlightTexture);
            else m_unitModel->setRimLighting(L"media/sharedtextures/rimlight.dds");
        }
        std::vector<CDataGroup*> groups;
        if (m_pDataGroup->GetDataGroupsMatchingName(L"BOUNDS", &groups)) {
            CDataGroup* bounds = groups[0];
            float minX = bounds->GetDataValue(L"MINX", -1.0f);
            float maxX = bounds->GetDataValue(L"MAXX", 1.0f);
            float minY = bounds->GetDataValue(L"MINY", -1.0f);
            float maxY = bounds->GetDataValue(L"MAXY", 1.0f);
            float minZ = bounds->GetDataValue(L"MINZ", -1.0f);
            float maxZ = bounds->GetDataValue(L"MAXZ", 1.0f);
            Ogre::AxisAlignedBox box(Ogre::Vector3(minX, minY, minZ), Ogre::Vector3(maxX, maxY, maxZ));
            m_unitModel->getEntity()->getMesh()->_setBounds(box, true);
        }
    }
    collision = FILESYSTEM::CleanPath(collision);
    m_unitCollisionModel = CMasterResourceManager::getSingleton()->addCollisionModel(collision);
    Ogre::Vector3 minimum, maximum;
    if (!m_bBlocksPath && m_unitModel) {
        const Ogre::AxisAlignedBox& box = m_unitModel->getEntity()->getMesh()->getBounds();
        minimum = box.getMinimum() + Ogre::Vector3(-0.25f, 0.0f, -0.25f);
        maximum = box.getMaximum() + Ogre::Vector3(0.25f, 1.0f, 0.25f);
    } else {
        if (m_bBlocksPath) m_bPathingFlag19C = true;
        CCollisionList* list = m_unitCollisionModel->getCollisionList();
        minimum = list->m_vBoundsMax + Ogre::Vector3(-0.25f, 0.0f, -0.25f);
        maximum = list->m_vBoundsMin + Ogre::Vector3(0.25f, 1.0f, 0.25f);
    }
    m_pCullingBounds->m_vLocalMinimum = minimum;
    m_pCullingBounds->m_vLocalMaximum = maximum;
    float radius = -minimum.x;
    if (radius <= maximum.x) radius = maximum.x;
    float value = -minimum.z;
    if (value <= radius) value = radius;
    radius = maximum.z <= value ? value : maximum.z;
    float negative = -radius;
    float minX = minimum.x <= negative ? minimum.x : negative;
    value = minX <= -maximum.z ? minX : -maximum.z;
    float minZ = value <= minimum.z ? value : minimum.z;
    value = -minZ <= maximum.z ? maximum.z : -minZ;
    float maxZ = -minimum.z <= value ? value : -minimum.z;
    value = -maxZ;
    if (maxZ < radius) {value = negative; maxZ = radius;}
    if (minimum.z <= negative) negative = minimum.z;
    if (negative <= value) value = negative;
    float finalMinZ = value <= minZ ? value : minZ;
    m_pCullingBounds->m_vMinimum = Ogre::Vector3(minZ, minimum.y, finalMinZ);
    m_pCullingBounds->m_vMaximum = Ogre::Vector3(radius, maximum.y, maxZ);
    updateCullingBounds();
    addSoundsToState(TRIGGER_STATE_ZERO, L"SOUND_STATE_ONE");
    addSoundsToState(TRIGGER_STATE_ONE, L"SOUND_STATE_TWO");
    m_requiredItem = data->GetDataValue(L"REQUIRED_UNIT", EMPTY_WSTRING);
    m_value2F0 = data->GetDataValue(L"REQUIRED_UNIT_COUNT", 0);
    m_flag2F4 = data->GetDataValue(L"TAKE_REQUIRED_UNIT", false);
    if (m_unitModel) addAnimations();
    unsigned int state = 0;
    if (m_maxState != -1) {
        do {
            unsigned int next = state + 1;
            std::wstring file = L"LAYOUT_STATE_" + STRINGS::GetValueAsWString(next);
            file = m_pDataGroup->GetDataValue(file, EMPTY_WSTRING);
            if (file != EMPTY_WSTRING) {
                while (m_stateLayouts.size() < next) m_stateLayouts.add(NULL);
                m_stateLayouts[state] = new CLayout(m_pResourceManager, static_cast<ELAYOUT_TYPES>(2));
                m_stateLayouts[state]->loadLayoutFile(file, false, NULL, false, false, 0);
                TArrayList<CEditorBaseObject*>* timelines = m_stateLayouts[state]->GetObjectsCreatedByADescriptor(L"Timeline");
                if (!timelines || timelines->size() == 0) {
                    if (m_stateLayouts[state]) {delete m_stateLayouts[state]; m_stateLayouts[state] = NULL;}
                    m_stateLayouts[state] = new CLayout(m_pResourceManager, static_cast<ELAYOUT_TYPES>(1));
                    m_stateLayouts[state]->loadLayoutFile(file, false, NULL, false, false, 0);
                }
                m_stateLayouts[state]->sceneNodeSetParent(m_pSceneNode, false);
                m_stateLayouts[state]->setActivated(true);
                m_stateLayouts[state]->setEnabled(true);
            }
            state = next;
        } while (state < m_maxState + 1u);
    }
    resetTrigger();
    setVisible(true, true);
    m_modelName = data->GetDataValue(L"NAME", m_modelName);
    CDataGroup* treasure = data->GetDataGroupByName(L"TREASURE", false);
    if (treasure) {
        m_treasureClass = treasure->GetDataValue(L"SPAWNCLASS", EMPTY_WSTRING);
        m_minTreasure = treasure->GetDataValue(L"MINCOUNT", 1);
        m_maxTreasure = treasure->GetDataValue(L"MAXCOUNT", 1);
    }
    if (m_pResourceManager && m_pResourceManager->getLevel() &&
        m_pResourceManager->getLevel()->m_automapRoomPieces) {
        const std::wstring& spawn = data->GetDataValue(L"SPAWNLAYOUT", EMPTY_WSTRING);
        if (spawn != EMPTY_WSTRING) {
            m_layout2C8 = new CLayout(m_pResourceManager, static_cast<ELAYOUT_TYPES>(1));
            m_layout2C8->loadLayoutFile(data->GetDataValue(L"SPAWNLAYOUT", EMPTY_WSTRING), false, NULL, false, false, 0);
            m_layout2C8->sceneNodeSetParent(m_pSceneNode, true);
            m_layout2C8->setVisible(true);
            m_layout2C8->setActivated(true);
            m_layout2C8->start();
        }
    }
    if (m_unitModel && m_state < static_cast<int>(m_animations.size())) {
        unsigned int animation = m_animations[m_state];
        if (animation != m_unitModel->m_animationPlaying)
            m_unitModel->playAnimation(m_animations[m_state], m_looping[m_state], 1.0f, -1.0f);
        if (animation != ~0u)
            m_unitModel->updateAnimation(m_unitModel->getAnimationLengthSeconds(animation) + 0.1f, true);
    }
    unitInitThemes();
}
