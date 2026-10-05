#ifndef LIGHTDESCRIPTOR_H
#define LIGHTDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "Light.h"

class CLightDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CLightDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    CLightDescriptor* GetLightStringByID(CEditorScene*, CEditorBaseObject*, unsigned int, void*);
    int GetLightIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring&, void*);
    CLightDescriptor();


    static void Set_setBitmapFile(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CLight*>(object)->setBitmapFile((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getBitmapFile(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetFileIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetFileStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setLightDensity(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getLightDensity(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CLight*>(object)->getLightDensity();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setScaleX(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CLight*>(object)->setScaleX(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getScaleX(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CLight*>(object)->getScaleX();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setScaleZ(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CLight*>(object)->setScaleZ(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getScaleZ(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CLight*>(object)->getScaleZ();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setRotation(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CLight*>(object)->setRotation(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getRotation(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CLight*>(object)->getRotation();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
};

#endif
