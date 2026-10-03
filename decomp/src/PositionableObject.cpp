#include "EmptyStrings.h"
#include "PositionableObject.h"
#include "OgreUtilities.h"
#include "EditorScene.h"
#include "ResourceManager.h"

CPositionableObject::CPositionableObject(CResourceManager* resourceManager, Ogre::SceneManager* sceneManager)
    : CSceneNodeObject(resourceManager, sceneManager), m_vPosition(0.0f, 0.0f, 0.0f), m_vScale(1.0f, 1.0f, 1.0f),
      m_vUp(0.0f, 1.0f, 0.0f), m_vRight(1.0f, 0.0f, 0.0f), m_vForward(0.0f, 0.0f, 1.0f),
      m_mOrientation(Ogre::Matrix4::IDENTITY)
{
    extractOrientationVectors();
}

CPositionableObject::~CPositionableObject()
{
}

Ogre::Vector3 CPositionableObject::getPosition(bool absolute)
{
    if (!absolute || !m_pSceneNode || !getParentPositionableObject())
        return m_vPosition;
    return m_pSceneNode->_getDerivedPosition();
}

void CPositionableObject::setPosition(const Ogre::Vector3& position)
{
    m_vPosition = position;
    if (m_pSceneNode)
        m_pSceneNode->setPosition(m_vPosition);
    positionUpdated(m_vPosition);
}

void CPositionableObject::updateOrientation()
{
    setOrientation(m_mOrientation, false);
}
