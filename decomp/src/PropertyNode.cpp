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

#include "UtilitiesMath.h"
#include "GameClient.h"
#include "Player.h"

void CPropertyNode::killOrMoveBaseUnits()
{
    CLevel* level=m_pResourceManager->getLevel();
    CGameClient* client=m_pResourceManager->getGameClient(0);
    if(!client || !level) return;
    CCharacter* master=client->getPlayer();
    TLinkedListNode<CCharacter*>* node=level->getCharacters()->getHead();
    const Ogre::Vector3 origin=getPosition(true);
    for(;node;node=node->m_pNext) {
        CCharacter* character=node->m_Data;
        if(!character->m_bInActiveRange) continue;
        const Ogre::Vector3 position=character->getPosition(true);
        if(m_bounds.contains(position)) {
            if(character==master || character->m_pMaster==master) {
                if(master && character->m_pMaster==master)
                    character->teleportToMaster(1.0f);
            } else if(m_iPropertyNodeType==8) {
                const float distance=(character->getPosition(true)-origin).length();
                if(getScaleX()>=distance)
                    character->modifyHP(static_cast<float>(-character->HP()));
            } else {
                character->modifyHP(static_cast<float>(-character->HP()));
            }
        } else if(master && character->m_pMaster==master) {
            const Ogre::Vector3 masterPosition=master->getPosition(true);
            const float distance=(character->getPosition(true)-masterPosition).length();
            if(distance>=getScaleX()) character->teleportToMaster(1.0f);
        }
    }
}

void CPropertyNode::updateBoundingBox()
{
    const Ogre::Vector3 position=getPosition(true);
    const Ogre::Vector3& scale=getScale();
    const float halfWidth=scale.x*0.5f;
    const float halfDepth=scale.z*0.5f;
    m_cullingBounds->m_vMinimum=Ogre::Vector3(-halfWidth,-1000.0f,-halfDepth);
    m_cullingBounds->m_vMaximum=Ogre::Vector3(halfWidth,1000.0f,halfDepth);
    m_cullingBounds->m_vLocalMinimum=m_cullingBounds->m_vMinimum;
    m_cullingBounds->m_vLocalMaximum=m_cullingBounds->m_vMaximum;

    Ogre::Matrix3 rotation;
    m_pSceneNode->_getDerivedOrientation().ToRotationMatrix(rotation);
    Ogre::Matrix4 transform(rotation);
    transform.setTrans(position);
    CCullingBounds* bounds=m_cullingBounds;
    bounds->m_vWorldMinimum=transform*bounds->m_vMinimum;
    bounds->m_vWorldMaximum=bounds->m_vWorldMinimum;
    MATH::expandBounds(bounds->m_vWorldMinimum,bounds->m_vWorldMaximum,transform*bounds->m_vMinimum);
    MATH::expandBounds(bounds->m_vWorldMinimum,bounds->m_vWorldMaximum,transform*bounds->m_vMaximum);
    MATH::expandBounds(bounds->m_vWorldMinimum,bounds->m_vWorldMaximum,transform*Ogre::Vector3(bounds->m_vMinimum.x,bounds->m_vMinimum.y,bounds->m_vMaximum.z));
    MATH::expandBounds(bounds->m_vWorldMinimum,bounds->m_vWorldMaximum,transform*Ogre::Vector3(bounds->m_vMinimum.x,bounds->m_vMaximum.y,bounds->m_vMaximum.z));
    MATH::expandBounds(bounds->m_vWorldMinimum,bounds->m_vWorldMaximum,transform*Ogre::Vector3(bounds->m_vMinimum.x,bounds->m_vMaximum.y,bounds->m_vMinimum.z));
    MATH::expandBounds(bounds->m_vWorldMinimum,bounds->m_vWorldMaximum,transform*Ogre::Vector3(bounds->m_vMaximum.x,bounds->m_vMinimum.y,bounds->m_vMinimum.z));
    MATH::expandBounds(bounds->m_vWorldMinimum,bounds->m_vWorldMaximum,transform*Ogre::Vector3(bounds->m_vMaximum.x,bounds->m_vMaximum.y,bounds->m_vMinimum.z));
    MATH::expandBounds(bounds->m_vWorldMinimum,bounds->m_vWorldMaximum,transform*Ogre::Vector3(bounds->m_vMaximum.x,bounds->m_vMinimum.y,bounds->m_vMaximum.z));
    for(unsigned int i=0;i<8;++i)
        bounds->m_WorldCorners[i]=Ogre::Vector3(
            i&1?bounds->m_vWorldMaximum.x:bounds->m_vWorldMinimum.x,
            i&2?bounds->m_vWorldMaximum.y:bounds->m_vWorldMinimum.y,
            i&4?bounds->m_vWorldMaximum.z:bounds->m_vWorldMinimum.z);
    m_bounds.setExtents(m_cullingBounds->m_vWorldMinimum,m_cullingBounds->m_vWorldMaximum);
}
