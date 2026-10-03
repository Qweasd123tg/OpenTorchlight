#ifndef AISKILL_H
#define AISKILL_H

#include <string>

#include "RunicCore.h"
#include "AIDefines.h"

// Named AI skill cooldown tracked by CAISkillManager.
class CAISkill : public CRunicCore
{
public:
    CAISkill(std::wstring name);
    virtual ~CAISkill();

    // Counts the remaining time down; false once it has run out.
    bool update(float elapsed);

private:
    float m_fTimeRemaining;
    std::wstring m_sName;
};

#endif
