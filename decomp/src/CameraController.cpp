#include "CameraController.h"
#include "GameVariables.h"
#include "GameClient.h"
#include "Player.h"
#include "Level.h"
#include "UnitResourceList.h"
#include "EmptyStrings.h"

void CCameraController::setUnitInteractWith(std::wstring name)
{
    if (m_pResourceManager)
    {
        m_sUnitInteractWith = name;
        m_unitDataGroup = CUnitResourceList::getSingleton()->getDataGroupByObjectName(name);
        if (m_unit.getObject())
            m_unit.setObject(0);
    }
}

void CCameraController::configureUnit()
{
    m_unit.setObject(m_pResourceManager->getLevel()->getBaseUnitByDataGroup(m_unitDataGroup));
}

void CCameraController::configureUnitsInLevel()
{
    if (m_pResourceManager && m_pResourceManager->getLevel())
        configureUnit();
}

CCameraController::CCameraController(CResourceManager* resourceManager)
    : CPositionableObject(resourceManager, 0), m_pResourceManager(resourceManager),
      m_pCategory(gRESOURCE_GROUP_NAMES[1]), m_sUnitInteractWith(), m_unitDataGroup(0),
      m_unit(), m_fCameraPanTime(1.5f), m_fUnknown14C(0.0f),
      m_fCameraEaseInPCT(0.8f), m_fCameraEaseInDistancePCT(0.9f),
      m_fCameraPauseTimer(0.0f), m_fUnknown15C(0.0f), m_bUnknown160(false),
      m_bRestoreCameraStateAfterMoving(true), m_bFollowUnit(false), m_bUnknown163(false),
      m_cameraGraph(GRAPH_CURVED, L"Interact", 1), m_iCameraType(1)
{
    m_bEnabled = false;
}

CCameraController::~CCameraController()
{
}

#include "CameraControl.h"
#include "GameUI.h"
#include "EditorScene.h"
void CCameraController::stopCamera()
{
    m_fUnknown15C=0;
    if(!m_pResourceManager->getGameClient() || !m_pResourceManager->getGameClient()->getPlayer()) return;
    if(!m_bUnknown163) {
        if(getEnabled()) BroadcastEvent(88);
        m_bUnknown163=true;
    }
    m_pResourceManager->getGameClient()->getPlayer()->setEnabled(true);
    m_pResourceManager->getGameClient()->getPlayer()->stopPathing();
    m_pResourceManager->getGameClient()->getPlayer()->setAIState(static_cast<EAIState>(2));
    m_pResourceManager->getGameClient()->m_cameraPosition=m_pResourceManager->getGameClient()->getPlayer()->getPosition(false);
    m_pResourceManager->getGameClient()->m_cameraState=static_cast<ECAMERA_STATES>(0);
    BroadcastEvent(90);setEnabled(false);
}
void CCameraController::startCamera()
{
    if(m_iCameraType==1 && !m_unit.getObject()) {
        configureUnit();if(!m_unit.getObject()) return;
    }
    m_bUnknown163=false;
    CCameraControl* camera=CCameraControl::getSingleton();
    m_fUnknown130=camera->m_fUnknown4C;m_fUnknown134=camera->m_fUnknown50;m_fUnknown138=camera->m_fUnknown54;
    Ogre::Vector3 destination;
    if(m_unit.getObject()) destination=m_unit.getObject()->getPosition(true);
    else { Ogre::Vector3 local=getPosition(false); Ogre::Vector3 owner=getSceneOwner()->getPosition(true); destination=local+owner; }
    m_fUnknown13C=destination.x-m_fUnknown130;m_fUnknown140=destination.y-m_fUnknown134;m_fUnknown144=destination.z-m_fUnknown138;
    m_cameraGraph.clear(0);m_cameraGraph.addValue(0,0,0);
    m_cameraGraph.addValue(m_fCameraEaseInPCT,m_fCameraEaseInDistancePCT,0);
    m_cameraGraph.addValue(1,1,0);m_cameraGraph.processPoints();
    m_fUnknown14C=m_fCameraPanTime;
    if(m_pResourceManager->getGameClient()->m_cameraState!=static_cast<ECAMERA_STATES>(1)) {
        CGameUI::getSingleton()->closeAll();CGameUI::getSingleton()->hideModalDialogs();
    }
    CPlayer* player=m_pResourceManager->getGameClient()->getPlayer();
    if(player) {player->setEnabled(false);player->stopPathing();player->setAIState(static_cast<EAIState>(44));}
    m_pResourceManager->getGameClient()->m_cameraState=static_cast<ECAMERA_STATES>(1);
    BroadcastEvent(87);m_fUnknown15C=0;m_bUnknown160=false;setEnabled(true);
}
void CCameraController::update(float elapsed)
{
    if(!getEnabled()) return;
    if(m_fUnknown14C<=0 && !m_bUnknown160) {
        if(m_bFollowUnit) {
            if(m_unit.getObject()) m_pResourceManager->getGameClient()->m_cameraPosition=m_unit.getObject()->getPosition(true);
        } else m_pResourceManager->getGameClient()->m_cameraPosition=getPosition(true);
        return;
    }
    if(m_bFollowUnit && m_unit.getObject()) {
        Ogre::Vector3 position=m_unit.getObject()->getPosition(true);
        m_fUnknown13C=position.x-m_fUnknown130;m_fUnknown140=position.y-m_fUnknown134;m_fUnknown144=position.z-m_fUnknown138;
    }
    if(m_bUnknown160) m_fUnknown15C-=elapsed;
    m_fUnknown14C-=elapsed;
    float ratio=1.0f-(m_fUnknown14C>0?m_fUnknown14C:0.0f)/m_fCameraPanTime;
    if(ratio>0) {if(ratio>1)ratio=1;} else ratio=0;
    float amount=m_cameraGraph.getValue(ratio,0);
    m_pResourceManager->getGameClient()->m_cameraPosition=Ogre::Vector3(m_fUnknown130+m_fUnknown13C*amount,m_fUnknown134+m_fUnknown140*amount,m_fUnknown138+m_fUnknown144*amount);
    if(amount>=1) {
        if(m_fCameraPauseTimer>0 && !m_bUnknown160) {
            m_fUnknown15C=m_fCameraPauseTimer;m_bUnknown160=true;BroadcastEvent(89);return;
        }
        if(m_fUnknown15C<=0 && !m_bUnknown163) {
            m_bUnknown163=true;BroadcastEvent(88);m_bUnknown160=false;
            if(m_bRestoreCameraStateAfterMoving) stopCamera();
        }
    }
}
