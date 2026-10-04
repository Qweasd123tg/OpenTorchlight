#ifndef COUNTERDESCRIPTOR_H
#define COUNTERDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "Counter.h"

class CCounterDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CCounterDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CCounterDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CCounter*>(object)->setEnabled(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CCounter*>(object)->getEnabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setCount(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CCounter*>(object)->setCount(((const UNIONDATA32BIT*)data)->m_iValue);
    }
    static UNIONDATA8BIT* Get_getCount(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CCounter*>(object)->getCount();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setStartingValue(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getStartingValue(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CCounter*>(object)->getStartingValue();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setLogicType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getLogicType(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetCounterTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetCounterTypeTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
};

#endif
