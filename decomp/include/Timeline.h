#ifndef TIMELINE_H
#define TIMELINE_H

#include <fstream>
#include <map>
#include <string>
#include <utility>

#include "DataGroup.h"
#include "DescriptorLoadConfiguration.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "GameEnums.h"
#include "OgreReader.h"

class CTimelineProperty;

class CTimeline : public CEditorBaseObject
{
public:
    virtual ~CTimeline();

    void setDurationModificationTime(float duration);
    void Pause();

    CTimelineProperty* GetProperty(long long objectID, int propertyID, bool isEvent);
    int GetNumberOfPropertiesForObjectInTimeline(long long objectID);
    int GetNumberOfPointsForAProperty(long long objectID, int propertyID, bool isEvent);
    void SetEnabled(bool enabled);

    std::wstring GetPropertyPointInterpolationType(long long objectID, int propertyID);
    void SetPropertyPointValue(long long objectID, int propertyID, int pointID,
                               void* value, unsigned int valueSize);
    float GetPropertyPointTimePercent(long long objectID, int propertyID,
                                      int pointID, bool isEvent);
    void* GetPropertyPointValue(long long objectID, int propertyID, int pointID,
                               unsigned int& value);
    void SetPropertyPointTimePercent(long long objectID, int propertyID,
                                      int pointID, float timePercent, bool isEvent);
    void SetPropertyPointValueByString(long long objectID, int propertyID,
                                       int pointID, std::wstring& value);
    void SetPropertyPointInterpolationType(long long objectID, int propertyID,
                                           ETIMELINE_INTERP_TYPES interpolationType);

    long long RemovePointFromProperty(long long objectID, int propertyID,
                                      int pointID, bool isEvent);
    long long AddPointToProperty(long long objectID, int propertyID, bool isEvent);
    long long RemoveProperty(long long objectID, int propertyID, bool isEvent);
    long long RemoveObjectByID(long long objectID);

    std::pair<int, bool> GetPropertyIDForObjectInTimelineByIndex(long long objectID, int index);
    long long GetObjectIDInTimelineByIndex(int index);
    void resetPropertiesToPercent(float timePercent);
    long long GetPointIDInTimelinePropertyByIndex(long long objectID, int propertyID,
                                                   int pointIndex, bool isEvent);

    void AddProperty(CEditorScene* scene, long long objectID, int propertyID,
                     bool isEvent);
    void loadTimelineFromBinaryFile(CEditorScene* scene, COgreReader* reader,
                                    CDescriptorLoadConfiguration* configuration);
    float UpdateTimeline(float elapsedTime);

    CTimeline();

    void saveTimelineToBinaryFile(CEditorScene* scene,
                                  std::basic_ofstream<char, std::char_traits<char> >* stream);
    float SetTimelinePercentDone(float percentDone);

    void Play_Backwards();
    void Play(bool forwards);
    void StopToBeginning();
    void StopToEnd();
    void Stop();
    void rewindToStart();
    void fastFowardToEnd();
    void Reset_To_Beginning();
    void Reset_To_End();

    void saveTimelineToDataGroup(CEditorScene* scene, CDataGroup* dataGroup);
    void loadTimelineFromDataGroup(CEditorScene* scene, CDataGroup* dataGroup,
                                   CDescriptorLoadConfiguration* configuration);

    std::map<long long,
             std::map<std::pair<int, bool>, CTimelineProperty*> >
        m_timelineProperties;

    bool m_bTimelineLoaded;
    bool m_bTimelineLoops;
    bool m_bStartOnLoad;
    bool m_bLayoutCanControl;
    bool m_bManualUpdate;

    float m_fGetTimelineStep;
    float m_fSetTimelineDuration;
    float m_fTimelinePosition;
    float m_fSetTimelineStep;

    bool m_bIsPlayingBackwards;
    bool m_bEnabled;
    bool m_bTimelineWasStopped;
    bool m_bSetPropertiesOnLoad;

    int m_iDefaultInterpolationType;
    int m_iDurationModificationType;
};

#endif
