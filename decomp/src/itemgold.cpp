#include <OgreEntity.h>
#include <algorithm>
#include "GenericModel.h"
#include "ItemGold.h"
#include "ItemSaveState.h"
#include "Particle.h"
#include "ResourceManager.h"
#include "SoundBank.h"

void CItemGold::unloadModel()
{
    if (m_goldModel && m_pResourceManager) {
        delete m_goldModel;
        m_goldModel = NULL;
    }
}

void CItemGold::playDropSound(Ogre::SceneNode* node)
{
    if (!node) node = m_pSceneNode;
    m_pSoundBank->playSample(17,node,0.0f,0.0f,false);
}

void CItemGold::playTakeSound(Ogre::SceneNode* node)
{
    if (!node) node = m_pSceneNode;
    m_pSoundBank->playSample(18,node,0.0f,0.0f,false);
}

void CItemGold::setActiveInLevel(bool active)
{
    setVisible(active);
    updateCullingBounds();
    if (active) {
        snapToGround();
        if (m_goldParticle) m_goldParticle->setPosition(m_vPosition);
    } else hideItemText();
}

void CItemGold::loadModel(std::wstring name)
{
    if (m_pResourceManager) {
        unloadModel();
        m_goldModel = m_pResourceManager->createGenericModel(NULL,name.c_str(),NULL,false,false,true);
        if (m_goldModel->getSceneNode() && m_goldModel->getSceneNode()->getParent())
            m_goldModel->getSceneNode()->getParent()->removeChild(m_goldModel->getSceneNode());
        m_goldModel->setCastsShadows(false);
        m_pSceneNode->addChild(m_goldModel->getSceneNode());
        setVisible(false,true);
        m_goldModel->setPosition(0.0f,0.0f,0.0f);
        m_goldModel->getEntity()->setRenderQueueGroup(50);
    }
    setCastsShadows(false);
}

CItemGold::~CItemGold()
{
    setVisible(false,true);
    if (m_goldParticle) {
        delete m_goldParticle;
        m_goldParticle = NULL;
    }
    unloadModel();
    if (m_pSoundBank) {
        delete m_pSoundBank;
        m_pSoundBank = NULL;
    }
}

void CItemGold::fillSaveState(CItemSaveState& state,int,bool)
{
    state.m_iUnitValue60 = -1;
    state.m_vLocalPosition = getPosition(true);
    state.m_mOrientation = getOrientation();
    state.m_sItemName = getItemName();
    state.m_iStackSize = m_goldAmount;
}

void CItemGold::applySaveState(CItemSaveState& state)
{
    setPosition(state.m_vLocalPosition);
    setOrientation(state.m_mOrientation,false);
    m_sItemName = std::wstring(state.m_sItemName);
    m_goldAmount = state.m_iStackSize;
}
