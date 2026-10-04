#ifndef VORTEXAFFECTORDESCRIPTOR_H
#define VORTEXAFFECTORDESCRIPTOR_H

#include "AffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CVortexAffectorDescriptor : public CAffectorDescriptor
{
public:
    virtual ~CVortexAffectorDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CVortexAffectorDescriptor();


    static void Set_setRotationVector(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRotationVector(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynamicPropRotationSpeed(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynamicPropRotationSpeed(CEditorBaseObject* object, unsigned int& count);
};

#endif
