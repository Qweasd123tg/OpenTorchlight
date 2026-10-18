#include "PropertyNode.h"

void CPropertyNode::setPropertyNodeType(unsigned int type)
{
    m_iPropertyNodeType = type;
}

void CPropertyNode::createEntity()
{
    
}

void CPropertyNode::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
    if (enabled)
        BroadcastEvent(6);
    else
        BroadcastEvent(7);
    switch (m_iPropertyNodeType) {
    case 6: jumpDownLogic(); break;
    case 8:
    case 9: updatePathNodes(); break;
    default: break;
    }
}

void CPropertyNode::orientationUpdated(const Ogre::Matrix4&)
{
    updateBoundingBox();
}

void CPropertyNode::positionUpdated(const Ogre::Vector3&)
{
    updateBoundingBox();
}

#include "Level.h"
void CPropertyNode::characterUpdatedInLevel(float, CCharacter* character)
{
    if (m_pSceneNode && getEnabled() && m_iPropertyNodeType==6) {
        Ogre::Vector3 position=character->getPosition(true);
        if (m_bounds.contains(position)) character->setAllowJumpDown(true);
    }
}
void CPropertyNode::activate()
{
    if (!m_bUnknown111 && m_pResourceManager->getLevel()) {
        if (m_bUnknown118) {
            m_pResourceManager->getLevel()->removeCharacterUpdateListener(this);
            m_bUnknown118=false;
        }
        if (m_iPropertyNodeType==6 && !m_bUnknown118) setEnabled(true);
    }
}
void CPropertyNode::jumpDownLogic()
{
    if (!m_pResourceManager->getLevel()) return;
    if (getEnabled()) {
        if (!m_bUnknown118) {
            m_pResourceManager->getLevel()->addCharacterUpdateListener(this);
            m_bUnknown118=true;
        }
    } else if (m_bUnknown118) {
        m_pResourceManager->getLevel()->removeCharacterUpdateListener(this);
        m_bUnknown118=false;
    }
}
CPropertyNode::~CPropertyNode()
{
    if (m_pResourceManager->getLevel()) {
        m_pResourceManager->getLevel()->removeCharacterUpdateListener(this);
        m_bUnknown118=false;
    }
    if (m_cullingBounds) { delete m_cullingBounds; m_cullingBounds=NULL; }
}
CPropertyNode::CPropertyNode(CResourceManager* resources)
    : CPositionableObject(resources,NULL), m_iUnknown108(4),m_iPropertyNodeType(1),
      m_bUnknown110(true),m_bUnknown111(false),m_bUnknown112(true),m_iUnknown114(0),
      m_bUnknown118(false),m_bounds(Ogre::Vector3::ZERO,Ogre::Vector3::ZERO),
      m_cullingBounds(NULL),m_bUnknown150(false)
{
    m_cullingBounds=new CCullingBounds;
    m_cullingBounds->m_vMinimum=Ogre::Vector3(-0.5f,0,-0.5f);
    m_cullingBounds->m_vMaximum=Ogre::Vector3(0.5f,2,0.5f);
    m_cullingBounds->m_vLocalMinimum=Ogre::Vector3(-0.5f,0,-0.5f);
    m_cullingBounds->m_vLocalMaximum=Ogre::Vector3(0.5f,2,0.5f);
    m_cullingBounds->m_vWorldMinimum=Ogre::Vector3(-0.5f,0,-0.5f);
    m_cullingBounds->m_vWorldMaximum=Ogre::Vector3(0.5f,2,0.5f);
    setScaleY(1.0f);
    setVisible(true);
}
void CPropertyNode::scaleUpdated(const Ogre::Vector3& scale)
{
    if (m_pResourceManager->getEditorIsRunning()) {
        if (scale.y!=3.0f) setScale(scale.x,3.0f,scale.z);
    } else if (scale.y!=1000.0f) setScale(scale.x,1000.0f,scale.z);
    updateBoundingBox();
}

void CPropertyNode::updatePathNodes()
{
    if(!m_pResourceManager->getLevel()) return;
    if(m_iPropertyNodeType==8) {
        if(getEnabled()) {
            if(!m_bUnknown150 && m_pResourceManager->getLevel()->m_passWidth && m_pResourceManager->getLevel()->m_passHeight) {
                m_bUnknown150=true;
                m_pResourceManager->getLevel()->incrementMapPassability(m_bounds,getScaleX());
                killOrMoveBaseUnits();
            }
        } else if(m_bUnknown150) {
            m_bUnknown150=false;
            m_pResourceManager->getLevel()->decrementMapPassability(m_bounds,getScaleX());
        }
    } else if(m_iPropertyNodeType==9) {
        if(getEnabled()) {
            if(!m_bUnknown150 && m_pResourceManager->getLevel()->m_passWidth && m_pResourceManager->getLevel()->m_passHeight) {
                m_bUnknown150=true;
                m_pResourceManager->getLevel()->incrementMapPassability(m_bounds,0);
                killOrMoveBaseUnits();
            }
        } else if(m_bUnknown150) {
            m_bUnknown150=false;
            m_pResourceManager->getLevel()->decrementMapPassability(m_bounds,0);
        }
    }
}
