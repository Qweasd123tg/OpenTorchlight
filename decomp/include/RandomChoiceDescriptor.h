#ifndef RANDOMCHOICEDESCRIPTOR_H
#define RANDOMCHOICEDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CRandomChoiceDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CRandomChoiceDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CRandomChoiceDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRandomType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRandomType(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetChoiceTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetChoiceTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setCount(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCount(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRandomValue0(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRandomValue0(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRandomValue1(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRandomValue1(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRandomValue2(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRandomValue2(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRandomValue3(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRandomValue3(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRandomValue4(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRandomValue4(CEditorBaseObject* object, unsigned int& count);
};

#endif
