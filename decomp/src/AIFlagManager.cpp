#include "EmptyStrings.h"
#include "AIFlagManager.h"
#include "AIFlag.h"
#include "AIManager.h"
#include "Character.h"
#include "Level.h"

CAIFlagManager::CAIFlagManager(CAIManager* aiManager, CCharacter* character)
    : m_Flags(10), m_pCharacter(character), m_pAIManager(aiManager)
{
    for (int i = 0; i < AIFLAG_COUNT; i++)
        m_Flags.add(new CAIFlag((EAIFLAG_TYPES)i, this));
}

CAIFlagManager::~CAIFlagManager()
{
    m_Flags.deleteAll();
}

bool CAIFlagManager::hasAIFlag(EAIFLAG_TYPES type)
{
    return m_Flags[type]->isActive();
}

void CAIFlagManager::updateAIFlag(EAIFLAG_TYPES type, float elapsed)
{
}

void CAIFlagManager::flagRemoved(EAIFLAG_TYPES type)
{
    if (type == AIFLAG_BERSERK)
        m_pCharacter->setAlignment(m_pCharacter->ISA(UNITTYPES::MONSTER) ? ALIGNMENT_EVIL : ALIGNMENT_GOOD);
}

void CAIFlagManager::removeAIFlag(EAIFLAG_TYPES type)
{
    bool active = hasAIFlag(type);
    m_Flags[type]->setTimeRemaining(0.0f);
    if (!active)
        flagRemoved(type);
}

void CAIFlagManager::flagSet(EAIFLAG_TYPES type)
{
    if (type == AIFLAG_AWARE)
    {
        // Wake up the whole formation.
        TArrayList<long long>& formation = m_pAIManager->getFormationUnits();
        for (unsigned int i = 0; i < formation.size(); i++)
        {
            CCharacter* unit = m_pCharacter->getLevel()->getCharacterByGuid(formation[i]);
            if (unit != NULL && unit->getAIManager() != NULL)
                unit->getAIManager()->addAIFlag(AIFLAG_AWARE, m_Flags[type]->getTimeRemaining());
        }
    }
    else if (type == AIFLAG_BERSERK)
    {
        m_pCharacter->interrupt(false);
        m_pCharacter->setTarget(NULL);
        m_pCharacter->setAIState(AISTATE_IDLE);
        m_pCharacter->updateAI(0.0f, true);
    }
}

CAIFlag* CAIFlagManager::addAIFlag(EAIFLAG_TYPES type, float time)
{
    bool active = m_Flags[type]->isActive();
    if (time > m_Flags[type]->getTimeRemaining())
        m_Flags[type]->setTimeRemaining(time);
    if (!active)
        flagSet(type);
    return m_Flags[type];
}

void CAIFlagManager::updateAIFlags(float elapsed)
{
    for (unsigned int i = 0; i < m_Flags.size(); i++)
    {
        if (m_Flags[i] != NULL && m_Flags[i]->getTimeRemaining() > 0.0f)
        {
            if (!m_Flags[i]->update(elapsed))
                removeAIFlag((EAIFLAG_TYPES)i);
        }
    }
}
