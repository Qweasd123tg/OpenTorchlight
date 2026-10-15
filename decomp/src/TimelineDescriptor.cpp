#include "EditorScene.h"
#include "Timeline.h"
#include "TimelineDescriptor.h"

CEditorBaseObject* CTimelineDescriptor::CreateObject(CEditorScene* scene)
{
    return new CTimeline();
}

CTimelineDescriptor::~CTimelineDescriptor()
{
}

#include <map>
#include <string>
#include "TimelineDescriptorNames.h"

void CTimelineDescriptor::descriptorSceneActivated(CEditorScene* scene)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CTimeline* timeline = dynamic_cast<CTimeline*>(m_Objects[i]);
        if (timeline)
            timeline->SetEnabled(timeline->m_bStartOnLoad);
    }
}

void CTimelineDescriptor::update(float elapsed)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i) {
        CTimeline* timeline = dynamic_cast<CTimeline*>(m_Objects[i]);
        if (timeline)
            timeline->UpdateTimeline(elapsed);
    }
}

#include "ResourceManager.h"

bool CTimelineDescriptor::loadAdditionalInfo(CEditorBaseObject* object, COgreReader* reader, CDataGroup* data, CDescriptorLoadConfiguration* configuration)
{
    CTimeline* timeline = dynamic_cast<CTimeline*>(object);
    if (!timeline)
        return false;
    if (data)
        timeline->loadTimelineFromDataGroup(getSceneOwner(), data, configuration);
    else if (reader)
        timeline->loadTimelineFromBinaryFile(getSceneOwner(), reader, configuration);
    if (!getSceneOwner()->getResourceManager()->getEditorIsRunning() && timeline->m_bStartOnLoad)
        timeline->SetEnabled(true);
    return true;
}

bool CTimelineDescriptor::saveAdditionalInfo(CEditorBaseObject* object, std::basic_ofstream<char, std::char_traits<char> >* stream, CDataGroup* data, CDescriptorSaveConfiguration* configuration)
{
    CTimeline* timeline = dynamic_cast<CTimeline*>(object);
    if (!timeline)
        return false;
    if (data)
        timeline->saveTimelineToDataGroup(getSceneOwner(), data);
    else if (stream)
        timeline->saveTimelineToBinaryFile(getSceneOwner(), stream);
    return true;
}

unsigned int CTimelineDescriptor::GetTimelineInterpolationIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring& value, void*)
{
    for (unsigned int i = 0; i < 7; ++i)
        if (value == gTIMELINE_INTERP_TYPES[i])
            return i;
    return 0;
}



void CTimelineDescriptor::descriptorSceneDeactivated(CEditorScene* scene)
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i)
    {
        CTimeline* timeline = dynamic_cast<CTimeline*>(getObject(i));
        if (timeline)
        {
            timeline->SetEnabled(false);
        }
    }
}

void CTimelineDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* initiator)
{
    if (object)
    {
        CTimeline* target = dynamic_cast<CTimeline*>(object);
        if (target)
        {
            switch (event)
            {
            case 2: target->m_bTimelineWasStopped = false; break;
            case 3: target->m_bTimelineWasStopped = true; break;
            case 21: target->Play(true); break;
            case 22: target->Play_Backwards(); break;
            case 23: target->StopToBeginning(); break;
            case 24: target->StopToEnd(); break;
            case 25: target->Pause(); break;
            case 26: target->Reset_To_Beginning(); break;
            case 27: target->Reset_To_End(); break;
            case 28: target->fastFowardToEnd(); break;
            case 29: target->rewindToStart(); break;
            }
        }
    }
}

std::wstring CTimelineDescriptor::GetTimelineInterpolationStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index < 1 || index > 6)
        return gTIMELINE_INTERP_TYPES[0];
    return gTIMELINE_INTERP_TYPES[index];
}

std::wstring CTimelineDescriptor::GetTimelineModStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 2)
        return gTIMELINE_MODIFICATION_TYPE_NAMES[0];
    return gTIMELINE_MODIFICATION_TYPE_NAMES[index];
}

unsigned int CTimelineDescriptor::GetTimelineModIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    for (unsigned int index = 0; index < 3; ++index)
    {
        if (value == gTIMELINE_MODIFICATION_TYPE_NAMES[index])
            return index;
    }
    return 0;
}
