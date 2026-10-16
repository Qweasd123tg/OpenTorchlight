#include "GameClient.h"
#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "SkillController.h"
#include "Player.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "UnitResourceList.h"
#include "SafePointer.h"
#include "SkillManager.h"

CCharacter* CSkillController::getSkillTarget()
{
    if (m_bUsePlayerAsTarget)
        return m_pResourceManager->getGameClient()->getPlayer();
    if (m_bUseUnitTarget && m_pRunicCore) {
        CCharacter* character = static_cast<CCharacter*>(m_pRunicCore);
        if (character->m_eBaseUnitType == static_cast<EBASEUNIT_TYPE>(0))
            return character->m_targetCharacter.getObject();
    }
    return NULL;
}

CSkillController::CSkillController(CResourceManager* resourceManager)
    : CPositionableObject(resourceManager, NULL),
      m_pResourceManager(resourceManager), m_pUnitInteractDataGroup(NULL),
      m_pRunicCore(NULL), m_iRunicCoreSafePointerId(-1),
      m_sCategory(gRESOURCE_GROUP_NAMES[1]),
      m_sUnitInteractWith(EMPTY_WSTRING), m_sSkillName(EMPTY_WSTRING),
      m_pSecondaryRunicCore(NULL),
      m_iSecondaryRunicCoreSafePointerId(-1), m_bLearnSkillOnStart(true),
      m_bUnlearnSkillOnStop(true), m_bSkillStartRequested(false),
      m_bSkillStopRequested(false), m_bForceStop(false),
      m_bUsePlayerAsTarget(false), m_bUseUnitTarget(true),
      m_iSkillLevel(0)
{
}

void CSkillController::setUnitInteractWith(std::wstring unitInteractWith)
{
    if (m_pResourceManager != NULL) {
        m_sUnitInteractWith = unitInteractWith;
        m_pUnitInteractDataGroup =
            CUnitResourceList::getSingleton()->getDataGroupByObjectName(unitInteractWith);

        if (m_pRunicCore != NULL) {
            m_pRunicCore->removeSafePointer(
                reinterpret_cast<TSafePointer<void*> *>(&m_pRunicCore),
                m_iRunicCoreSafePointerId);
            m_pRunicCore = NULL;
        }
    }
}

bool CSkillController::initSkillController()
{
    return configureUnit();
}

void CSkillController::stopSkill()
{
    if (configureUnit() && !m_sSkillName.empty()) {
        m_bSkillStartRequested = false;
        m_bSkillStopRequested = true;
    }
}

void CSkillController::startSkill()
{
    if (configureUnit() && !m_sSkillName.empty()) {
        m_bSkillStartRequested = true;
        m_bSkillStopRequested = false;
    }
}

void CSkillController::unlearnSkill()
{
    if (configureUnit() && !m_sSkillName.empty() && m_pRunicCore) {
        CSkillManager* skills = static_cast<CBaseUnit*>(m_pRunicCore)->getSkillManager();
        if (skills)
            skills->deleteSkill(m_sSkillName);
        BroadcastEvent(106);
    }
}

void CSkillController::learnSkill()
{
    if (!configureUnit() || m_sSkillName.empty() || !m_pRunicCore)
        return;
    CSkillManager* skills = static_cast<CBaseUnit*>(m_pRunicCore)->getSkillManager();
    if (skills && skills->knowsSkill(m_sSkillName))
        return;
    CSkill* skill = static_cast<CBaseUnit*>(m_pRunicCore)->addSkillByName(m_sSkillName, false);
    if (skill) {
        static_cast<CBaseUnit*>(m_pRunicCore)->getSkillManager()->setSkillLevel(skill, 1);
        BroadcastEvent(105);
    }
}
