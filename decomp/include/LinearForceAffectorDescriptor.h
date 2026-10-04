#ifndef LINEARFORCEAFFECTORDESCRIPTOR_H
#define LINEARFORCEAFFECTORDESCRIPTOR_H

#include "ForceAffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CLinearForceAffectorDescriptor : public CForceAffectorDescriptor
{
public:
    virtual ~CLinearForceAffectorDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CLinearForceAffectorDescriptor();

};

#endif
