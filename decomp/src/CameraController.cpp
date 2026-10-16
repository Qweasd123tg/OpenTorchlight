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
