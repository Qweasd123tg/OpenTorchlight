#ifndef JETAFFECTORDESCRIPTOR_H
#define JETAFFECTORDESCRIPTOR_H

#include "AffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CJetAffectorDescriptor : public CAffectorDescriptor
{
public:
    virtual ~CJetAffectorDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CJetAffectorDescriptor();


    static void Set_setDynamicPropAcceleration(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynamicPropAcceleration(CEditorBaseObject* object, unsigned int& count);
};

#endif
