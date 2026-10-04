#ifndef ITEMDESCRIPTOR_H
#define ITEMDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CItemDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CItemDescriptor();
    virtual void deleteNotification();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual bool DescriptorObjectBeingDeleted(CEditorBaseObject*);
    virtual void descriptorSceneActivated(CEditorScene*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CItemDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
    static void Set_createNewEquipment(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getUnitDataName(CEditorBaseObject* object, unsigned int& count);
    static unsigned int getItemIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring getItemStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
};

#endif
