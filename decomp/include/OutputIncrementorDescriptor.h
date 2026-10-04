#ifndef OUTPUTINCREMENTORDESCRIPTOR_H
#define OUTPUTINCREMENTORDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "OutputIncrementor.h"

class COutputIncrementorDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~COutputIncrementorDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    COutputIncrementorDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<COutputIncrementor*>(object)->setEnabled(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<COutputIncrementor*>(object)->getEnabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setMaxIncrement(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMaxIncrement(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(unsigned int);
        gUnionOf32BitData[0].m_uValue = static_cast<COutputIncrementor*>(object)->getMaxIncrement();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setLoopCount(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getLoopCount(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<COutputIncrementor*>(object)->getLoopCount();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setLoopForever(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<COutputIncrementor*>(object)->setLoopForever(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getLoopForever(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<COutputIncrementor*>(object)->getLoopForever();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
};

#endif
