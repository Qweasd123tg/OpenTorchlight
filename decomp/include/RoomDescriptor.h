#ifndef ROOMDESCRIPTOR_H
#define ROOMDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "DataGroup.h"
#include "DescriptorSaveConfiguration.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CRoomDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CRoomDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void saveObject(CEditorBaseObject*, CDataGroup*, CDescriptorSaveConfiguration*);
    CRoomDescriptor();


    static void Set_setSceneOverrideFile(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSceneOverrideFile(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMeshFileCreatedDynamically(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMeshFileCreatedDynamically(CEditorBaseObject* object, unsigned int& count);
};

#endif
