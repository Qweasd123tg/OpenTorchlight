#include "SkillEffectAndAffixes.h"
#include "BaseUnit.h"
#include "Effect.h"
#include "EmptyStrings.h"

void CSkillEffectAndAffixes::setDurationOverride(float duration)
{
    for (unsigned int i = 0; i < m_affixData.size(); ++i)
        m_affixData[i]->m_durationOverride = duration;
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        for (unsigned int j = 0; j < m_effectData[i]->m_effects.size(); ++j)
            // The original uses the outer index for this inner access.
            if (!m_effectData[i]->m_effects[i]->m_bFlag28)
                m_effectData[i]->m_effects[i]->m_fValue24 = duration;
}

bool CSkillEffectAndAffixes::effectsTargetEnemy(CBaseUnit* unit)
{
    if (unit != NULL)
        for (unsigned int i = 0; i < m_affixData.size(); ++i)
            if (unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_affixData[i]->m_unitType)) &&
                m_affixData[i]->m_targetType == 0)
                return true;
    return false;
}

std::wstring CSkillEffectAndAffixes::getPortalSkillName()
{
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        for (unsigned int j = 0; j < m_effectData[i]->m_effects.size(); ++j)
            if (m_effectData[i]->m_effects[j]->m_eType == static_cast<EEFFECT_TYPE>(0x71))
                return m_effectData[i]->m_effects[j]->m_sName;
    return EMPTY_WSTRING;
}

void CSkillEffectAndAffixes::appendName(const std::wstring& name)
{
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        if (m_effectData[i] != NULL)
            for (unsigned int j = 0; j < m_effectData[i]->m_effects.size(); ++j)
                m_effectData[i]->m_effects[j]->m_sName =
                    m_effectData[i]->m_effects[j]->m_sName + name;
}

#include "Affix.h"
#include "ResourceManager.h"
#include <algorithm>

void CSkillEffectAndAffixes::addMinAndMaxValuesOfAnEffect(CResourceManager* resources, unsigned int type, float& minimum, float& maximum)
{
    for (unsigned int i = 0; i < m_displayAffixes.size(); ++i)
        for (unsigned int j = 0; j < m_displayAffixes[i]->m_Effects.size(); ++j)
        {
            CEffect* effect = m_displayAffixes[i]->m_Effects[j];
            if (effect && effect->m_eType == static_cast<EEFFECT_TYPE>(type))
            {
                minimum = effect->getMinCaculatedValue() + minimum;
                maximum = effect->getMaxCaculatedValue() + maximum;
            }
        }
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        for (unsigned int j = 0; j < m_effectData[i]->m_effects.size(); ++j)
        {
            CEffect* effect = m_effectData[i]->m_effects[j];
            if (effect && effect->m_eType == static_cast<EEFFECT_TYPE>(type))
            {
                minimum = effect->getMinCaculatedValue() + minimum;
                maximum = effect->getMaxCaculatedValue() + maximum;
            }
        }
}

void CSkillEffectAndAffixes::createAffixesForDisplay(CResourceManager* resources)
{
    if (m_displayAffixes.size() || !m_affixData.size()) return;
    for (unsigned int i = 0; i < m_affixData.size(); ++i)
    {
        CAffix* affix = resources->getNewAffixByName(m_affixData[i]->m_name, m_affixData[i]->m_value18);
        if (affix)
        {
            affix->setSkillOwner(m_pSkill);
            if (!affix->m_bHasDuration && m_affixData[i]->m_durationOverride > 0.0f)
                affix->m_fDuration = m_affixData[i]->m_durationOverride;
            m_displayAffixes.add(affix);
        }
    }
}

bool CSkillEffectAndAffixes::isDamaging()
{
    for (unsigned int i = 0; i < m_displayAffixes.size(); ++i)
        if (m_displayAffixes[i]->effectExists(static_cast<EEFFECT_TYPE>(52)) ||
            m_displayAffixes[i]->effectExists(static_cast<EEFFECT_TYPE>(7)) ||
            m_displayAffixes[i]->effectExists(static_cast<EEFFECT_TYPE>(124))) return true;
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        for (unsigned int j = 0; j < m_effectData[i]->m_effects.size(); ++j)
            if (m_effectData[i]->m_effects[j]->m_eType == static_cast<EEFFECT_TYPE>(52) ||
                m_effectData[i]->m_effects[j]->m_eType == static_cast<EEFFECT_TYPE>(7) ||
                m_effectData[i]->m_effects[j]->m_eType == static_cast<EEFFECT_TYPE>(124)) return true;
    return false;
}

