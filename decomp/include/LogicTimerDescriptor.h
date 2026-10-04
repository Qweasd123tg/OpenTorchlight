#ifndef LOGICTIMERDESCRIPTOR_H
#define LOGICTIMERDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "LogicTimer.h"

class CLogicTimerDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CLogicTimerDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CLogicTimerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CLogicTimer*>(object)->setEnabled(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CLogicTimer*>(object)->getEnabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setTimer(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getTimer(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CLogicTimer*>(object)->getTimer();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setMaxTimer(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMaxTimer(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CLogicTimer*>(object)->getMaxTimer();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setLoopCount(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getLoopCount(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CLogicTimer*>(object)->getLoopCount();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setLoopForever(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CLogicTimer*>(object)->setLoopForever(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getLoopForever(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CLogicTimer*>(object)->getLoopForever();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
};

#endif
