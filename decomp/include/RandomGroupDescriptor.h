#ifndef RANDOMGROUPDESCRIPTOR_H
#define RANDOMGROUPDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "RandomGroup.h"

class CRandomGroupDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CRandomGroupDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneLoaded(CEditorScene*);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CRandomGroupDescriptor();

    long long m_Unknown170;
    long long m_Unknown178;
    void* m_pUnknown180;
    void* m_pUnknown188;
    int m_iUnknown190;

    static void Set_setVisible(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRandomGroup*>(object)->setVisible(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getVisible(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CRandomGroup*>(object)->getVisible();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setIsDynamicGroup(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRandomGroup*>(object)->setIsDynamicGroup(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getIsDynamicGroup(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CRandomGroup*>(object)->getIsDynamicGroup();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_SetRandomWeight(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRandomGroup*>(object)->SetRandomWeight(((const UNIONDATA32BIT*)data)->m_uValue);
    }
    static UNIONDATA8BIT* Get_GetRandomWeight(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(unsigned int);
        gUnionOf32BitData[0].m_uValue = static_cast<CRandomGroup*>(object)->GetRandomWeight();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_SetNumberOfPicks(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRandomGroup*>(object)->SetNumberOfPicks(((const UNIONDATA32BIT*)data)->m_iValue);
    }
    static UNIONDATA8BIT* Get_GetNumberOfPicks(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CRandomGroup*>(object)->GetNumberOfPicks();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_SetRandomType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRandomGroup*>(object)->SetRandomType(((const UNIONDATA32BIT*)data)->m_uValue);
    }
    static UNIONDATA8BIT* Get_GetRandomType(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(unsigned int);
        gUnionOf32BitData[0].m_uValue = static_cast<CRandomGroup*>(object)->GetRandomType();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static unsigned int GetRandomGroupTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetRandomGroupTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setDifficulty(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CRandomGroup*>(object)->setDifficulty(((const UNIONDATA32BIT*)data)->m_iValue);
    }
    static UNIONDATA8BIT* Get_getDifficulty(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CRandomGroup*>(object)->getDifficulty();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static unsigned int getDifficultyIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring setDifficultyStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setDungeonForGroup(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDungeonForGroup(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getDungeonIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getDungeonStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setPlayerClassName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getPlayerClassName(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getPlayerClassIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getPlayerClassStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setQuestHasToBeActiveOrComplete(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getQuestHasToBeActiveOrComplete(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getQuestIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getQuestStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setQuestHasToBeComplete(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getQuestHasToBeComplete(CEditorBaseObject* object, unsigned int& count);
    static void Set_setQuestNotComplete(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getQuestNotComplete(CEditorBaseObject* object, unsigned int& count);
    static void Set_setQuestHasToBeActive(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getQuestHasToBeActive(CEditorBaseObject* object, unsigned int& count);
    static void Set_setQuestCannotBeActiveOrComplete(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getQuestCannotBeActiveOrComplete(CEditorBaseObject* object, unsigned int& count);
};

#endif
