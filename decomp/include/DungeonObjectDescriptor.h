#ifndef DUNGEONOBJECTDESCRIPTOR_H
#define DUNGEONOBJECTDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "DungeonObject.h"

class CDungeonObjectDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CDungeonObjectDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CDungeonObjectDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setDungeon(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CDungeonObject*>(object)->setDungeon((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getDungeon(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        {
            const std::wstring& value = static_cast<CDungeonObject*>(object)->getDungeon();
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
