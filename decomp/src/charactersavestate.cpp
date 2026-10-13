#include "CharacterSaveState.h"
#include "ItemSaveState.h"


CCharacterSaveState::CCharacterSaveState()
    : m_guid10(-1), m_flag18(false), m_guid20(-1), m_guid28(-1),
      m_flag30(false), m_flag31(false), m_flag32(false), m_flag33(false),
      m_flag34(false), m_value38(0), m_guid50(-1), m_guid58(-1),
      m_value60(-1), m_value64(0), m_value68(0), m_guidB8(-1),
      m_guidC0(-1), m_guidC8(-1), m_valueD0(0), m_valueD4(0),
      m_valueD8(0), m_valueDC(0), m_hp(0), m_valueE4(0), m_valueE8(0),
      m_value184(-1), m_guid200(-1), m_value208(-1), m_flag20C(false), m_strings(10)
{
}

CCharacterSaveState::~CCharacterSaveState()
{
    for (int group = 0; group < 3; ++group)
        for (int i = 0; i < static_cast<int>(m_items[group].size()); ++i)
            if (m_items[group][i]) {
                delete m_items[group][i];
                m_items[group][i] = NULL;
            }
    for (unsigned int i = 0; i < m_pets.size(); ++i)
        if (m_pets[i]) {
            delete m_pets[i];
            m_pets[i] = NULL;
        }
    m_pets.clear();
    m_items[0].clear();
}
