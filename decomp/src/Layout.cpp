#include "Editor.h"
#include "OgreUtilities.h"
#include <OgreEntity.h>
#include "Particle.h"
#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Layout.h"
#include "Descriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "Timeline.h"
#include "ParticleTechWrapper.h"
#include "SoundObject.h"
#include "CameraShake.h"

void CLayout::setCacheingParticlesForLevel(bool enable)
{
    g_bCachParticles = true;
}

void CLayout::editorObjectLoaded(CEditorBaseObject* editorObject)
{
}

void CLayout::update(float elapsedTime)
{
    if (m_bVisible && getEnabled()) {
        CEditorScene::update(elapsedTime);
    }
}

void CLayout::editorObjectsAboutToBeDelete()
{
    m_Unknown1D0.clear();
}

void CLayout::setDurationModification(float durationModification)
{
    if (m_Unknown1B8 == 2)
    {
        m_fDurationModification = durationModification;

        if (!(durationModification <= 0.0f))
        {
            for (unsigned int i = 0; i < m_Unknown1D0.size(); ++i)
            {
                CTimeline* timeline = dynamic_cast<CTimeline*>(m_Unknown1D0[i]);
                if (timeline != NULL && timeline->m_bLayoutCanControl)
                    timeline->setDurationModificationTime(m_fDurationModification);
            }
        }
    }
}

void CLayout::eventFiredByDescriptor(unsigned int eventID,
                                     CDescriptor* descriptor,
                                     CEditorBaseObject* eventObject)
{
    if (descriptor && getDescriptor())
        getDescriptor()->BroadcastEventFromObject(this, eventID);
}

void CLayout::setHighlighted(bool highlighted)
{
    std::map<long long, CEditorBaseObject*>& objects = getObjects();
    for (std::map<long long, CEditorBaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
        iHighlight* highlight = dynamic_cast<iHighlight*>(it->second);
        if (highlight) highlight->setHighlighted(highlighted);
    }
}

CLayout* CLayout::getLayoutToClone(const std::wstring& layoutName)
{
    std::map<std::wstring, CLayout*>& layouts =
        *reinterpret_cast<std::map<std::wstring, CLayout*>*>(g_LayoutToCloneOrControl);
    std::map<std::wstring, CLayout*>::iterator it = layouts.lower_bound(layoutName);
    if (it != layouts.end() && !(layoutName < it->first)) return it->second;
    return NULL;
}

void CLayout::resume()
{
    callFunctionOnObjects(LAYOUT_FUNCTION_RESUME, false);
}

void CLayout::pause()
{
    callFunctionOnObjects(LAYOUT_FUNCTION_PAUSE, false);
}

void CLayout::stop(bool stopImmediately)
{
    callFunctionOnObjects(LAYOUT_FUNCTION_STOP, stopImmediately);
}

void CLayout::startBackwards()
{
    callFunctionOnObjects(LAYOUT_FUNCTION_START_BACKWARDS, false);
}

void CLayout::start()
{
    callFunctionOnObjects(LAYOUT_FUNCTION_START, false);
}

void CLayout::addLayoutForCloningAndControlling(std::wstring layoutName)
{
    if (getLayoutToClone(layoutName) != NULL)
        return;

    typedef std::map<std::wstring, CLayout*> LayoutMap;
    LayoutMap& layouts =
        *reinterpret_cast<LayoutMap*>(g_LayoutToCloneOrControl);

    layouts[layoutName] = this;
    m_bUnknown1C8 = true;
}

void CLayout::removeAllCloneableObjects()
{
    reinterpret_cast<std::map<std::wstring, CLayout*>*>(g_LayoutToCloneOrControl)->clear();
}

CLayout::~CLayout()
{
}

unsigned int CLayout::getNumberOfParticlesUpdating()
{
    if (m_pParticle == NULL)
        return CEditorScene::getNumberOfParticlesUpdating();
    return m_pParticle->getNumberOfParticlesUpdating(false);
}

