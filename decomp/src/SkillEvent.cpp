#include "SkillEvent.h"
#include "SkillEffectAndAffixes.h"
#include "SkillProperty.h"
#include "Equipment.h"
#include "Missile.h"
#include "UnitSpawner.h"
#include "ParticleWrapper.h"
#include "Layout.h"
#include "DamageShape.h"
#include "EmptyStrings.h"
#include "Item.h"
#include "ExecuteSkillProps.h"
#include "PathController.h"
#include "Level.h"
#include "AIManager.h"
#include "GenericModel.h"
#include <OgreEntity.h>
#include <OgreMesh.h>
#include <cmath>
#include <new>

bool CSkillEvent::canAffixesAndEffectsBeAppliedToUnit(CBaseUnit* unit,CCharacter* character)
{
    return m_pSkillEffectAndAffixes ? m_pSkillEffectAndAffixes->canAffixesAndEffectsBeAppliedToUnit(unit,character) : true;
}

std::wstring CSkillEvent::getDisplayStats(CSkillProperty* property)
{
    if(m_pSkillEffectAndAffixes && !m_statsHidden && (property || m_pSkillProperty || m_initialProperty))
        return m_pSkillEffectAndAffixes->getDisplayStats();
    return EMPTY_WSTRING;
}

bool CSkillEvent::canEffectPosObject(const Ogre::Vector3& point,CPositionableObject* object)
{
    return !(std::fabs(point.y-object->getPosition(true).y)>3.0f);
}

bool CSkillEvent::effectsTargetEnemy(CBaseUnit* unit)
{
    if(m_pSkillProperty) {
        CSkillEffectAndAffixes* effects=m_pSkillEffectAndAffixes;
        if(!effects)effects=m_pSkillProperty->m_pSkillEffectAndAffixes;
        if(effects)return effects->effectsTargetEnemy(unit);
    }
    return false;
}

bool CSkillEvent::shouldStop()
{
    if(m_missiles.size() || m_remainingTime>0.0f || m_pSkill->m_eActivationType==SKILL_ACTIVATION_PASSIVE)
        return false;
    if(m_pEditorScene) {
        if(m_pEditorScene->getNumberOfTimelinesUpdating(true) || m_pEditorScene->getNumberOfParticlesUpdating() || m_pSkill->m_animationIndexLoopInto!=static_cast<unsigned int>(-1))
            return false;
        for(unsigned i=0;i<m_spawners.size();++i)
            if(m_spawners[i]->getParticlesStillVisible())return false;
    }
    return true;
}

bool CSkillEvent::canStop()
{
    if(!(m_remainingTime>0.0f)) {
        if(!m_pEditorScene || m_pSkill->m_animationIndexLoopInto!=static_cast<unsigned int>(-1))return true;
        if(m_pEditorScene->getNumberOfTimelinesUpdating(true)==0 && m_pEditorScene->getNumberOfParticlesUpdating()==0) {
            for(unsigned i=0;i<m_spawners.size();++i)
                if(m_spawners[i]->getParticlesStillVisible())return false;
            return true;
        }
    }
    return false;
}

void CSkillEvent::disableAllDamageShapes()
{
    if(m_pEditorScene) {
        TArrayList<CEditorBaseObject*> shapes(10);
        m_pEditorScene->GetObjectsCreatedByADescriptor(L"Damage Shape",&shapes);
        for(unsigned i=0;i<shapes.size();++i)static_cast<CDamageShape*>(shapes[i])->setEnabled(false);
    }
}

void CSkillEvent::stopAllParticles(bool immediately)
{
    if(m_pEditorScene) {
        TArrayList<CEditorBaseObject*> particles(10);
        m_pEditorScene->GetObjectsCreatedByADescriptor(L"Particle",&particles);
        for(unsigned i=0;i<particles.size();++i)static_cast<CParticleWrapper*>(particles[i])->stop();
        particles.clear();
        m_pEditorScene->GetObjectsCreatedByADescriptor(L"Layout Link Particle",&particles);
        for(unsigned i=0;i<particles.size();++i)static_cast<CLayout*>(particles[i])->stop(immediately);
    }
    for(unsigned i=0;i<m_spawners.size();++i)m_spawners[i]->stopAllParticles();
}

void CSkillEvent::stopEvent()
{
    m_active=false;
    if(m_pEditorScene)static_cast<CLayout*>(m_pEditorScene)->stop(false);
    stopAllParticles(m_pSkill->m_animationIndexLoopInto!=static_cast<unsigned int>(-1));
    disableAllDamageShapes();
}