void CSkillEffectAndAffixes::fillOutStatBonuses(float (&values)[6], bool takeHighest)
{
    if (!m_displayAffixes.size()) getDisplayStats();
    for (unsigned int i = 0; i < m_displayAffixes.size(); ++i) m_displayAffixes[i]->fillOutStatBonuses(values, takeHighest);
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        for (unsigned int j = 0; j < m_effectData[i]->m_effects.size(); ++j)
            for (unsigned int stat = 0; stat < 6; ++stat)
            {
                CEffect* effect = m_effectData[i]->m_effects[j];
                int index = effect->m_statModifiers.find(static_cast<EEFFECT_STAT_MODIFIERS>(stat));
                float value = index == -1 ? 0.0f : effect->m_statModifierValues[index];
                if (takeHighest) values[stat] = std::max(values[stat], value);
                else values[stat] = value;
            }
}

CSkillEffectAndAffixes::~CSkillEffectAndAffixes()
{
    m_displayAffixes.deleteAll();
    m_affixNames.clear();
    m_effectNames.clear();
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
        if (m_effectData[i]->m_flag10) m_effectData[i]->m_effects.deleteAll();
    m_effectData.deleteAll();
    m_affixData.deleteAll();
}

#include "EffectManager.h"
#include "MasterResourceManager.h"
#include "Skill.h"

bool CSkillEffectAndAffixes::removeAffixesAndEffects(CBaseUnit* unit, CCharacter*)
{
    if (!unit || !unit->m_pEffectManager)
        return false;
    bool removed = false;
    for (unsigned int i = 0; i < m_affixNames.size(); ++i)
        if (unit->m_pEffectManager->deleteAffix(m_affixNames[i]))
            removed = true;
    for (unsigned int i = 0; i < m_effectNames.size(); ++i)
        if (unit->m_pEffectManager->removeEffect(m_effectNames[i], true))
            removed = true;
    return removed;
}

std::wstring CSkillEffectAndAffixes::getDisplayStats()
{
    if (!m_pSkill)
        return EMPTY_WSTRING;
    createAffixesForDisplay(m_pSkill->m_resources);
    std::wstring result = m_name;
    CMasterResourceManager::getSingleton();
    for (unsigned int i = 0; i < m_displayAffixes.size(); ++i)
    {
        std::wstring text = m_displayAffixes[i]->getDisplayStats(static_cast<unsigned int>(-1));
        if (result != EMPTY_WSTRING && text != EMPTY_WSTRING)
            result += L"\n";
        result += text;
    }
    std::wstring effects = EMPTY_WSTRING;
    for (unsigned int i = 0; i < m_effectData.size(); ++i)
    {
        std::wstring group = EMPTY_WSTRING;
        CSkillEffectData* data = m_effectData[i];
        if (data)
            for (unsigned int j = 0; j < data->m_effects.size(); ++j)
            {
                std::wstring text = data->m_effects[j]->getDisplayStats(static_cast<unsigned int>(-1), false);
                if (group != EMPTY_WSTRING && text != EMPTY_WSTRING)
                    group += L"\n";
                group += text;
            }
        if (effects != EMPTY_WSTRING && group != EMPTY_WSTRING)
            effects += L"\n";
        effects += group;
    }
    if (result != EMPTY_WSTRING && effects != EMPTY_WSTRING)
        result += L"\n";
    result += effects;
    return result;
}

#include "Character.h"
#include "Skill.h"
#include "Level.h"

