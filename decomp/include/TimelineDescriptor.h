#ifndef TIMELINEDESCRIPTOR_H
#define TIMELINEDESCRIPTOR_H

#include "DataGroup.h"
#include "Descriptor.h"
#include "DescriptorLoadConfiguration.h"
#include "DescriptorSaveConfiguration.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "OgreReader.h"
#include "DescriptorProp.h"

class CTimelineDescriptor : public CDescriptor
{
public:
    virtual ~CTimelineDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void descriptorSceneDeactivated(CEditorScene*);
    virtual bool saveAdditionalInfo(CEditorBaseObject*, std::basic_ofstream<char, std::char_traits<char> >*, CDataGroup*, CDescriptorSaveConfiguration*);
    virtual bool loadAdditionalInfo(CEditorBaseObject*, COgreReader*, CDataGroup*, CDescriptorLoadConfiguration*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CTimelineDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_SetTimelineDuration(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_GetTimelineDuration(CEditorBaseObject* object, unsigned int& count);
    static void Set_SetTimelineStep(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_GetTimelineStep(CEditorBaseObject* object, unsigned int& count);
    static void Set_SetTimelineLoops(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_GetTimelineLoops(CEditorBaseObject* object, unsigned int& count);
    static void Set_setSetPropertiesOnLoad(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSetPropertiesOnLoad(CEditorBaseObject* object, unsigned int& count);
    static void Set_SetStartOnLoad(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_GetStartOnLoad(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDefaultInterpolationType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDefaultInterpolationType(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetTimelineInterpolationIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetTimelineInterpolationStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setLayoutCanControl(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getLayoutCanControl(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDurationModicationType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDurationModicationType(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetTimelineModIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetTimelineModStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
};

#endif
