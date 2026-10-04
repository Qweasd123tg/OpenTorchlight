#ifndef PUZZLERANDOMIZERDESCRIPTOR_H
#define PUZZLERANDOMIZERDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "PuzzleRandomizer.h"

class CPuzzleRandomizerDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CPuzzleRandomizerDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CPuzzleRandomizerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CPuzzleRandomizer*>(object)->setEnabled(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CPuzzleRandomizer*>(object)->getEnabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setActiveInputs(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CPuzzleRandomizer*>(object)->setActiveInputs(((const UNIONDATA32BIT*)data)->m_uValue);
    }
    static UNIONDATA8BIT* Get_getActiveInputs(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CPuzzleRandomizer*>(object)->getActiveInputs();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
};

#endif
