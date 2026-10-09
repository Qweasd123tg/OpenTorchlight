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
