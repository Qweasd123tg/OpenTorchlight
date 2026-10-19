#ifndef OBJECTCONTROL3D_H
#define OBJECTCONTROL3D_H
#include "RunicCore.h"
#include "KeyManager.h"
#include "MouseManager.h"
#include "LinuxUtils.h"
#include <OgreQuaternion.h>
#include <OgrePlane.h>
#include <vector>
#include "TArrayList.h"
class CEditorBaseObject;
class CPositionableObject;
class CGenericModel;
class CResourceManager;
class CMouseHandler;
class CUndo;
namespace Ogre { class SceneManager; class SceneNode; }

class CObjectControl3D : public CRunicCore
{
public:
    void cloneObjectsIfNeedBe(TArrayList<CEditorBaseObject*>& objects);
    void showControls(bool show);
    int configureDragType();
    Ogre::Vector3 getGroupRotationPoint(TArrayList<CEditorBaseObject*>& objects);
    void updateBoundingBox(TArrayList<CEditorBaseObject*>& objects);
    void manipulateSelectedItems(float elapsed, TArrayList<CEditorBaseObject*>& objects);
    void doObjectPick();
    void InitControls();
    CEditorBaseObject* getObjectUnderMouse();
    Ogre::Vector3 getMousePlaneInstersect(POINT point, Ogre::Plane plane);
    Ogre::Vector3 getCameraPlaneIntersect(Ogre::Plane plane);
    void UpdateChunkTemplate();
    void createUndo(TArrayList<CEditorBaseObject*>& objects);
    void ApplyRotationNoise(float amount, TArrayList<CEditorBaseObject*>& objects);
    void ApplyNormalNoise(float amount, TArrayList<CEditorBaseObject*>& objects);
    void ApplyScaleNoise(float amount, bool uniform, TArrayList<CEditorBaseObject*>& objects);
    void ResetScale(TArrayList<CEditorBaseObject*>& objects);
    void ResetOrientation(TArrayList<CEditorBaseObject*>& objects);
    void snapObjectsToGround(bool orient, TArrayList<CEditorBaseObject*>& objects);
    void snapObjectToGround(CPositionableObject* object, bool orient);
    Ogre::Vector3 getSelectedPivot(TArrayList<CEditorBaseObject*>& objects);
    void configureSceneManager(CPositionableObject* object);
    void UpdateWorkingPlane();
    Ogre::Vector3 getWorkingPlanePosition();
    void updateControls(float elapsed);
    void resnapObjects(TArrayList<CEditorBaseObject*>& objects, bool flag);
    void update(float elapsed, TArrayList<CEditorBaseObject*>& objects, bool flag);

    CObjectControl3D(CResourceManager* resources);
    virtual ~CObjectControl3D();
    void doCameraMovement(float elapsed);
    Ogre::Quaternion GetSelectionOrientation();
    int getManipulationType();
    void flushKeyManager();
    void mouseEvent(unsigned int event, unsigned int value);
    void keyEvent(unsigned int event, unsigned int value);

private:
    friend class CEditorObjectManager;
    bool m_editorEnabled; // +0x10
    unsigned char m_unrecovered11[7];
    CMouseHandler* m_mouseHandler; // +0x18
    CGenericModel* m_boxModel; // +0x20
    Ogre::SceneManager* m_sceneManager; // +0x28
    CResourceManager* m_resources; // +0x30
    unsigned int m_selectionCount; // +0x38
    bool m_boxSelecting; // +0x3c
    unsigned char m_gap3d[3];
    Ogre::Vector3 m_boxStart; // +0x40
    Ogre::Vector3 m_boxEnd; // +0x4c
    bool m_flag58;
    bool m_flag59;
    bool m_previousLeftDown; // +0x5a
    bool m_flag5b;
    unsigned char m_gap5c[4];
    POINT m_previousMouse; // +0x60
    POINT m_dragMouse; // +0x70
    Ogre::Vector3 m_dragPivot; // +0x80
    unsigned int m_dragType; // +0x8c
    Ogre::Vector3 m_dragDirection; // +0x90
    Ogre::Plane m_dragPlane; // +0x9c
    Ogre::Vector3 m_selectedPivot; // +0xac
    Ogre::Vector3 m_controlOffset; // +0xb8
    unsigned char m_gapc4[4];
    std::vector<CGenericModel*> m_models; // +0xc8
    Ogre::Vector3 m_viewDelta; // +0xe0
    float m_planeScale; // +0xec
    float m_positionVerticalSnap; // +0xf0
    float m_orientationSnap; // +0xf4
    float m_chunkSize; // +0xf8
    float m_chunkWidth; // +0xfc
    float m_chunkDepth; // +0x100
    Ogre::Vector3 m_chunkPositions[20]; // +0x104
    int m_chunkCount; // +0x1f4
    float m_snapToGroundBias; // +0x1f8
    float m_workingHeight; // +0x1fc
    Ogre::Plane m_workingPlane; // +0x200
    CKeyManager m_keys;
    CMouseManager m_mouse;
    unsigned char m_unrecoveredMouse[0x50-sizeof(CMouseManager)];
    CUndo* m_undo; // +0xf78
    Ogre::SceneNode* m_controlsNode; // +0xf80
};
#endif
