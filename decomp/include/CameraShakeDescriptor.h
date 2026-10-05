#ifndef CAMERASHAKEDESCRIPTOR_H
#define CAMERASHAKEDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "CameraShake.h"

class CCameraShakeDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CCameraShakeDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CCameraShakeDescriptor();


    static void Set_setDirection(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDirection(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDuration(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CCameraShake*>(object)->setDuration(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getDuration(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CCameraShake*>(object)->getDuration();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setMagnitudeMult(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CCameraShake*>(object)->setMagnitudeMult(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getMagnitudeMult(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CCameraShake*>(object)->getMagnitudeMult();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setDirectionOrientation(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDirectionOrientation(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getCameraShakeOrientationByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getCameraShakeOrientationStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setCameraShakeName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CCameraShake*>(object)->setCameraShakeName((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getCameraShakeName(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getCameraShakeNameByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getCameraShakeNameStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setCameraFallsOffWithDistance(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CCameraShake*>(object)->setCameraFallsOffWithDistance(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getCameraFallsOffWithDistance(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CCameraShake*>(object)->getCameraFallsOffWithDistance();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
};

#endif