bool CLayout::processInputs(unsigned int inputID, CEditorBaseObject* inputObject)
{
    bool processed = false;
    for (unsigned int i = 0; i < m_Unknown1D0.size(); ++i) {
        if (m_Unknown1D0[i]->getDescriptor()) {
            if (m_Unknown1B8 == 2) {
                CTimeline* timeline = dynamic_cast<CTimeline*>(m_Unknown1D0[i]);
                if (!timeline || !timeline->m_bLayoutCanControl) continue;
            }
            m_Unknown1D0[i]->getDescriptor()->InputLogicEvent(m_Unknown1D0[i], inputID, inputObject);
            processed = true;
        }
    }
    return processed;
}
void CLayout::setVisible(bool visible)
{
    bool oldVisible = m_bVisible;
    CSceneNodeObject::setVisible(visible);
    if (visible != oldVisible && m_pParticle) {
        if (visible) m_pParticle->Start();
        else m_pParticle->Stop(false);
    }
}
CLayout::CLayout(CResourceManager* manager, ELAYOUT_TYPES type)
    : CAllDescriptorsScene(), m_bStartOnLoad(true), m_iRandomWeight(1), m_iUnknown1A8(0),
      m_iUnknown1AC(0), m_iUnknown1B0(0), m_fDurationModification(0), m_Unknown1B8(type),
      m_iUnknown1C0(0), m_bUnknown1C8(false), m_bUnknown1C9(false), m_Unknown1D0(10),
      m_bUnknown1E8(false), m_pParticle(NULL)
{
    InitScene(manager, 0);
    CEditorScene::setEnabled(true);
}
void CLayout::setStartOnLoad(bool startOnLoad)
{
    m_bStartOnLoad = startOnLoad;
    if (!getResourceManager()->getEditorIsRunning()) return;
    if (m_bStartOnLoad) {
        if (m_Unknown1B8 == 2) {
            for (unsigned int i = 0; i < m_Unknown1D0.size(); ++i) {
                CTimeline* timeline = dynamic_cast<CTimeline*>(m_Unknown1D0[i]);
                if (timeline) timeline->m_bManualUpdate = true;
            }
        }
        start();
    } else stop(false);
}
void CLayout::initOnLoad()
{
    if (m_bStartOnLoad) return;
    TArrayList<CEditorBaseObject*>* objects = GetObjectsCreatedByADescriptor(L"Timeline");
    if (!objects) return;
    for (unsigned int i = 0; i < objects->size(); ++i)
        static_cast<CTimeline*>((*objects)[i])->m_bStartOnLoad = false;
}

void CLayout::SetSceneOwner(CEditorScene* sceneOwner)
{
    CSceneNodeObject::SetSceneOwner(sceneOwner);
    if (m_pResourceManager->getEditorIsRunning()) {
        CEditor* editor = gEditor;
        TArrayList<CEditorScene*>& scenes = editor->getEditorScenes();
        for (unsigned int i = 0; i < scenes.size(); ++i) {
            if (scenes[i] == sceneOwner && m_pSceneNode) {
                sceneNodeAttachEntity(OGRE_UTILITIES::createEntity(
                    m_pResourceManager->getSceneManager(), static_cast<OGRE_UTILITIES::EPRIMITIVES>(0),
                    static_cast<OGRE_UTILITIES::EQUERYMASK>(8), "gm"));
                m_pEntity->setMaterialName("lightBlue");
                setScale(1.0f);
            }
        }
    }
}

void CLayout::editorObjectCreated(CEditorBaseObject* object)
{
    if (!object->getParentPositionableObject() || object->getParentPositionableObject() == getSceneOwner())
        object->setParentPositionableObject(this);
    if (m_Unknown1B8 == 1) {
        if (dynamic_cast<CParticleTechWrapper*>(object) || dynamic_cast<CSoundObject*>(object) || dynamic_cast<CCameraShake*>(object))
            m_Unknown1D0.add(object);
    } else if (m_Unknown1B8 == 2) {
        CTimeline* timeline = dynamic_cast<CTimeline*>(object);
        if (timeline) {
            timeline->m_bManualUpdate = true;
            m_Unknown1D0.add(object);
        } else if (dynamic_cast<CSoundObject*>(object)) {
            m_Unknown1D0.add(object);
        }
    }
}

#include "CameraControl.h"
#include "ParticleUniverseSystem.h"

