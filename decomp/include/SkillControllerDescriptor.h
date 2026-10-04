#ifndef SKILLCONTROLLERDESCRIPTOR_H
#define SKILLCONTROLLERDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "SkillController.h"

class CSkillControllerDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CSkillControllerDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CSkillControllerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setSkillLearnOnStart(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CSkillController*>(object)->setSkillLearnOnStart(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getSkillLearnOnStart(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CSkillController*>(object)->getSkillLearnOnStart();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setSkillUnlearnOnStop(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CSkillController*>(object)->setSkillUnlearnOnStop(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getSkillUnlearnOnStop(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CSkillController*>(object)->getSkillUnlearnOnStop();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setForceStop(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CSkillController*>(object)->setForceStop(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getForceStop(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CSkillController*>(object)->getForceStop();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setPlayerAsTarget(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CSkillController*>(object)->setPlayerAsTarget(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getPlayerAsTarget(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CSkillController*>(object)->getPlayerAsTarget();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setUseUnitTarget(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CSkillController*>(object)->setUseUnitTarget(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getUseUnitTarget(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CSkillController*>(object)->getUseUnitTarget();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setLevelOfSkill(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CSkillController*>(object)->setLevelOfSkill(((const UNIONDATA32BIT*)data)->m_iValue);
    }
    static UNIONDATA8BIT* Get_getLevelOfSkill(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CSkillController*>(object)->getLevelOfSkill();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setCategory(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCategory(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetGroupIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetGroupStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setUnitInteractWith(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUnitInteractWith(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetResourceIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetResourceStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setSkillName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSkillName(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getSkillIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getSkillStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
};

#endif
