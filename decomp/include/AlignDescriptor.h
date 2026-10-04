#ifndef ALIGNDESCRIPTOR_H
#define ALIGNDESCRIPTOR_H

#include "AffectorDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CAlignDescriptor : public CAffectorDescriptor
{
public:
    virtual ~CAlignDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CAlignDescriptor();


    static void Set_setAlignByVelocity(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAlignByVelocity(CEditorBaseObject* object, unsigned int& count);
    static void Set_setAllowStretch(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAllowStretch(CEditorBaseObject* object, unsigned int& count);
};

#endif
