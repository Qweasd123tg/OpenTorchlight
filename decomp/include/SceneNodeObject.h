#ifndef SCENENODEOBJECT_H
#define SCENENODEOBJECT_H

#include "EditorBaseObject.h"

class CResourceManager;

namespace Ogre
{
    class Entity;
    class SceneManager;
    class SceneNode;
}

// Editor object with an Ogre scene node: owns the node and an optional entity,
// and keeps the node attached under its parent (scene, parent object or the
// scene root) while it is visible.
class CSceneNodeObject : public CEditorBaseObject
{
public:
    CSceneNodeObject(CResourceManager* resourceManager, Ogre::SceneManager* sceneManager);
    virtual ~CSceneNodeObject();

    virtual void setParentPositionableObject(CPositionableObject* parent);
    virtual void SetSceneOwner(CEditorScene* scene);
    virtual void setEnabled(bool enabled) { m_bEnabled = enabled; }
    virtual bool getEnabled() { return m_bEnabled; }
    virtual void setVisible(bool visible);

    void setResourceManager(CResourceManager* resourceManager);
    CResourceManager* getResourceManager() { return m_pResourceManager; }
    Ogre::SceneNode* getSceneNode() { return m_pSceneNode; }

    bool getVisible() const { return m_bVisible; }

    void sceneNodeCreate();
    void sceneNodeDestroy();
    void sceneNodeAttachEntity(Ogre::Entity* entity);
    void sceneNodeDetachEntity();
    void sceneNodeDestroyEntity();
    void sceneNodeAddChild(Ogre::SceneNode* child);
    void sceneNodeAddChild(CSceneNodeObject* child);
    void sceneNodeSetParent(Ogre::SceneNode* parent, bool keepParent);
    void sceneNodeRemoveFromParent();

protected:
    Ogre::SceneNode* m_pSceneNode;
    Ogre::Entity* m_pEntity;
    CResourceManager* m_pResourceManager;
    Ogre::SceneNode* m_pParentSceneNode;
    Ogre::SceneManager* m_pSceneManager;
    // Set by sceneNodeSetParent(…, true): later parent changes are ignored.
    bool m_bKeepParent;
    bool m_bVisible;
    bool m_bEnabled;
};

#endif
