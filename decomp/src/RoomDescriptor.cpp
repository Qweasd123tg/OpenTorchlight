#include "EmptyStrings.h"
#include "RoomDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "Room.h"
#include "DescriptorSaveConfiguration.h"
#include <OgreLogManager.h>

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

void CRoomDescriptor::saveObject(CEditorBaseObject* object, CDataGroup* group, CDescriptorSaveConfiguration* configuration)
{
    CRoom* room = dynamic_cast<CRoom*>(object);
    if (!room)
        return;
    TArrayList<CEditorBaseObject*>* pieces = getSceneOwner()->GetObjectsCreatedByADescriptor(L"Room Piece");
    if (pieces && pieces->size() == 0) {
        if (room->getSceneOverrideFile().empty())
            Ogre::LogManager::getSingleton().logMessage("You are saving a room piece without specifying a scene override or actually creating the room dynamically by using room pieces.\n\n This is just a warning.", Ogre::LML_CRITICAL, false);
        CDescriptor::saveObject(object, group, configuration);
    } else {
        std::wstring filename(configuration->m_sFileName, 0, configuration->m_sFileName.find_first_of(L"."));
        filename += L"mesh";
        room->setMeshFileCreatedDynamically(filename);
        CDescriptor::saveObject(object, group, configuration);
    }
}
