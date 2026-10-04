#ifndef LIGHTDESCRIPTOR_H
#define LIGHTDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CLightDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CLightDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    CLightDescriptor* GetLightStringByID(CEditorScene*, CEditorBaseObject*, unsigned int, void*);
    int GetLightIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring&, void*);
    CLightDescriptor();


    static void Set_setBitmapFile(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getBitmapFile(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetFileIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetFileStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setLightDensity(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getLightDensity(CEditorBaseObject* object, unsigned int& count);
    static void Set_setScaleX(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getScaleX(CEditorBaseObject* object, unsigned int& count);
    static void Set_setScaleZ(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getScaleZ(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRotation(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRotation(CEditorBaseObject* object, unsigned int& count);
};

#endif
