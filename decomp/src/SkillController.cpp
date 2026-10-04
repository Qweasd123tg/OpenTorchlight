#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "SkillController.h"
#include "Player.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "UnitResourceList.h"
#include "SafePointer.h"

CPlayer* CSkillController::getSkillTarget()
{
    if (m_bUsePlayerAsTarget)
        return *reinterpret_cast<CPlayer **>(
            reinterpret_cast<char *>(m_pResourceManager->getGameClient()) + 0x58);

    if (m_bUseUnitTarget && m_pRunicCore != NULL &&
        *reinterpret_cast<int *>(reinterpret_cast<char *>(m_pRunicCore) + 0xBC) == 0)
        return *reinterpret_cast<CPlayer **>(
            reinterpret_cast<char *>(m_pRunicCore) + 0x340);

    return NULL;
}

CSkillController::CSkillController(CResourceManager* resourceManager)
    : CPositionableObject(resourceManager, NULL),
      m_pResourceManager(resourceManager), m_iUnitInteractDataGroup(0),
      m_pRunicCore(NULL), m_iRunicCoreSafePointerId(-1),
      m_sCategory(*reinterpret_cast<const std::wstring *>(
          gRESOURCE_GROUP_NAMES + 8)),
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
        m_iUnitInteractDataGroup =
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
