#ifndef ATTACKDESCRIPTION_H
#define ATTACKDESCRIPTION_H
#include "RunicCore.h"
#include <string>
// Partial: layout initialized by the original constructor at 0x8996e0.
class CAttackDescription : public CRunicCore
{
public:
    CAttackDescription(const std::string&,bool,float,float,unsigned int,unsigned int,int,float);
    virtual ~CAttackDescription();
    std::string m_sAnimationName;
    bool m_bUnknown18;
    unsigned char m_AttackData19[0x24-0x19];
    unsigned int m_DamageMaximums[7];
    unsigned int m_DamageMinimums[7];
    unsigned char m_AttackData5C[0x68-0x5c];
    float m_fRange;
    float m_fStrikeRange;
    float m_fAttackSpeed;
    int m_iToHit;
    int m_iUnknown78;
    unsigned char m_AttackData7C[4];
};
#endif
