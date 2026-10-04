#ifndef MUSICOBJECTDESCRIPTOR_H
#define MUSICOBJECTDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "MusicObject.h"

class CMusicObjectDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CMusicObjectDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CMusicObjectDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setMusicFile(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMusicFile(CEditorBaseObject* object, unsigned int& count);
    static void Set_setLoops(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CMusicObject*>(object)->setLoops(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getLoops(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CMusicObject*>(object)->getLoops();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
};

#endif
