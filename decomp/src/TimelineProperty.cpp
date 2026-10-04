#include "EmptyStrings.h"
#include "GameEnums.h"
#include "TimelineProperty.h"
#include "Descriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "RunicCore.h"
#include "Timeline.h"

void CTimelineProperty::DoQuaternion(CTimeline *timeline, float timePercent)
{
}

void CTimelineProperty::SetValueOnObject(CTimelineProperty::CTimelinePoint *point)
{
    if (point != NULL && m_editorScene != NULL) {
        unsigned int dataSize = 0;
        void *data = point->m_descriptorProperty.getData(dataSize, NULL);
        m_descriptor->SetProperty(
            m_editorScene->GetObjectInScene(m_objectID),
            m_propertyID,
            data,
            0);
    }
}

void CTimelineProperty::SetValueOnObject(void *value, unsigned int dataSize)
{
    if (m_descriptorProperty == NULL)
        return;
    if (value == NULL)
        return;
    if (m_descriptor == NULL)
        return;

    CEditorBaseObject *object = m_editorScene->GetObjectInScene(m_objectID);
    if (object != NULL)
        m_descriptor->SetProperty(object, m_propertyID, value, dataSize);
}

CTimelineProperty::CTimelineProperty(CTimeline *timeline, CEditorScene *editorScene, CDescriptor *descriptor, unsigned int eventID, bool inputEvent, long long objectID)
    : CRunicCore()
{
    m_eventID = eventID;
    m_inputEvent = inputEvent;
    m_editorScene = editorScene;
    m_descriptor = descriptor;
    m_timeline = timeline;
    m_objectID = objectID;
    m_propertyID = -1;
    m_lastTimePercent = -0.01f;
    m_descriptorProperty = NULL;
    m_timelinePoints = NULL;
    m_interpolationType = 7;
    m_spline = NULL;
    m_updating = false;
}
