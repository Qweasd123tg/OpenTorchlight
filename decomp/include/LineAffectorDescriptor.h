#ifndef LINEAFFECTORDESCRIPTOR_H
#define LINEAFFECTORDESCRIPTOR_H

#include "AffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CLineAffectorDescriptor : public CAffectorDescriptor
{
public:
    virtual ~CLineAffectorDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CLineAffectorDescriptor();


    static void Set_setMaxDeviation(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMaxDeviation(CEditorBaseObject* object, unsigned int& count);
    static void Set_setTimeStep(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getTimeStep(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDrift(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDrift(CEditorBaseObject* object, unsigned int& count);
    static void Set_setEnd(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnd(CEditorBaseObject* object, unsigned int& count);
};

#endif
