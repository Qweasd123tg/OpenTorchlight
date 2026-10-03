#ifndef SKILLMANAGER_H
#define SKILLMANAGER_H

#include <string>

#include "RunicCore.h"

class CSkill;

// Partial: members are declared as SkillManager.cpp is recovered.
class CSkillManager : public CRunicCore
{
public:
    CSkill* getSkill(const std::wstring& name);
};

#endif
