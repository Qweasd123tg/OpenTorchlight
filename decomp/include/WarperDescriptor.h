#ifndef WARPERDESCRIPTOR_H
#define WARPERDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "Warper.h"

class CWarperDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CWarperDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CWarperDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CWarper*>(object)->setEnabled(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CWarper*>(object)->getEnabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setLevelDelta(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CWarper*>(object)->setLevelDelta(((const UNIONDATA32BIT*)data)->m_iValue);
    }
    static UNIONDATA8BIT* Get_getLevelDelta(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CWarper*>(object)->getLevelDelta();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setLevelDepth(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CWarper*>(object)->setLevelDepth(((const UNIONDATA32BIT*)data)->m_iValue);
    }
    static UNIONDATA8BIT* Get_getLevelDepth(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CWarper*>(object)->getLevelDepth();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setDungeon(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDungeon(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWarpName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWarpName(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWaypoint(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CWarper*>(object)->setWaypoint(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getWaypoint(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CWarper*>(object)->getWaypoint();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
};

#endif
