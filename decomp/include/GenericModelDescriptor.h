#ifndef GENERICMODELDESCRIPTOR_H
#define GENERICMODELDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "GenericModel.h"

class CGenericModelDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CGenericModelDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void DescriptorObjectHasBeenInited(CEditorBaseObject*);
    CGenericModelDescriptor();

    unsigned char m_gap170[0x70] __attribute__((aligned(8)));
    void* m_pUnknown1E0;
    unsigned char m_gap1E8[0x51];
    bool m_bUnknown239;
    unsigned char m_gap23A[0x2];
    bool m_bUnknown23C;
    unsigned char m_gap23D[0x3];
    float m_fUnknown240;
    int m_iUnknown244;

    static void Set_loadModel(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getModelPath(CEditorBaseObject* object, unsigned int& count);
    static void Set_setScaleX(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CGenericModel*>(object)->setScaleX(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getScaleX(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CGenericModel*>(object)->getScaleX();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setScaleY(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CGenericModel*>(object)->setScaleY(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getScaleY(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CGenericModel*>(object)->getScaleY();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setScaleZ(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CGenericModel*>(object)->setScaleZ(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getScaleZ(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CGenericModel*>(object)->getScaleZ();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setAnimationSpeed(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAnimationSpeed(CEditorBaseObject* object, unsigned int& count);
    static void Set_setAnimationLoop(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAnimationLoop(CEditorBaseObject* object, unsigned int& count);
    static void Set_setAnimationPlaying(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAnimationPlaying(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetAnimationIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetAnimationStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setRenderToLightMap(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRenderToLightMap(CEditorBaseObject* object, unsigned int& count);
    static void Set_setTextureOverride(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CGenericModel*>(object)->setTextureOverride((const wchar_t*)data);
    }
    static UNIONDATA8BIT* Get_getTextureOverridePath(CEditorBaseObject* object, unsigned int& count);
    static void Set_setPolyCount(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getPolyCount(CEditorBaseObject* object, unsigned int& count);
};

#endif
