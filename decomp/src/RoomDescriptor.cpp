#include "EmptyStrings.h"
#include "RoomDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "Room.h"

CRoomDescriptor::CRoomDescriptor()
    : CBaseObjectDescriptor(L"Room", L"A definition of the room", L"house")
{
    AddInputLogic(INPUT_EVENT_RESET);
    AddOutputLogic(OUTPUT_EVENT_INITIALIZED);
    AddOutputLogic(OUTPUT_EVENT_RESET);
    AddProperty(L"SCENE OVERRIDE", L"SCENE FILE", L"A scene file to use instead of creating the file dynamicly.", (void*)Set_setSceneOverrideFile, (void*)Get_getSceneOverrideFile, VARIABLE_TYPE_STRING, 2);
    AddProperty(L"NOT VISIBLE", L"MESH FILE", L"Mesh file created dynamicly.", (void*)Set_setMeshFileCreatedDynamically, (void*)Get_getMeshFileCreatedDynamically, VARIABLE_TYPE_STRING, 128);
}

CRoomDescriptor::~CRoomDescriptor()
{
}

CEditorBaseObject* CRoomDescriptor::CreateObject(CEditorScene* scene)
{
    return new CRoom(scene->getResourceManager());
}
