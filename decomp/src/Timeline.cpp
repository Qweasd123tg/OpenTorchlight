#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Timeline.h"
#include "DataGroup.h"
#include "Descriptor.h"
#include "DescriptorLoadConfiguration.h"
#include "DescriptorProp.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "OgreReader.h"
#include "TimelineProperty.h"
#include "StringUtilities.h"

void CTimeline::setDurationModificationTime(float duration)
{
    if (m_iDurationModificationType == 1) {
        m_fSetTimelineDuration = duration;
        return;
    }

    if (m_iDurationModificationType == 2) {
        m_fSetTimelineDuration *= duration;
    }
}

void CTimeline::Pause()
{
    if (!m_bEnabled)
        return;

    m_bEnabled = false;
    BroadcastEvent(OUTPUT_EVENT_PAUSED);
}

CTimelineProperty* CTimeline::GetProperty(long long objectID, int propertyID,
                                          bool isEvent)
{
    if (propertyID == -1 || objectID == -1)
        return NULL;

    std::map<long long,
             std::map<std::pair<int, bool>, CTimelineProperty*> >::iterator
        objectIterator = m_timelineProperties.find(objectID);
    if (objectIterator == m_timelineProperties.end())
        return NULL;

    std::map<std::pair<int, bool>, CTimelineProperty*>::iterator
        propertyIterator =
            objectIterator->second.find(std::make_pair(propertyID, isEvent));
    if (propertyIterator == objectIterator->second.end())
        return NULL;

    return propertyIterator->second;
}

int CTimeline::GetNumberOfPropertiesForObjectInTimeline(long long objectID)
{
    if (objectID == -1)
        return 0;

    std::map<long long, std::map<std::pair<int, bool>, CTimelineProperty*> >::iterator
        property = m_timelineProperties.find(objectID);

    if (property == m_timelineProperties.end())
        return 0;

    return property->second.size();
}

void CTimeline::SetEnabled(bool enabled)
{
    m_bEnabled = enabled;
}

void CTimeline::SetPropertyPointValue(long long objectID, int propertyID, int pointID,
                                     void* value, unsigned int valueSize)
{
    CTimelineProperty* property = GetProperty(objectID, propertyID, false);
    if (property != NULL)
        property->SetValueAtPoint(pointID, value, valueSize);
}

float CTimeline::GetPropertyPointTimePercent(long long objectID, int propertyID,
                                              int pointID, bool isEvent)
{
    CTimelineProperty* property = GetProperty(objectID, propertyID, isEvent);
    if (property != NULL)
        return property->GetTimePercentAtPoint(pointID);
    return 0.0f;
}

void CTimeline::GetPropertyPointValue(long long objectID, int propertyID, int pointID,
                                      unsigned int& value)
{
    CTimelineProperty* property = GetProperty(objectID, propertyID, false);
    if (property != NULL)
        property->GetValueAtPoint(pointID, value);
}

void CTimeline::SetPropertyPointTimePercent(long long objectID, int propertyID,
                                              int pointID, float timePercent,
                                              bool isEvent)
{
    CTimelineProperty* property = GetProperty(objectID, propertyID, isEvent);
    if (property != NULL)
        property->SetTimePercentAtPoint(pointID, timePercent);
}

void CTimeline::SetPropertyPointValueByString(long long objectID, int propertyID,
                                              int pointID, std::wstring& value)
{
    CTimelineProperty* property = GetProperty(objectID, propertyID, false);
    if (property != NULL)
        property->SetValueAtPointByString(pointID, value);
}

void CTimeline::SetPropertyPointInterpolationType(long long objectID, int propertyID,
                                                  ETIMELINE_INTERP_TYPES interpolationType)
{
    CTimelineProperty* property = GetProperty(objectID, propertyID, false);
    if (property != NULL)
        property->SetInterpolationType(interpolationType);
}

long long CTimeline::RemovePointFromProperty(long long objectID, int propertyID,
                                              int pointID, bool isEvent)
{
    CTimelineProperty* property = GetProperty(objectID, propertyID, isEvent);
    if (property != NULL)
        return property->RemovePoint(pointID);
    return 1;
}

long long CTimeline::AddPointToProperty(long long objectID, int propertyID, bool isEvent)
{
    CTimelineProperty* property = GetProperty(objectID, propertyID, isEvent);
    if (property != NULL)
        return property->AddPoint();
    return 0xffffffff;
}

