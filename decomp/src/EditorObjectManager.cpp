#include "iSelected.h"
#include "EditorScene.h"
#include "EmptyStrings.h"
#include "GameVariables.h"
#include "EditorObjectManager.h"
#include "EditorBaseObject.h"
#include "iHighlight.h"
#include "ObjectControl3D.h"



CEditorObjectManager::~CEditorObjectManager()
{
    if (m_pObjectControl != NULL)
    {
        delete m_pObjectControl;
        m_pObjectControl = NULL;
    }
}

void CEditorObjectManager::EditorUpdateEnd()
{
}

void CEditorObjectManager::EditorUpdateBeginning()
{
}

Ogre::Vector3 CEditorObjectManager::getSelectedPivot()
{
    if (m_pObjectControl)
        return m_pObjectControl->m_selectedPivot;
    return Ogre::Vector3::ZERO;
}

float CEditorObjectManager::EditorGetWorkingPlaneHeight()
{
    if (m_pObjectControl)
        return m_pObjectControl->m_workingHeight;
    return 0.0f;
}

void CEditorObjectManager::EditorSetSnapToGroundBias(float value)
{
    if (m_pObjectControl)
        m_pObjectControl->m_snapToGroundBias = value;
}

void CEditorObjectManager::EditorSetPosHSnapSize(float value)
{
    if (m_pObjectControl)
        m_pObjectControl->m_planeScale = value;
}

void CEditorObjectManager::EditorSetPosVSnapSize(float value)
{
    if (m_pObjectControl)
        m_pObjectControl->m_positionVerticalSnap = value;
}

void CEditorObjectManager::EditorSetOrientSnapSize(float value)
{
    if (m_pObjectControl)
        m_pObjectControl->m_orientationSnap = value;
}

void CEditorObjectManager::EditorSetChunkTemplateBasisSize(float value)
{
    if (m_pObjectControl)
        m_pObjectControl->m_chunkSize = value;
}

void CEditorObjectManager::EditorSetChunkTemplateWidth(float value)
{
    if (m_pObjectControl)
        m_pObjectControl->m_chunkWidth = value;
}

void CEditorObjectManager::EditorSetChunkTemplateHeight(float value)
{
    if (m_pObjectControl)
        m_pObjectControl->m_chunkDepth = value;
}

void CEditorObjectManager::EditorSetChunkTemplateExits(int value)
{
    if (m_pObjectControl)
        m_pObjectControl->m_chunkCount = value;
}

void CEditorObjectManager::highlightObject(CEditorBaseObject* object)
{
    iHighlight* highlight = dynamic_cast<iHighlight*>(object);
    if (highlight)
        highlight->setHighlighted(true);
}

void CEditorObjectManager::dehighlightObject(CEditorBaseObject* object)
{
    iHighlight* highlight = dynamic_cast<iHighlight*>(object);
    if (highlight)
        highlight->setHighlighted(false);
}

void CEditorObjectManager::mouseEvent(unsigned int event, unsigned int value)
{
    if (m_pObjectControl)
        m_pObjectControl->mouseEvent(event, value);
}

void CEditorObjectManager::keyEvent(unsigned int event, unsigned int value)
{
    if (m_pObjectControl)
        m_pObjectControl->keyEvent(event, value);
}

void CEditorObjectManager::flushKeyManager()
{
    if (m_pObjectControl)
        m_pObjectControl->flushKeyManager();
}

void CEditorObjectManager::EditorResnapSelectedObjects(bool flag)
{
    if (m_pObjectControl)
        m_pObjectControl->resnapObjects(m_SelectedObjects, flag);
}

void CEditorObjectManager::EditorSnapObjectsToGround(bool flag)
{
    if (m_pObjectControl)
        m_pObjectControl->snapObjectsToGround(flag, m_SelectedObjects);
}

void CEditorObjectManager::EditorResetOrientation()
{
    if (m_pObjectControl)
        m_pObjectControl->ResetOrientation(m_SelectedObjects);
}

