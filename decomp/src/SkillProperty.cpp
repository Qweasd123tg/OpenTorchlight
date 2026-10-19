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
#include "EmptyStrings.h"
#include "StringTranslate.h"
#include "StringUtilities.h"
#include "ExecuteSkillProps.h"

std::wstring CSkillProperty::getSkillStats()
{
    std::wstring result=EMPTY_WSTRING;
    bool hasText=false;
    if(m_pSkillEffectAndAffixes) {
        result+=m_pSkillEffectAndAffixes->getDisplayStats();
        hasText=!result.empty();
    }
    static std::wstring g_WeaponDamage;
    if(g_WeaponDamage.empty())g_WeaponDamage=CStringTranslate::getSinglton()->getTranslateString(L"Weapon Damage");
    static std::wstring g_WeaponDPS;
    if(g_WeaponDPS.empty())g_WeaponDPS=CStringTranslate::getSinglton()->getTranslateString(L"of Weapon DPS");
    static std::wstring g_Inflicts;
    if(g_Inflicts.empty())g_Inflicts=CStringTranslate::getSinglton()->getTranslateString(L"Inflicts ");
    bool foundWeapon=false;
    for(unsigned int i=0;i<m_eventLists.size() && !foundWeapon;++i)
        for(unsigned int j=0;j<m_eventLists[i]->size();++j)
            if(!(*m_eventLists[i])[j]->m_cloneSource && (*m_eventLists[i])[j]->m_weaponDamageScale!=0.0f) {
                float value=(*m_eventLists[i])[j]->m_weaponDamageScale;
                if(hasText)result+=L"\n";
                if((*m_eventLists[i])[j]->m_useDPS)
                    result=result+g_Inflicts+STRINGS::GetValueAsWString(value*100.0f)+L"% "+g_WeaponDPS+L"\n";
                else
                    result=result+g_WeaponDamage+L": "+STRINGS::GetValueAsWString(value*100.0f)+L"%\n";
                foundWeapon=true;
                hasText=false;
                break;
            }
    for(unsigned int i=0;i<m_eventLists.size();++i)
        for(unsigned int j=0;j<m_eventLists[i]->size();++j)
            if(!(*m_eventLists[i])[j]->m_cloneSource) {
                std::wstring value=(*m_eventLists[i])[j]->getDisplayStats(this);
                if(!value.empty()) {
                    if(hasText)result+=L"\n";
                    result+=value;
                    hasText=true;
                }
            }
    if(!result.empty() && result[result.size()-1]==L'\n')result=result.substr(0,result.size()-1);
    bool hasSecondary=false;
    for(unsigned int i=0;i<m_eventLists.size();++i)
        for(unsigned int j=0;j<m_eventLists[i]->size();++j)
            if(!(*m_eventLists[i])[j]->m_cloneSource && (*m_eventLists[i])[j]->m_executeSkills.size()!=0)hasSecondary=true;
    static std::wstring g_SecondaryEffects;
    if(g_SecondaryEffects.empty())g_SecondaryEffects=CStringTranslate::getSinglton()->getTranslateString(L"Secondary Effects");
    if(hasSecondary && !result.empty())result=result+L"\n  -"+g_SecondaryEffects+L"-";
    for(unsigned int i=0;i<m_eventLists.size();++i)
        for(unsigned int j=0;j<m_eventLists[i]->size();++j)
            if(!(*m_eventLists[i])[j]->m_cloneSource && !(*m_eventLists[i])[j]->m_statsHidden) {
                CSkillEvent* event=(*m_eventLists[i])[j];
                for(unsigned int k=0;k<event->m_executeSkills.size();++k) {
                    CBaseUnit* owner=m_pSkill?m_pSkill->m_pOwner:NULL;
                    std::wstring value=event->m_executeSkills[k]->getSkillStats(owner,m_uiSkillId);
                    result=result+L"\n"+value;
                }
            }
    return result;
}

#include "DataGroup.h"
#include "ResourceManager.h"
#include "UnitThemes.h"
#include "SkillDefines.h"
#include <vector>
#include <math.h>

