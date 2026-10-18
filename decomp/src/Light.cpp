#include "Light.h"

void CLight::scaleUpdated(const Ogre::Vector3& scale)
{
    if (scale.y != 0.25f)
        setScale(scale.x, 0.25f, scale.z);
}
void CLight::orientationUpdated(const Ogre::Matrix4&)
{
}

float CLight::getRotation()
{
    Ogre::Matrix3 orientation;
    getOrientation(orientation);
    Ogre::Quaternion rotation(orientation);
    return rotation.getYaw().valueDegrees();
}

void CLight::setRotation(float rotation)
{
    Ogre::Quaternion orientation(Ogre::Degree(rotation), Ogre::Vector3::UNIT_Y);
    setOrientation(orientation);
}

#include "EmptyStrings.h"
#include "OgreUtilities.h"
#include <OgreSceneManager.h>
void CLight::destroyLights()
{
    if (m_pResourceManager->getSceneManager())
        for (unsigned int i=0;i<m_entities.size();++i) {
            OGRE_UTILITIES::detachEntityFromParent(m_entities[i]);
            m_pResourceManager->getSceneManager()->destroyEntity(m_entities[i]);
        }
    m_entities.clear();
}
CLight::CLight(CResourceManager* resources)
    : CPositionableObject(resources,NULL), m_iLightDensity(1), m_entities(10),
      m_bitmapFile(EMPTY_WSTRING),m_iUnknown128(0),m_pGenericModel(NULL)
{
    setScale(1.0f,0.25f,1.0f);
    setVisible(true);
}
CLight::~CLight()
{
    if (m_pGenericModel) { delete m_pGenericModel; m_pGenericModel=NULL; }
    destroyLights();
}
void CLight::setBitmapFile(std::wstring name)
{
    if (name.empty() || name==m_bitmapFile) return;
    destroyLights();
    m_bitmapFile=name;
    if (!m_pGenericModel)
        m_pGenericModel=new CGenericModel(m_pResourceManager,NULL,EMPTY_WSTRING,EMPTY_WSTRING,false);
    m_pGenericModel->loadModel(m_bitmapFile,EMPTY_WSTRING,false,false,false);
    m_pGenericModel->setVisible(false);
    updateLightDensity(false);
}

#include "StringUtilities.h"
void CLight::updateLightDensity(bool force)
{
    if (!m_pResourceManager->getEditorIsRunning()) return;
    if (!m_pResourceManager->getEditorIsRunning() && !force) return;
    if (m_bitmapFile==EMPTY_WSTRING || !m_pGenericModel) return;
    for (unsigned int i=0;i<m_entities.size();++i)
        OGRE_UTILITIES::detachEntityFromParent(m_entities[i]);
    for (unsigned int i=m_entities.size();i<=static_cast<unsigned int>(m_iLightDensity);++i) {
        m_entities.add(m_pGenericModel->getEntity()->clone(STRINGS::uniqueName("light")));
        m_entities[i]->setRenderQueueGroup(95);
        m_entities[i]->setQueryFlags(8);
        m_entities[i]->setVisibilityFlags(2);
    }
    for (unsigned int i=0;i<static_cast<unsigned int>(m_iLightDensity);++i)
        OGRE_UTILITIES::attachEntityToSceneNode(m_entities[i],m_pSceneNode);
}
