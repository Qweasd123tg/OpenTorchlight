#ifndef OBJECTCONTROL3D_H
#define OBJECTCONTROL3D_H
#include "RunicCore.h"
#include "KeyManager.h"
#include "MouseManager.h"
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
    void createUndo(TArrayList<CEditorBaseObject*>& objects);
    void ResetScale(TArrayList<CEditorBaseObject*>& objects);
    void ResetOrientation(TArrayList<CEditorBaseObject*>& objects);
    void snapObjectsToGround(bool orient, TArrayList<CEditorBaseObject*>& objects);
    void snapObjectToGround(CPositionableObject* object, bool orient);
    Ogre::Vector3 getSelectedPivot(TArrayList<CEditorBaseObject*>& objects);
    void configureSceneManager(CPositionableObject* object);
    void UpdateWorkingPlane();
    Ogre::Vector3 getWorkingPlanePosition();

    virtual ~CObjectControl3D();
    void doCameraMovement(float elapsed);
    Ogre::Quaternion GetSelectionOrientation();
    int getManipulationType();
    void flushKeyManager();
    void mouseEvent(unsigned int event, unsigned int value);
    void keyEvent(unsigned int event, unsigned int value);

private:
    unsigned char m_unrecovered10[8];
    CMouseHandler* m_mouseHandler; // +0x18
    CGenericModel* m_boxModel; // +0x20
    Ogre::SceneManager* m_sceneManager; // +0x28
    CResourceManager* m_resources; // +0x30
    unsigned char m_unrecovered38[0x90];
    std::vector<CGenericModel*> m_models; // +0xc8
    unsigned char m_unrecoveredE0[0xc];
    float m_planeScale; // +0xec
    unsigned char m_unrecoveredF0[0x10c];
    float m_workingHeight; // +0x1fc
    Ogre::Plane m_workingPlane; // +0x200
    CKeyManager m_keys;
    unsigned char m_unrecoveredKeys[0xd18-sizeof(CKeyManager)];
    CMouseManager m_mouse;
    unsigned char m_unrecoveredMouse[0x50-sizeof(CMouseManager)];
    CUndo* m_undo; // +0xf78
    Ogre::SceneNode* m_controlsNode; // +0xf80
};
#endif
