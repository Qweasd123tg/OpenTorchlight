#include "EmptyStrings.h"
#include "AIFlag.h"

CAIFlag::CAIFlag(EAIFLAG_TYPES type, CAIFlagManager* manager)
    : m_fTimeRemaining(0.0f), m_pManager(manager), m_eType(type)
{
}

CAIFlag::~CAIFlag()
{
}

bool CAIFlag::update(float elapsed)
{
    m_fTimeRemaining -= elapsed;
    return m_fTimeRemaining > 0.0f;
}
