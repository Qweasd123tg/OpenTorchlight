#include "SkillProperty.h"
#include "Skill.h"
#include "BaseUnit.h"
#include "Character.h"


CBaseUnit* CSkillProperty::getOwner()
{
    return m_pSkill ? m_pSkill->m_pOwner : NULL;
}

CCharacter* CSkillProperty::getOwnerCharacter()
{
    if (m_pSkill)
    {
        CBaseUnit* owner = m_pSkill->m_pOwner;
        if (owner && owner->m_eBaseUnitType == 0)
            return static_cast<CCharacter*>(owner);
    }
    return NULL;
}


std::wstring CSkillProperty::getSkillDescription()
{
    return m_sDescription;
}

float CSkillProperty::getCoolDown()
{
    if (m_pSkill && m_pSkill->m_pOwner &&
        m_pSkill->m_pOwner->m_eBaseUnitType == 0 &&
        m_pSkill->m_pOwner->ISA(UNITTYPES::MONSTER))
        return m_fMonsterCoolDown;
    return m_fCoolDown;
}

#include "SkillEffectAndAffixes.h"
#include "Character.h"

bool CSkillProperty::applyAffixesAndEffectsToUnit(CCharacter* character, const Ogre::Vector3* position)
{
    if (character && !m_pSkillEffectAndAffixes)
        return false;
    CCharacter* owner = dynamic_cast<CCharacter*>(m_pSkill->getMasterOwner());
    return m_pSkillEffectAndAffixes->applyAffixesAndEffects(character, owner, position, false);
}

#include "SkillEvent.h"

void CSkillProperty::fillOutStatBonuses(float (&values)[6],bool includeBase)
{
    if(m_pSkillEffectAndAffixes)m_pSkillEffectAndAffixes->fillOutStatBonuses(values,includeBase);
    for(unsigned i=0;i<m_eventLists.size();++i)
        for(unsigned j=0;j<m_eventLists[i]->size();++j) {
            CSkillEffectAndAffixes* effects=(*m_eventLists[i])[j]->m_pSkillEffectAndAffixes;
            if(effects)effects->fillOutStatBonuses(values,includeBase);
        }
}

bool CSkillProperty::canAffixesAndEffectsBeAppliedToUnit(CBaseUnit* unit,CCharacter* character)
{
    if(m_pSkillEffectAndAffixes)return m_pSkillEffectAndAffixes->canAffixesAndEffectsBeAppliedToUnit(unit,character);
    for(unsigned i=0;i<m_eventLists.size();++i)
        for(unsigned j=0;j<m_eventLists[i]->size();++j)
            if(!(*m_eventLists[i])[j]->canAffixesAndEffectsBeAppliedToUnit(unit,character))return false;
    return true;
}

void CSkillProperty::addMinAndMaxValuesOfAnEffect(CResourceManager* resources,unsigned effect,float& minimum,float& maximum)
{
    if(m_pSkillEffectAndAffixes)m_pSkillEffectAndAffixes->addMinAndMaxValuesOfAnEffect(resources,effect,minimum,maximum);
    for(unsigned i=0;i<m_eventLists.size();++i)
        for(unsigned j=0;j<m_eventLists[i]->size();++j)
            (*m_eventLists[i])[j]->addMinAndMaxValuesOfAnEffect(resources,effect,minimum,maximum);
}

CSkillEvent* CSkillProperty::cloneEventForSkill(CSkillEvent* event)
{
    if(event && static_cast<unsigned>(event->m_eventType)<11) {
        TArrayList<CSkillEvent*>* events=m_eventLists[event->m_eventType];
        if(events && events->size()) {
            CSkillEvent* clone=new CSkillEvent(m_pSkill,this,m_pResourceManager,event->m_data);
            clone->m_cloneSource=event;
            events->add(clone);
            return clone;
        }
    }
    return NULL;
}

CSkillProperty::~CSkillProperty()
{
    for(unsigned i=0;i<m_eventLists.size();++i)m_eventLists[i]->deleteAll();
    m_eventLists.deleteAll();
    delete m_pSkillEffectAndAffixes;
    m_pSkillEffectAndAffixes=NULL;
}
