#include "EmptyStrings.h"
#include "GameVariables.h"
#include "AnimationPlayer.h"
#include "EditorBaseObject.h"
#include "ResourceManager.h"

CAnimationPlayer::CAnimationPlayer(CResourceManager* resourceManager)
    : CEditorBaseObject()
    , m_pResourceManager(resourceManager)
    , m_lAnimationTargets(2)
    , m_sCategory(*reinterpret_cast<const std::wstring *>(gANIMATIONPLAYER_TYPE_NAMES))
    , m_sUnitType(L"PLAYER")
    , m_bStartOnLoad(false)
    , m_bAnimationPlaying(false)
    , m_bLoop(false)
    , m_bPlayIdle(false)
    , m_bDurationActive(false)
    , m_fBlendTime(0.2f)
    , m_fBlendOutTime(0.2f)
    , m_fForceDuration(0.0f)
{
}

void CAnimationPlayer::update(float deltaTime)
{
    if (!m_pResourceManager->getEditorIsRunning() && m_bAnimationPlaying)
    {
        if (m_bDurationActive)
        {
            if (m_fRemainingDuration <= m_fBlendOutTime)
                return;

            m_fRemainingDuration -= deltaTime;
            if (m_fRemainingDuration <= m_fBlendOutTime)
            {
                stopAnimation(false);
                return;
            }
        }

        playAnimation();
    }
}

#include "BaseUnit.h"
#include "GenericModel.h"

void CAnimationPlayer::setAnimationDuration(float duration)
{
    m_fRemainingDuration = duration;
    if (!m_bLoop)
        for (unsigned int i = 0; i < m_lAnimationTargets.size(); ++i)
            if (m_lAnimationTargets[i]->getObject() && m_lAnimationTargets[i]->getObject()->getUnitModel())
                static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->updateAnimation(m_fRemainingDuration, true);
}

CAnimationPlayer::~CAnimationPlayer()
{
    m_bAnimationPlaying = false;
    for (unsigned int i = 0; i < m_lAnimationTargets.size(); ++i) {
        if (m_lAnimationTargets[i]) {
            OGRE_DELETE_T(m_lAnimationTargets[i], TSafePointer<CBaseUnit>, Ogre::MEMCATEGORY_GENERAL);
            m_lAnimationTargets[i] = NULL;
        }
    }
    m_lAnimationTargets.clear();
}

#include "Character.h"
#include "Player.h"
#include "GameClient.h"
#include "Level.h"
#include "MasterResourceManager.h"
#include "UnitResourceList.h"
#include "Hierarchy.h"
#include "StringUtilities.h"
#include <algorithm>

void CAnimationPlayer::stopAnimation(bool forceIdle)
{
    if (!m_bAnimationPlaying) return;
    m_bAnimationPlaying = false;
    if (m_bPlayIdle || forceIdle) {
        for (unsigned int i = 0; i < m_lAnimationTargets.size(); ++i) {
            if (!m_lAnimationTargets[i]->getObject() || !m_lAnimationTargets[i]->getObject()->getUnitModel()) continue;
            CCharacter* character = dynamic_cast<CCharacter*>(m_lAnimationTargets[i]->getObject());
            if (character) {
                if (!static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->animationQueued("IDLE") &&
                    !static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->animationPlaying("IDLE"))
                    character->setAIPlayAnimation("IDLE", true, 0.1f, 1.0f);
                character->setAIState(static_cast<EAIState>(0));
            } else if (!static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->animationQueued("IDLE") &&
                       !static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->animationPlaying("IDLE")) {
                float blendTime = m_fBlendTime;
                static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->blendAnimation("IDLE", true, blendTime, 1.0f, -1.0f);
            }
        }
    }
    BroadcastEvent(112);
}

