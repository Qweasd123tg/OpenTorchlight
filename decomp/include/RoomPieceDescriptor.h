#ifndef ROOMPIECEDESCRIPTOR_H
#define ROOMPIECEDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "RoomPiece.h"

class CRoomPieceDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CRoomPieceDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual bool DescriptorObjectBeingDeleted(CEditorBaseObject*);
    virtual void DescriptorObjectHasBeenInited(CEditorBaseObject*);
    CRoomPieceDescriptor();


    static void Set_setCollisionEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRoomPiece*>(object)->setCollisionEnabled(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getCollisionEnabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CRoomPiece*>(object)->getCollisionEnabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setIsBakeable(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getIsBakeable(CEditorBaseObject* object, unsigned int& count);
    static void Set_setVisibleOnMap(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRoomPiece*>(object)->setVisibleOnMap(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getVisibleOnMap(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CRoomPiece*>(object)->getVisibleOnMap();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setRoomPieceGuidByString(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRoomPieceGuidAsString(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRoomPieceName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRoomPieceName(CEditorBaseObject* object, unsigned int& count);
    static void Set_setVisualIndex(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getVisualIndex(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CRoomPiece*>(object)->getVisualIndex();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static unsigned int GetRoomPieceVisualIndexIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetRoomPieceVisualIndexStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setScale(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRoomPiece*>(object)->setScale(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getScaleFloat(CEditorBaseObject* object, unsigned int& count);
    static void Set_setScaleX(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRoomPiece*>(object)->setScaleX(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getScaleX(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CRoomPiece*>(object)->getScaleX();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setScaleY(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRoomPiece*>(object)->setScaleY(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getScaleY(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CRoomPiece*>(object)->getScaleY();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setScaleZ(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRoomPiece*>(object)->setScaleZ(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getScaleZ(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CRoomPiece*>(object)->getScaleZ();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
};

#endif
