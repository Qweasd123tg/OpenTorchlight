#ifndef CAMERACONTROLLERDESCRIPTOR_H
#define CAMERACONTROLLERDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "CameraController.h"

class CCameraControllerDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CCameraControllerDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CCameraControllerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setCameraPanTime(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CCameraController*>(object)->setCameraPanTime(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getCameraPanTime(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CCameraController*>(object)->getCameraPanTime();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setCameraEaseInDistancePCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCameraEaseInDistancePCT(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CCameraController*>(object)->getCameraEaseInDistancePCT();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setCameraEaseInPCT(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCameraEaseInPCT(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CCameraController*>(object)->getCameraEaseInPCT();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setCameraPauseTimer(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CCameraController*>(object)->setCameraPauseTimer(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getCameraPauseTimer(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CCameraController*>(object)->getCameraPauseTimer();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setRestoreCameraStateAfterMoving(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CCameraController*>(object)->setRestoreCameraStateAfterMoving(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getRestoreCameraStateAfterMoving(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CCameraController*>(object)->getRestoreCameraStateAfterMoving();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setFollowUnit(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CCameraController*>(object)->setFollowUnit(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getFollowUnit(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CCameraController*>(object)->getFollowUnit();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setCameraType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CCameraController*>(object)->setCameraType(((const UNIONDATA32BIT*)data)->m_iValue);
    }
    static UNIONDATA8BIT* Get_getCameraType(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CCameraController*>(object)->getCameraType();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static unsigned int getTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setCategory(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCategory(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetGroupIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetGroupStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setUnitInteractWith(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUnitInteractWith(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetResourceIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetResourceStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
};

#endif
