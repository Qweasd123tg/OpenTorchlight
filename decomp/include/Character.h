#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include "BaseUnit.h"
#include "EquipmentDefines.h"
#include "WardrobeDefines.h"
#include "iInventoryListener.h"
#include "iMissile.h"

class CAIManager;
class CCharacterSaveState;
class CPathController;

// Partial: AI states of a character (character+0x330). Only the values used by
// recovered code are named; the names are ours.
enum EAIState
{
    // Leaves updateAI without an action; berserk resets the AI to it.
    AISTATE_IDLE = 2
};

// Partial: members used by recovered TUs. The vtable is complete; return
// types of virtual methods that recovered code does not call are not verified
// yet. Unnamed regions are padding until character.cpp is recovered.
class CCharacter : public CBaseUnit, public iInventoryListener, public iMissile
{
public:
    CCharacter(CResourceManager* resourceManager);
    virtual ~CCharacter();

    virtual void setVisible(bool visible);
    virtual void scaleUpdated(const Ogre::Vector3& scale);
    virtual void setActiveInLevel(bool active);
    virtual void unitThemeUpdated(CUnitTheme* theme, bool updated);
    virtual void* getUnitModel();
    virtual void* getUnitCollisionModel();
    virtual void unitInit(CDataGroup* dataGroup, bool initialize);
    virtual void levelResetting();
    virtual void update(Ogre::Camera* camera, const Ogre::Vector3& cameraPosition, float elapsed);
    virtual void setHighlighted(bool highlighted);
    virtual bool isEffectValidForUnit(CCharacter* source, CBaseUnit* target, CEffect* effect);
    virtual void applyEffectOnUnit(CCharacter* source, CBaseUnit* target, CEffect* effect);
    virtual float getEffectValue(EEFFECT_TYPE type, float value, const std::wstring& name);
    virtual void deactivateEffect(CEffect* effect);
    virtual void removeFromAvoidanceMap(CLevel& level);
    virtual void addToAvoidanceMap(CLevel& level);

    virtual bool getIsPlayer();
    virtual void levelLoaded(CLevel* level);
    virtual bool getIsInGodMode();
    virtual void fillSaveState(CCharacterSaveState& saveState);
    virtual void applySaveState(CCharacterSaveState& saveState);
    virtual void missileBeingFired(CMissile* missile);
    virtual void missileDieing(CMissile* missile);
    virtual void missileApplyingEffects(CMissile* missile, CCharacter* target, const Ogre::Vector3* position,
                                        float damageScale, float effectScale);
    virtual bool getCharacterCanBeHarmedByMissile(CMissile* missile, CCharacter* target);
    virtual bool missileValidateTargetBeforeLaunch(CMissile* missile, CPositionableObject* target,
                                                   Ogre::Vector3& position);
    virtual void equipmentPickedUp(CEquipment* equipment);
    virtual void equipmentDropped(CEquipment* equipment);
    virtual void equipmentEquipped(CEquipment* equipment);
    virtual void equipmentUnequipped(CEquipment* equipment);
    virtual void equipmentUsed(CEquipment* equipment);
    virtual void inventoryDestroyed();
    virtual void updateAnimation(float elapsed);
    virtual void loadModel(std::wstring model, std::wstring skeleton);
    virtual void setPathToFollow(CPathController* path);
    virtual void setLevel(unsigned int level, bool apply);
    virtual void levelUp();
    virtual void fameUp();
    virtual void die(CCharacter* killer, const Ogre::Vector3* direction, float force, bool silent);
    virtual void startFishing();
    virtual void catchFish();
    virtual void setAIState(EAIState state);
    virtual void reactToDamage(CCharacter* attacker, bool critical);
    virtual void updateAI(float elapsed, bool force);
    virtual void dyingAI(float elapsed, CLevel& level);
    virtual void returnToTownAI(float elapsed, CLevel& level);
    virtual void handInteractiveSequence(float elapsed);
    virtual void spawningAI(float elapsed, CLevel& level);
    virtual void updateActiveSkill(float elapsed);
    virtual void performingSkillAI(float elapsed);
    virtual void interruptAI(float elapsed, CLevel& level);
    virtual void fishingAICast(float elapsed, CLevel& level);
    virtual void immobileAI(float elapsed);
    virtual void fishingAI(float elapsed, CLevel& level);
    virtual void fishingAICatch(float elapsed, CLevel& level);
    virtual void huntAI(float elapsed, CLevel& level);
    virtual void skillApproachAI(float elapsed, CLevel& level, long long skillGuid);
    virtual void getItemAI(float elapsed, CLevel& level);
    virtual void approachAI(float elapsed, CLevel& level);
    virtual void attackAI(float elapsed, CLevel& level);
    virtual void skillAI(float elapsed, CLevel& level);
    virtual void openPortal(CLevel& level);
    virtual void openMapPortal(std::wstring dungeon, CLevel& level);
    virtual bool canAttackWithCurrentWeapon();
    virtual void applyAchievementsForKilledCharacter(CCharacter* killed);
    virtual void notifyAISkillComplete();
    virtual void calculateMaxMana();
    virtual void calculateMaxHP();

    void interrupt(bool force);
    void setTarget(CCharacter* target);
    void setAlignment(EAlignment alignment);

    CAIManager* getAIManager() { return m_pAIManager; }

private:
    char m_CharacterData[0x718 - 0x1e8];
    CAIManager* m_pAIManager;
};

#endif
