#ifndef OUTPUTINCREMENTORDESCRIPTOR_H
#define OUTPUTINCREMENTORDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class COutputIncrementorDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~COutputIncrementorDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    COutputIncrementorDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMaxIncrement(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMaxIncrement(CEditorBaseObject* object, unsigned int& count);
    static void Set_setLoopCount(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getLoopCount(CEditorBaseObject* object, unsigned int& count);
    static void Set_setLoopForever(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getLoopForever(CEditorBaseObject* object, unsigned int& count);
};

#endif
