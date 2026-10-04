#include "EmptyStrings.h"
#include "RoomPieceDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "RoomPiece.h"

CRoomPieceDescriptor::CRoomPieceDescriptor()
    : CPositionableObjectDescriptor(L"Room Piece", L"Room piece for building rooms", L"piece", true, true, true, true, true)
{
    m_iFlags &= ~(DESCRIPTOR_FLAG_CHILDREN | DESCRIPTOR_FLAG_4000);
    AddProperty(L"PROPERTIES", L"COLLISION ENABLED", L"If set to false the piece will not have collision", (void*)Set_setCollisionEnabled, (void*)Get_getCollisionEnabled, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"BAKE", L"If true the level piece will be baked and destroyed on the level load. If it's bakeable it can't move dynamically.", (void*)Set_setIsBakeable, (void*)Get_getIsBakeable, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"VISIBLE ON MAP", L"If true the level piece will be visible on the ingame map.", (void*)Set_setVisibleOnMap, (void*)Get_getVisibleOnMap, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"GUID", L"GUID", L"GUID", (void*)Set_setRoomPieceGuidByString, (void*)Get_getRoomPieceGuidAsString, VARIABLE_TYPE_STRING, 1);
    AddProperty(L"ROOM PIECE", L"PIECE", L"This is the room piece selected.", (void*)Set_setRoomPieceName, (void*)Get_getRoomPieceName, VARIABLE_TYPE_STRING, 257);
    AddPropertyWithInterpreterFunctions(L"VISUAL PIECE INDEX", L"VISUAL", L"Room Pieces can have multiple types of visual pieces. Selecting random will choose a random piece from the set.", (void*)Set_setVisualIndex, (void*)Get_getVisualIndex, GetRoomPieceVisualIndexIDByString, GetRoomPieceVisualIndexStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 16388);
    AddProperty(L"SCALE", L"SCALE", L"Scale the piece (if set to be scalable)", (void*)Set_setScale, (void*)Get_getScaleFloat, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SCALE", L"X", L"Scale the piece (if set to be scalable)", (void*)Set_setScaleX, (void*)Get_getScaleX, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SCALE", L"Y", L"Scale the piece (if set to be scalable)", (void*)Set_setScaleY, (void*)Get_getScaleY, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SCALE", L"Z", L"Scale the piece (if set to be scalable)", (void*)Set_setScaleZ, (void*)Get_getScaleZ, VARIABLE_TYPE_FLOAT, 0);
}

CRoomPieceDescriptor::~CRoomPieceDescriptor()
{
}

bool CRoomPieceDescriptor::DescriptorObjectBeingDeleted(CEditorBaseObject* object)
{
    return true;
}

CEditorBaseObject* CRoomPieceDescriptor::CreateObject(CEditorScene* scene)
{
    return new CRoomPiece(scene->getResourceManager());
}
