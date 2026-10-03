#include "EmptyStrings.h"
#include "SceneNodeObject.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "EditorScene.h"

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>

CSceneNodeObject::CSceneNodeObject(CResourceManager* resourceManager, Ogre::SceneManager* sceneManager)
    : m_pSceneNode(NULL), m_pEntity(NULL), m_pResourceManager(NULL), m_pParentSceneNode(NULL),
      m_pSceneManager(sceneManager), m_bKeepParent(false), m_bVisible(false), m_bEnabled(false)
{
    if (m_pSceneManager == NULL && resourceManager != NULL)
        m_pSceneManager = resourceManager->getSceneManager();
    if (resourceManager != NULL)
        setResourceManager(resourceManager);
}

CSceneNodeObject::~CSceneNodeObject()
{
    sceneNodeDestroyEntity();
    sceneNodeDestroy();
    m_pResourceManager = NULL;
}

void CSceneNodeObject::sceneNodeDestroyEntity()
{
    if (m_pEntity)
        m_pSceneManager->destroyEntity(m_pEntity);
    m_pEntity = NULL;
}

void CSceneNodeObject::sceneNodeDetachEntity()
{
    if (m_pEntity && m_pSceneNode)
        m_pSceneNode->detachObject(m_pEntity);
}

void CSceneNodeObject::sceneNodeAttachEntity(Ogre::Entity* entity)
{
    if (m_pSceneNode && m_pEntity && m_pEntity->getParentSceneNode() == m_pSceneNode)
        m_pSceneNode->detachObject(m_pEntity);
    m_pEntity = entity;
    if (m_pSceneNode && m_pEntity)
        m_pSceneNode->attachObject(m_pEntity);
}

void CSceneNodeObject::sceneNodeAddChild(Ogre::SceneNode* child)
{
    if (m_pSceneNode == NULL)
        return;
    if (child == NULL)
        return;
    OGRE_UTILITIES::removeChildFromParentNode(child);
    m_pSceneNode->addChild(child);
}

void CSceneNodeObject::sceneNodeDestroy()
{
    sceneNodeDestroyEntity();
    if (m_pSceneNode)
    {
        OGRE_UTILITIES::removeChildFromParentNode(m_pSceneNode);
        m_pParentSceneNode = NULL;
        // Both results are unused in the original.
        m_pSceneNode->numAttachedObjects();
        m_pSceneNode->numChildren();
        m_pSceneNode->removeAllChildren();
        m_pSceneManager->destroySceneNode(m_pSceneNode);
        m_pSceneNode = NULL;
    }
}

void CSceneNodeObject::sceneNodeRemoveFromParent()
{
    if (m_pSceneNode)
    {
        OGRE_UTILITIES::removeChildFromParentNode(m_pSceneNode);
        m_bVisible = false;
    }
}

void CSceneNodeObject::setVisible(bool visible)
{
    if (m_bVisible == visible)
        return;
    m_bVisible = visible;
    if (m_pSceneNode == NULL)
        return;

    OGRE_UTILITIES::removeChildFromParentNode(m_pSceneNode);
    if (!m_bVisible && getParentPositionableObject() == NULL)
        return;
    if (m_pParentSceneNode)
        m_pParentSceneNode->addChild(m_pSceneNode);
    m_pSceneNode->_update(true, true);
    if (getParentPositionableObject())
        m_pSceneNode->setVisible(m_bVisible, true);
}

void CSceneNodeObject::sceneNodeCreate()
{
    if (m_pResourceManager == NULL || m_pSceneNode != NULL)
        return;
    m_pSceneNode = m_pSceneManager->createSceneNode();
    if (m_pEntity)
        sceneNodeAttachEntity(m_pEntity);
    CSceneNodeObject::setVisible(m_bVisible);
}

void CSceneNodeObject::setResourceManager(CResourceManager* resourceManager)
{
    if (m_pResourceManager == resourceManager)
        return;
    if (m_pResourceManager != NULL && (m_pSceneNode != NULL || m_pParentSceneNode != NULL || m_pEntity != NULL))
        return;

    m_pResourceManager = resourceManager;
    if (m_pResourceManager != NULL && m_pSceneManager == NULL)
        m_pSceneManager = m_pResourceManager->getSceneManager();
    if (m_pResourceManager != NULL)
    {
        if (m_pSceneNode == NULL)
            sceneNodeCreate();
        m_pParentSceneNode = m_pSceneManager->getRootSceneNode();
    }
}

void CSceneNodeObject::sceneNodeSetParent(Ogre::SceneNode* parent, bool keepParent)
{
    if (m_pParentSceneNode != NULL && m_bKeepParent)
        return;
    m_bKeepParent = keepParent;
    if (m_pParentSceneNode == parent)
        return;

    bool visible = m_bVisible;
    if (m_pSceneNode)
    {
        OGRE_UTILITIES::removeChildFromParentNode(m_pSceneNode);
        m_bVisible = false;
    }
    m_pParentSceneNode = parent;
    if (parent)
        CSceneNodeObject::setVisible(visible);
    else
        m_bKeepParent = false;
}

void CSceneNodeObject::sceneNodeAddChild(CSceneNodeObject* child)
{
    if (m_pSceneNode == NULL)
        return;
    if (child == NULL)
        return;
    child->sceneNodeSetParent(m_pSceneNode, false);
}

void CSceneNodeObject::SetSceneOwner(CEditorScene* scene)
{
    if (m_pResourceManager == NULL)
        return;
    CEditorBaseObject::SetSceneOwner(scene);
    if (scene)
        sceneNodeSetParent(scene->getSceneNode(), false);
    else if (m_pResourceManager)
        sceneNodeSetParent(m_pSceneManager->getRootSceneNode(), false);
}

void CSceneNodeObject::setParentPositionableObject(CPositionableObject* parent)
{
    CEditorBaseObject::setParentPositionableObject(parent);
    sceneNodeSetParent(parent ? parent->getSceneNode() : NULL, false);
}
