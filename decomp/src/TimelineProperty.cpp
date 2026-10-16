#include "LogicWrapper.h"
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

void CTimelineProperty::triggerEvent(CTimeline* timeline)
{
    if (!m_descriptor || !m_editorScene || m_eventID == ~0u) return;
    CEditorBaseObject* object = m_editorScene->GetObjectInScene(m_objectID);
    if (!object) return;
    if (m_inputEvent) {
        CLogicWrapper* wrapper = object->getDescriptor()->GetInputLogicWrapper(m_eventID);
        if (wrapper) m_descriptor->InputLogicEvent(object, wrapper->m_iID, timeline);
    } else {
        CLogicWrapper* wrapper = object->getDescriptor()->GetOutputLogicWrapper(m_eventID);
        if (wrapper) object->BroadcastEvent(wrapper->m_iID);
    }
}
std::wstring CTimelineProperty::GetValueAtPointAsString(int pointID)
{
    TLinkedListNode<CTimelinePoint*>* node = m_timelinePoints;
    while (node) {
        if (pointID == node->m_Data->m_pointID)
            return node->m_Data->m_descriptorProperty.getPropertyValueAsString(NULL);
        node = node->m_pNext;
    }
    return EMPTY_WSTRING;
}
void CTimelineProperty::SetValueAtPointByString(int pointID, std::wstring& value)
{
    TLinkedListNode<CTimelinePoint*>* node = m_timelinePoints;
    while (node) {
        if (pointID == node->m_Data->m_pointID) {
            node->m_Data->m_descriptorProperty.setPropertyValueByString(value, NULL);
            return;
        }
        node = node->m_pNext;
    }
}
double CTimelineProperty::getValueOfLinearPropertyByPercent(unsigned int interpolationType,
 double timePercent, CTimelinePoint* fromPoint, CTimelinePoint* toPoint, unsigned int componentIndex)
{
    unsigned int toCount, fromCount;
    UNIONDATA32BIT* to = toPoint->m_descriptorProperty.getData(toCount, NULL);
    UNIONDATA32BIT* from = fromPoint->m_descriptorProperty.getData(fromCount, NULL);
    if (componentIndex >= toCount || componentIndex >= fromCount) return 0.0;
    double value;
    switch (m_descriptorProperty->getVariableType()) {
    case VARIABLE_TYPE_FLOAT: case VARIABLE_TYPE_VECTOR2: case VARIABLE_TYPE_VECTOR3: case VARIABLE_TYPE_VECTOR4:
        value = static_cast<double>(from[componentIndex].m_fValue)
              + static_cast<double>(to[componentIndex].m_fValue - from[componentIndex].m_fValue) * timePercent;
        break;
    case VARIABLE_TYPE_INTEGER: case VARIABLE_TYPE_UNSIGNED_INTEGER:
        value = static_cast<double>(from[componentIndex].m_iValue)
              + static_cast<double>(to[componentIndex].m_iValue - from[componentIndex].m_iValue) * timePercent;
        break;
    case VARIABLE_TYPE_STRING: case VARIABLE_TYPE_BOOL: value = timePercent; break;
    default: return 0.0;
    }
    switch (interpolationType) {
    case 1: return static_cast<int>(value + 0.5);
    case 2: return static_cast<int>(value);
    case 3: return static_cast<int>(value + 1.0);
    default: return value;
    }
}
void CTimelineProperty::fillSplineWithData()
{
    if (!m_descriptorProperty) return;
    if (m_spline) delete m_spline;
    m_spline = new Ogre::SimpleSpline;
    TLinkedListNode<CTimelinePoint*>* node = m_timelinePoints;
    if (!node) return;
    while (node) {
        unsigned int count = 0;
        UNIONDATA32BIT* data = node->m_Data->m_descriptorProperty.getData(count, NULL);
        Ogre::Vector3 value;
        switch (m_descriptorProperty->getVariableType()) {
        case VARIABLE_TYPE_INTEGER: case VARIABLE_TYPE_FLOAT:
        case VARIABLE_TYPE_UNSIGNED_INTEGER: case VARIABLE_TYPE_BOOL:
            if (count != 1) return;
            value.x = data[0].m_iValue;
            break;
        case VARIABLE_TYPE_VECTOR2:
            if (count != 2) return;
            value.x = data[0].m_fValue; value.y = data[1].m_fValue;
            break;
        case VARIABLE_TYPE_VECTOR3:
            if (count != 3) return;
            value.x = data[0].m_fValue; value.y = data[1].m_fValue; value.z = data[2].m_fValue;
            break;
        default: SetInterpolationType(static_cast<ETIMELINE_INTERP_TYPES>(0)); return;
        }
        m_spline->addPoint(value);
        node = node->m_pNext;
    }
    m_spline->recalcTangents();
}
void CTimelineProperty::SetInterpolationType(ETIMELINE_INTERP_TYPES interpolationType)
{
    if (!m_descriptorProperty) interpolationType = static_cast<ETIMELINE_INTERP_TYPES>(0);
    else if (m_descriptorProperty->getVariableType() == VARIABLE_TYPE_BOOL)
        interpolationType = static_cast<ETIMELINE_INTERP_TYPES>(6);
    m_interpolationType = interpolationType;
    if (m_spline) delete m_spline;
    if (m_interpolationType == 4) fillSplineWithData();
    else if (m_interpolationType == 5 && m_descriptorProperty->getVariableType() != VARIABLE_TYPE_VECTOR3)
        SetInterpolationType(static_cast<ETIMELINE_INTERP_TYPES>(0));
}
void CTimelineProperty::DoSplineInterpolation(CTimeline*, float timePercent)
{
    if (!m_descriptorProperty || !m_spline) return;
    Ogre::Vector3 value = m_spline->interpolate(timePercent);
    float data[3];
    switch (m_descriptorProperty->getVariableType()) {
    case VARIABLE_TYPE_INTEGER: case VARIABLE_TYPE_FLOAT: case VARIABLE_TYPE_UNSIGNED_INTEGER: case VARIABLE_TYPE_BOOL:
        data[0] = value.x; SetValueOnObject(data, 1); break;
    case VARIABLE_TYPE_VECTOR2:
        data[0] = value.x; data[1] = value.y; SetValueOnObject(data, 2); break;
    case VARIABLE_TYPE_VECTOR3:
        data[0] = value.x; data[1] = value.y; data[2] = value.z; SetValueOnObject(data, 3); break;
    default: break;
    }
}
void CTimelineProperty::SetTimePercentAtPoint(int pointID, float timePercent)
{
    if (!(timePercent < 1.0f)) timePercent = 1.0f;
    TLinkedListNode<CTimelinePoint*>* node = m_timelinePoints;
    while (node && node->m_Data->m_pointID != pointID) node = node->m_pNext;
    if (!node || !node->m_Data) return;
    node->m_Data->m_timePercent = timePercent;
    TLinkedListNode<CTimelinePoint*>* position = m_timelinePoints;
    while (position) {
        if (position != node && position->m_Data->m_timePercent > node->m_Data->m_timePercent) {
            if (node == m_timelinePoints) m_timelinePoints = node->m_pNext;
            if (node->m_pPrevious) node->m_pPrevious->m_pNext = node->m_pNext;
            if (node->m_pNext) node->m_pNext->m_pPrevious = node->m_pPrevious;
            node->m_pNext = NULL; node->m_pPrevious = NULL;
            TLinkedListNode<CTimelinePoint*>* previous = position->m_pPrevious;
            position->m_pPrevious = node;
            if (previous) previous->m_pNext = node;
            node->m_pPrevious = previous; node->m_pNext = position;
            while (m_timelinePoints->m_pPrevious) m_timelinePoints = m_timelinePoints->m_pPrevious;
            return;
        }
        if (!position->m_pNext) break;
        position = position->m_pNext;
    }
    if (!position || position == node) return;
    if (node == m_timelinePoints) m_timelinePoints = node->m_pNext;
    if (node->m_pPrevious) node->m_pPrevious->m_pNext = node->m_pNext;
    if (node->m_pNext) node->m_pNext->m_pPrevious = node->m_pPrevious;
    node->m_pNext = NULL; node->m_pPrevious = NULL;
    TLinkedListNode<CTimelinePoint*>* next = position->m_pNext;
    position->m_pNext = node;
    if (next) next->m_pPrevious = node;
    node->m_pPrevious = position; node->m_pNext = next;
    while (m_timelinePoints->m_pPrevious) m_timelinePoints = m_timelinePoints->m_pPrevious;
}
