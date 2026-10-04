#ifndef SINEFORCEAFFECTORDESCRIPTOR_H
#define SINEFORCEAFFECTORDESCRIPTOR_H

#include "ForceAffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CSineForceAffectorDescriptor : public CForceAffectorDescriptor
{
public:
    virtual ~CSineForceAffectorDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CSineForceAffectorDescriptor();


    static void Set_setFrequencyMin(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getFrequencyMin(CEditorBaseObject* object, unsigned int& count);
    static void Set_setFrequencyMax(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getFrequencyMax(CEditorBaseObject* object, unsigned int& count);
};

#endif
