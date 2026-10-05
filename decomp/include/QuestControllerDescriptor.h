#ifndef QUESTCONTROLLERDESCRIPTOR_H
#define QUESTCONTROLLERDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "QuestController.h"

class CQuestControllerDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CQuestControllerDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CQuestControllerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setPlayerGetsDisabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CQuestController*>(object)->setPlayerGetsDisabled(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getPlayerGetsDisabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CQuestController*>(object)->getPlayerGetsDisabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setBroadcastEventsOnLoad(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CQuestController*>(object)->setBroadcastEventsOnLoad(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getBroadcastEventsOnLoad(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CQuestController*>(object)->getBroadcastEventsOnLoad();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setCategory(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CQuestController*>(object)->setCategory((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getCategory(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetGroupIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetGroupStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setUnitInteractWith(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUnitInteractWith(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetResourceIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetResourceStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setQuest(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CQuestController*>(object)->setQuest((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getQuest(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getQuestIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getQuestStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
};

#endif
