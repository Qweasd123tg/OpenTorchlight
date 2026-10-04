#ifndef TIMELINE_H
#define TIMELINE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <fstream>
#include <string>
#include "DataGroup.h"
#include "DescriptorLoadConfiguration.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "GameEnums.h"
#include "OgreReader.h"

class CTimeline : public CEditorBaseObject
{
public:
    virtual ~CTimeline();
    void setDurationModificationTime(float);
    void Pause();
    long long GetProperty(long long, int, bool);
    int GetNumberOfPropertiesForObjectInTimeline(long long);
    int GetNumberOfPointsForAProperty(long long, int, bool);
    void SetEnabled(bool);
    CTimeline* GetPropertyPointInterpolationType(long long, int);
    void SetPropertyPointValue(long long, int, int, void*, unsigned int);
    long long GetPropertyPointTimePercent(long long, int, int, bool);
    void GetPropertyPointValue(long long, int, int, unsigned int&);
    void SetPropertyPointTimePercent(long long, int, int, float, bool);
    void SetPropertyPointValueByString(long long, int, int, std::wstring&);
    void SetPropertyPointInterpolationType(long long, int, ETIMELINE_INTERP_TYPES);
    long long RemovePointFromProperty(long long, int, int, bool);
    long long AddPointToProperty(long long, int, bool);
    long long RemoveProperty(long long, int, bool);
    long long RemoveObjectByID(long long);
    long long GetPropertyIDForObjectInTimelineByIndex(long long, int);
    long long GetObjectIDInTimelineByIndex(int);
    void resetPropertiesToPercent(float);
    long long GetPointIDInTimelinePropertyByIndex(long long, int, int, bool);
    void AddProperty(CEditorScene*, long long, int, bool);
    void loadTimelineFromBinaryFile(CEditorScene*, COgreReader*, CDescriptorLoadConfiguration*);
    float UpdateTimeline(float);
    CTimeline();
    void saveTimelineToBinaryFile(CEditorScene*, std::basic_ofstream<char, std::char_traits<char> >*);
    float SetTimelinePercentDone(float);
    void Play_Backwards();
    void Play(bool);
    void StopToBeginning();
    void StopToEnd();
    void Stop();
    void rewindToStart();
    void fastFowardToEnd();
    void Reset_To_Beginning();
    void Reset_To_End();
    void saveTimelineToDataGroup(CEditorScene*, CDataGroup*);
    void loadTimelineFromDataGroup(CEditorScene*, CDataGroup*, CDescriptorLoadConfiguration*);

    // fields
    long long m_Unknown58;
    int m_iUnknown60;
    unsigned char m_gap64[0x4] __attribute__((aligned(4)));
    void* m_pUnknown68;
    void* m_pUnknown70;
    long long m_iUnknown78;
    long long m_iUnknown80;
    bool m_bUnknown88;
    bool m_bSetTimelineLoops;
    bool m_bSetStartOnLoad;
    bool m_bLayoutCanControl;
    bool m_bUnknown8C;
    unsigned char m_gap8D[0x3];
    float m_fGetTimelineStep;
    float m_fSetTimelineDuration;
    float m_fUnknown98;
    float m_fSetTimelineStep;
    bool m_bUnknownA0;
    bool m_bEnabled;
    bool m_bUnknownA2;
    bool m_bSetPropertiesOnLoad;
    int m_iDefaultInterpolationType;
    int m_iDurationModicationType;
};

#endif
