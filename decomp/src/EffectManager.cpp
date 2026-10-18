#include "DataGroup.h"
#include "Affix.h"
#include "BaseUnit.h"
#include "Effect.h"
#include "EffectManager.h"
#include "EmptyStrings.h"
#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EffectManager.h"
#include "Affix.h"
#include "BaseUnit.h"
#include "Effect.h"
#include "ResourceManager.h"
#include "TArrayList.h"

bool CEffectManager::hasEffect(EEFFECT_TYPE type)
{
    for (unsigned int i = 0; i < 2; ++i) {
        TArrayList<CEffect*>* effects =
            &m_Effects[i];

        for (unsigned int j = 0; j < effects->size(); ++j) {
            if (*reinterpret_cast<EEFFECT_TYPE*>(
                    reinterpret_cast<char*>((*effects)[j]) + 0x1c) == type)
                return true;
        }
    }

    return false;
}

float CEffectManager::getEffectValue(EEFFECT_TYPE type, EDAMAGE_TYPES damage)
{
    const float* effectValues =
        m_EffectValues;

    if (damage == 7)
        return effectValues[type];

    float result = 0.0f;
    if (effectValues[type] != 0.0f) {
        for (unsigned int pass = 0; pass < 2; ++pass) {
            TArrayList<CEffect*>& effects =
                m_Effects[pass];

            for (unsigned int index = 0; index < effects.size(); ++index) {
                const unsigned char* effect =
                    reinterpret_cast<const unsigned char*>(effects[index]);

                if (*reinterpret_cast<const int*>(effect + 0x1c) != type)
                    continue;
                if (*reinterpret_cast<const int*>(effect + 0x14) != damage)
                    continue;

                float value =
                    *reinterpret_cast<const float*>(effect + 0xc0);
                float activation =
                    *reinterpret_cast<const float*>(effect + 0x24);
                int effectType =
                    *reinterpret_cast<const int*>(effect + 0x1c);

                if (activation != -900.0f && activation != -1000.0f &&
                    (effectType == 7 || effectType == 6 ||
                     effectType == 124 || effectType == 123))
                    value *= 0.016f;

                result += value;
            }
        }
    }

    return result;
}

float CEffectManager::getEffectValue(EEFFECT_ACTIVATION activation, EEFFECT_TYPE type, EDAMAGE_TYPES damage)
{
    struct CEffectDataView
    {
        void *m_Unknown00;
        unsigned char m_Unknown08[0x0c];
        int m_Damage;
        unsigned char m_Unknown18[4];
        int m_Type;
        unsigned char m_Unknown20[4];
        float m_Unknown24;
        unsigned char m_Unknown28[0xc0 - 0x28];
        float m_Value;
    };

    float value = 0.0f;

    if (m_EffectValues[type] == 0.0f)
        return value;

    TArrayList<CEffect*>& effects =
        m_Effects[activation];

    for (unsigned int i = 0; i < effects.size(); ++i) {
        CEffect* effect = effects[i];
        const CEffectDataView* effectData =
            reinterpret_cast<const CEffectDataView *>(effect);
        int effectType = effectData->m_Type;

        if (effectType != type)
            continue;

        if (damage != 7 && effectData->m_Damage != damage)
            continue;

        float effectValue = effectData->m_Value;

        if (effectData->m_Unknown24 != -900.0f &&
            effectData->m_Unknown24 != -1000.0f &&
            (effectType == 7 || effectType == 6 ||
             effectType == 124 || effectType == 123)) {
            effectValue *= 0.016f;
        }

        value += effectValue;
    }

    return value;
}

extern "C" CAffix* getNewAffixByNameThunk(CResourceManager*, const std::wstring&, unsigned int)
    __asm__("_ZN16CResourceManager17getNewAffixByNameERKSbIwSt11char_traitsIwESaIwEEj");

extern "C" void clearOutDescriptionsThunk(CEffectManager*)
    __asm__("_ZN14CEffectManager20clearOutDescriptionsEv");

CAffix* CEffectManager::addAffix(const std::wstring& name, unsigned int level, CBaseUnit* source, CResourceManager* resources, float scale)
{
    CAffix* affix = NULL;

    if (resources != NULL) {
        affix = getNewAffixByNameThunk(resources, name, level);
        addAffix(affix, level, source, scale);
        clearOutDescriptionsThunk(this);
    }
    return affix;
}

