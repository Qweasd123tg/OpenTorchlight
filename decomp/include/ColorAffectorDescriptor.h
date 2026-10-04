#ifndef COLORAFFECTORDESCRIPTOR_H
#define COLORAFFECTORDESCRIPTOR_H

#include "AffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CColorAffectorDescriptor : public CAffectorDescriptor
{
public:
    virtual ~CColorAffectorDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CColorAffectorDescriptor();


    static void Set_setColors(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getColors(CEditorBaseObject* object, unsigned int& count);
};

#endif
