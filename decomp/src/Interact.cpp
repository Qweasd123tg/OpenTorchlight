#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Interact.h"
#include "EditorBaseObject.h"
#include "GameClient.h"
#include "Graph.h"
#include "ResourceManager.h"
#include "UnitResourceList.h"
#include "SafePointer.h"

void CInteract::update(float elapsed)
{
    if (m_fUnknownB4 <= 0.0f)
        return;
    m_fUnknownB4 -= elapsed;
    float remaining = m_fUnknownB4;
    if (!(remaining > 0.0f))
        remaining = 0.0f;
    float value = m_cameraGraph.getValue(1.0f - remaining / m_fUnknownB0, 0);
    CGameClient* gameClient = m_pResourceManager->getGameClient();
    gameClient->m_cameraPosition.x = m_fUnknownA4 * value + m_fUnknown98;
    gameClient->m_cameraPosition.y = m_fUnknownA8 * value + m_fUnknown9C;
    gameClient->m_cameraPosition.z = m_fUnknownAC * value + m_fUnknownA0;
}

void CInteract::setUnitInteractWithByIndex(unsigned int unitIndex, std::wstring unitName)
{
    if (unitIndex != 0 || !m_pResourceManager)
        return;
    m_sUnknown78 = unitName;
    m_pUnitDataGroup = CUnitResourceList::getSingleton()->getDataGroupByObjectName(unitName);
    m_unit.setObject(NULL);
}

void CInteract::menuEventOccured(void* arg1, EMENU_TYPE arg2, EMENU_EVENT arg3)
{
    reinterpret_cast<CInteract*>(reinterpret_cast<char*>(this) - 0x58)
        ->CInteract::menuEventOccured(arg1, arg2, arg3);
}

void CInteract::configureUnitsInLevel()
{
    if ((m_pResourceManager != NULL) && (m_pResourceManager->getLevel() != NULL))
        configureSpecificUnitIndex(static_cast<EINTERACTABLE_UNITS>(0));
}

CInteract::~CInteract()
{
}

CInteract::CInteract(CResourceManager* resourceManager)
    : CEditorBaseObject(),
      m_pResourceManager(resourceManager),
      m_pUnknown70(gRESOURCE_GROUP_NAMES[1]),
      m_unit(),
      m_fUnknownB0(1.5f),
      m_fUnknownB4(0.0f),
      m_fUnknownB8(0.8f),
      m_fUnknownBC(0.9f),
      m_UnknownC0(0),
      m_cameraGraph(static_cast<EGRAPH_TYPES>(1), std::wstring(L"Interact"), 1)
{
    m_iUnknown120 = 0;
    m_pUnitDataGroup = NULL;

}

#include "Level.h"
#include "CameraControl.h"
#include "GameUI.h"
#include "Player.h"

void CInteract::configureSpecificUnitIndex(EINTERACTABLE_UNITS index)
{
    // The original indexes one-element unit storage without a bounds check.
    CDataGroup** groups = &m_pUnitDataGroup;
    TSafePointer<CBaseUnit>* units = &m_unit;
    units[index].setObject(m_pResourceManager->getLevel()->getBaseUnitByDataGroup(groups[index]));
}

void CInteract::interactWithUnit(EINTERACTABLE_UNITS index)
{
    TSafePointer<CBaseUnit>* units = &m_unit;
    if (!units[index].getObject()) {
        configureSpecificUnitIndex(index);
        if (!units[index].getObject())
            return;
    }
    m_UnknownC0 = index;
    CCameraControl* camera = CCameraControl::getSingleton();
    m_fUnknown98 = camera->m_fUnknown4C;
    m_fUnknown9C = camera->m_fUnknown50;
    m_fUnknownA0 = camera->m_fUnknown54;
    Ogre::Vector3 position = units[index].getObject()->getPosition(false);
    m_fUnknownA4 = position.x - m_fUnknown98;
    m_fUnknownA8 = position.y - m_fUnknown9C;
    m_fUnknownAC = position.z - m_fUnknownA0;
    m_cameraGraph.clear(0);
    m_cameraGraph.addValue(0.0f, 0.0f, 0);
    m_cameraGraph.addValue(m_fUnknownB8, m_fUnknownBC, 0);
    m_cameraGraph.addValue(1.0f, 1.0f, 0);
    m_cameraGraph.processPoints();
    m_fUnknownB4 = m_fUnknownB0;
    CGameUI::getSingleton()->closeAll();
    m_pResourceManager->getGameClient()->getPlayer()->setInvulnerable(true);
    m_pResourceManager->getGameClient()->getPlayer()->stopPathing();
    m_pResourceManager->getGameClient()->getPlayer()->setAIState(static_cast<EAIState>(44));
    m_pResourceManager->getGameClient()->m_interactionState = true;
    BroadcastEvent(87);
    BroadcastEvent(91);
}