bool CEffectManager::removeEffect(const std::wstring& name, bool flag)
{
    extern void clearOutDescriptionsThunk(CEffectManager*)
        asm("_ZN14CEffectManager20clearOutDescriptionsEv");

    bool removed = false;
    TArrayList<CEffect*>* effectLists =
        m_Effects;

    for (int listIndex = 0; listIndex < 3; ++listIndex) {
        TArrayList<CEffect*>& effects = effectLists[listIndex];

        for (unsigned int index = 0; index < effects.size(); ++index) {
            CEffect* effect = effects[index];
            const std::wstring& effectName =
                *reinterpret_cast<const std::wstring*>(
                    reinterpret_cast<const unsigned char*>(effect) + 0x80);

            if (effectName == name) {
                if (flag && effect != NULL) {
                    delete effect;
                    effects[index] = NULL;
                }

                effects.removeAt(index);
                removed = true;
                --index;
            }
        }
    }

    if (removed)
        clearOutDescriptionsThunk(this);

    return removed;
}

float CEffectManager::getEffectValue(EEFFECT_TYPE type, const std::wstring& name)
{
    typedef TArrayList<CEffect*> EffectList;

    struct EffectLayout {
        unsigned char unknown00[0x1c];
        int effectType;
        unsigned char unknown20[4];
        float adjustment;
        unsigned char unknown28[0x58];
        std::wstring effectName;
        unsigned char unknown88[0xc0-0x88];
        float value;
    };

    float result = 0.0f;
    const float* effectValues =
        m_EffectValues;

    if (effectValues[type] != 0.0f) {
        for (unsigned int listIndex = 0; listIndex < 2; ++listIndex) {
            EffectList& effects = m_Effects[listIndex];

            for (unsigned int i = 0; i < effects.size(); ++i) {
                const EffectLayout* effect =
                    reinterpret_cast<const EffectLayout*>(effects[i]);

                if (effect->effectType == type && effect->effectName == name) {
                    float value = effect->value;

                    if (effect->adjustment != -900.0f &&
                        effect->adjustment != -1000.0f) {
                        if (type == 7 || type == 6 ||
                            type == 124 || type == 123) {
                            value *= 0.016f;
                        }
                    }

                    result += value;
                }
            }
        }
    }

    return result;
}

bool CEffectManager::hasEffect(const std::wstring& name)
{
    for (unsigned int i = 0; i < 2; ++i)
    {
        TArrayList<CEffect*>* effects =
            &m_Effects[i];

        for (unsigned int j = 0; j < effects->size(); ++j)
        {
            const std::wstring* effectName =
                reinterpret_cast<const std::wstring*>(
                    reinterpret_cast<const char*>((*effects)[j]) + 0x80);

            if (*effectName == name)
                return true;
        }
    }
    return false;
}


// Imported source candidates; historical status is not fresh acceptance.
void CEffectManager::notifyOfDeletion(CCharacter* character)
{
}

void CEffectManager::clearAllUnitReferences()
{
}

CAffix* CEffectManager::cloneAffix(CAffix* affix, unsigned int level, CBaseUnit* source, float scale)
{
    CAffix* result=NULL;
    if (affix) {
        result=new CAffix(affix, level);
        if (result) {
            result->addEffectsToEffectManager(this);
            if (scale>0.0f) result->m_fDuration=scale;
            addAffix(result,level,source,scale);
            clearOutDescriptions();
        }
    }
    return result;
}

CEffect* CEffectManager::getEffect(EEFFECT_TYPE type)
{
    for (unsigned int group = 0; group < 2; ++group)
        for (unsigned int i = 0; i < getActiveEffects(group).size(); ++i)
            if (getActiveEffects(group)[i]->m_eType == type)
                return getActiveEffects(group)[i];
    return NULL;
}

bool CEffectManager::hasEffectFromSkill(const CSkill* skill)
{
    for (unsigned int group = 0; group < 2; ++group)
        for (unsigned int i = 0; i < getActiveEffects(group).size(); ++i)
            if (getActiveEffects(group)[i]->m_pSkillOwner == skill)
                return true;
    return false;
}

