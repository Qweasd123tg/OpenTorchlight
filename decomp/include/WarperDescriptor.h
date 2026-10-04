#ifndef WARPERDESCRIPTOR_H
#define WARPERDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CWarperDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CWarperDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CWarperDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
    static void Set_setLevelDelta(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getLevelDelta(CEditorBaseObject* object, unsigned int& count);
    static void Set_setLevelDepth(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getLevelDepth(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDungeon(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDungeon(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWarpName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWarpName(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWaypoint(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWaypoint(CEditorBaseObject* object, unsigned int& count);
};

#endif
