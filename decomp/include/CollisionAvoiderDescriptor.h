#ifndef COLLISIONAVOIDERDESCRIPTOR_H
#define COLLISIONAVOIDERDESCRIPTOR_H

#include "ColliderDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CCollisionAvoiderDescriptor : public CColliderDescriptor
{
public:
    virtual ~CCollisionAvoiderDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CCollisionAvoiderDescriptor();


    static void Set_setRadius(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRadius(CEditorBaseObject* object, unsigned int& count);
    static void Set_setShowSphere(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getShowSphere(CEditorBaseObject* object, unsigned int& count);
};

#endif
