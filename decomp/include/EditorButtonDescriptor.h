#ifndef EDITORBUTTONDESCRIPTOR_H
#define EDITORBUTTONDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "EditorButton.h"

class CEditorButtonDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CEditorButtonDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CEditorButtonDescriptor();


    static void Set_setVisible(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setVisible(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getVisible(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CEditorButton*>(object)->getVisible();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setEnabled(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CEditorButton*>(object)->getEnabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setPosXPCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setPosXPCT(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getPosXPCT(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorButton*>(object)->getPosXPCT();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setPosYPCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setPosYPCT(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getPosYPCT(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorButton*>(object)->getPosYPCT();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setWidthPCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWidthPCT(CEditorBaseObject* object, unsigned int& count);
    static void Set_setHeightPCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getHeightPCT(CEditorBaseObject* object, unsigned int& count);
    static void Set_setPosX(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setPosX(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getPosX(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorButton*>(object)->getPosX();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setPosY(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setPosY(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getPosY(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorButton*>(object)->getPosY();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setWidth(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWidth(CEditorBaseObject* object, unsigned int& count);
    static void Set_setHeight(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getHeight(CEditorBaseObject* object, unsigned int& count);
    static void Set_setOffsetX(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setOffsetX(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getOffsetX(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorButton*>(object)->getOffsetX();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setOffsetY(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setOffsetY(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getOffsetY(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorButton*>(object)->getOffsetY();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setOffsetXPct(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setOffsetXPct(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getOffsetXPct(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorButton*>(object)->getOffsetXPct();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setOffsetYPct(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setOffsetYPct(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getOffsetYPct(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CEditorButton*>(object)->getOffsetYPct();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setNormalImage(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setNormalImage((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getNormalImage(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRolloverImage(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setRolloverImage((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getRolloverImage(CEditorBaseObject* object, unsigned int& count);
    static void Set_setClickedImage(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setClickedImage((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getClickedImage(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDisabledImage(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CEditorButton*>(object)->setDisabledImage((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getDisabledImage(CEditorBaseObject* object, unsigned int& count);
};

#endif
