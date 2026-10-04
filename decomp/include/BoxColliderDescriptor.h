#ifndef BOXCOLLIDERDESCRIPTOR_H
#define BOXCOLLIDERDESCRIPTOR_H

#include "ColliderDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CBoxColliderDescriptor : public CColliderDescriptor
{
public:
    virtual ~CBoxColliderDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CBoxColliderDescriptor();


    static void Set_setWidth(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWidth(CEditorBaseObject* object, unsigned int& count);
    static void Set_setHeight(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getHeight(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDepth(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDepth(CEditorBaseObject* object, unsigned int& count);
    static void Set_setShowBox(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getShowBox(CEditorBaseObject* object, unsigned int& count);
};

#endif
