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

        if (durationModification > 1.0f)
        {
            for (int i = 0; i < static_cast<int>(m_Unknown1D0.size()); ++i)
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
    if (descriptor)
        BroadcastEvent(eventID);
}

void CLayout::setHighlighted(bool highlighted)
{
}

CLayout* CLayout::getLayoutToClone(const std::wstring& layoutName)
{
    std::map<std::wstring, CLayout*>& layouts =
        *reinterpret_cast<std::map<std::wstring, CLayout*>*>(g_LayoutToCloneOrControl);
    std::map<std::wstring, CLayout*>::iterator it = layouts.find(layoutName);
    if (it != layouts.end() && it->first == layoutName)
        return it->second;
    return 0;
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

    LayoutMap::iterator it = layouts.find(layoutName);
    if (it == layouts.end())
        it = layouts.insert(
                std::make_pair(layoutName, (CLayout*)NULL)).first;

    (*it).second = this;
    m_bUnknown1C8 = true;
}

void CLayout::removeAllCloneableObjects()
{
    reinterpret_cast<std::map<std::wstring, CLayout*>*>(g_LayoutToCloneOrControl)->clear();
}

CLayout::~CLayout()
{
}
