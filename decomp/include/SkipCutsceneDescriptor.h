#ifndef SKIPCUTSCENEDESCRIPTOR_H
#define SKIPCUTSCENEDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "SkipCutscene.h"

class CSkipCutsceneDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CSkipCutsceneDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CSkipCutsceneDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CSkipCutscene*>(object)->setEnabled(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CSkipCutscene*>(object)->getEnabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setSkillsDisabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CSkipCutscene*>(object)->setSkillsDisabled(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getSkillsDisabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CSkipCutscene*>(object)->getSkillsDisabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
};

#endif
