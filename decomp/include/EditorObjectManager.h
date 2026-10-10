#ifndef EDITOROBJECTMANAGER_H
#define EDITOROBJECTMANAGER_H

#include <map>

#include "RunicCore.h"
#include "TArrayList.h"

class CEditorBaseObject;
class CEditorScene;
class CObjectControl3D;
class CResourceManager;
class CEditorScene;

// Partial: layout from CEditorObjectManager::CEditorObjectManager; members of
// EditorObjectManager.cpp are declared as recovered TUs need them.
class CEditorObjectManager : public CRunicCore
{
public:
    TArrayList<CEditorBaseObject*>& getCreatedObjects() { return m_CreatedObjects; }

    void markChanged() { m_bUnknown79 = true; }

    void flushKeyManager();
    Ogre::Vector3 getSelectedPivot();

    void EditorResnapSelectedObjects(bool value);
    void EditorResetOrientation();
    void EditorResetScale();
    void EditorApplyRotationNoise(float value);
    void EditorSnapObjectsToGround(bool value);
    void EditorApplyNormalNoise(float value);
    void EditorApplyScaleNoise(float value, bool uniform);
    CEditorBaseObject* getObjectUnderMouse();
    void ClearSelectedObjects();
    void EditorObjectSelected(CEditorBaseObject* object);

    void keyEvent(unsigned int event, unsigned int code);
    void mouseEvent(unsigned int event, unsigned int code);
    void EditorSetChunkTemplateExits(int count);
    void EditorSetChunkTemplateExit(int index, float x, float y, float z);
    void EditorDeleteAllObjectsInScene(CEditorScene* scene);
    void EditorSetOrientSnapSize(float value);
    void EditorSetPosVSnapSize(float value);
    void EditorSetPosHSnapSize(float value);
    void EditorSetChunkTemplateHeight(float value);
    void EditorSetChunkTemplateWidth(float value);
    void EditorSetChunkTemplateBasisSize(float value);
    float EditorGetWorkingPlaneHeight();
    void EditorSetWorkingPlaneHeight(float value);
    void EditorSetSnapToGroundBias(float value);

    typedef std::map<long long, CEditorBaseObject*> ObjectMap;

    CEditorObjectManager(CResourceManager* resourceManager);
    virtual ~CEditorObjectManager();

    ObjectMap* getObjects() { return &m_Objects; }
    TArrayList<CEditorBaseObject*>* getSelectedObjects() { return &m_SelectedObjects; }

private:
    ObjectMap m_Objects;
    TArrayList<CEditorBaseObject*> m_SelectedObjects;
    TArrayList<CEditorBaseObject*> m_CreatedObjects;
    CObjectControl3D* m_pObjectControl;
    bool m_bUnknown78;
    bool m_bUnknown79;
};

#endif
