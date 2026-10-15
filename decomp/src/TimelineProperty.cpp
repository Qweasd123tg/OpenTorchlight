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

int CTimelineProperty::GetFreeIDForPoint()
{
    int id = 0;
    TLinkedListNode<CTimelinePoint*>* node = m_timelinePoints;
    while (node != NULL)
    {
        if (id == node->m_Data->m_pointID)
        {
            ++id;
            node = m_timelinePoints;
        }
        else
            node = node->m_pNext;
    }
    return id;
}

int CTimelineProperty::GetTimelinePointIDByIndex(int index)
{
    if (index < 0)
        return -1;
    TLinkedListNode<CTimelinePoint*>* node = m_timelinePoints;
    while (node != NULL)
    {
        if (index == 0)
            return node->m_Data->m_pointID;
        --index;
        node = node->m_pNext;
    }
    return -1;
}

CTimelineProperty::CTimelinePoint* CTimelineProperty::GetTimelinePoint(int pointID)
{
    TLinkedListNode<CTimelinePoint*>* node = m_timelinePoints;
    while (node != NULL)
    {
        if (node->m_Data->m_pointID == pointID)
            return node->m_Data;
        node = node->m_pNext;
    }
    return NULL;
}

float CTimelineProperty::GetTimePercentAtPoint(int pointID)
{
    TLinkedListNode<CTimelinePoint*>* node = m_timelinePoints;
    while (node != NULL)
    {
        if (pointID == node->m_Data->m_pointID)
            return node->m_Data->m_timePercent;
        node = node->m_pNext;
    }
    return 0.0f;
}

const std::wstring& CTimelineProperty::GetBaseTypeValueAsString(int pointID)
{
    TLinkedListNode<CTimelinePoint*>* node = m_timelinePoints;
    while (node != NULL)
    {
        if (pointID == node->m_Data->m_pointID)
            return KEditorObjectPropertyTypeNames[node->m_Data->m_descriptorProperty.getVariableType()];
        node = node->m_pNext;
    }
    return EMPTY_WSTRING;
}

void* CTimelineProperty::GetValueAtPoint(int pointID, unsigned int& dataSize)
{
    TLinkedListNode<CTimelinePoint*>* node = m_timelinePoints;
    while (node != NULL)
    {
        if (pointID == node->m_Data->m_pointID)
        {
            if (m_editorScene != NULL)
                return node->m_Data->m_descriptorProperty.getData(dataSize, NULL);
            return NULL;
        }
        node = node->m_pNext;
    }
    return NULL;
}

void CTimelineProperty::SetValueAtPoint(int pointID, void* value, unsigned int dataSize)
{
    TLinkedListNode<CTimelinePoint*>* node = m_timelinePoints;
    while (node != NULL)
    {
        if (pointID == node->m_Data->m_pointID)
        {
            if (value != NULL && m_editorScene != NULL)
                node->m_Data->m_descriptorProperty.setData(static_cast<UNIONDATA32BIT*>(value), dataSize, NULL);
            return;
        }
        node = node->m_pNext;
    }
}

bool CTimelineProperty::RemovePoint(int pointID)
{
    TLinkedListNode<CTimelinePoint*>* node = m_timelinePoints;
    while (node != NULL)
    {
        if (node->m_Data->m_pointID == pointID)
        {
            CTimelinePoint* point = node->m_Data;
            if (node == m_timelinePoints)
                m_timelinePoints = node->m_pNext;
            if (node->m_pPrevious != NULL)
                node->m_pPrevious->m_pNext = node->m_pNext;
            if (node->m_pNext != NULL)
                node->m_pNext->m_pPrevious = node->m_pPrevious;
            node->m_pNext = NULL;
            node->m_pPrevious = NULL;
            delete node;
            delete point;
            return true;
        }
        node = node->m_pNext;
    }
    return false;
}
