#ifndef SHAPEDESCRIPTOR_H
#define SHAPEDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CShapeDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CShapeDescriptor();
    CShapeDescriptor* GetSpawnOrderStringByID(CEditorScene*, CEditorBaseObject*, unsigned int, void*);
    int GetSpawnOrderIDByString(CEditorScene*, CEditorBaseObject*, const std::wstring&, void*);
    CShapeDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description, bool option1, bool option2, bool option3);


    static void Set_setShape(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getShape(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetSpawnShapeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetSpawnShapeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setShapeDirection(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getShapeDirection(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetSpawnDirectionIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetSpawnDirectionStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setBoxSize(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getBoxSize(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUseMaxRadiusOnly(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUseMaxRadiusOnly(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMinRadius(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMinRadius(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMaxRadius(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMaxRadius(CEditorBaseObject* object, unsigned int& count);
    static void Set_setAngleOfRelease(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAngleOfRelease(CEditorBaseObject* object, unsigned int& count);
    static void Set_setAngleOffset(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAngleOffset(CEditorBaseObject* object, unsigned int& count);
};

#endif
