#ifndef COLLISIONSHAPEDESCRIPTOR_H
#define COLLISIONSHAPEDESCRIPTOR_H

#include "ShapeDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CCollisionShapeDescriptor : public CShapeDescriptor
{
public:
    virtual ~CCollisionShapeDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CCollisionShapeDescriptor();


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
};

#endif