void CAnimationPlayer::playAnimation(bool loop)
{
    for (unsigned int i = 0; i < m_lAnimationTargets.size(); ++i) {
        if (m_lAnimationTargets[i]) {
            OGRE_DELETE_T(m_lAnimationTargets[i], TSafePointer<CBaseUnit>, Ogre::MEMCATEGORY_GENERAL);
            m_lAnimationTargets[i] = NULL;
        }
        m_lAnimationTargets[i] = NULL;
    }
    m_lAnimationTargets.clear();
    if (!m_pResourceManager || !m_pResourceManager->getLevel()) return;

    if (m_sCategory == gANIMATIONPLAYER_TYPE_NAMES[0]) {
        CBaseUnit* unit = m_pResourceManager->getGameClient()->getPlayer();
        TSafePointer<CBaseUnit>* reference = OGRE_NEW_T(TSafePointer<CBaseUnit>, Ogre::MEMCATEGORY_GENERAL)();
        try { reference->setObject(unit); }
        catch (...) { OGRE_DELETE_T(reference, TSafePointer<CBaseUnit>, Ogre::MEMCATEGORY_GENERAL); throw; }
        m_lAnimationTargets.add(reference);
    } else if (m_sCategory == gANIMATIONPLAYER_TYPE_NAMES[1] || m_sCategory == gANIMATIONPLAYER_TYPE_NAMES[3]) {
        CDataGroup* group;
        if (m_sCategory == gANIMATIONPLAYER_TYPE_NAMES[1])
            group = m_pResourceManager->getMasterResourceList()->getDataGroupByObjectName(gRESOURCE_GROUP_NAMES[1], m_sUnitType);
        else if (m_sCategory == gANIMATIONPLAYER_TYPE_NAMES[3])
            group = m_pResourceManager->getMasterResourceList()->getDataGroupByObjectName(gRESOURCE_GROUP_NAMES[3], m_sUnitType);
        else group = NULL;
        if (group) {
            TArrayList<CBaseUnit*> units(10);
            m_pResourceManager->getLevel()->getBaseUnitsByDataGroup(group, units);
            for (unsigned int i = 0; i < units.size(); ++i) {
                CBaseUnit* unit = units[i];
                TSafePointer<CBaseUnit>* reference = OGRE_NEW_T(TSafePointer<CBaseUnit>, Ogre::MEMCATEGORY_GENERAL)();
                try { reference->setObject(unit); }
                catch (...) { OGRE_DELETE_T(reference, TSafePointer<CBaseUnit>, Ogre::MEMCATEGORY_GENERAL); throw; }
                m_lAnimationTargets.add(reference);
            }
        }
    } else if (m_sCategory == gANIMATIONPLAYER_TYPE_NAMES[2]) {
        UNITTYPES::EUNITTYPES type = CMasterResourceManager::getSingleton()->m_pHierarchy->getTypeIDByName(m_sUnitType);
        TArrayList<CBaseUnit*> units(10);
        m_pResourceManager->getLevel()->getUnitsByUnitType(type, units);
        for (unsigned int i = 0; i < units.size(); ++i) {
            CBaseUnit* unit = units[i];
            TSafePointer<CBaseUnit>* reference = OGRE_NEW_T(TSafePointer<CBaseUnit>, Ogre::MEMCATEGORY_GENERAL)();
            try { reference->setObject(unit); }
            catch (...) { OGRE_DELETE_T(reference, TSafePointer<CBaseUnit>, Ogre::MEMCATEGORY_GENERAL); throw; }
            m_lAnimationTargets.add(reference);
        }
    }
    m_fRemainingDuration = 0.0f;
    if (m_lAnimationTargets.size() && m_lAnimationTargets[0]->getObject() &&
        m_lAnimationTargets[0]->getObject()->getUnitModel()) {
        std::string animation = STRINGS::StringConvertToNarrow(m_sAnimationName.c_str());
        m_fRemainingDuration = static_cast<CGenericModel*>(m_lAnimationTargets[0]->getObject()->getUnitModel())->getAnimationLengthSeconds(animation);
    }
    if (m_fForceDuration > 0.0f) {
        if (loop || !(m_fRemainingDuration > 0.0f)) m_fRemainingDuration = m_fForceDuration;
        else m_fRemainingDuration = std::min(m_fRemainingDuration, m_fForceDuration);
        m_fRemainingDuration -= m_fBlendOutTime;
        m_bDurationActive = true;
    } else if (!loop) {
        m_fRemainingDuration -= m_fBlendOutTime;
        m_bDurationActive = true;
    } else {
        m_bDurationActive = false;
    }
    m_bLoop = loop;
    if (m_lAnimationTargets.size()) playAnimation();
    m_bAnimationPlaying = true;
    BroadcastEvent(113);
}

void CAnimationPlayer::playAnimation()
{
    if (!m_lAnimationTargets.size()) { playAnimation(m_bLoop); return; }
    std::string animation = STRINGS::StringConvertToNarrow(m_sAnimationName.c_str());
    if (m_bLoop) {
        for (unsigned int i = 0; i < m_lAnimationTargets.size(); ++i) {
            if (!m_lAnimationTargets[i]->getObject() || !m_lAnimationTargets[i]->getObject()->getUnitModel()) continue;
            if (static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->animationPlaying(animation) ||
                static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->animationQueued(animation)) continue;
            CCharacter* character = dynamic_cast<CCharacter*>(m_lAnimationTargets[i]->getObject());
            if (character) character->setAIPlayAnimation(animation, true, m_fBlendTime, 1.0f);
            else if (m_lAnimationTargets[i]->getObject()->getUnitModel()) {
                float blendTime = m_fBlendTime;
                static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->blendAnimation(animation, true, blendTime, 1.0f, -1.0f);
                static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->queueBlendAnimation("IDLE", true, 0.2f, 1.0f);
            }
        }
    } else {
        for (unsigned int i = 0; i < m_lAnimationTargets.size(); ++i) {
            if (!m_lAnimationTargets[i]->getObject() || !m_lAnimationTargets[i]->getObject()->getUnitModel()) continue;
            if (static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->animationPlaying(animation) ||
                static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->animationQueued(animation)) continue;
            CCharacter* character = dynamic_cast<CCharacter*>(m_lAnimationTargets[i]->getObject());
            if (character) character->setAIPlayAnimation(animation, false, m_fBlendTime, 1.0f);
            else {
                float blendTime = m_fBlendTime;
                static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->blendAnimation(animation, false, blendTime, 1.0f, -1.0f);
                static_cast<CGenericModel*>(m_lAnimationTargets[i]->getObject()->getUnitModel())->queueBlendAnimation("IDLE", true, 0.2f, 1.0f);
            }
        }
    }
}
