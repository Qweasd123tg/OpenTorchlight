#ifndef CHARACTER_SAVE_STATE_H
#define CHARACTER_SAVE_STATE_H
#include "RunicCore.h"
// Partial 0x228-byte save record. HP is tested by the original continue menu.
class CCharacterSaveState : public CRunicCore
{
public:
    virtual ~CCharacterSaveState();
    unsigned char m_unrecovered10[0xe0-0x10];
    float m_hp;
    unsigned char m_unrecoveredE4[0x228-0xe4];
};
#endif
