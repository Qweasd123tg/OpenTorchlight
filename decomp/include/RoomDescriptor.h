#ifndef ROOMDESCRIPTOR_H
#define ROOMDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "DataGroup.h"
#include "DescriptorSaveConfiguration.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "Room.h"

class CRoomDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CRoomDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void saveObject(CEditorBaseObject*, CDataGroup*, CDescriptorSaveConfiguration*);
    CRoomDescriptor();


    static void Set_setSceneOverrideFile(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRoom*>(object)->setSceneOverrideFile((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getSceneOverrideFile(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        {
            const std::wstring& value = static_cast<CRoom*>(object)->getSceneOverrideFile();
            unsigned int length = value.length();
            unsigned int size = 0;
            if (length < 1000000)
            {
                size = length * sizeof(wchar_t);
                memcpy(sEditorTmpMemory, value.c_str(), size);
                *(wchar_t*)&sEditorTmpMemory[size] = 0;
            }
            count = size;
        }
        return (UNIONDATA8BIT*)sEditorTmpMemory;
    }
    static void Set_setMeshFileCreatedDynamically(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRoom*>(object)->setMeshFileCreatedDynamically((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getMeshFileCreatedDynamically(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        {
            const std::wstring& value = static_cast<CRoom*>(object)->getMeshFileCreatedDynamically();
            unsigned int length = value.length();
            unsigned int size = 0;
            if (length < 1000000)
            {
                size = length * sizeof(wchar_t);
                memcpy(sEditorTmpMemory, value.c_str(), size);
                *(wchar_t*)&sEditorTmpMemory[size] = 0;
            }
            count = size;
        }
        return (UNIONDATA8BIT*)sEditorTmpMemory;
    }
};

#endif