void CEffectManager::getEffects(TArrayList<CEffect*>* effects)
{
    if (effects != NULL)
        for (unsigned int group = 0; group < 3; ++group)
        {
            unsigned int count = getActiveEffects(group).size();
            CEffect** data = &getActiveEffects(group)[0];
            if (data != NULL)
                for (unsigned int i = 0; i < count; ++i)
                    effects->add(data[i]);
        }
}

CAffix* CEffectManager::getAffix(const std::wstring& name)
{
    for (unsigned int i = 0; i < getAffixes().size(); ++i)
        if (getAffixes()[i]->m_sDisplayName == name)
            return getAffixes()[i];
    return NULL;
}

bool CEffectManager::hasEffect(EEFFECT_TYPE type, const std::wstring& name)
{
    for (unsigned int group = 0; group < 2; ++group)
        for (unsigned int i = 0; i < getActiveEffects(group).size(); ++i)
            if (getActiveEffects(group)[i]->m_eType == type &&
                getActiveEffects(group)[i]->m_sName == name)
                return true;
    return false;
}

CEffect* CEffectManager::getEffect(const std::wstring& name, unsigned int index)
{
    for (unsigned int group = 0; group < 2; ++group)
        for (unsigned int i = 0; i < getActiveEffects(group).size(); ++i)
            if (getActiveEffects(group)[i]->m_sName == name)
            {
                if (index == 0)
                    return getActiveEffects(group)[i];
                --index;
            }
    return NULL;
}

void CEffectManager::clearOutDescriptions()
{
    m_EffectString2E0 = EMPTY_WSTRING;
    m_EffectString2E8 = EMPTY_WSTRING;
    m_EffectString2F0 = EMPTY_WSTRING;
}

bool CEffectManager::removeEffect(CEffect* effect, bool destroy)
{
    for (unsigned int i = 0; i < getActiveEffects(effect->m_activation).size(); ++i)
    {
        CEffect* found = getActiveEffects(effect->m_activation)[i];
        if (found == effect)
        {
            if (destroy && getActiveEffects(effect->m_activation)[i] != NULL)
            {
                delete getActiveEffects(effect->m_activation)[i];
                getActiveEffects(found->m_activation)[i] = NULL;
            }
            getActiveEffects(found->m_activation).removeAt(i);
            clearOutDescriptions();
            return true;
        }
    }
    return false;
}

void CEffectManager::recalculateEffects()
{
    std::wstring* descriptions = &m_EffectString2E0;
    for (unsigned int i = 0; i < descriptions[0].size(); ++i)
        descriptions[i] = EMPTY_WSTRING;
    for (unsigned int group = 0; group < 3; ++group)
        for (unsigned int i = 0; i < getActiveEffects(group).size(); ++i)
            getActiveEffects(group)[i]->getMaxCaculatedValue();
}

void CEffectManager::clearOutAffixEffects()
{
    for (unsigned int i = 0; i < getAffixes().size(); ++i)
        getAffixes()[i]->clearEffectsFromOwner();
    clearOutDescriptions();
}

void CEffectManager::addAffixEffectsBackIn()
{
    for (unsigned int i = 0; i < getAffixes().size(); ++i)
    {
        getAffixes()[i]->clearEffectsFromOwner();
        getAffixes()[i]->addEffectsToEffectManager(this);
    }
    clearOutDescriptions();
}

void CEffectManager::updateAffixes(float elapsed)
{
    bool removed = false;
    for (unsigned int i = 0; i < getAffixes().size(); ++i)
        if (!getAffixes()[i]->updateAffixDuration(elapsed))
        {
            if (getAffixes()[i] != NULL)
            {
                delete getAffixes()[i];
                getAffixes()[i] = NULL;
            }
            getAffixes().removeAt(i);
            --i;
            removed = true;
        }
    if (removed)
    {
        calculateEffectValues();
        clearOutDescriptions();
    }
}

bool CEffectManager::deleteAffix(CAffix* affix)
{
    for (unsigned int i = 0; i < getAffixes().size(); ++i)
        if (getAffixes()[i] == affix)
        {
            getAffixes().removeAt(i);
            affix->clearEffectsFromOwner();
            delete affix;
            calculateEffectValues();
            clearOutDescriptions();
            return true;
        }
    return false;
}