long long CTimeline::RemoveProperty(long long objectID, int propertyID, bool isEvent)
{
    std::map<long long,
             std::map<std::pair<int, bool>, CTimelineProperty*> >::iterator
        objectIt = m_timelineProperties.find(objectID);

    if (objectIt != m_timelineProperties.end())
    {
        std::map<std::pair<int, bool>, CTimelineProperty*>::iterator propertyIt =
            objectIt->second.find(std::make_pair(propertyID, isEvent));

        if (propertyIt != objectIt->second.end())
        {
            if (propertyIt->second != NULL)
                delete propertyIt->second;

            objectIt->second.erase(propertyIt);
            return 1;
        }
    }

    return 0;
}

long long CTimeline::RemoveObjectByID(long long objectID)
{
    if (objectID == -1)
    {
        return 0;
    }

    std::map<long long, std::map<std::pair<int, bool>, CTimelineProperty*> >::iterator
        object = m_timelineProperties.find(objectID);
    if (object == m_timelineProperties.end())
    {
        return 1;
    }

    std::map<std::pair<int, bool>, CTimelineProperty*>::iterator property =
        object->second.begin();
    while (property != object->second.end())
    {
        if (property->second != NULL)
        {
            delete property->second;
            property->second = NULL;
        }
        ++property;
    }

    object->second.clear();
    m_timelineProperties.erase(object);
    return 1;
}

long long CTimeline::GetObjectIDInTimelineByIndex(int index)
{
    if (index < 0 || static_cast<unsigned int>(index) >= m_timelineProperties.size())
    {
        return -1;
    }

    std::map<long long, std::map<std::pair<int, bool>, CTimelineProperty*> >::iterator it =
        m_timelineProperties.begin();

    while (index > 0)
    {
        ++it;
        --index;
    }

    return it->first;
}

long long CTimeline::GetPointIDInTimelinePropertyByIndex(long long objectID, int propertyID,
                                                          int pointIndex, bool isEvent)
{
    if (propertyID < 0 || objectID == -1 || pointIndex < 0)
        return 0xffffffff;

    CTimelineProperty* property = GetProperty(objectID, propertyID, isEvent);
    if (!property)
        return 0xffffffff;

    return property->GetTimelinePointIDByIndex(pointIndex);
}

void CTimeline::AddProperty(CEditorScene* scene, long long objectID, int propertyID,
                            bool isEvent)
{
    if (objectID == -1 || scene == NULL || propertyID == -1)
        return;

    if (GetProperty(objectID, propertyID, isEvent) != NULL)
        return;

    CEditorBaseObject* object = scene->GetObjectInScene(objectID);
    if (object == NULL)
        return;

    CDescriptor* descriptor = object->getDescriptor();
    if (descriptor == NULL)
        return;

    CDescriptorProp* descriptorProperty =
        descriptor->GetPropertyByIndex((unsigned int)propertyID);
    if (descriptorProperty == NULL)
        return;

    CTimelineProperty* property;
    if (isEvent) {
        property = new CTimelineProperty(this, scene, descriptor,
                                         (unsigned int)propertyID, true,
                                         objectID);
    } else {
        property = new CTimelineProperty(this, scene, descriptor,
                                         descriptorProperty, objectID);
    }

    property->SetInterpolationType(
        (ETIMELINE_INTERP_TYPES)m_iDefaultInterpolationType);

    std::pair<int, bool> key(propertyID, isEvent);
    if (m_timelineProperties.find(objectID) == m_timelineProperties.end() ||
        m_timelineProperties[objectID].find(key) ==
            m_timelineProperties[objectID].end()) {
        m_timelineProperties[objectID][key] = property;
    } else {
        delete property;
    }
}

void CTimeline::loadTimelineFromBinaryFile(CEditorScene* scene,
                                           COgreReader* reader,
                                           CDescriptorLoadConfiguration* configuration)
{
    if (scene == NULL || reader == NULL || configuration == NULL)
        return;

    unsigned int objectCount = 0;
    reader->read(&objectCount, 4);
    if (objectCount == 0)
        return;

    for (unsigned int objectIndex = 0; objectIndex < objectCount; ++objectIndex) {
        long long objectID = 0;
        unsigned int propertyCount = 0;
        reader->read(&objectID, 8);
        reader->read(&propertyCount, 4);

        objectID = configuration->getRemappedID(objectID);
        CEditorBaseObject* sceneObject = scene->GetObjectInScene(objectID);

        for (unsigned int propertyIndex = 0;
             propertyIndex < propertyCount;
             ++propertyIndex) {
            int propertyID = 0;
            bool isEvent = false;
            unsigned int pointCount = 0;
            reader->read(&propertyID, 4);
            reader->read(&isEvent, 1);
            reader->read(&pointCount, 4);

            CTimelineProperty* property = NULL;
            if (sceneObject != NULL) {
                AddProperty(scene, objectID, propertyID, isEvent);
                property = GetProperty(objectID, propertyID, isEvent);
            }

            for (unsigned int pointIndex = 0;
                 pointIndex < pointCount;
                 ++pointIndex) {
                float timePercent = 0.0f;
                int interpolationType = 0;
                int pointID = -1;
                reader->read(&timePercent, 4);
                reader->read(&interpolationType, 4);

                if (sceneObject != NULL) {
                    pointID = AddPointToProperty(objectID, propertyID, isEvent);
                    SetPropertyPointTimePercent(objectID, propertyID, pointID,
                                                timePercent, isEvent);
                    SetPropertyPointInterpolationType(
                        objectID, propertyID,
                        static_cast<ETIMELINE_INTERP_TYPES>(interpolationType));
                }

                if (!isEvent) {
                    unsigned int valueSize = 0;
                    reader->read(&valueSize, 4);

                    unsigned int* values = new unsigned int[valueSize]();
                    reader->read(values, valueSize * sizeof(unsigned int));

                    if (sceneObject != NULL)
                        property->SetValueAtPoint(pointID, values, valueSize);

                    delete[] values;
                }
            }
        }
    }
}

