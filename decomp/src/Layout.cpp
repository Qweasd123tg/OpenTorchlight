#include "Particle.h"
#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Layout.h"
#include "Descriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "Timeline.h"

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
