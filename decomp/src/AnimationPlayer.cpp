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
