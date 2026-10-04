#ifndef GEOMETRYROTATEDESCRIPTOR_H
#define GEOMETRYROTATEDESCRIPTOR_H

#include "AffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CGeometryRotateDescriptor : public CAffectorDescriptor
{
public:
    virtual ~CGeometryRotateDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CGeometryRotateDescriptor();


    static void Set_setDynamicPropRotationSpeed(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynamicPropRotationSpeed(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUseOwnRotationSpeed(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUseOwnRotationSpeed(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRotationAxis(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRotationAxis(CEditorBaseObject* object, unsigned int& count);
};

#endif
