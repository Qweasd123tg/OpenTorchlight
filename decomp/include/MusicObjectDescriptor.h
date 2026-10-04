#ifndef MUSICOBJECTDESCRIPTOR_H
#define MUSICOBJECTDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

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
    static void Set_setLoops(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getLoops(CEditorBaseObject* object, unsigned int& count);
};

#endif
