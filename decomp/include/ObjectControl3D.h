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
    unsigned char m_unrecovered38[0x74];
    Ogre::Vector3 m_selectedPivot; // +0xac
    unsigned char m_unrecoveredB8[0x10];
    std::vector<CGenericModel*> m_models; // +0xc8
    unsigned char m_unrecoveredE0[0xc];
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