void CLayout::callFunctionOnObjects(ELAYOUT_FUNCTION_TYPES functionType,
                                    bool stopImmediately)
{
    if (m_pParticle) {
        switch (functionType) {
        case LAYOUT_FUNCTION_START:
        case LAYOUT_FUNCTION_START_BACKWARDS:
            m_pParticle->Start(); BroadcastEvent(31); break;
        case LAYOUT_FUNCTION_STOP:
            m_pParticle->Stop(stopImmediately); BroadcastEvent(32); break;
        case LAYOUT_FUNCTION_PAUSE:
            m_pParticle->Pause(); BroadcastEvent(33); break;
        case LAYOUT_FUNCTION_RESUME:
            m_pParticle->Resume(); BroadcastEvent(34); break;
        }
        return;
    }
    for (unsigned int i = 0; i < m_Unknown1D0.size(); ++i) {
        if (m_Unknown1B8 == 1) {
            CParticleTechWrapper* technique = dynamic_cast<CParticleTechWrapper*>(m_Unknown1D0[i]);
            if (technique) {
                switch (functionType) {
                case LAYOUT_FUNCTION_START:
                case LAYOUT_FUNCTION_START_BACKWARDS:
                    technique->setActivated(true); break;
                case LAYOUT_FUNCTION_STOP:
                    technique->setActivated(false); break;
                case LAYOUT_FUNCTION_PAUSE:
                    if (technique->m_pParticleSystem) technique->m_pParticleSystem->pause();
                    break;
                case LAYOUT_FUNCTION_RESUME:
                    if (technique->m_pParticleSystem) technique->m_pParticleSystem->resume();
                    break;
                }
                continue;
            }
        } else if (m_Unknown1B8 == 2) {
            CTimeline* timeline = dynamic_cast<CTimeline*>(m_Unknown1D0[i]);
            if (timeline && timeline->m_bLayoutCanControl) {
                switch (functionType) {
                case LAYOUT_FUNCTION_START:
                    timeline->Reset_To_Beginning(); timeline->SetEnabled(false); timeline->Play(true); break;
                case LAYOUT_FUNCTION_STOP:
                    timeline->Stop(); break;
                case LAYOUT_FUNCTION_PAUSE:
                    timeline->Pause(); break;
                case LAYOUT_FUNCTION_RESUME:
                    timeline->Play(true); break;
                case LAYOUT_FUNCTION_START_BACKWARDS:
                    timeline->Reset_To_End(); timeline->SetEnabled(false); timeline->Play_Backwards(); break;
                }
                continue;
            }
        } else {
            continue;
        }
        CSoundObject* sound = dynamic_cast<CSoundObject*>(m_Unknown1D0[i]);
        if (sound) {
            switch (functionType) {
            case LAYOUT_FUNCTION_START:
                if (sound->m_bSoundStartsOnActivated) sound->play();
                break;
            case LAYOUT_FUNCTION_STOP:
                if (sound->isLooping()) sound->stop();
                break;
            case LAYOUT_FUNCTION_PAUSE:
                sound->pause(); break;
            case LAYOUT_FUNCTION_RESUME:
                sound->resume(); break;
            }
        } else if (m_Unknown1B8 == 1) {
            CCameraShake* shake = dynamic_cast<CCameraShake*>(m_Unknown1D0[i]);
            if (shake && functionType == LAYOUT_FUNCTION_START) {
                Ogre::Vector3 position = getPosition(true);
                shake->m_fCameraPositionX = position.x;
                shake->m_fCameraPositionY = position.y;
                shake->m_fCameraPositionZ = position.z;
                shake->m_bCameraShakeActive = true;
                CCameraControl* camera = m_pResourceManager->getCameraControl();
                TSafePointer<CCameraShake>* reference =
                    OGRE_NEW_T(TSafePointer<CCameraShake>, Ogre::MEMCATEGORY_GENERAL)();
                try {
                    reference->setObject(shake);
                } catch (...) {
                    OGRE_DELETE_T(reference, TSafePointer<CCameraShake>, Ogre::MEMCATEGORY_GENERAL);
                    throw;
                }
                camera->m_cameraShakesSecondary.add(reference);
            }
        }
    }
}