bool CSkillEffectAndAffixes::canAffixesAndEffectsBeAppliedToUnit(CBaseUnit* unit,CCharacter* source)
{
    CCharacter* character=unit->m_eBaseUnitType==static_cast<EBASEUNIT_TYPE>(0)?static_cast<CCharacter*>(unit):NULL;
    for(unsigned int i=0;i<m_effectData.size();++i) {
        if(!unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_effectData[i]->m_value30)))
            return false;
        int target=m_effectData[i]->m_value34;
        if(target==1) {
            if(character && character!=source)return false;
        } else if(target==2) {
            if(!character || !source || source!=character->m_pMaster)return false;
        } else if(target==0) {
            if(!source)return false;
            if(character) {
                EAlignment alignment=character->alignment();
                EAlignment sourceAlignment=source->alignment();
                if(alignment==sourceAlignment)return false;
            }
        }
        for(unsigned int j=0;j<m_effectData[i]->m_effects.size();++j)
            if(!unit->isEffectValidForUnit(source,source,m_effectData[i]->m_effects[j]))
                return false;
    }
    for(unsigned int i=0;i<m_affixData.size();++i) {
        if(!unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_affixData[i]->m_unitType)))
            return false;
        int target=m_affixData[i]->m_targetType;
        if(target==1) {
            if(!source || (character && character!=source))return false;
        } else if(target==2) {
            if(!character || !source || source!=character->m_pMaster)return false;
        } else if(target==0) {
            if(!source)return false;
            if(character) {
                EAlignment alignment=character->alignment();
                EAlignment sourceAlignment=source->alignment();
                if(alignment==sourceAlignment)return false;
            }
        }
    }
    return true;
}

bool CSkillEffectAndAffixes::applyAffixesAndEffects(CBaseUnit* unit,CCharacter* source,const Ogre::Vector3* direction,bool ignoreTarget)
{
    if(!unit)return false;
    bool result=false;
    bool listenerAdded=false;
    CCharacter* character=unit->m_eBaseUnitType==static_cast<EBASEUNIT_TYPE>(0)?static_cast<CCharacter*>(unit):NULL;
    for(unsigned int i=0;i<m_affixData.size();++i) {
        if(!unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_affixData[i]->m_unitType)))continue;
        if(!ignoreTarget) {
            int target=m_affixData[i]->m_targetType;
            if(target==1) {
                if(!source || (character && character!=source))continue;
            } else if(target==2) {
                if(!character || !source || source!=character->m_pMaster)continue;
            } else if(target==0) {
                if(source && character) {
                    EAlignment alignment=character->alignment();
                    EAlignment sourceAlignment=source->alignment();
                    if(alignment==sourceAlignment)continue;
                }
            } else if(target==4) {
                if(source && character && (character->isEnemy(source) || character==source))continue;
            }
        }
        CAffix* affix=source->getResourceManager()->getNewAffixByName(m_affixData[i]->m_name,m_affixData[i]->m_value18);
        if(affix) {
            affix->setSkillOwner(m_pSkill);
            affix->setLevel(m_affixData[i]->m_value18);
            affix->setDirection(direction);
            if(!affix->m_bHasDuration && m_affixData[i]->m_durationOverride>0.0f)
                affix->m_fDuration=m_affixData[i]->m_durationOverride;
            unit->addAffix(affix,m_affixData[i]->m_value18,source,-1.0f);
            if(affix->effectHasDuration(static_cast<EEFFECT_TYPE>(0x34)) ||
               affix->effectHasDuration(static_cast<EEFFECT_TYPE>(7)) ||
               affix->effectHasDuration(static_cast<EEFFECT_TYPE>(0x7c))) {
                CLevel* level=unit->getResourceManager()?unit->getResourceManager()->getLevel():NULL;
                level->addListenerToUnit(unit,static_cast<iUnitObserver*>(m_pSkill));
                listenerAdded=true;
            }
            result=true;
        }
    }
    for(unsigned int i=0;i<m_effectData.size();++i) {
        if(!unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(m_effectData[i]->m_value30)))continue;
        if(!ignoreTarget) {
            int target=m_effectData[i]->m_value34;
            if(target==1) {
                if(character && character!=source)continue;
            } else if(target==2) {
                if(!character || !source || source!=character->m_pMaster)continue;
            } else if(target==0) {
                if(source && character) {
                    EAlignment alignment=character->alignment();
                    EAlignment sourceAlignment=source->alignment();
                    if(alignment==sourceAlignment)continue;
                }
            } else if(target==4) {
                if(source && character && (character->isEnemy(source) || character==source))continue;
            }
        }
        for(unsigned int j=0;j<m_effectData[i]->m_effects.size();++j) {
            if(direction && unit->isEffectValidForUnit(source,source,m_effectData[i]->m_effects[j]))
                m_effectData[i]->m_effects[j]->m_direction=*direction;
            m_effectData[i]->m_effects[j]->setSkillOwner(m_pSkill);
            m_effectData[i]->m_effects[j]->setOwner(source,true);
            if(unit->applyEffectOnUnit(source,source,m_effectData[i]->m_effects[j])) {
                if(!listenerAdded && m_effectData[i]->m_effects[j]->m_fValue24>0.0f &&
                   (m_effectData[i]->m_effects[j]->m_eType==static_cast<EEFFECT_TYPE>(0x34) ||
                    m_effectData[i]->m_effects[j]->m_eType==static_cast<EEFFECT_TYPE>(7) ||
                    m_effectData[i]->m_effects[j]->m_eType==static_cast<EEFFECT_TYPE>(0x7c))) {
                    CLevel* level=unit->getResourceManager()?unit->getResourceManager()->getLevel():NULL;
                    level->addListenerToUnit(unit,static_cast<iUnitObserver*>(m_pSkill));
                    listenerAdded=true;
                }
                result=true;
            }
        }
    }
    return result;
}

