#ifndef PROPERTYNODEDESCRIPTOR_H
#define PROPERTYNODEDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "PropertyNode.h"

class CPropertyNodeDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CPropertyNodeDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CPropertyNodeDescriptor();


    static void Set_setPropertyNodeType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CPropertyNode*>(object)->setPropertyNodeType(((const UNIONDATA32BIT*)data)->m_uValue);
    }
    static UNIONDATA8BIT* Get_getPropertyNodeType(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(unsigned int);
        gUnionOf32BitData[0].m_uValue = static_cast<CPropertyNode*>(object)->getPropertyNodeType();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static unsigned int getPropertyNodeTypeByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getPropertyNodeTypeString(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
    static void Set_setRadius(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CPropertyNode*>(object)->setScaleX(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getRadius(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CPropertyNode*>(object)->getScaleX();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setScaleX(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CPropertyNode*>(object)->setScaleX(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getScaleX(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CPropertyNode*>(object)->getScaleX();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setScaleZ(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CPropertyNode*>(object)->setScaleZ(((const UNIONDATA32BIT*)data)->m_fValue);
    }
    static UNIONDATA8BIT* Get_getScaleZ(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CPropertyNode*>(object)->getScaleZ();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CPropertyNode*>(object)->setEnabled(data->m_bValue);
    }
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(bool);
        gUnionOf32BitData[0].m_bValue = static_cast<CPropertyNode*>(object)->getEnabled();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
};

#endif