CTimeline::CTimeline()
    : CEditorBaseObject(),
      m_bTimelineLoaded(false),
      m_bTimelineLoops(false),
      m_bStartOnLoad(true),
      m_bLayoutCanControl(true),
      m_bManualUpdate(false),
      m_fGetTimelineStep(0.0f),
      m_fSetTimelineDuration(1.0f),
      m_fTimelinePosition(-0.01f),
      m_fSetTimelineStep(0.0f),
      m_bIsPlayingBackwards(false),
      m_bEnabled(false),
      m_bTimelineWasStopped(false),
      m_bSetPropertiesOnLoad(true),
      m_iDefaultInterpolationType(0),
      m_iDurationModificationType(0)
{
}

void CTimeline::Play_Backwards()
{
    if (m_bEnabled && m_bIsPlayingBackwards)
        return;

    m_bIsPlayingBackwards = true;
    m_bEnabled = true;
    resetPropertiesToPercent(1.01f);
    SetTimelinePercentDone(1.01f);
    BroadcastEvent(OUTPUT_EVENT_STARTED);
    BroadcastEvent(OUTPUT_EVENT_STARTED_BACKWARDS);
}

void CTimeline::Play(bool forwards)
{
    if (!forwards)
    {
        Play_Backwards();
        return;
    }

    if (m_bEnabled && !m_bIsPlayingBackwards)
        return;

    m_bIsPlayingBackwards = false;
    m_bEnabled = true;
    resetPropertiesToPercent(-0.01f);
    SetTimelinePercentDone(-0.01f);
    BroadcastEvent(OUTPUT_EVENT_STARTED);
    BroadcastEvent(OUTPUT_EVENT_STARTED_FORWARDS);
}

void CTimeline::StopToBeginning()
{
    if (!m_bEnabled)
        return;

    m_bEnabled = false;
    resetPropertiesToPercent(0.01f);
    SetTimelinePercentDone(0.01f);
    BroadcastEvent(OUTPUT_EVENT_STOPPED_2);
    BroadcastEvent(m_bTimelineLoops ? 43 : 44);
}

void CTimeline::StopToEnd()
{
    if (!m_bEnabled)
        return;

    m_bEnabled = false;
    resetPropertiesToPercent(1.01f);
    SetTimelinePercentDone(1.01f);
    BroadcastEvent(OUTPUT_EVENT_STOPPED_2);

    if (m_bIsPlayingBackwards)
        BroadcastEvent(43);
    else
        BroadcastEvent(44);
}

void CTimeline::Stop()
{
    if (!m_bIsPlayingBackwards) {
        if (m_fTimelinePosition > 0.0f) {
            StopToBeginning();
        }
    } else if (m_fTimelinePosition < 1.0f) {
        StopToEnd();
    }
}

void CTimeline::rewindToStart()
{
    m_bEnabled = true;
    resetPropertiesToPercent(-0.01f);
    SetTimelinePercentDone(-0.01f);
    BroadcastEvent(OUTPUT_EVENT_STOPPED_2);
    BroadcastEvent(OUTPUT_EVENT_STOPPED_BACKWARDS);
    m_bEnabled = false;
}

void CTimeline::fastFowardToEnd()
{
    m_bEnabled = true;
    resetPropertiesToPercent(1.01f);
    SetTimelinePercentDone(1.01f);
    BroadcastEvent(OUTPUT_EVENT_STOPPED_2);
    BroadcastEvent(OUTPUT_EVENT_STOPPED_FORWARDS);
    m_bEnabled = false;
}

