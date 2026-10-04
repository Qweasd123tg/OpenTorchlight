#ifndef GRAVITYAFFECTORDESCRIPTOR_H
#define GRAVITYAFFECTORDESCRIPTOR_H

#include "AffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CGravityAffectorDescriptor : public CAffectorDescriptor
{
public:
    virtual ~CGravityAffectorDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CGravityAffectorDescriptor();


    static void Set_setGravity(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getGravity(CEditorBaseObject* object, unsigned int& count);
};

#endif
