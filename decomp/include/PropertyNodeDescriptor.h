#ifndef PROPERTYNODEDESCRIPTOR_H
#define PROPERTYNODEDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CPropertyNodeDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CPropertyNodeDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CPropertyNodeDescriptor();


    static void Set_setPropertyNodeType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getPropertyNodeType(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getPropertyNodeTypeByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getPropertyNodeTypeString(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setRadius(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRadius(CEditorBaseObject* object, unsigned int& count);
    static void Set_setScaleX(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getScaleX(CEditorBaseObject* object, unsigned int& count);
    static void Set_setScaleZ(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getScaleZ(CEditorBaseObject* object, unsigned int& count);
    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
};

#endif
