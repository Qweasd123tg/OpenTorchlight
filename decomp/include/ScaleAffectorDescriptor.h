#ifndef SCALEAFFECTORDESCRIPTOR_H
#define SCALEAFFECTORDESCRIPTOR_H

#include "AffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CScaleAffectorDescriptor : public CAffectorDescriptor
{
public:
    virtual ~CScaleAffectorDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CScaleAffectorDescriptor();


    static void Set_setUnifiedScale(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUnifiedScale(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynamicPropXScale(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynamicPropXScale(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynamicPropYScale(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynamicPropYScale(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDynamicPropZScale(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDynamicPropZScale(CEditorBaseObject* object, unsigned int& count);
};

#endif
