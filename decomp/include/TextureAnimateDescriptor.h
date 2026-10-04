#ifndef TEXTUREANIMATEDESCRIPTOR_H
#define TEXTUREANIMATEDESCRIPTOR_H

#include "AffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CTextureAnimateDescriptor : public CAffectorDescriptor
{
public:
    virtual ~CTextureAnimateDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CTextureAnimateDescriptor();


    static void Set_setDynamicPropAnimationSpeed(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynamicPropAnimationSpeed(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUseOwnAnimationSpeed(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUseOwnAnimationSpeed(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUseRandomStartingFrame(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUseRandomStartingFrame(CEditorBaseObject* object, unsigned int& count);
};

#endif