#include "DataGroup.h"
#include "DataValue.h"
#include "MasterResourceManager.h"
#include "Hierarchy.h"
#include "StringUtilities.h"
#include "SkillDefines.h"
#include <vector>

CSkillEffectAndAffixes::CSkillEffectAndAffixes(CSkill* skill,CDataGroup* data,CSkillEffectAndAffixes* source)
    : m_pSkill(skill),m_affixData(10),m_effectData(10),m_displayAffixes(10),m_affixNames(10),m_effectNames(10)
{
    std::wstring instance=STRINGS::GetValueAsWString(static_cast<unsigned int>(g_iTotalCountOfObjects));
    std::wstring targetType;
    std::wstring target;
    std::wstring defaultTarget=STRINGS::StringUpper(data->GetDataValue(L"TARGET",L""));
    if(defaultTarget.empty()) {
        switch(skill->getTargetType()) {
        case 2:defaultTarget=gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES[skill->m_iTargetAlignment==1?4:0];break;
        case 3:case 10:defaultTarget=gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES[1];break;
        case 4:defaultTarget=gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES[3];break;
        case 9:defaultTarget=gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES[2];break;
        }
    }
    int defaultTargetIndex=STRINGS::getStringIndex(defaultTarget,gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES,5,0,false);
    CDataGroup* effects=data;
    unsigned int effectUnitType=0;
    if(data->GetDataGroupByName(L"EFFECTS",false)) {
        effects=data->GetDataGroupByName(L"EFFECTS",false);
        m_name=effects->GetDataValue(L"ADDITIONALDESCRIPTION",m_name);
        targetType=effects->GetDataValue(L"TARGETTYPE",targetType);
        target=STRINGS::StringUpper(effects->GetDataValue(L"TARGET",target));
        if(targetType!=EMPTY_WSTRING)
            effectUnitType=CMasterResourceManager::getSingleton()->m_pHierarchy->getTypeIDByName(targetType);
        if(target!=EMPTY_WSTRING)
            for(unsigned int i=0;i<5;++i)
                if(target==gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES[i])defaultTargetIndex=i;
    }
    std::vector<CDataGroup*> effectGroups;
    effects->GetDataGroupsMatchingName(L"EFFECT",&effectGroups);
    if(!effectGroups.empty()) {
        CSkillEffectData* value=new CSkillEffectData;
        value->m_effects.setGrowBy(10);
        value->m_value30=effectUnitType;
        value->m_value34=defaultTargetIndex;
        value->m_flag10=true;
        for(unsigned int i=0;i<effectGroups.size();++i)
            value->m_effects.add(new CEffect(effectGroups[i],NULL));
        m_effectData.add(value);
    } else if(source)
        for(unsigned int i=0;i<source->m_effectData.size();++i) {
            CSkillEffectData* value=new CSkillEffectData;
            value->m_flag10=false;
            value->m_effects.setGrowBy(10);
            value->m_value30=source->m_effectData[i]->m_value30;
            value->m_value34=source->m_effectData[i]->m_value34;
            for(unsigned int j=0;j<source->m_effectData[i]->m_effects.size();++j)
                value->m_effects.add(source->m_effectData[i]->m_effects[j]);
            m_effectData.add(value);
        }
    std::vector<CDataGroup*> affixGroups;
    data->GetDataGroupsMatchingName(L"AFFIXES",&affixGroups);
    for(unsigned int i=0;i<affixGroups.size();++i) {
        unsigned int level=affixGroups[i]->GetDataValue(L"AFFIXLEVEL",1);
        float duration=affixGroups[i]->GetDataValue(L"DURATION",-1.0f);
        targetType=affixGroups[i]->GetDataValue(L"TARGETTYPE",EMPTY_WSTRING);
        m_name=affixGroups[i]->GetDataValue(L"ADDITIONALDESCRIPTION",m_name);
        unsigned int unitType=0;
        if(targetType!=EMPTY_WSTRING)
            unitType=CMasterResourceManager::getSingleton()->m_pHierarchy->getTypeIDByName(targetType);
        target=STRINGS::StringUpper(affixGroups[i]->GetDataValue(L"TARGET",EMPTY_WSTRING));
        int targetIndex=0;
        if(target!=EMPTY_WSTRING)
            for(unsigned int j=0;j<5;++j)
                if(target==gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES[j])targetIndex=j;
        for(unsigned int j=0;j<affixGroups[i]->GetNumberOfDataValues();++j) {
            CDataValue* dataValue=affixGroups[i]->GetDataValue(j);
            if((dataValue->GetValueType()==CDataValue::DATAVALUE_TRANSLATE || dataValue->GetValueType()==CDataValue::DATAVALUE_STRING) &&
               dataValue->GetDataValueName()==L"AFFIX") {
                CSkillAffixData* value=new CSkillAffixData;
                value->m_name=dataValue->GetValueString(true);
                value->m_value18=level;
                value->m_durationOverride=duration;
                value->m_targetType=targetIndex;
                value->m_unitType=unitType;
                m_affixData.add(value);
            }
        }
    }
    if(m_affixData.size()==0 && source)
        for(unsigned int i=0;i<source->m_affixData.size();++i) {
            CSkillAffixData* value=new CSkillAffixData;
            value->m_durationOverride=-1.0f;
            value->m_name=source->m_affixData[i]->m_name;
            value->m_value18=source->m_affixData[i]->m_value18;
            value->m_unitType=source->m_affixData[i]->m_unitType;
            value->m_targetType=source->m_affixData[i]->m_targetType;
            m_affixData.add(value);
        }
    CDataGroup* removeAffixes=data->GetDataGroupByName(L"AFFIXESREMOVE",false);
    CDataGroup* removeEffects=data->GetDataGroupByName(L"EFFECTSREMOVE",false);
    if(removeAffixes) {
        m_name=removeAffixes->GetDataValue(L"ADDITIONALDESCRIPTION",m_name);
        for(unsigned int i=0;i<removeAffixes->GetNumberOfDataValues();++i) {
            CDataValue* value=removeAffixes->GetDataValue(i);
            if(value->GetValueType()==CDataValue::DATAVALUE_TRANSLATE || value->GetValueType()==CDataValue::DATAVALUE_STRING)
                m_affixNames.add(value->GetValueString(true));
        }
    }
    if(removeEffects) {
        m_name=removeEffects->GetDataValue(L"ADDITIONALDESCRIPTION",m_name);
        for(unsigned int i=0;i<removeEffects->GetNumberOfDataValues();++i) {
            CDataValue* value=removeEffects->GetDataValue(i);
            if(value->GetValueType()==CDataValue::DATAVALUE_TRANSLATE || value->GetValueType()==CDataValue::DATAVALUE_STRING)
                m_effectNames.add(value->GetValueString(true));
        }
    }
    m_name=STRINGS::replaceWString(m_name,L"\\n",L"\n");
    createAffixesForDisplay(m_pSkill->m_resources);
}
