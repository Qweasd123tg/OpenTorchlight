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
