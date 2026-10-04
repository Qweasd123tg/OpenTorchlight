#ifndef TIMELINEPROPERTY_H
#define TIMELINEPROPERTY_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <string>
#include "Descriptor.h"
#include "DescriptorProp.h"
#include "EditorScene.h"
#include "GameEnums.h"
#include "RunicCore.h"
class CTimeline;

class CTimelineProperty : public CRunicCore
{
public:
    virtual ~CTimelineProperty();
    void GetFreeIDForPoint();
    int GetTimelinePointIDByIndex(int);
    long GetTimelinePoint(int);
    int GetTimePercentAtPoint(int);
    void SetTimePercentAtPoint(int, float);
    void DoQuaternion(CTimeline*, float);
    void triggerEvent(CTimeline*);
    long long* GetBaseTypeValueAsString(int);
    // unresolved: CTimelineProperty::getValueOfLinearPropertyByPercent(unsigned int, double, CTimelineProperty::CTimelinePoint*, CTimelineProperty::CTimelinePoint*, unsigned int)
    long long GetValueAtPoint(int, unsigned int&);
    void fillSplineWithData();
    void SetInterpolationType(ETIMELINE_INTERP_TYPES);
    void SetValueAtPoint(int, void*, unsigned int);
    // unresolved: CTimelineProperty::SetValueOnObject(CTimelineProperty::CTimelinePoint*)
    void SetValueOnObject(void*, unsigned int);
    // unresolved: CTimelineProperty::DoLinearInterpolation(CTimeline*, float, CTimelineProperty::CTimelinePoint*, CTimelineProperty::CTimelinePoint*)
    void DoSplineInterpolation(CTimeline*, float);
    void Update(float, bool);
    CTimelineProperty* GetValueAtPointAsString(int);
    long long RemovePoint(int);
    CTimelineProperty(CTimeline*, CEditorScene*, CDescriptor*, unsigned int, bool, long long);
    int AddPoint();
    CTimelineProperty(CTimeline*, CEditorScene*, CDescriptor*, CDescriptorProp*, long long);
    void SetValueAtPointByString(int, std::wstring&);

    // fields
    long long m_iUnknown10;
    int m_iUnknown18;
    unsigned int m_iUnknown1C;
    bool m_bUnknown20;
    unsigned char m_gap21[0x3];
    float m_fUnknown24;
    CEditorScene* m_pEditorScene;
    CDescriptor* m_pDescriptor;
    CDescriptorProp* m_pDescriptorProp;
    void* m_pUnknown40;
    int m_iUnknown48;
    unsigned char m_gap4C[0x4] __attribute__((aligned(4)));
    long long m_iUnknown50;
    CTimeline* m_pTimeline;
    bool m_bUnknown60;
};

#endif
