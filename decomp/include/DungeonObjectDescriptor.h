#ifndef DUNGEONOBJECTDESCRIPTOR_H
#define DUNGEONOBJECTDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CDungeonObjectDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CDungeonObjectDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CDungeonObjectDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setDungeon(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDungeon(CEditorBaseObject* object, unsigned int& count);
};

#endif
