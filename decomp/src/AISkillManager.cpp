#include "EmptyStrings.h"
#include "AISkillManager.h"
#include "AISkill.h"
#include "Character.h"
#include "Skill.h"
#include "SkillManager.h"

CAISkillManager::CAISkillManager(CAIManager* aiManager, CCharacter* character)
    : m_pCharacter(character), m_pAIManager(aiManager)
{
}

CAISkillManager::~CAISkillManager()
{
}

void CAISkillManager::skillAdded(std::wstring name)
{
    if (m_pCharacter != NULL)
    {
        CSkill* skill = m_pCharacter->getSkillManager()->getSkill(name);
        if (skill != NULL)
            skill->setEnabled(true);
    }
}

void CAISkillManager::skillRemoved(std::wstring name)
{
    if (m_pCharacter != NULL)
    {
        CSkill* skill = m_pCharacter->getSkillManager()->getSkill(name);
        if (skill != NULL)
            skill->setEnabled(false);
    }
}

bool CAISkillManager::hasAISkill(CAISkill* skill)
{
    for (unsigned int i = 0; i < m_Skills.size(); i++)
    {
        if (m_Skills[i]->getName() == skill->getName())
            return true;
    }
    return false;
}

CAISkill* CAISkillManager::getSkill(std::wstring name)
{
    for (unsigned int i = 0; i < m_Skills.size(); i++)
    {
        if (m_Skills[i]->getName() == name)
            return m_Skills[i];
    }
    return NULL;
}

void CAISkillManager::updateAISkill(std::wstring name, float elapsed)
{
    CAISkill* skill = getSkill(name);
    if (skill != NULL)
        skill->update(elapsed);
}

void CAISkillManager::removeAISkill(CAISkill* skill)
{
    if (skill == NULL)
        return;

    if (hasAISkill(skill))
        skill->setTimeRemaining(0.0f);

    std::wstring name = skill->getName();
    for (unsigned int i = 0; i < m_Skills.size(); i++)
    {
        if (m_Skills[i]->getName() == name)
        {
            m_Skills.removeAt(i);
            i--;
        }
    }
    skillRemoved(skill->getName());
}

void CAISkillManager::updateAISkills(float elapsed)
{
    for (unsigned int i = 0; i < m_Skills.size(); i++)
    {
        if (m_Skills[i] != NULL && m_Skills[i]->getTimeRemaining() > 0.0f)
        {
            updateAISkill(m_Skills[i]->getName(), elapsed);
            if (!m_Skills[i]->update(elapsed))
                removeAISkill(m_Skills[i]);
        }
    }
}

void CAISkillManager::addAISkill(CAISkill* skill, float time)
{
    if (hasAISkill(skill))
        return;

    m_Skills.add(skill);
    skill->setTimeRemaining(time);
    skillAdded(skill->getName());
}
