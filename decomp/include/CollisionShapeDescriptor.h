#ifndef COLLISIONSHAPEDESCRIPTOR_H
#define COLLISIONSHAPEDESCRIPTOR_H

#include "ShapeDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "CollisionShape.h"

class CCollisionShapeDescriptor : public CShapeDescriptor
{
public:
    virtual ~CCollisionShapeDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CCollisionShapeDescriptor();


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CCollisionShape*>(object)->setEnabled(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CCollisionShape*>(object)->getEnabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
};

#endif
