#include "EmptyStrings.h"
#include "AISkill.h"

CAISkill::CAISkill(std::wstring name)
    : m_fTimeRemaining(0.0f)
{
    m_sName = name;
}

CAISkill::~CAISkill()
{
}

bool CAISkill::update(float elapsed)
{
    m_fTimeRemaining -= elapsed;
    return m_fTimeRemaining > 0.0f;
}
