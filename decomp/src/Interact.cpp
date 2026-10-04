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
    if (m_fUnknownB4 > 0.0f)
    {
        m_fUnknownB4 -= elapsed;
        m_fUnknownB4 = m_fUnknownB4 > 0.0f ? m_fUnknownB4 : 0.0f;

        CGraph* graph = reinterpret_cast<CGraph*>(&m_UnknownC8);
        float value = graph->getValue(
            1.0f - m_fUnknownB4 / m_fUnknownB0, 0);

        CGameClient* gameClient = m_pResourceManager->getGameClient();
        float* position = reinterpret_cast<float*>(
            reinterpret_cast<char*>(gameClient) + 0x38e0);

        position[0] = m_fUnknownA4 * value + m_fUnknown98;
        position[1] = m_fUnknownA8 * value + m_fUnknown9C;
        position[2] = m_fUnknownAC * value + m_fUnknownA0;
    }
}

void CInteract::setUnitInteractWithByIndex(unsigned int unitIndex, std::wstring unitName)
{
    if (unitIndex == 0 && m_pResourceManager != NULL) {
        m_sUnknown78 = unitName;
        m_iUnknown80 =
            CUnitResourceList::getSingleton()->getDataGroupByObjectName(unitName);

        if (m_pRunicCore != NULL) {
            m_pRunicCore->removeSafePointer(
                (TSafePointer<void *> *)&m_pRunicCore, m_iUnknown90);
            m_pRunicCore = NULL;
        }
    }
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
      m_pRunicCore(NULL),
      m_iUnknown90(-1),
      m_fUnknownB0(1.5f),
      m_fUnknownB4(0.0f),
      m_fUnknownB8(0.8f),
      m_fUnknownBC(0.9f),
      m_UnknownC0(0)
{
    new (static_cast<void*>(&m_pUnknown70)) std::wstring(
        *reinterpret_cast<const std::wstring*>(gRESOURCE_GROUP_NAMES + 8));

    new (static_cast<void*>(&m_UnknownC8)) CGraph(
        static_cast<EGRAPH_TYPES>(1),
        std::wstring(L"Interact"),
        1);

    m_iUnknown120 = 0;
    m_iUnknown80 = 0;

    if (m_pRunicCore != NULL)
        m_pRunicCore->removeSafePointer(
            reinterpret_cast<TSafePointer<void*>*>(&m_pRunicCore),
            m_iUnknown90);
}
