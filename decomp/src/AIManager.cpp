#include "EmptyStrings.h"
#include "AIManager.h"
#include "AIStatWatcher.h"
#include "AIFlagManager.h"
#include "AISkillManager.h"
#include "Character.h"
#include "DataGroup.h"

CAIManager::CAIManager(CCharacter* character)
    : m_pCharacter(character), m_pFlagManager(NULL), m_StatWatchers(10), m_FormationUnits(10)
{
    m_pFlagManager = new CAIFlagManager(this, character);
    m_pSkillManager = new CAISkillManager(this, character);
}

CAIManager::~CAIManager()
{
    if (m_pFlagManager != NULL)
    {
        delete m_pFlagManager;
        m_pFlagManager = NULL;
    }
    if (m_pSkillManager != NULL)
    {
        delete m_pSkillManager;
        m_pSkillManager = NULL;
    }
    m_StatWatchers.deleteAll();
    m_FormationUnits.clear();
}

void CAIManager::update(float elapsed)
{
    m_pFlagManager->updateAIFlags(elapsed);
    m_pSkillManager->updateAISkills(elapsed);
    for (unsigned int i = 0; i < m_StatWatchers.size(); i++)
        m_StatWatchers[i]->update(elapsed);
}

void CAIManager::removeAIFlag(EAIFLAG_TYPES type)
{
    m_pFlagManager->removeAIFlag(type);
}

void CAIManager::removeAISkill(CAISkill* skill)
{
    m_pSkillManager->removeAISkill(skill);
}

bool CAIManager::hasAIFlag(EAIFLAG_TYPES type)
{
    return m_pFlagManager->hasAIFlag(type);
}

bool CAIManager::hasAISkill(CAISkill* skill)
{
    return m_pSkillManager->hasAISkill(skill);
}

void CAIManager::addAISkill(CAISkill* skill, float time)
{
    m_pSkillManager->addAISkill(skill, time);
}

CAIFlag* CAIManager::addAIFlag(EAIFLAG_TYPES type, float time)
{
    return m_pFlagManager->addAIFlag(type, time);
}

void CAIManager::addFormationUnit(CBaseUnit* unit)
{
    m_FormationUnits.add(unit->getGuid());
}

CLevel* CAIManager::getLevel()
{
    return m_pCharacter->getLevel();
}

CResourceManager* CAIManager::getResourceManager()
{
    return m_pCharacter->getResourceManager();
}

void CAIManager::initalize()
{
    if (m_pCharacter == NULL || m_pCharacter->getDataGroup() == NULL)
        return;

    CDataGroup* aiGroup = m_pCharacter->getDataGroup()->GetDataGroupByName(L"AI", false);
    if (aiGroup == NULL)
        return;

    std::vector<CDataGroup*> statGroups;
    aiGroup->GetDataGroupsMatchingName(L"STAT", &statGroups);
    for (unsigned int i = 0; i < statGroups.size(); i++)
        m_StatWatchers.add(new CAIStatWatcher(statGroups[i], this));
}
