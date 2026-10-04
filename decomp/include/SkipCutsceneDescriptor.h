#ifndef SKIPCUTSCENEDESCRIPTOR_H
#define SKIPCUTSCENEDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CSkipCutsceneDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CSkipCutsceneDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CSkipCutsceneDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
    static void Set_setSkillsDisabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSkillsDisabled(CEditorBaseObject* object, unsigned int& count);
};

#endif