void CEditorObjectManager::EditorResetScale()
{
    if (m_pObjectControl)
        m_pObjectControl->ResetScale(m_SelectedObjects);
}

void CEditorObjectManager::EditorApplyRotationNoise(float amount)
{
    if (m_pObjectControl)
        m_pObjectControl->ApplyRotationNoise(amount, m_SelectedObjects);
}

void CEditorObjectManager::EditorApplyNormalNoise(float amount)
{
    if (m_pObjectControl)
        m_pObjectControl->ApplyNormalNoise(amount, m_SelectedObjects);
}

void CEditorObjectManager::EditorApplyScaleNoise(float amount, bool flag)
{
    if (m_pObjectControl)
        m_pObjectControl->ApplyScaleNoise(amount, flag, m_SelectedObjects);
}

Ogre::Vector3 CEditorObjectManager::EditorGetWorkingPlanePosition()
{
    if (m_pObjectControl)
        return m_pObjectControl->getWorkingPlanePosition();
    return Ogre::Vector3::ZERO;
}

void CEditorObjectManager::EditorSetWorkingPlaneHeight(float value)
{
    CObjectControl3D* control = m_pObjectControl;
    if (control)
    {
        control->m_workingHeight = value;
        control->updateControls(0.0f);
    }
}

void CEditorObjectManager::EditorUpdate(float elapsed)
{
    if (m_pObjectControl)
    {
        m_pObjectControl->updateControls(elapsed);
        m_pObjectControl->update(elapsed, m_SelectedObjects, m_bUnknown78);
    }
    m_bUnknown78 = false;
}


CEditorObjectManager::CEditorObjectManager(CResourceManager* resources)
    : m_SelectedObjects(10), m_CreatedObjects(10),
      m_pObjectControl(NULL), m_bUnknown78(false), m_bUnknown79(false)
{
    m_pObjectControl = new CObjectControl3D(resources);
    m_pObjectControl->m_editorEnabled = true;
}

template TArrayList<CEditorBaseObject*>::~TArrayList();

void CEditorObjectManager::EditorSetChunkTemplateExit(int index, float x, float y, float z)
{
    if (m_pObjectControl != NULL)
        m_pObjectControl->m_chunkPositions[index] = Ogre::Vector3(x, y, z);
}

void CEditorObjectManager::ClearSelectedObjects()
{
    for (unsigned int i = 0; i < m_SelectedObjects.size(); ++i) {
        dehighlightObject(m_SelectedObjects[i]);
        iSelected* selected = dynamic_cast<iSelected*>(m_SelectedObjects[i]);
        if (selected != NULL)
            selected->editorSelectionChanged(false);
    }
    m_SelectedObjects.clear();
    m_bUnknown78 = true;
}

void CEditorObjectManager::EditorDeleteAllObjectsInScene(CEditorScene* scene)
{
    ClearSelectedObjects();
    for (ObjectMap::iterator it = m_Objects.begin(); it != m_Objects.end();) {
        if (it->second->getSceneOwner() == scene)
            m_Objects.erase(it++);
        else
            ++it;
    }
    scene->DeleteAllObjectsFromScene();
}

void CEditorObjectManager::EditorObjectSelected(CEditorBaseObject* object)
{
    if (object == NULL || m_SelectedObjects.find(object) != -1)
        return;
    iSelected* selected = dynamic_cast<iSelected*>(object);
    if (selected)
        selected->editorSelectionChanged(true);
    highlightObject(object);
    m_SelectedObjects.add(object);
    m_bUnknown78 = true;
}

void CEditorObjectManager::EditorObjectCreated(CEditorBaseObject* object)
{
    if (object) {
        m_Objects[object->getGuid()] = object;
        m_CreatedObjects.add(object);
    }
}

#include "ObjectControl3D.h"

CEditorBaseObject* CEditorObjectManager::getObjectUnderMouse()
{
    if (m_pObjectControl != NULL)
        return m_pObjectControl->getObjectUnderMouse();
    return NULL;
}
