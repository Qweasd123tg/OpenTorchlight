#ifndef CAMERASHAKEDESCRIPTOR_H
#define CAMERASHAKEDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CCameraShakeDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CCameraShakeDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CCameraShakeDescriptor();


    static void Set_setDirection(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDirection(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDuration(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDuration(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMagnitudeMult(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMagnitudeMult(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDirectionOrientation(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDirectionOrientation(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getCameraShakeOrientationByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getCameraShakeOrientationStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setCameraShakeName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCameraShakeName(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getCameraShakeNameByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getCameraShakeNameStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setCameraFallsOffWithDistance(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCameraFallsOffWithDistance(CEditorBaseObject* object, unsigned int& count);
};

#endif