CAffix* CEffectManager::addAffix(CAffix* affix, unsigned int level, CBaseUnit* source, float scale)
{
    if (affix != NULL)
    {
        if (scale > 0.0f)
            affix->m_fDuration = scale;
        if (level != static_cast<unsigned int>(-1))
            affix->setLevel(level);
        getAffixes().add(affix);
        affix->setOwner(source);
        affix->addEffectsToEffectManager(this);
        calculateEffectValues();
        clearOutDescriptions();
    }
    return affix;
}

bool CEffectManager::deleteAffix(const std::wstring& name)
{
    bool removed = false;
    for (unsigned int i = 0; i < getAffixes().size(); ++i)
        if (getAffixes()[i]->m_sDisplayName == name)
        {
            getAffixes()[i]->clearEffectsFromOwner();
            if (getAffixes()[i] != NULL)
            {
                delete getAffixes()[i];
                getAffixes()[i] = NULL;
            }
            getAffixes().removeAt(i);
            --i;
            removed = true;
        }
    if (removed)
    {
        calculateEffectValues();
        clearOutDescriptions();
    }
    return removed;
}

CEffect* CEffectManager::cloneEffect(CBaseUnit* source, CEffect* effect)
{
    if (effect->m_pAffixOwner != NULL &&
        effect->m_pAffixOwner->m_EffectManager.getObject() == this)
    {
        addNewEffect(effect);
        return effect;
    }
    CEffect* copy = new CEffect(effect);
    copy->setOwner(source, true);
    addNewEffect(copy);
    if (getOwnerReference().getObject() != NULL)
        getOwnerReference().getObject()->activateEffect(copy);
    clearOutDescriptions();
    return copy;
}

void CEffectManager::cloneEffects(CBaseUnit* source, TArrayList<CEffect*>* effects)
{
    if (effects != NULL)
    {
        for (unsigned int i = 0; i < effects->size(); ++i)
            cloneEffect(source, (*effects)[i]);
        clearOutDescriptions();
    }
}

void CEffectManager::removeNonSavedEffects()
{
    for (unsigned int group = 0; group < 3; ++group)
        for (unsigned int i = 0; i < getActiveEffects(group).size(); ++i)
            if (!getActiveEffects(group)[i]->m_flag33)
            {
                CEffect* effect = getActiveEffects(group)[i];
                if (effect->m_fValue24 != -900.0f && effect->m_fValue24 != -1000.0f)
                    effect->m_fRemainingDuration = effect->m_fValue24;
                effect->m_bDead = true;
            }
    deleteDeadEffects();
}

unsigned int CEffectManager::createEffects(CDataGroup* data, bool flag)
{
    if (data == NULL)
        return 0;
    if (data->GetGroupName().compare(L"EFFECT") == 0)
    {
        createEffect(data, flag);
        return 1;
    }
    std::vector<CDataGroup*> groups;
    unsigned int count = data->GetDataGroupsMatchingName(L"EFFECT", &groups);
    for (unsigned int i = 0; i < count; ++i)
        createEffect(groups[i], flag);
    clearOutDescriptions();
    return count;
}

#include "Character.h"

void CEffectManager::clearEffects(bool removeEffects)
{
    if (removeEffects)
        for (unsigned int group = 0; group < 3; ++group)
            for (unsigned int i = 0; i < m_Effects[group].size(); ++i)
            {
                if (m_Effects[group][i]->m_eType == static_cast<EEFFECT_TYPE>(62)) continue;
                delete m_Effects[group][i];
                m_Effects[group][i] = NULL;
                m_Effects[group].removeAt(i);
                --i;
            }
    m_Affixes.deleteAll();
    clearOutDescriptions();
    m_UnitThemes.clear();
}

void CEffectManager::calculateEffectValues()
{
    m_UnitThemes.clear();
    for (unsigned int type = 0; type < 145; ++type)
    {
        m_EffectValues[type] = 0.0f;
        for (unsigned int group = 0; group < 2; ++group)
            for (unsigned int i = 0; i < m_Effects[group].size(); ++i)
            {
                CEffect* effect = m_Effects[group][i];
                if (effect->m_eType != static_cast<EEFFECT_TYPE>(type)) continue;
                if (effect->m_fValue24 != -900.0f && effect->m_fValue24 != -1000.0f &&
                    effect->m_fRemainingDuration >= effect->m_fValue24) continue;
                if (effect->m_bDead) continue;
                if (effect->m_pUnitTheme && m_UnitThemes.find(effect->m_pUnitTheme) == -1)
                    m_UnitThemes.add(effect->m_pUnitTheme);
                float value = effect->m_fValueC0;
                if (effect->m_fValue24 != -900.0f && effect->m_fValue24 != -1000.0f &&
                    (effect->m_eType == static_cast<EEFFECT_TYPE>(7) || effect->m_eType == static_cast<EEFFECT_TYPE>(6) ||
                     effect->m_eType == static_cast<EEFFECT_TYPE>(124) || effect->m_eType == static_cast<EEFFECT_TYPE>(123)))
                    value *= 0.016f;
                m_EffectValues[type] = value + m_EffectValues[type];
            }
    }
}

