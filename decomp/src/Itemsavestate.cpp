#include "Effect.h"
#include "ItemSaveState.h"


CItemSaveState::CItemSaveState()
    : m_iStateValue28(0), m_iOriginalGuid(-1), m_iStateValue38(-1), m_iParentHierarchyHash(-1),
      m_bSaveFlag48(false), m_bSaveFlag5C(false), m_bEnabled(false), m_iUnitValue60(-1),
      m_StateByte74(0), m_bIdentified(false), m_iBaseDamage(-1), m_iBaseArmor(-1),
      m_iRoomIndex(-1), m_bItemFlag17C(true)
{
}

CItemSaveState::~CItemSaveState()
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < static_cast<int>(m_Effects[i].size()); ++j) {
            if (m_Effects[i][j]) {
                delete m_Effects[i][j];
                m_Effects[i][j] = NULL;
            }
        }
    }
    m_Effects[0].clear();
    for (unsigned int i = 0; i < m_SocketedItems.size(); ++i) {
        if (m_SocketedItems[i]) {
            delete m_SocketedItems[i];
            m_SocketedItems[i] = NULL;
        }
    }
    m_SocketedItems.clear();
}
