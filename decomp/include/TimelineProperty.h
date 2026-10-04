#ifndef TIMELINEPROPERTY_H
#define TIMELINEPROPERTY_H

#include <string>

#include "Descriptor.h"
#include "DescriptorProp.h"
#include "EditorScene.h"
#include "GameEnums.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CTimeline;

class __attribute__((packed)) CTimelineProperty : public CRunicCore
{
public:
    class CTimelinePoint : public CRunicCore
    {
    public:
        float m_timePercent;                         // 0x10
        unsigned char m_padding14[4];                 // 0x14
        CDescriptorProp m_descriptorProperty;         // 0x18
        int m_pointID;                                // 0x98
    };

    virtual ~CTimelineProperty();

    int GetFreeIDForPoint();
    int GetTimelinePointIDByIndex(int index);
    CTimelinePoint *GetTimelinePoint(int pointID);
    float GetTimePercentAtPoint(int pointID);
    void SetTimePercentAtPoint(int pointID, float timePercent);
    void DoQuaternion(CTimeline *timeline, float timePercent);
    void triggerEvent(CTimeline *timeline);
    const std::wstring &GetBaseTypeValueAsString(int pointID);
    double getValueOfLinearPropertyByPercent(
        unsigned int interpolationType,
        double timePercent,
        CTimelinePoint *fromPoint,
        CTimelinePoint *toPoint,
        unsigned int componentIndex);
    void *GetValueAtPoint(int pointID, unsigned int &dataSize);
    void fillSplineWithData();
    void SetInterpolationType(ETIMELINE_INTERP_TYPES interpolationType);
    void SetValueAtPoint(int pointID, void *value, unsigned int dataSize);
    void SetValueOnObject(CTimelinePoint *point);
    void SetValueOnObject(void *value, unsigned int dataSize);
    void DoLinearInterpolation(
        CTimeline *timeline,
        float timePercent,
        CTimelinePoint *fromPoint,
        CTimelinePoint *toPoint);
    void DoSplineInterpolation(CTimeline *timeline, float timePercent);
    void Update(float timePercent, bool forward);
    std::wstring GetValueAtPointAsString(int pointID);
    bool RemovePoint(int pointID);

    CTimelineProperty(
        CTimeline *timeline,
        CEditorScene *editorScene,
        CDescriptor *descriptor,
        unsigned int eventID,
        bool inputEvent,
        long long objectID);

    int AddPoint();

    CTimelineProperty(
        CTimeline *timeline,
        CEditorScene *editorScene,
        CDescriptor *descriptor,
        CDescriptorProp *descriptorProperty,
        long long objectID);

    void SetValueAtPointByString(int pointID, std::wstring &value);

    long long m_objectID;                             // 0x10
    int m_propertyID;                                // 0x18
    unsigned int m_eventID;                          // 0x1C
    bool m_inputEvent;                               // 0x20
    unsigned char m_padding21[3];                     // 0x21
    float m_lastTimePercent;                         // 0x24
    CEditorScene *m_editorScene;                      // 0x28
    CDescriptor *m_descriptor;                        // 0x30
    CDescriptorProp *m_descriptorProperty;            // 0x38
    TArrayList<CTimelinePoint *> *m_timelinePoints;   // 0x40
    int m_interpolationType;                         // 0x48
    unsigned char m_padding4C[4];                     // 0x4C
    void *m_spline;                                  // 0x50
    CTimeline *m_timeline;                           // 0x58
    bool m_updating;                                  // 0x60
};

#endif
