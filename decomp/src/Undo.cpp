#include "Descriptor.h"
#include "Editor.h"
#include "EditorScene.h"
#include "EditorObjectManager.h"
#include "PositionableObject.h"
#include <cstring>
#include "EmptyStrings.h"
#include "Undo.h"
#include "EditorBaseObject.h"
#include "RunicCore.h"
#include "GameVariables.h"

CUndo::CUndo()
    : CRunicCore(), m_undoData(10)
{
}

CUndo::CUndo(CEditorBaseObject* pObject, unsigned int uiProperty)
    : CRunicCore(), m_undoData(10)
{
    AddUndoProperty(pObject, uiProperty);
}


CUndo::CUndoData::~CUndoData()
{
    if (m_data) {
        Ogre::NedAllocImpl::deallocBytes(m_data);
        m_data = NULL;
    }
    m_object = NULL;
}

CUndo::~CUndo()
{
    m_undoData.deleteAll();
}

void CUndo::resetPropertiesOnObject(CUndo* pUndo)
{
    for (unsigned int i = 0; i < m_undoData.size(); ++i) {
        switch (m_undoData[i]->m_action) {
        case 0:
            DoUndoOnProperty(m_undoData[i], pUndo);
            break;
        case 1:
            DoUndoUndelete(m_undoData[i], pUndo);
            break;
        case 2:
            DoUndoCreate(m_undoData[i], pUndo);
            break;
        }
    }
}

void CUndo::AddUndoProperty(CEditorBaseObject* object, unsigned int property)
{
    if (!object || !object->getSceneOwner() || property == ~0u || !object->getDescriptor()) return;
    CDescriptorProp* descriptorProperty = object->getDescriptor()->GetProperty(property);
    if (!descriptorProperty) return;
    CUndoData* data = new CUndoData;
    data->m_objectGuid = -1;
    data->m_property = property;
    data->m_object = NULL;
    data->m_data = NULL;
    data->m_count = 0;
    data->m_action = 0;
    data->m_objectGuid = object->getGuid();
    data->m_parentGuid = object->getParentGuid();
    data->m_sceneID = gEditor->GetEditorSceneIDByName(object->getSceneOwner()->getName().c_str());
    UNIONDATA32BIT* value = descriptorProperty->getData(data->m_count, object);
    data->m_data = static_cast<UNIONDATA32BIT*>(Ogre::NedAllocImpl::allocBytes(static_cast<size_t>(data->m_count)*4, NULL, 0, NULL));
    std::memcpy(data->m_data, value, data->m_count * 4);
    m_undoData.add(data);
}
void CUndo::AddUndoProperty(CEditorBaseObject* object, const wchar_t* propertyName)
{
    if (!object || !object->getSceneOwner() || !object->getDescriptor()) return;
    unsigned int property = object->getDescriptor()->GetPropertyID(std::wstring(propertyName));
    AddUndoProperty(object, property);
}
void CUndo::AddNewObject(CEditorBaseObject* object)
{
    if (!object || !object->getSceneOwner() || !object->getDescriptor()) return;
    CUndoData* data = new CUndoData;
    data->m_object = object;
    data->m_property = ~0u;
    data->m_objectGuid = -1;
    data->m_data = NULL;
    data->m_count = 0;
    data->m_action = 2;
    m_undoData.add(data);
}
void CUndo::DoUndoOnProperty(CUndoData* data, CUndo* undo)
{
    if (!data || data->m_property == ~0u) return;
    CEditorScene* scene = gEditor->GetEditorScene(data->m_sceneID);
    if (!scene) return;
    CEditorBaseObject* object = scene->GetObjectInScene(data->m_objectGuid);
    if (!object || !object->getDescriptor()) return;
    undo->AddUndoProperty(object, data->m_property);
    object->getDescriptor()->SetProperty(object, data->m_property, data->m_data, data->m_count);
}
void CUndo::DoUndoUndelete(CUndoData* data, CUndo* undo)
{
    if (!data || !data->m_object || !data->m_object->getSceneOwner()) return;
    undo->AddNewObject(data->m_object);
    gEditor->getObjectManager()->EditorObjectCreated(data->m_object);
    data->m_object->RemoveBaseObjectFlag(static_cast<EEDITOROBJECT_FLAG>(1));
    data->m_object->RemoveBaseObjectFlag(static_cast<EEDITOROBJECT_FLAG>(2));
    data->m_object->RemoveBaseObjectFlag(static_cast<EEDITOROBJECT_FLAG>(8));
    CSceneNodeObject* object = dynamic_cast<CSceneNodeObject*>(data->m_object);
    if (object) object->setVisible(true);
    data->m_object = NULL;
}
void CUndo::DoUndoCreate(CUndoData* data, CUndo* undo)
{
    if (!data || !data->m_object || !data->m_object->getSceneOwner()) return;
    CSceneNodeObject* object = dynamic_cast<CSceneNodeObject*>(data->m_object);
    if (object) object->setVisible(false);
    undo->AddObjectDeleted(data->m_object);
    data->m_object->AddBaseObjectFlag(static_cast<EEDITOROBJECT_FLAG>(1));
    data->m_object->AddBaseObjectFlag(static_cast<EEDITOROBJECT_FLAG>(2));
    data->m_object->AddBaseObjectFlag(static_cast<EEDITOROBJECT_FLAG>(8));
    gEditor->m_bUnknown164 = true;
    data->m_object = NULL;
}
void CUndo::DoAsRedo()
{
    if (!m_undoData.size()) return;
    CUndo* undo = new CUndo;
    resetPropertiesOnObject(undo);
    if (!undo->m_undoData.size()) delete undo;
    else gEditor->addUndo(undo, false);
}
void CUndo::DoAsUndo()
{
    if (!m_undoData.size()) return;
    CUndo* undo = new CUndo;
    resetPropertiesOnObject(undo);
    if (!undo->m_undoData.size()) delete undo;
    else gEditor->addRedo(undo);
}
