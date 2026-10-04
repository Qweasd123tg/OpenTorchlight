#ifndef EDITORBUTTONDESCRIPTOR_H
#define EDITORBUTTONDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CEditorButtonDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CEditorButtonDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CEditorButtonDescriptor();


    static void Set_setVisible(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getVisible(CEditorBaseObject* object, unsigned int& count);
    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
    static void Set_setPosXPCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getPosXPCT(CEditorBaseObject* object, unsigned int& count);
    static void Set_setPosYPCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getPosYPCT(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWidthPCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWidthPCT(CEditorBaseObject* object, unsigned int& count);
    static void Set_setHeightPCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getHeightPCT(CEditorBaseObject* object, unsigned int& count);
    static void Set_setPosX(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getPosX(CEditorBaseObject* object, unsigned int& count);
    static void Set_setPosY(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getPosY(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWidth(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWidth(CEditorBaseObject* object, unsigned int& count);
    static void Set_setHeight(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getHeight(CEditorBaseObject* object, unsigned int& count);
    static void Set_setOffsetX(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getOffsetX(CEditorBaseObject* object, unsigned int& count);
    static void Set_setOffsetY(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getOffsetY(CEditorBaseObject* object, unsigned int& count);
    static void Set_setOffsetXPct(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getOffsetXPct(CEditorBaseObject* object, unsigned int& count);
    static void Set_setOffsetYPct(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getOffsetYPct(CEditorBaseObject* object, unsigned int& count);
    static void Set_setNormalImage(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getNormalImage(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRolloverImage(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRolloverImage(CEditorBaseObject* object, unsigned int& count);
    static void Set_setClickedImage(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getClickedImage(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDisabledImage(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDisabledImage(CEditorBaseObject* object, unsigned int& count);
};

#endif