CSkillProperty::CSkillProperty(CSkill* skill,CResourceManager* resources,CSkillProperty* parent,CDataGroup* data,unsigned int id)
    :m_iRequirementRight(0),m_iRequirementLeft(0),m_bDuelWeaponRequired(false),
     m_pSkillEffectAndAffixes(NULL),m_pResourceManager(resources),m_pSkillProperty(parent),m_pSkill(skill),
     m_uiSkillId(id),m_iLevelRequired(0),m_pDataGroup(data),m_iSkillLevel(2),m_eventLists(10),
     m_eTargetType(0),m_eTargetUnitType(0),m_iManaCost(0),m_iManaCostOverTime(0),
     m_fRange(100),m_iMinimumRange(0),m_fRandomRange(2),m_iRandomRangeMinimum(0),
     m_fSpeed(1),m_fCoolDown(0),m_fMonsterCoolDown(0),m_fMinimumTime(0),m_fDurationOverride(0),m_fSlowDown(0),m_iChance(100),
     m_bHasAnimation(false),m_bInterruptable(false),m_bContinuousLooping(false),m_bExclusive(false),m_bSingleTarget(false),
     m_pRequiredTheme(NULL),m_pForbiddenTheme(NULL)
{
    if(!data || !skill || !resources)return;
    for(unsigned int i=0;i<11;++i)m_eventLists.add(new TArrayList<CSkillEvent*>(10));
    if(parent)m_eTargetType=parent->m_eTargetType;
    std::wstring target=STRINGS::StringUpper(data->GetDataValue(L"TARGET_TYPE",EMPTY_WSTRING));
    if(target.empty())target=STRINGS::StringUpper(data->GetDataValue(L"TARGET",EMPTY_WSTRING));
    if(target!=EMPTY_WSTRING)m_eTargetType=STRINGS::getStringIndex(target,gSKILL_TARGET_TYPE_NAMES,12,m_eTargetType,false);
    if(parent)m_eTargetUnitType=parent->m_eTargetUnitType;
    std::wstring type=data->GetDataValue(L"TARGET_UNITTYPE",EMPTY_WSTRING);
    if(type!=EMPTY_WSTRING)m_eTargetUnitType=resources->getUnitTypeByName(type);
    std::wstring required=data->GetDataValue(L"THEMEREQUIRED",EMPTY_WSTRING);
    if(required.empty())m_pRequiredTheme=parent?parent->m_pRequiredTheme:NULL;
    else {std::wstring name=STRINGS::StringUpper(required);m_pRequiredTheme=CUnitThemes::getSingleton()->getTheme(name);}
    std::wstring forbidden=data->GetDataValue(L"NOTTHEMED",EMPTY_WSTRING);
    if(forbidden.empty())m_pForbiddenTheme=parent?parent->m_pForbiddenTheme:NULL;
    else {std::wstring name=STRINGS::StringUpper(forbidden);m_pForbiddenTheme=CUnitThemes::getSingleton()->getTheme(name);}
    if(parent){m_iRequirementRight=parent->m_iRequirementRight;m_iRequirementLeft=parent->m_iRequirementLeft;}
    std::wstring requirement=data->GetDataValue(L"REQUIREMENT_RIGHT",EMPTY_WSTRING);
    if(requirement!=EMPTY_WSTRING)m_iRequirementRight=resources->getUnitTypeByName(requirement);
    requirement=data->GetDataValue(L"REQUIREMENT_LEFT",EMPTY_WSTRING);
    if(requirement!=EMPTY_WSTRING)m_iRequirementLeft=resources->getUnitTypeByName(requirement);
    m_bDuelWeaponRequired=data->GetDataValue(L"DUELWIELD_REQUIRED",parent?parent->m_bDuelWeaponRequired:m_bDuelWeaponRequired);
    m_bUseWeaponAnimation=data->GetDataValue(L"USEWEAPONANIMATION",parent?parent->m_bUseWeaponAnimation:false);
    m_bSingleTarget=data->GetDataValue(L"SINGLETARGET",parent?parent->m_bSingleTarget:false);
    m_sSkillIcon=data->GetDataValue(L"SKILL_ICON",parent?parent->m_sSkillIcon:EMPTY_WSTRING);
    m_sSkillIconInactive=data->GetDataValue(L"SKILL_ICON_INACTIVE",parent?parent->m_sSkillIconInactive:m_sSkillIcon);
    m_sName=data->GetDataValue(L"NAME",parent?parent->m_sName:EMPTY_WSTRING);
    m_sDisplayName=data->GetDataValue(L"DISPLAYNAME",parent?parent->m_sDisplayName:m_sName);
    m_sUsageDescription=data->GetDataValue(L"USAGE_DESCRIPTION",parent?parent->m_sUsageDescription:m_sUsageDescription);
    m_sDescription=data->GetDataValue(L"DESCRIPTION",parent?parent->m_sDescription:EMPTY_WSTRING);
    m_sDescription=STRINGS::replaceWString(m_sDescription,L"\\n",L"\n");
#define SKILL_ANIMATION(field,key) field=STRINGS::StringConvertToNarrow(data->GetDataValue(key,parent?STRINGS::StringConvertToWide(parent->field):EMPTY_WSTRING).c_str())
    SKILL_ANIMATION(m_sAnimation,L"ANIMATION");
    SKILL_ANIMATION(m_sAnimationDualWield,L"ANIMATIONDW");
    SKILL_ANIMATION(m_sAnimationLoop,L"ANIMATIONLOOP");
    SKILL_ANIMATION(m_sAnimationDualWieldLoop,L"ANIMATIONDWLOOP");
    SKILL_ANIMATION(m_sAnimationLoopEnd,L"ANIMATIONLOOPEND");
#undef SKILL_ANIMATION
    m_sAnimation=STRINGS::StringUpper(m_sAnimation);
    m_sAnimationDualWield=STRINGS::StringUpper(m_sAnimationDualWield);
    m_sAnimationLoop=STRINGS::StringUpper(m_sAnimationLoop);
    m_sAnimationLoopEnd=STRINGS::StringUpper(m_sAnimationLoopEnd);
    m_sAnimationDualWieldLoop=STRINGS::StringUpper(m_sAnimationDualWieldLoop);
    m_iLevelRequired=data->GetDataValue(L"LEVEL_REQUIRED",static_cast<unsigned int>(parent?parent->m_iLevelRequired:0));
    m_bHasAnimation=(m_sAnimationDualWield!=EMPTY_STRING || m_sAnimationDualWieldLoop!=EMPTY_STRING);
    m_iManaCost=data->GetDataValue(L"MANACOST",parent?parent->m_iManaCost:0.0f);
    m_iManaCostOverTime=data->GetDataValue(L"MANACOSTOT",parent?parent->m_iManaCostOverTime:0.0f);
    m_fFindTargetAngle=data->GetDataValue(L"FINDTARGETANGLE",parent?parent->m_fFindTargetAngle:0.0f);
    m_fRange=data->GetDataValue(L"RANGE",parent?parent->m_fRange:m_fRange);
    m_iMinimumRange=data->GetDataValue(L"RANGEMIN",parent?parent->m_iMinimumRange:0.0f);
    m_fRandomRange=data->GetDataValue(L"RANDOMRANGE",parent?parent->m_fRandomRange:m_fRandomRange);
    m_iRandomRangeMinimum=data->GetDataValue(L"RANDOMRANGEMIN",parent?parent->m_iRandomRangeMinimum:0.0f);
    m_fCoolDown=static_cast<float>(data->GetDataValue(L"COOLDOWNMS",parent?static_cast<int>(ceilf(parent->m_fCoolDown*1000.0f)):0))/1000.0f;
    m_fMonsterCoolDown=static_cast<float>(data->GetDataValue(L"MONSTERCOOLDOWNMS",parent?static_cast<int>(ceilf(parent->m_fMonsterCoolDown*1000.0f)):static_cast<int>(m_fCoolDown*1000.0f)))/1000.0f;
    m_fMinimumTime=static_cast<float>(data->GetDataValue(L"MINIMUMTIMEMS",parent?static_cast<int>(ceilf(parent->m_fMinimumTime*1000.0f)):0))/1000.0f;
    m_fDurationOverride=static_cast<float>(data->GetDataValue(L"DURATIONOVERRIDEMS",parent?static_cast<int>(ceilf(parent->m_fDurationOverride*1000.0f)):0))/1000.0f;
    m_fSlowDown=static_cast<float>(data->GetDataValue(L"SLOWDOWNMS",parent?static_cast<int>(ceilf(parent->m_fSlowDown*1000.0f)):0))/1000.0f;
    m_fSpeed=data->GetDataValue(L"SPEED",parent?parent->m_fSpeed:1.0f);
    m_iChance=data->GetDataValue(L"CHANCE",static_cast<unsigned int>(parent?parent->m_iChance:100));
    m_bInterruptable=data->GetDataValue(L"INTERRUPTABLE",parent?parent->m_bInterruptable:m_bInterruptable);
    m_bContinuousLooping=data->GetDataValue(L"CONTINUOUSLOOPING",parent?parent->m_bContinuousLooping:false);
    m_bExclusive=data->GetDataValue(L"EXCLUSIVE",parent?parent->m_bExclusive:false);
    if(m_sAnimationLoop!=EMPTY_STRING && m_fDurationOverride<=0.0f)m_fDurationOverride=1.0f;
    std::vector<CDataGroup*> groups;
    for(unsigned int i=0;i<11;++i)data->GetDataGroupsMatchingName(gSKILL_EVENT_TYPE_NAMES[i],&groups);
    if(groups.empty()) {
        if(parent)
            for(unsigned int i=0;i<parent->m_eventLists.size();++i)
                for(unsigned int j=0;j<parent->m_eventLists[i]->size();++j)m_eventLists[i]->add((*parent->m_eventLists[i])[j]);
    } else
        for(unsigned int i=0;i<groups.size();++i) {
            CSkillEvent* event=new CSkillEvent(m_pSkill,this,m_pResourceManager,groups[i]);
            m_eventLists[event->m_eventType]->add(event);
            int count=groups[i]->GetDataValue(L"CLONECOUNT",0);
            for(int j=0;j<count;++j)cloneEventForSkill(event);
        }
    if(data->GetDataGroupByName(L"EFFECT",false) || data->GetDataGroupByName(L"EFFECTS",false) ||
       data->GetDataGroupByName(L"AFFIXES",false) || data->GetDataGroupByName(L"AFFIXESREMOVE",false))
        m_pSkillEffectAndAffixes=new CSkillEffectAndAffixes(m_pSkill,data,NULL);
    if(m_fDurationOverride>0.0f && m_pSkillEffectAndAffixes)m_pSkillEffectAndAffixes->setDurationOverride(m_fDurationOverride);
}
