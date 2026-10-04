#ifndef TEXTUREROTATEDESCRIPTOR_H
#define TEXTUREROTATEDESCRIPTOR_H

#include "AffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CTextureRotateDescriptor : public CAffectorDescriptor
{
public:
    virtual ~CTextureRotateDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CTextureRotateDescriptor();


    static void Set_setDynamicPropRotationSpeed(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynamicPropRotationSpeed(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynamicPropRotation(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynamicPropRotation(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUseOwnRotationSpeed(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUseOwnRotationSpeed(CEditorBaseObject* object, unsigned int& count);
};

#endif