void CSkillEvent::resetEvent()
{
    stopEvent();
    m_started=false;
}

void CSkillEvent::addMinAndMaxValuesOfAnEffect(CResourceManager* resources,unsigned effect,float& minimum,float& maximum)
{
    if(m_pSkillEffectAndAffixes)m_pSkillEffectAndAffixes->addMinAndMaxValuesOfAnEffect(resources,effect,minimum,maximum);
    const float scale=m_weaponDamageScale;
    if(scale<=0.0f)return;
    CCharacter* owner=m_ownerCharacter.getObject();
    if(!owner) {
        owner=m_pSkill->getMasterOwnerCharacter();
        m_ownerCharacter.setObject(owner);
        if(!owner)return;
    }
    CEquipment* right=static_cast<CEquipment*>(owner->getWeaponInRightHand());
    CEquipment* left=m_ownerCharacter.getObject()?static_cast<CEquipment*>(m_ownerCharacter.getObject()->getWeaponInLeftHand()):NULL;
    bool dual=m_pSkillProperty?m_pSkillProperty->m_bHasAnimation:false;
    CEquipment* weapon=right?right:left;
    if(weapon) {
        minimum+=static_cast<float>(static_cast<unsigned int>(weapon->minimumDamage()))*scale;
        maximum+=static_cast<float>(static_cast<unsigned int>(weapon->maximumDamage()))*scale;
    }
    if(dual && left) {
        minimum+=static_cast<float>(static_cast<unsigned int>(left->minimumDamage()))*scale;
        maximum+=static_cast<float>(static_cast<unsigned int>(left->maximumDamage()))*scale;
    }
}

CPositionableObject* CSkillEvent::missileValidateTargetBeforeLaunch(CMissile* missile,CPositionableObject* target,Ogre::Vector3& position)
{
    if(!m_missileTargetSelf) {
        if(m_pSkill) {
            if(m_pSkill->getTargetType()==0)return NULL;
            if(m_pSkill && m_pSkill->m_Target.getObject() && m_pSkill->getTargetType()!=1 && m_pSkill->getTargetType()!=11) {
                position=m_pSkill->m_Target.getObject()->getPosition(true);
                return m_pSkill->m_Target.getObject();
            }
        }
        position=m_targetOffset;
        return target;
    }
    CCharacter* owner=m_pSkill->getOwnerCharacter();
    if(owner) {
        position=getBonePosition(owner,SKILL_BONE_CENTER,true);
        missile->m_bUnknown144=true;
    }
    return owner;
}

void CSkillEvent::missileBeingFired(CMissile* missile)
{
    typedef TSafePointer<CMissile> Pointer;
    void* storage=Ogre::GeneralAllocPolicy::allocateBytes(sizeof(Pointer));
    Pointer* pointer=new(storage)Pointer;
    pointer->setObject(missile);
    m_missiles.add(pointer);
}

void CSkillEvent::missileDieing(CMissile* missile)
{
    unsigned i=0;
    while(i<m_missiles.size()) {
        TSafePointer<CMissile>* pointer=m_missiles[i];
        if(!pointer->getObject() || pointer->getObject()==missile) {
            if(pointer) {
                pointer->~TSafePointer<CMissile>();
                Ogre::GeneralAllocPolicy::deallocateBytes(pointer);
                m_missiles[i]=NULL;
            }
            m_missiles.removeAt(i);
        } else ++i;
    }
    if(m_pSkill && static_cast<int>(m_eventType)!=7)
        m_pSkill->triggerEvent(static_cast<ESKILL_EVENT_TYPE>(7),missile->getPosition(true),missile->getSceneNode()->getOrientation(),NULL,NULL);
}

void CSkillEvent::reset()
{
    if(m_pEditorScene)m_pEditorScene->setVisible(false);
    for(unsigned i=0;i<m_missiles.size();++i) {
        CMissile* missile=m_missiles[i]->getObject();
        if(missile)missile->m_Listeners.remove(static_cast<iMissile*>(this));
    }
    // The original clears the handle array here without deleting its elements.
    m_missiles.clear();
    m_active=false;m_started=false;m_effectApplied=false;m_hitSkillInvoked=false;
    m_ownerCharacter.setObject(NULL);m_target.setObject(NULL);m_pSkillProperty=NULL;m_caster.setObject(NULL);
}

