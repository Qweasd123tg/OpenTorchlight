#ifndef PATHCONTROLLERDESCRIPTOR_H
#define PATHCONTROLLERDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CPathControllerDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CPathControllerDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void DescriptorObjectCreatedInEditor(CEditorBaseObject*);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CPathControllerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setArrayOfVectors(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getArrayOfVectors(CEditorBaseObject* object, unsigned int& count);
    static void Set_setNumberOfPathPoints(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getNumberOfPathPoints(CEditorBaseObject* object, unsigned int& count);
    static void Set_setVisible(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getVisible(CEditorBaseObject* object, unsigned int& count);
    static void Set_setEnableUnitOnStart(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnableUnitOnStart(CEditorBaseObject* object, unsigned int& count);
    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
    static void Set_setPathName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getPathName(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUnitRunsOnPath(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUnitRunsOnPath(CEditorBaseObject* object, unsigned int& count);
    static void Set_setWalkToPlayer(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getWalkToPlayer(CEditorBaseObject* object, unsigned int& count);
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
