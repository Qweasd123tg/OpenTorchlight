#ifndef ANIMATIONPLAYERDESCRIPTOR_H
#define ANIMATIONPLAYERDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "AnimationPlayer.h"

class CAnimationPlayerDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CAnimationPlayerDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CAnimationPlayerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setStartOnLoad(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CAnimationPlayer*>(object)->setStartOnLoad(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getStartOnLoad(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CAnimationPlayer*>(object)->getStartOnLoad();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setBlendTime(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CAnimationPlayer*>(object)->setBlendTime(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getBlendTime(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CAnimationPlayer*>(object)->getBlendTime();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setBlendOutTime(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CAnimationPlayer*>(object)->setBlendOutTime(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getBlendOutTime(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CAnimationPlayer*>(object)->getBlendOutTime();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setForceDuration(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CAnimationPlayer*>(object)->setForceDuration(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getForceDuration(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CAnimationPlayer*>(object)->getForceDuration();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setPlayIdle(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CAnimationPlayer*>(object)->setPlayIdle(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getPlayIdle(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CAnimationPlayer*>(object)->getPlayIdle();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setAnimationName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CAnimationPlayer*>(object)->setAnimationName((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getAnimationName(CEditorBaseObject* object, unsigned int& count);
    static void Set_setCategory(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CAnimationPlayer*>(object)->setCategory((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getCategory(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        {
            const std::wstring& value = static_cast<CAnimationPlayer*>(object)->getCategory();
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
    static unsigned int GetGroupIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetGroupStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setUnitString(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CAnimationPlayer*>(object)->setUnitString((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getUnitString(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetResourceIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetResourceStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
};

#endif