void CSkillEvent::invokeHitSkills(CCharacter* character)
{
    if(character || m_pSkill) {
        if(static_cast<int>(m_eventType)!=4)
            m_pSkill->triggerEvent(static_cast<ESKILL_EVENT_TYPE>(4),character->getPosition(true),character->getSceneNode()->getOrientation(),character,NULL);
        if(character->HP()<1 && static_cast<int>(m_eventType)!=5)
            m_pSkill->triggerEvent(static_cast<ESKILL_EVENT_TYPE>(5),character->getPosition(true),character->getSceneNode()->getOrientation(),character,NULL);
    }
}

bool CSkillEvent::applyEffects(CBaseUnit* unit,const Ogre::Vector3* position,bool flag)
{
    if(!m_pSkillProperty || !unit)return false;
    CCharacter* character=dynamic_cast<CCharacter*>(unit);
    const bool wasAlive=character?character->alive():true;
    if(m_damageRequiresLOS) {
        Ogre::Vector3 end=unit->getPosition(true)+Ogre::Vector3(0,1,0);
        Ogre::Vector3 start=m_pSkill->getMasterOwner()->getPosition(true)+Ogre::Vector3(0,1,0);
        Ogre::Vector3 hit,normal;
        if(m_pResourceManager->getLevel()->rayCollision(start,end,hit,normal,true))return true;
    }
    bool result=false;
    if(m_pSkillEffectAndAffixes) {
        result=m_pSkillEffectAndAffixes->applyAffixesAndEffects(unit,m_pSkill->getMasterOwnerCharacter(),position,flag);
        result=m_pSkillEffectAndAffixes->removeAffixesAndEffects(unit,m_pSkill->getMasterOwnerCharacter())|result;
    } else if(m_pSkillProperty->m_pSkillEffectAndAffixes) {
        result=m_pSkillProperty->m_pSkillEffectAndAffixes->applyAffixesAndEffects(unit,m_pSkill->getMasterOwnerCharacter(),position,flag);
        result=m_pSkillProperty->m_pSkillEffectAndAffixes->removeAffixesAndEffects(unit,m_pSkill->getMasterOwnerCharacter())|result;
    }
    if(character) {
        CLevel* level=unit->getResourceManager()?unit->getResourceManager()->getLevel():NULL;
        character->updateEffects(0.0f,*level);
        if(!wasAlive && character->HP()>0)character->setAIState(static_cast<EAIState>(2));
    }
    return result;
}

bool CSkillEvent::characterEffectedByDamageShape(CDamageShape* shape,CCharacter* character,Ogre::Vector3* direction)
{
    if(!canEffectPosObject(shape->getPosition(true),character))return false;
    if(shape->m_shapeKind==4 && m_pSkillProperty->getOwnerCharacter() && direction) {
        Ogre::Vector3 ownerPosition=m_pSkillProperty->getOwnerCharacter()->getPosition(true);
        *direction=character->getPosition(true)-ownerPosition;
        direction->y=0;
        direction->normalise();
    }
    bool result=applyEffects(character,direction,false);
    result=applyWeaponDamage(character,NULL,1.0f,1.0f,false,false)|result;
    invokeHitSkills(character);
    return result;
}

bool CSkillEvent::itemEffectedByDamageShape(CDamageShape* shape,CItem* item)
{
    if(!canEffectPosObject(shape->getPosition(true),item))return false;
    bool result=applyWeaponDamage(NULL,item,1.0f,1.0f,false,false);
    CSkillEffectAndAffixes* effects=m_pSkillEffectAndAffixes?m_pSkillEffectAndAffixes:m_pSkillProperty->m_pSkillEffectAndAffixes;
    if(effects && effects->isDamaging())result=true;
    return result;
}

bool CSkillEvent::missileApplyingEffects(CMissile* missile,CCharacter* character,const Ogre::Vector3* position,float damageScale,float effectScale)
{
    if(!canEffectPosObject(missile->getPosition(true),character))return false;
    if(m_pSkill && !missile->m_bUnknown294 && static_cast<int>(m_eventType)!=6)
        m_pSkill->triggerEvent(static_cast<ESKILL_EVENT_TYPE>(6),missile->getPosition(true),missile->getSceneNode()->getOrientation(),character,NULL);
    bool result=applyWeaponDamage(character,NULL,damageScale,effectScale,true,missile->m_bUnknown294);
    result=applyEffects(character,position,missile->m_bUnknown294)|result;
    invokeHitSkills(character);
    return result;
}

