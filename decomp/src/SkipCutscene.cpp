#include "EmptyStrings.h"
#include "GameNamespaces.h"
#include "SkipCutscene.h"
#include "ResourceManager.h"

void CSkipCutscene::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
    if (enabled)
    {
        BroadcastEvent(6);
        m_bSkipRequested = false;
    }
    else
    {
        BroadcastEvent(7);
    }
}

CSkipCutscene::~CSkipCutscene()
{
}

CSkipCutscene::CSkipCutscene(CResourceManager* resourceManager)
    : m_bEnabled(false), m_bSkipRequested(false), m_bSkillsDisabled(false),
      m_pResourceManager(resourceManager)
{
}

#include "AnimationPlayer.h"
#include "CameraControl.h"
#include "CameraController.h"
#include "Character.h"
#include "EditorScene.h"
#include "GameClient.h"
#include "GameUI.h"
#include "KeyManager.h"
#include "LogicTimer.h"
#include "Player.h"
#include "SkillManager.h"

void CSkipCutscene::update(float)
{
    if (!m_bEnabled) return;
    if (m_pResourceManager->getGameClient()->getKeyManager()->keyPressed(27)) {
        m_bSkipRequested = true;
        return;
    }
    if (!m_bSkipRequested) return;
    if (m_bSkillsDisabled) CSkillManager::globallyDisableSkills(true);
    m_pResourceManager->m_bFlag1 = false;
    CEditorScene* scene = getSceneOwner();
    CGameUI::getSingleton()->closeAll();
    TArrayList<CEditorBaseObject*>* objects = scene->GetObjectsCreatedByADescriptor(L"Animation Controller");
    if (objects) {
        for (unsigned int i = 0; i < objects->size(); ++i) {
            if ((*objects)[i]->isChildOfObject(getParentGuid())) {
                CAnimationPlayer* animation = static_cast<CAnimationPlayer*>((*objects)[i]);
                if (animation->m_bAnimationPlaying && !animation->m_bStartOnLoad)
                    animation->stopAnimation(true);
            }
        }
    }
    objects = scene->GetObjectsCreatedByADescriptor(L"Camera Controller");
    if (objects) {
        for (unsigned int i = 0; i < objects->size(); ++i) {
            if ((*objects)[i]->isChildOfObject(getParentGuid())) {
                CCameraController* camera = static_cast<CCameraController*>((*objects)[i]);
                if (camera->getEnabled()) camera->stopCamera();
            }
        }
    }
    objects = scene->GetObjectsCreatedByADescriptor(L"Timer");
    if (objects) {
        for (unsigned int i = 0; i < objects->size(); ++i) {
            if ((*objects)[i]->isChildOfObject(getParentGuid())) {
                CLogicTimer* timer = static_cast<CLogicTimer*>((*objects)[i]);
                if (timer->getEnabled()) timer->setEnabled(false);
            }
        }
    }
    CCameraControl::getSingleton()->clearCameraShakes();
    m_pResourceManager->m_bFlag1 = true;
    m_pResourceManager->getGameClient()->getPlayer()->setEnabled(true);
    m_pResourceManager->getGameClient()->getPlayer()->setPathToFollow(NULL);
    m_pResourceManager->getGameClient()->getPlayer()->setVisible(true);
    m_pResourceManager->getGameClient()->getPlayer()->setMeshVisible(true, true);
    setEnabled(false);
    BroadcastEvent(114);
    if (m_bSkillsDisabled) CSkillManager::globallyDisableSkills(false);
}
