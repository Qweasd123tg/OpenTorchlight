#ifndef SKILLEVENT_H
#define SKILLEVENT_H

// SkillEvent.cpp: original base offsets 0, 0x10, 0x18, 0x20; size 0x228.

#include <OgreQuaternion.h>
#include <OgreVector3.h>
#include "BaseUnit.h"
#include "Character.h"
#include "DataGroup.h"
#include "EditorScene.h"
#include "SafePointer.h"
#include "SkillDefines.h"

enum ESKILL_BONE_ATTACHMENT { SKILL_BONE_NONE, SKILL_BONE_CENTER, SKILL_BONE_HEAD, SKILL_BONE_RIGHTHAND, SKILL_BONE_LEFTHAND, SKILL_BONE_RIGHTSHOULDER, SKILL_BONE_LEFTSHOULDER, SKILL_BONE_POSITION };
#include "TArrayList.h"
#include "PositionableObject.h"
#include "Randomizer.h"
#include "ResourceManager.h"
#include "RunicCore.h"
#include "Skill.h"
#include "iDamageShape.h"
#include "iMissile.h"
#include "iUnitSpawner.h"
class CDamageShape;
class CItem;
class CMissile;
class CSkillEffectAndAffixes;
class CSkillProperty;
class CUnitSpawner;
class CExecuteSkillProps;
class CPathController;
class CParticle;
namespace ParticleUniverse { class LineEmitter; }

class CSkillEvent : public CRunicCore, public iDamageShape, public iMissile, public iUnitSpawner
{
public:
    virtual ~CSkillEvent();
    virtual bool getCharacterCanBeAffectedByDamageShape(CDamageShape*, CCharacter*);
    virtual bool characterEffectedByDamageShape(CDamageShape*, CCharacter*, Ogre::Vector3*);
    virtual bool itemEffectedByDamageShape(CDamageShape*, CItem*);
    virtual void unitSpawnedFromUnitSpawner(CUnitSpawner*, CPositionableObject*);
    virtual void missileBeingFired(CMissile*);
    virtual void missileDieing(CMissile*);
    virtual bool missileApplyingEffects(CMissile*, CCharacter*, const Ogre::Vector3*, float, float);
    virtual bool getCharacterCanBeHarmedByMissile(CMissile*, CCharacter*);
    virtual CPositionableObject* missileValidateTargetBeforeLaunch(CMissile*, CPositionableObject*, Ogre::Vector3&);
    bool canAffixesAndEffectsBeAppliedToUnit(CBaseUnit*, CCharacter*);
    void addMinAndMaxValuesOfAnEffect(CResourceManager*, unsigned int, float&, float&);
    std::wstring getDisplayStats(CSkillProperty*);
    bool canEffectPosObject(const Ogre::Vector3&, CPositionableObject*);
    void invokeHitSkills(CCharacter*);
    bool effectsTargetEnemy(CBaseUnit*);
    bool applyEffects(CBaseUnit*, const Ogre::Vector3*, bool);
    bool applyWeaponDamage(CCharacter*, CItem*, float, float, bool, bool);
    bool shouldStop();
    bool canStop();
    Ogre::Vector3 getBonePosition(CBaseUnit*, ESKILL_BONE_ATTACHMENT, bool);
    void reset();
    void disableAllDamageShapes();
    void addListeners();
    void stopAllParticles(bool);
    void stopEvent();
    void resetEvent();
    bool startEvent(CBaseUnit*, CSkillProperty*, Ogre::Vector3, const Ogre::Quaternion&, CBaseUnit*, const Ogre::Vector3*);
    bool updateEvent(float);
    CSkillEvent(CSkill*, CSkillProperty*, CResourceManager*, CDataGroup*);

    class CLineEmitterWrapper : public CRunicCore
    {
    public:
        virtual ~CLineEmitterWrapper();
        CPositionableObject* m_object;
        ParticleUniverse::LineEmitter* m_emitter;
    };