bool CSkillEvent::getCharacterCanBeAffectedByDamageShape(CDamageShape* shape,CCharacter* character)
{
    Ogre::Vector3 position=shape->getPosition(true);
    bool deadOnly=shape->m_bTargetOnlyDead;
    CCharacter* owner=m_pSkill->getMasterOwnerCharacter();
    if(!character || !m_pSkillProperty)return false;
    if(deadOnly || m_targetCorpses) {
        if(character->HP()>0)return false;
    } else if(character->HP()<1)return false;
    if(m_pSkillProperty->m_bSingleTarget && character!=m_skillTarget.getObject())return false;
    if(!owner) {
        owner=m_pSkillProperty->getOwnerCharacter();
        if(!owner)return true;
    }
    if(!canEffectPosObject(position,character))return false;
    if(m_pSkillProperty->m_eTargetUnitType && !character->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_pSkillProperty->m_eTargetUnitType)))return false;
    if(m_specificUnits.size()) {
        unsigned i=0;
        for(;i<m_specificUnits.size();++i)if(m_specificUnits[i]==character->m_pDataGroup)break;
        if(i==m_specificUnits.size())return false;
    }
    if(m_pSkillProperty->m_eTargetType==4)return true;
    if(m_pSkill->getTargetType()==10 && character!=owner && character->m_pMaster!=owner && (!owner->m_pMaster || character!=owner->m_pMaster))return false;
    if(m_pSkill->getTargetType()==9 && character->m_pMaster!=owner)return false;
    bool enemy=owner->isEnemy(character);
    if(!owner->m_pAIManager || owner->m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(1)) || owner->alignment()==4)return true;
    if(m_pSkillProperty->m_iSkillLevel==2)return enemy;
    if(m_pSkillProperty->m_iSkillLevel==1)return !enemy;
    return false;
}

bool CSkillEvent::getCharacterCanBeHarmedByMissile(CMissile* missile,CCharacter* character)
{
    CCharacter* owner=m_pSkill->getMasterOwnerCharacter();
    if(!owner && missile->m_owner.getObject())owner=dynamic_cast<CCharacter*>(missile->m_owner.getObject());
    if(m_missileTargetSelf && character==owner)return character!=NULL;
    if(!character || !m_pSkillProperty)return false;
    if(m_targetCorpses) {
        if(character->HP()>0)return false;
    } else if(character->HP()<1)return false;
    if(m_pSkillProperty->m_bSingleTarget && character!=m_skillTarget.getObject() && (!missile || !missile->m_bUnknown294))return false;
    if(!owner) {
        owner=m_pSkillProperty->getOwnerCharacter();
        if(!owner)return true;
    }
    if(m_pSkillProperty->m_eTargetUnitType && !character->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_pSkillProperty->m_eTargetUnitType)))return false;
    if(m_specificUnits.size()) {
        unsigned i=0;
        for(;i<m_specificUnits.size();++i)if(m_specificUnits[i]==character->m_pDataGroup)break;
        if(i==m_specificUnits.size())return false;
    }
    if(m_pSkillProperty->m_eTargetType==4)return true;
    if(m_pSkill->getTargetType()==10 && character!=owner && character->m_pMaster!=owner && (!owner->m_pMaster || character!=owner->m_pMaster))return false;
    if(m_pSkill->getTargetType()==9 && character->m_pMaster!=owner)return false;
    bool enemy=owner->isEnemy(character);
    if(!owner->m_pAIManager || owner->m_pAIManager->hasAIFlag(static_cast<EAIFLAG_TYPES>(1)) || owner->alignment()==4)return true;
    if(m_pSkillProperty->m_iSkillLevel==2 && enemy)return true;
    if(m_pSkillProperty->m_iSkillLevel==1 && !enemy)return true;
    return missile?missile->m_bUnknown294:false;
}

Ogre::Vector3 CSkillEvent::getBonePosition(CBaseUnit* unit,ESKILL_BONE_ATTACHMENT attachment,bool includePosition)
{
    Ogre::Vector3 result=Ogre::Vector3::ZERO;
    if(!unit)return result;
    if(includePosition) {
        result+=unit->getPosition(true);
        result.y-=unit->m_fBaseUnitValue194;
    }
    CCharacter* character=m_caster.getObject()?dynamic_cast<CCharacter*>(m_caster.getObject()):NULL;
    float scale=*unit->getScaleFloat();
    if((!character && attachment==SKILL_BONE_NONE) || attachment==SKILL_BONE_CENTER) {
        if(unit->getUnitModel() && static_cast<CGenericModel*>(unit->getUnitModel())->getEntity() && !static_cast<CGenericModel*>(unit->getUnitModel())->getEntity()->getMesh().isNull()) {
            float maximum=static_cast<CGenericModel*>(unit->getUnitModel())->getEntity()->getMesh()->getBounds().getMaximum().y;
            float minimum=static_cast<CGenericModel*>(unit->getUnitModel())->getEntity()->getMesh()->getBounds().getMinimum().y;
            result+=Ogre::Vector3(0,std::fabs((maximum-minimum)*0.5f)*scale,0);
        }
        return result;
    }
    Ogre::SceneNode* node=NULL;
    switch(attachment) {
    case SKILL_BONE_HEAD:node=character->m_pHeadNode;break;
    case SKILL_BONE_RIGHTHAND:node=character->m_pRightHandNode;break;
    case SKILL_BONE_LEFTHAND:node=character->m_pLeftHandNode;break;
    case SKILL_BONE_RIGHTSHOULDER:node=character->m_pRightShoulderNode;break;
    case SKILL_BONE_LEFTSHOULDER:node=character->m_pLeftShoulderNode;break;
    default:return result;
    }
    return node?node->getPosition()*scale+result:Ogre::Vector3::ZERO;
}

