#ifndef PATHCONTROLLERDESCRIPTOR_H
#define PATHCONTROLLERDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "PathController.h"

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
    static void Set_setNumberOfPathPoints(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CPathController*>(object)->setNumberOfPathPoints(((const UNIONDATA32BIT*)data)->m_uValue);
    }
    static UNIONDATA8BIT* Get_getNumberOfPathPoints(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CPathController*>(object)->getNumberOfPathPoints();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setVisible(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CPathController*>(object)->setVisible(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getVisible(CEditorBaseObject* object, unsigned int& count);
    static void Set_setEnableUnitOnStart(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CPathController*>(object)->setEnableUnitOnStart(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getEnableUnitOnStart(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CPathController*>(object)->getEnableUnitOnStart();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CPathController*>(object)->setEnabled(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CPathController*>(object)->getEnabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setPathName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getPathName(CEditorBaseObject* object, unsigned int& count);
    static void Set_setUnitRunsOnPath(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CPathController*>(object)->setUnitRunsOnPath(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getUnitRunsOnPath(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CPathController*>(object)->getUnitRunsOnPath();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setWalkToPlayer(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CPathController*>(object)->setWalkToPlayer(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getWalkToPlayer(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CPathController*>(object)->getWalkToPlayer();
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
};

#endif
