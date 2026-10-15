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

CTimelineDescriptor::CTimelineDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CDescriptor(0)
{
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
    AddInputLogic(INPUT_EVENT_PLAY_2);
    AddInputLogic(INPUT_EVENT_PLAY_BACKWARDS);
    AddInputLogic(INPUT_EVENT_STOP_2);
    AddInputLogic(INPUT_EVENT_STOP_TO_END);
    AddInputLogic(INPUT_EVENT_PAUSE_2);
    AddInputLogic(INPUT_EVENT_RESET_2);
    AddInputLogic(INPUT_EVENT_RESET_TO_END);
    AddInputLogic(INPUT_EVENT_FAST_FORWARD_TO_END);
    AddInputLogic(INPUT_EVENT_REWIND_TO_START);
    AddOutputLogic(OUTPUT_EVENT_STARTED);
    AddOutputLogic(OUTPUT_EVENT_STARTED_FORWARDS);
    AddOutputLogic(OUTPUT_EVENT_STARTED_BACKWARDS);
    AddOutputLogic(OUTPUT_EVENT_STOPPED_2);
    AddOutputLogic(OUTPUT_EVENT_STOPPED_FORWARDS);
    AddOutputLogic(OUTPUT_EVENT_STOPPED_BACKWARDS);
    AddOutputLogic(OUTPUT_EVENT_LOOPED);
    AddOutputLogic(OUTPUT_EVENT_PAUSED_2);
    AddOutputLogic(OUTPUT_EVENT_RESET_TO_BEGINNING);
    AddOutputLogic(OUTPUT_EVENT_RESET_TO_END);
    AddOutputLogic(OUTPUT_EVENT_FINISHED);
    m_sName = std::wstring(name);
    m_sIcon = std::wstring(description);
    m_sDescription = std::wstring(group);
    m_iFlags &= ~(DESCRIPTOR_FLAG_CLONABLE | DESCRIPTOR_FLAG_CHILDREN);
    AddProperty(L"TIMELINE", L"DURATION", L"Duration of the timeline", (void*)Set_SetTimelineDuration, (void*)Get_GetTimelineDuration, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"TIMELINE", L"STEP", L"The update step", (void*)Set_SetTimelineStep, (void*)Get_GetTimelineStep, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"TIMELINE", L"LOOPS", L"Duration", (void*)Set_SetTimelineLoops, (void*)Get_GetTimelineLoops, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"LOAD", L"RESET PROPERTIES", L"if true the timeline will reset the properties of the objects.", (void*)Set_setSetPropertiesOnLoad, (void*)Get_getSetPropertiesOnLoad, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"LOAD", L"START ON LOAD", L"if set to true it will automatically start when the layout loads", (void*)Set_SetStartOnLoad, (void*)Get_GetStartOnLoad, VARIABLE_TYPE_BOOL, 0);
    AddPropertyWithInterpreterFunctions(L"TIMELINE", L"DEFAULT INTERPOLATION TYPE", L"The interpolation type that all timeline properties will default to.", (void*)Set_setDefaultInterpolationType, (void*)Get_getDefaultInterpolationType, GetTimelineInterpolationIDByString, GetTimelineInterpolationStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddProperty(L"MODIFICATION", L"LAYOUT CONTROL", L"if set to true timeline layout links can start and stop the timeline.", (void*)Set_setLayoutCanControl, (void*)Get_getLayoutCanControl, VARIABLE_TYPE_BOOL, 0);
    AddPropertyWithInterpreterFunctions(L"MODIFICATION", L"TYPE", L"When a layout link loads a timeline, it can adjust the length by the type of modification specified here.", (void*)Set_setDurationModicationType, (void*)Get_getDurationModicationType, GetTimelineModIDByString, GetTimelineModStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
}