void CSkillEvent::addListeners()
{
    if(!m_pEditorScene)return;
    TArrayList<CEditorBaseObject*>* shapes=m_pEditorScene->GetObjectsCreatedByADescriptor(L"Damage Shape");
    if(shapes) {
        for(unsigned i=0;i<shapes->size();++i) {
            CDamageShape* shape=dynamic_cast<CDamageShape*>((*shapes)[i]);
            if(shape) {
                if(m_targetCorpses)shape->m_bTargetOnlyDead=true;
                if(m_maxUnitsHit>0)shape->m_iTotalNumberOfTargets=m_maxUnitsHit;
                if(shape->m_damageListeners.find(static_cast<iDamageShape*>(this))==-1)shape->m_damageListeners.add(static_cast<iDamageShape*>(this));
                if(!m_firstDamageShape)m_firstDamageShape=shape;
            }
        }
    }
    TArrayList<CEditorBaseObject*>* spawners=m_pEditorScene->GetObjectsCreatedByADescriptor(L"Unit Spawner");
    if(spawners) {
        for(unsigned i=0;i<spawners->size();++i) {
            CUnitSpawner* spawner=dynamic_cast<CUnitSpawner*>((*spawners)[i]);
            if(spawner) {
                m_spawners.add(spawner);
                if(spawner->m_spawnListeners.find(static_cast<iUnitSpawner*>(this))==-1)spawner->m_spawnListeners.add(static_cast<iUnitSpawner*>(this));
            }
        }
    }
}

CSkillEvent::~CSkillEvent()
{
    reset();
    m_particleWrappers.deleteAll();
    m_specificUnits.clear();
    m_cloneSource=NULL;
    m_executeSkills.deleteAll();
    m_active=false;m_firstDamageShape=NULL;m_pSkill=NULL;
    m_ownerCharacter.setObject(NULL);
    delete m_pathToTarget;m_pathToTarget=NULL;
    delete m_pEditorScene;m_pEditorScene=NULL;
    delete m_pSkillEffectAndAffixes;m_pSkillEffectAndAffixes=NULL;
    delete m_pRandomizer;m_pRandomizer=NULL;
}

void CSkillEvent::unitSpawnedFromUnitSpawner(CUnitSpawner*,CPositionableObject* object)
{
    if(!object)return;
    CMissile* missile=dynamic_cast<CMissile*>(object);
    if(missile) {
        missile->m_owner.setObject(m_ownerCharacter.getObject());
        if(missile->m_Listeners.find(static_cast<iMissile*>(this))==-1)missile->m_Listeners.add(static_cast<iMissile*>(this));
        return;
    }
    CCharacter* character=dynamic_cast<CCharacter*>(object);
    if(!character || !m_ownerCharacter.getObject())return;
    character->setAlignment(m_ownerCharacter.getObject()->alignment());
    character->setLevel(m_ownerCharacter.getObject()->m_iUnitLevel,false);
    if(m_makePet)m_ownerCharacter.getObject()->addPet(character);
    if(m_syncPetsToOwner) {
        std::string animation=EMPTY_STRING;
        float time=0,speed=1;
        if(m_ownerCharacter.getObject()->getUnitModel()) {
            unsigned index=m_ownerCharacter.getObject()->getAnimationPlaying();
            animation=static_cast<CGenericModel*>(m_ownerCharacter.getObject()->getUnitModel())->getAnimationName(index);
            time=static_cast<CGenericModel*>(m_ownerCharacter.getObject()->getUnitModel())->getAnimationTime();
            speed=static_cast<CGenericModel*>(m_ownerCharacter.getObject()->getUnitModel())->m_animationSpeed;
        }
        if(!animation.empty() && character->getUnitModel()) {
            int index=static_cast<CGenericModel*>(character->getUnitModel())->getAnimationIndex(animation);
            if(index>=0) {
                character->setAIPlayAnimation(animation,false,0.1f,speed);
                character->updateAnimation(time);
            }
        }
    }
    applyEffects(character,NULL,false);
    if(m_matchPetDuration)m_remainingTime=character->getEffectValue(static_cast<EEFFECT_TYPE>(0x2f),static_cast<EDAMAGE_TYPES>(7));
}