CEffectManager::CEffectManager(CBaseUnit* owner)
    : m_Affixes(1), m_UnitThemes(1)
{
    m_Owner.setObject(owner);
    for (unsigned int group = 0; group < 3; ++group) m_Effects[group].setGrowBy(1);
    calculateEffectValues();
}

CEffectManager::~CEffectManager()
{
    clearEffects(false);
    m_Owner.setObject(NULL);
}



void CEffectManager::deleteDeadEffects()
{
    bool removed = false;
    for (unsigned int group = 0; group < 3; ++group)
        for (unsigned int i = 0; i < m_Effects[group].size(); ++i)
        {
            CEffect* effect = m_Effects[group][i];
            if (effect->m_fValue24 == -900.0f ||
                (effect->m_fValue24 != -1000.0f && effect->m_fRemainingDuration >= effect->m_fValue24) ||
                effect->m_bDead)
            {
                if (effect->m_name88 != EMPTY_WSTRING)
                    for (unsigned int otherGroup = 0; otherGroup < 3; ++otherGroup)
                        for (unsigned int j = 0; j < m_Effects[otherGroup].size(); ++j)
                        {
                            CEffect* other = m_Effects[otherGroup][j];
                            if (other->m_sName != effect->m_name88) continue;
                            if (other->m_fValue24 != -900.0f && other->m_fValue24 != -1000.0f)
                                other->m_fRemainingDuration = other->m_fValue24;
                            other->m_bDead = true;
                        }
                if (!m_Effects[group][i]->m_pAffixOwner)
                {
                    delete m_Effects[group][i];
                    m_Effects[group][i] = NULL;
                }
                m_Effects[group].removeAt(i);
                --i;
                removed = true;
            }
        }
    if (removed) clearOutDescriptions();
}

void CEffectManager::transferEffects(CCharacter* target, EEFFECT_ACTIVATION activation, EEFFECT_TYPE type)
{
    TArrayList<CEffect*>& effects = m_Effects[activation];
    for (unsigned int i = 0; i < effects.size(); ++i)
        if (effects[i]->m_eType == type &&
            target->isEffectValidForUnit(target, m_Owner.getObject(), effects[i]))
        {
            CEffect* effect = new CEffect(type, false, EFFECT_ACTIVATION_DYNAMIC,
                                          effects[i]->m_fValue24, effects[i]->m_fValueC0, 0.0f, false);
            effect->m_flag33 = false;
            effect->m_flag31 = effects[i]->m_flag31;
            effect->m_pUnitTheme = effects[i]->m_pUnitTheme;
            target->applyEffectOnUnit(target, m_Owner.getObject(), effect);
            delete effect;
            clearOutDescriptions();
        }
}

CEffect* CEffectManager::addNewEffect(CEffect* effect)
{
    if (effect->m_flag31)
        for (unsigned int group = 0; group < 3; ++group)
            for (unsigned int i = 0; i < m_Effects[group].size(); ++i)
            {
                CEffect* previous = m_Effects[group][i];
                if (previous->m_sName == effect->m_sName && previous->m_eType == effect->m_eType &&
                    (previous->m_fValue24 == -900.0f || previous->m_fValue24 == -1000.0f ||
                     !(previous->m_fRemainingDuration >= previous->m_fValue24)) && !previous->m_bDead)
                {
                    if (previous->m_fValue24 != -900.0f && previous->m_fValue24 != -1000.0f)
                        previous->m_fRemainingDuration = previous->m_fValue24;
                    previous->m_bDead = true;
                }
            }
    if (m_Owner.getObject() && !effect->m_Owner.getObject())
        effect->setOwner(m_Owner.getObject(), true);
    m_Effects[effect->m_activation].add(effect);
    clearOutDescriptions();
    return effect;
}