    class CSkillEventPause : public CRunicCore
    {
    public:
        virtual ~CSkillEventPause();
        CBaseUnit* m_caster; // +0x10
        CSkillProperty* m_property;
        Ogre::Vector3 m_position;
        Ogre::Quaternion m_orientation; // +0x2c
        TSafePointer<CBaseUnit> m_target; // +0x40
        Ogre::Vector3 m_targetPosition; // +0x50
        bool m_paused; // +0x5c
        bool m_delayEnabled;
    };

    CSkill* m_pSkill; // +0x28
    CResourceManager* m_pResourceManager;
    CEditorScene* m_pEditorScene;
    CDamageShape* m_firstDamageShape; // +0x40
    ESKILL_EVENT_TYPE m_eventType;
    TSafePointer<CBaseUnit> m_caster; // +0x50
    TSafePointer<CBaseUnit> m_target; // +0x60
    TSafePointer<CCharacter> m_ownerCharacter; // +0x70
    TSafePointer<CBaseUnit> m_skillTarget; // +0x80
    CSkillProperty* m_pSkillProperty; // +0x90
    CSkillProperty* m_initialProperty;
    CSkillEffectAndAffixes* m_pSkillEffectAndAffixes;
    TArrayList<CLineEmitterWrapper*> m_particleWrappers; // +0xa8
    TArrayList<CUnitSpawner*> m_spawners; // +0xc0
    TArrayList<CDataGroup*> m_specificUnits; // +0xd8
    TArrayList<TSafePointer<CMissile>*> m_missiles; // +0xf0
    ESKILL_BONE_ATTACHMENT m_fireFromBone; // +0x108
    ESKILL_BONE_ATTACHMENT m_fireAtBone;
    TArrayList<CExecuteSkillProps*> m_executeSkills; // +0x110
    CRandomizer* m_pRandomizer; // +0x128
    int m_randomExecutionCount;
    bool m_active; // +0x134
    bool m_effectApplied; // +0x135
    bool m_hitSkillInvoked; // +0x136
    bool m_attaches; // +0x137
    bool m_applyEffects; // +0x138
    bool m_attachOwner; // +0x139
    bool m_castFromTarget; // +0x13a
    bool m_statsHidden; // +0x13b
    bool m_attachIgnoresUnits; // +0x13c
    bool m_attachIgnoresObstructions; // +0x13d
    bool m_attachToTarget; // +0x13e
    bool m_scaleAttachDistance; // +0x13f
    bool m_started; // +0x140
    bool m_applyEffectsAlways; // +0x141
    bool m_matchPetDuration; // +0x142
    bool m_makePet; // +0x143
    bool m_useDPS; // +0x144
    bool m_noStrikeParticles; // +0x145
    bool m_noStealEffects; // +0x146
    bool m_attachLineEmitter; // +0x147
    bool m_attachLineToMaxDistance; // +0x148
    bool m_lineEmitterCollides; // +0x149
    bool m_damageRequiresLOS; // +0x14a
    bool m_placeOnTarget; // +0x14b
    bool m_canClone; // +0x14c
    bool m_targetCorpses; // +0x14d
    bool m_syncPetsToOwner; // +0x14e
    bool m_missileTargetSelf; // +0x14f
    float m_weaponDamageScale; // +0x150
    float m_soakScale;
    float m_durationOverride;
    float m_remainingTime;
    float m_attachmentDistance;
    float m_targetAheadOfUnit;
    int m_maxUnitsHit;
    CPathController* m_pathToTarget; // +0x170
    bool m_pathFollowsTarget;
    unsigned int m_damageType;
    CSkillEventPause m_pause; // +0x180, size 0x60
    float m_minDelay; // expected +0x1e0
    float m_maxDelay;
    float m_delayRemaining;
    unsigned char m_gap1EC[4];
    Ogre::Vector3 m_targetOffset; // +0x1f0
    Ogre::Vector3 m_direction;
    int m_targetPositionX; // +0x208
    int m_targetPositionY;
    int m_targetPositionZ;
    CDataGroup* m_data; // +0x218
    CSkillEvent* m_cloneSource;
};

#endif