namespace ParticleUniverse { class LineEmitter { public: void setEnd(const Ogre::Vector3&); }; }

bool CSkillEvent::updateEvent(float elapsed)
{
    if(m_pause.m_paused) {
        m_delayRemaining-=elapsed;
        if(!(m_delayRemaining<=0.0f))return true;
        const Ogre::Vector3* target=m_pause.m_targetPosition!=Ogre::Vector3::ZERO?&m_pause.m_targetPosition:NULL;
        startEvent(m_pause.m_caster,m_pause.m_property,m_pause.m_position,m_pause.m_orientation,m_pause.m_target.getObject(),target);
    }
    if(!m_pSkillProperty)return false;
    if(!m_skillTarget.getObject())m_skillTarget.setObject(m_pSkill->m_Target.getObject());
    if(!m_active)return !canStop();
    m_remainingTime-=elapsed;
    if(!m_pEditorScene)return !canStop();
    if(m_attaches && m_pSkillProperty->getOwnerCharacter()) {
        CCharacter* owner=m_pSkillProperty->getOwnerCharacter();
        Ogre::Vector3 ahead=Ogre::Vector3::ZERO;
        if(owner && m_targetAheadOfUnit!=0.0f) {
            CCharacter* character=dynamic_cast<CCharacter*>(static_cast<CBaseUnit*>(owner));
            if(character && character->m_returningToTown && character->m_runningSpeed>character->m_walkingSpeed)
                ahead=owner->getForward()*m_targetAheadOfUnit;
        }
        Ogre::Vector3 position=ahead+m_pSkillProperty->getOwnerCharacter()->getPosition(true);
        m_pEditorScene->setPosition(position);
        m_pEditorScene->setOrientation(m_pSkillProperty->getOwnerCharacter()->getSceneNode()->getOrientation());
    }
    if(m_attachToTarget) {
        if(!m_skillTarget.getObject() || m_attachLineToMaxDistance) {
            Ogre::Vector3 local=getBonePosition(m_pSkillProperty->getOwnerCharacter(),m_fireFromBone,false);
            Ogre::Vector3 offset=m_pSkillProperty->getOwnerCharacter()->getOrientation()*local;
            float height=m_pSkillProperty->getOwnerCharacter()->m_fBaseUnitValue194;
            Ogre::Vector3 position=m_pSkillProperty->getOwnerCharacter()->getPosition(true);
            Ogre::Vector3 start(offset.x+position.x,(position.y-height)+offset.y,offset.z+position.z);
            float range=m_pSkill->getRange();
            Ogre::Vector3 end=m_pSkillProperty->getOwnerCharacter()->getForward()*range+start;
            if(m_lineEmitterCollides) {
                Ogre::Vector3 hit,normal;
                if(m_pResourceManager->getLevel()->rayCollision(start,end,hit,normal,true))end=normal*-0.1f+hit;
            }
            m_pEditorScene->setPosition(end);
            m_pEditorScene->setOrientation(m_pSkillProperty->getOwnerCharacter()->getOrientation(),false);
        } else {
            ESKILL_BONE_ATTACHMENT attachment=m_fireFromBone==SKILL_BONE_NONE?SKILL_BONE_CENTER:m_fireFromBone;
            Ogre::Vector3 position=getBonePosition(m_skillTarget.getObject(),attachment,true);
            CBaseUnit* target=m_skillTarget.getObject();
            Ogre::Vector3 ahead=Ogre::Vector3::ZERO;
            if(target && m_targetAheadOfUnit!=0.0f) {
                CCharacter* character=dynamic_cast<CCharacter*>(target);
                if(character && character->m_returningToTown && character->m_runningSpeed>character->m_walkingSpeed)
                    ahead=target->getForward()*m_targetAheadOfUnit;
            }
            m_pEditorScene->setPosition(ahead+position);
            m_pEditorScene->setOrientation(m_skillTarget.getObject()->getSceneNode()->getOrientation());
        }
    }
    if(m_pathFollowsTarget && m_pathToTarget && m_skillTarget.getObject()) {
        Ogre::Vector3 position=getBonePosition(m_skillTarget.getObject(),SKILL_BONE_CENTER,true);
        CBaseUnit* target=m_skillTarget.getObject();
        Ogre::Vector3 ahead=Ogre::Vector3::ZERO;
        if(target && m_targetAheadOfUnit!=0.0f) {
            CCharacter* character=dynamic_cast<CCharacter*>(target);
            if(character && character->m_returningToTown && character->m_runningSpeed>character->m_walkingSpeed)
                ahead=target->getForward()*m_targetAheadOfUnit;
        }
        m_pathToTarget->positionUpdated(ahead+position);
    }
    unsigned timelines=0;
    bool stoppedParticles=false;
    if(m_pSkill->m_animationIndexLoopInto==static_cast<unsigned>(-1)) {
        timelines=m_pEditorScene->getNumberOfTimelinesUpdating(true);
        m_pEditorScene->update(elapsed);
        if(timelines) {
            unsigned remaining=m_pEditorScene->getNumberOfTimelinesUpdating(true);
            if((remaining==0 || m_durationOverride>0.0f) && m_remainingTime<=0.0f) {
                stopAllParticles(false);
                stoppedParticles=true;
            }
        }
    } else m_pEditorScene->update(elapsed);
    if(!stoppedParticles && m_pathToTarget && (m_pathToTarget->m_bUnknown136 || m_durationOverride>0.0f) && m_remainingTime<=0.0f)
        stopAllParticles(false);
    if(timelines && m_firstDamageShape && m_attachOwner && m_pSkillProperty->getOwnerCharacter()) {
        Ogre::Vector3 position=m_firstDamageShape->getPosition(false);
        if(m_pSkill && m_pSkill->getTargetType()==1)
            position=m_direction*position.z+m_pEditorScene->getPosition(true);
        else {
            if(m_scaleAttachDistance) {position.x*=m_attachmentDistance;position.z*=m_attachmentDistance;}
            position=m_pEditorScene->getOrientationQuaternion()*position;
            position+=m_pEditorScene->getPosition(true);
        }
        if(!m_pSkillProperty->getOwnerCharacter()->moveToPosition(position,m_attachIgnoresUnits,m_attachIgnoresObstructions))stopEvent();
    }
    if((m_attachLineEmitter || m_attachLineToMaxDistance) && m_particleWrappers.size()) {
        for(unsigned i=0;i<m_particleWrappers.size();++i) {
            Ogre::Vector3 local=getBonePosition(m_pSkillProperty->getOwnerCharacter(),m_fireFromBone,false);
            Ogre::Vector3 offset=m_pSkillProperty->getOwnerCharacter()->getOrientation()*local;
            float height=m_pSkillProperty->getOwnerCharacter()->m_fBaseUnitValue194;
            Ogre::Vector3 position=m_pSkillProperty->getOwnerCharacter()->getPosition(true);
            Ogre::Vector3 start(offset.x+position.x,(position.y-height)+offset.y,offset.z+position.z);
            m_particleWrappers[i]->m_object->setPosition(local);
            Ogre::Vector3 end;
            CBaseUnit* target;
            if(!m_skillTarget.getObject() || m_attachLineToMaxDistance) {
                float range=m_pSkill->getRange();
                end=m_pSkillProperty->getOwnerCharacter()->getForward()*range+start;
                if(m_lineEmitterCollides) {
                    Ogre::Vector3 hit,normal;
                    if(m_pResourceManager->getLevel()->rayCollision(start,end,hit,normal,true))end=normal*-0.1f+hit;
                }
                target=m_pSkillProperty->getOwnerCharacter();
            } else {
                end=getBonePosition(m_skillTarget.getObject(),m_fireAtBone,true);
                if(m_lineEmitterCollides) {
                    Ogre::Vector3 hit,normal;
                    if(m_pResourceManager->getLevel()->rayCollision(start,end,hit,normal,true))end=normal*-0.1f+hit;
                }
                target=m_skillTarget.getObject();
            }
            Ogre::Vector3 ahead=Ogre::Vector3::ZERO;
            if(target && m_targetAheadOfUnit!=0.0f) {
                CCharacter* character=dynamic_cast<CCharacter*>(target);
                if(character && character->m_returningToTown && character->m_runningSpeed>character->m_walkingSpeed)
                    ahead=target->getForward()*m_targetAheadOfUnit;
            }
            m_particleWrappers[i]->m_emitter->setEnd((end-start)+ahead);
        }
    }
    if(m_applyEffectsAlways && m_pSkillProperty && m_skillTarget.getObject())applyEffects(m_skillTarget.getObject(),NULL,false);
    if(!shouldStop())return true;
    if(m_pathToTarget && m_pSkillProperty->getOwnerCharacter() && m_pathToTarget==m_pSkillProperty->getOwnerCharacter()->m_pathToFollow.getObject())
        m_pSkillProperty->getOwnerCharacter()->setPathToFollow(NULL);
    disableAllDamageShapes();
    if(m_pEditorScene)m_pEditorScene->setPosition(-100000.0f,-100000.0f,-10000.0f);
    return false;
}

