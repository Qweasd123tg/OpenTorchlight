#ifndef PLANECOLLIDERDESCRIPTOR_H
#define PLANECOLLIDERDESCRIPTOR_H

#include "ColliderDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CPlaneColliderDescriptor : public CColliderDescriptor
{
public:
    virtual ~CPlaneColliderDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CPlaneColliderDescriptor();


    static void Set_setNormal(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getNormal(CEditorBaseObject* object, unsigned int& count);
    static void Set_setShowPlane(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getShowPlane(CEditorBaseObject* object, unsigned int& count);
};

#endif
