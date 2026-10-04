#ifndef EDITORIMAGEDESCRIPTOR_H
#define EDITORIMAGEDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "EditorImage.h"

class CEditorImageDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CEditorImageDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CEditorImageDescriptor();


    static void Set_setVisible(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorImage*>(object)->setVisible(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getVisible(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CEditorImage*>(object)->getVisible();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setPosXPCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorImage*>(object)->setPosXPCT(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getPosXPCT(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorImage*>(object)->getPosXPCT();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setPosYPCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorImage*>(object)->setPosYPCT(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getPosYPCT(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorImage*>(object)->getPosYPCT();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setWidthPCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWidthPCT(CEditorBaseObject* object, unsigned int& count);
    static void Set_setHeightPCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getHeightPCT(CEditorBaseObject* object, unsigned int& count);
    static void Set_setPosX(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorImage*>(object)->setPosX(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getPosX(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorImage*>(object)->getPosX();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setPosY(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorImage*>(object)->setPosY(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getPosY(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorImage*>(object)->getPosY();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setWidth(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWidth(CEditorBaseObject* object, unsigned int& count);
    static void Set_setHeight(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getHeight(CEditorBaseObject* object, unsigned int& count);
    static void Set_setOffsetX(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorImage*>(object)->setOffsetX(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getOffsetX(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorImage*>(object)->getOffsetX();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setOffsetY(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorImage*>(object)->setOffsetY(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getOffsetY(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorImage*>(object)->getOffsetY();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setOffsetXPct(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorImage*>(object)->setOffsetXPct(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getOffsetXPct(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorImage*>(object)->getOffsetXPct();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setOffsetYPct(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorImage*>(object)->setOffsetYPct(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getOffsetYPct(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorImage*>(object)->getOffsetYPct();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setImageFileName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getImageFileName(CEditorBaseObject* object, unsigned int& count);
};

#endif
