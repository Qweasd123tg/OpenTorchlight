#ifndef UNITTRIGGERDESCRIPTOR_H
#define UNITTRIGGERDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "Descriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CUnitTriggerDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CUnitTriggerDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual bool DescriptorObjectBeingDeleted(CEditorBaseObject*);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    void AddInputsAndOutputs(CDescriptor*);
    CUnitTriggerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUnitModelName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUnitModelName(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetTriggerModelIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetTriggerModelStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setLoopType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getLoopType(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetLoopTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetLoopTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setRequiredQuest(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRequiredQuest(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getQuestIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getQuestStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setRequiredUnit(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRequiredUnit(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getItemIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getItemStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setRequiredUnitCount(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRequiredUnitCount(CEditorBaseObject* object, unsigned int& count);
    static void Set_setTakeRequiredUnit(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getTakeRequiredUnit(CEditorBaseObject* object, unsigned int& count);
};

#endif
