#ifndef ATTACKDESCRIPTION_H
#define ATTACKDESCRIPTION_H
#include "RunicCore.h"
// Partial. Original 0x80-byte allocation at 0x8814c1; speed read at +0x70.
class CAttackDescription : public CRunicCore
{
public:
    virtual ~CAttackDescription();
    unsigned char m_AttackData10[0x70-0x10];
    float m_fAttackSpeed;
    unsigned char m_AttackData74[0x80-0x74];
};
#endif