void CTimeline::Reset_To_Beginning()
{
    if (m_fTimelinePosition != -0.01f) {
        resetPropertiesToPercent(-0.01f);
        SetTimelinePercentDone(-0.01f);
        BroadcastEvent(OUTPUT_EVENT_RESET_TO_BEGINNING);
    }
}

void CTimeline::Reset_To_End()
{
    if (m_fTimelinePosition != 1.01f) {
        resetPropertiesToPercent(1.01f);
        SetTimelinePercentDone(1.01f);
        BroadcastEvent(OUTPUT_EVENT_RESET_TO_END);
    }
}

void CTimeline::loadTimelineFromDataGroup(CEditorScene* scene, CDataGroup* dataGroup,
                                           CDescriptorLoadConfiguration* configuration)
{
    static const wchar_t* const interpolationTypes[] = {
        L"LINEAR",
        L"EASEIN",
        L"EASEOUT",
        L"EASEINOUT",
        L"CONSTANT",
        L"STEP",
        L"DISCRETE",
        L"NONE"
    };

    if (configuration == NULL || scene == NULL || dataGroup == NULL)
        return;

    CDataGroup* timelineData = dataGroup->GetDataGroupByName(L"TIMELINEDATA", false);
    if (timelineData == NULL)
        return;

    long long timelineID =
        configuration->getRemappedID(timelineData->GetDataValue(L"ID", -1LL));
    if (timelineID != getGuid())
        return;

    for (unsigned int objectIndex = 0;
         objectIndex < timelineData->GetNumberOfDataGroups();
         ++objectIndex) {
        CDataGroup* objectGroup = timelineData->GetDataGroup(objectIndex);

        long long objectID =
            configuration->getRemappedID(objectGroup->GetDataValue(L"OBJECTID", -1LL));
        if (objectID == -1)
            continue;

        CEditorBaseObject* object = scene->GetObjectInScene(objectID);
        if (object == NULL || object->getDescriptor() == NULL ||
            objectGroup->GetNumberOfDataGroups() == 0)
            continue;

        CDescriptor* descriptor = object->getDescriptor();

        for (unsigned int propertyIndex = 0;
             propertyIndex < objectGroup->GetNumberOfDataGroups();
             ++propertyIndex) {
            CDataGroup* propertyGroup = objectGroup->GetDataGroup(propertyIndex);

            if (propertyGroup->GetGroupName() != L"TIMELINEOBJECTPROPERTY" &&
                propertyGroup->GetGroupName() != L"TIMELINEOBJECTEVENT")
                return;

            std::wstring propertyName = STRINGS::StringUpper(
                propertyGroup->GetDataValue(L"OBJECTPROPERTYNAME", EMPTY_WSTRING));
            std::wstring eventName =
                propertyGroup->GetDataValue(L"OBJECTEVENTNAME", EMPTY_WSTRING);

            int propertyID = -1;
            bool isEvent = false;

            if (propertyName != EMPTY_WSTRING) {
                propertyID = descriptor->GetPropertyID(propertyName);
            } else if (eventName != EMPTY_WSTRING) {
                propertyID = descriptor->GetInputLogicWrapperIndex(eventName);
                isEvent = propertyID != -1;
            }

            if (propertyID == -1)
                continue;

            AddProperty(scene, objectID, propertyID, isEvent);

            for (unsigned int pointIndex = 0;
                 pointIndex < propertyGroup->GetNumberOfDataGroups();
                 ++pointIndex) {
                CDataGroup* pointGroup = propertyGroup->GetDataGroup(pointIndex);

                float timePercent = pointGroup->GetDataValue(L"TIMEPERCENT", 0.0f);
                std::wstring interpolation =
                    pointGroup->GetDataValue(L"INTERPOLATION", interpolationTypes[7]);

                int interpolationType = 7;
                for (int i = 0; i < 8; ++i) {
                    if (interpolation == interpolationTypes[i]) {
                        interpolationType = i;
                        break;
                    }
                }

                int pointID = AddPointToProperty(objectID, propertyID, isEvent);
                SetPropertyPointTimePercent(objectID, propertyID, pointID,
                                            timePercent, isEvent);
                SetPropertyPointInterpolationType(
                    objectID, propertyID,
                    static_cast<ETIMELINE_INTERP_TYPES>(interpolationType));

                if (!isEvent) {
                    std::wstring value =
                        pointGroup->GetDataValue(L"VALUE", EMPTY_WSTRING);
                    SetPropertyPointValueByString(objectID, propertyID, pointID, value);
                }
            }
        }
    }

    Reset_To_Beginning();
}