#include "EffectManager.h"

bool CSkillEvent::applyWeaponDamage(CCharacter* character,CItem* item,float damage,float soak,bool immediate,bool ignoreSingleTarget)
{
    if(!m_pSkillProperty || !m_target.getObject() || m_weaponDamageScale==0.0f ||
       (!ignoreSingleTarget && m_pSkillProperty->m_bSingleTarget && character!=m_skillTarget.getObject()))
        return false;
    CCharacter* attacker=static_cast<CCharacter*>(m_target.getObject());
    if(m_ownerCharacter.getObject())
        attacker=m_ownerCharacter.getObject();
    if(!immediate) {
        CPositionableObject* target=character?static_cast<CPositionableObject*>(character):static_cast<CPositionableObject*>(item);
        Ogre::Vector3 position=attacker->getPosition(true);
        if(!canEffectPosObject(position,target))
            return false;
    }
    if(m_damageRequiresLOS && (character || item)) {
        CPositionableObject* target=character?static_cast<CPositionableObject*>(character):static_cast<CPositionableObject*>(item);
        Ogre::Vector3 end=target->getPosition(true)+Ogre::Vector3(0,1,0);
        Ogre::Vector3 start=attacker->getPosition(true)+Ogre::Vector3(0,1,0);
        Ogre::Vector3 collision,normal;
        if(m_pResourceManager->getLevel()->rayCollision(start,end,collision,normal,true))
            return true;
    }
    if(attacker->m_pEffectManager)
        attacker->m_pEffectManager->calculateEffectValues();
    CCharacter* oldCharacter=attacker->m_targetCharacter.getObject();
    CItem* oldItem=attacker->m_targetItem.getObject();
    if(character)attacker->setTarget(character);
    if(item)attacker->setTargetItem(item);
    CEquipment* right=attacker->getWeaponInRightHand();
    CEquipment* left=attacker->getWeaponInLeftHand();
    unsigned int flags=immediate?0x30f:0xf;
    if(m_useDPS)flags|=0x400;
    if(m_noStrikeParticles)flags|=0x800;
    if(m_noStealEffects)flags|=0x1000;
    bool dual=m_pSkillProperty->m_bHasAnimation;
    bool result=false;
    CEquipment* weapon=right?right:left;
    if(weapon) {
        if(character)
            attacker->performAttack(weapon,flags|0x10,damage*m_weaponDamageScale,soak*m_soakScale,static_cast<EDAMAGE_TYPES>(m_damageType));
        else
            item->interact(m_ownerCharacter.getObject());
        result=true;
    }
    if(dual && !immediate && character && left && left->ISA(static_cast<UNITTYPES::EUNITTYPES>(8)) &&
       (!m_pSkillProperty || left->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_pSkillProperty->m_iRequirementLeft)))) {
        attacker->performAttack(left,flags|0x10,damage*m_weaponDamageScale,soak*m_soakScale,static_cast<EDAMAGE_TYPES>(m_damageType));
        result=true;
    }
    if(!left && !right) {
        attacker->performAttack(NULL,flags|0x50,damage*m_weaponDamageScale,soak*m_soakScale,static_cast<EDAMAGE_TYPES>(m_damageType));
        result=true;
    }
    if(attacker->m_pEffectManager)
        attacker->m_pEffectManager->calculateEffectValues();
    if(character && character->HP()<1 && character->m_pSceneNode &&
       character->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x1d)) && m_eventType!=5) {
        const Ogre::Quaternion& orientation=character->m_pSceneNode->getOrientation();
        Ogre::Vector3 position=character->getPosition(true);
        m_pSkill->triggerEvent(static_cast<ESKILL_EVENT_TYPE>(5),position,orientation,character,NULL);
    }
    attacker->setTarget(oldCharacter);
    if(oldItem)attacker->setTargetItem(oldItem);
    return result;
}
