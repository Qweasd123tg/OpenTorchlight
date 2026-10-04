#include "EmptyStrings.h"
#include "GameEnums.h"
#include "RandomGroup.h"
#include "PositionableObject.h"
#include "ResourceManager.h"

void CRandomGroup::SetRandomType(unsigned int randomType)
{
    if (randomType <= 2) {
        m_iRandomType = randomType;
    }
}

bool CRandomGroup::canGroupBeCreatedBasedOffOfDungeon()
{
    struct ResourceManagerLayout {
        unsigned char padding[0x43];
        bool ignoreRestrictions;
    };

    struct LevelLayout {
        unsigned char padding[0x280];
        std::wstring dungeonName;
    };

    if (m_sDungeonForGroup.empty())
        return true;

    if (m_pResourceManager->getEditorIsRunning())
        return true;

    const ResourceManagerLayout* resourceManager =
        reinterpret_cast<const ResourceManagerLayout*>(m_pResourceManager);

    if (resourceManager->ignoreRestrictions)
        return true;

    const LevelLayout* level =
        reinterpret_cast<const LevelLayout*>(m_pResourceManager->getLevel());

    if (level == NULL)
        return true;

    return level->dungeonName.empty() ||
           level->dungeonName == m_sDungeonForGroup;
}

bool CRandomGroup::getGroupCanBeCreated()
{
    if (reinterpret_cast<const unsigned char*>(m_pResourceManager)[0x43])
        return true;

    return canGroupBeCreatedBasedOffOfPlayerClass() &&
           canGroupBeCreatedBasedOffOfQuests() &&
           canGroupBeCreatedBasedOffOfDungeon() &&
           canGroupBeCreatedBasedOffOfDifficulty();
}

CRandomGroup::CRandomGroup(CResourceManager* resourceManager)
    : CPositionableObject(resourceManager, NULL),
      m_bPropagatePosition(true),
      m_iMinimumChildren(0),
      m_iMaximumChildren(0),
      m_iChildSelectionLimit(0),
      m_iChildSpawnLimit(0),
      m_iRandomType(0),
      m_iRandomWeight(1),
      m_iNumberOfPicks(1),
      m_lastPosition(0.0f, 0.0f, 0.0f),
      m_children(10),
      m_bIsDynamicGroup(true),
      m_sPlayerClassName(EMPTY_WSTRING),
      m_sDungeonForGroup(EMPTY_WSTRING),
      m_iDifficulty(-1)
{
    setVisible(true);
}

CRandomGroup::~CRandomGroup()
{
}
