#include "Affix.h"
#include "BaseUnit.h"
#include "Effect.h"
#include "EffectManager.h"
#include "EmptyStrings.h"
#include "Particle.h"
#include "ResourceManager.h"
#include "Skill.h"


// Imported source candidates; historical status is not fresh acceptance.
float CEffect::getMaxCaculatedValue()
{
    return calculateBaseValue(static_cast<ECALCULATETYPES>(1));
}

float CEffect::getMinCaculatedValue()
{
    return calculateBaseValue(static_cast<ECALCULATETYPES>(2));
}

void CEffect::playFX(CResourceManager* manager, const Ogre::Vector3& position)
{
    if (!m_particle) {
        m_particle=manager->createParticle(m_particleName.c_str());
        if (m_particle) {
            m_particle->setPosition(position);
            m_particle->Start();
        }
    }
}

bool CEffect::fxShouldPlay()
{
    if (m_particle && m_particle->m_pParticleCache) return false;
    return m_particleName != EMPTY_WSTRING;
}

#include "Character.h"
#include "Graph.h"
#include "GraphManager.h"
#include "ParticlePreloader.h"
#include "StringTranslate.h"
#include "Equipment.h"
#include "Inventory.h"
#include "Utilities.h"
#include <algorithm>

void CEffect::initValues()
{
    m_particleName = EMPTY_WSTRING;
    m_name90 = EMPTY_WSTRING;
    m_pUnitTheme = NULL;
    m_resources = NULL;
    m_fValueC0 = 0.0f;
    m_flag37 = false;
    for (unsigned int i = 0; i < 4; ++i)
    {
        m_values[i] = 0.0f;
        m_graphs[i] = NULL;
    }
    m_useOwnerLevel = false;
    m_showStats = true;
    m_pSkillOwner.setObject(NULL);
    m_statModifiers.clear();
    m_statModifierValues.clear();
    m_pAffixOwner = NULL;
    m_particle = NULL;
    m_value2C = 0;
    m_fRemainingDuration = 0.0f;
    m_value3C = 100;
    m_value40 = 0;
    m_value44 = 0;
    m_name78 = EMPTY_WSTRING;
    m_sName = EMPTY_WSTRING;
    m_name88 = EMPTY_WSTRING;
    m_Owner.setObject(NULL);
    m_sourceCharacter.setObject(NULL);
    m_flag31 = 0;
    m_padding32 = 0;
    m_flag33 = false;
    m_direction = Ogre::Vector3::ZERO;
    m_eDamageType = DAMAGE_MAGICAL;
}

float CEffect::value(EEFFECT_VALUES index)
{
    if (m_graphs[index])
        return m_graphs[index]->getValue(static_cast<float>(m_iLevel), 0) *
            (m_values[index] / 100.0f);
    return m_values[index];
}

void CEffect::setOwner(CBaseUnit* owner, bool recalculate)
{
    CBaseUnit* previous = m_Owner.getObject();
    if (previous && previous->getResourceManager() && previous->getResourceManager()->getLevel())
        m_resources = previous->getResourceManager();
    m_Owner.setObject(owner);
    m_sourceCharacter.setObject(dynamic_cast<CCharacter*>(owner));
    if (m_useOwnerLevel && owner && recalculate)
    {
        m_iLevel = owner->m_iUnitLevel;
        if (m_iLevel == static_cast<unsigned int>(-1) || m_iLevel >= 1001)
            m_iLevel = 0;
    }
    if (recalculate)
        calculateBaseValue(static_cast<ECALCULATETYPES>(0));
}

void CEffect::setSkillOwner(CSkill* owner)
{
    m_pSkillOwner.setObject(owner);
    if (owner)
    {
        if (!m_Owner.getObject())
            setOwner(owner->m_pOwner, true);
        m_resources = owner->m_resources;
    }
}

void CEffect::setAffixOwner(CAffix* owner)
{
    m_pAffixOwner = owner;
    if (owner && !m_useOwnerLevel)
    {
        m_iLevel = owner->m_uiLevel;
        if (m_iLevel == static_cast<unsigned int>(-1) || m_iLevel >= 1001)
            m_iLevel = 0;
    }
    calculateBaseValue(static_cast<ECALCULATETYPES>(0));
}

CEffect::~CEffect()
{
    if (m_pAffixOwner)
    {
        m_pAffixOwner->effectDeleted(this);
        m_pAffixOwner = NULL;
    }
    if (m_particle)
    {
        delete m_particle;
        m_particle = NULL;
    }
    setOwner(NULL, false);
}

CEffect::CEffect(EEFFECT_TYPE type, bool flag, EEFFECT_ACTIVATION activation,
                 float duration, float amount, float value38, bool graphsLoaded)
    : m_iLevel(0), m_eType(type), m_activation(activation), m_fValue24(duration),
      m_flag30(flag), m_bDead(false), m_showStats(true), m_useOwnerLevel(false),
      m_flag37(graphsLoaded), m_value38(value38), m_statModifiers(10),
      m_statModifierValues(10), m_resources(NULL), m_pUnitTheme(NULL)
{
    initValues();
    m_values[0] = amount;
    calculateBaseValue(static_cast<ECALCULATETYPES>(0));
    calculateBaseValue(static_cast<ECALCULATETYPES>(0));
}

void CEffect::clone(const CEffect* source)
{
    for (unsigned int i = 0; i < 4; ++i)
    {
        m_values[i] = source->m_values[i];
        m_graphs[i] = source->m_graphs[i];
    }
    m_statModifiers.clear();
    m_statModifierValues.clear();
    for (unsigned int i = 0; i < source->m_statModifiers.size(); ++i)
    {
        m_statModifiers.add(source->m_statModifiers[i]);
        m_statModifierValues.add(source->m_statModifierValues[i]);
    }
    m_flag37 = source->m_flag37;
    m_useOwnerLevel = source->m_useOwnerLevel;
    m_pUnitTheme = source->m_pUnitTheme;
    m_showStats = source->m_showStats;
    m_pSkillOwner.setObject(source->m_pSkillOwner.getObject());
    m_flag33 = source->m_flag33;
    m_eType = source->m_eType;
    m_activation = source->m_activation;
    m_fValue24 = source->m_fValue24;
    m_bFlag28 = source->m_bFlag28;
    m_value2C = source->m_value2C;
    m_flag30 = source->m_flag30;
    m_value38 = source->m_value38;
    m_value3C = source->m_value3C;
    m_value40 = source->m_value40;
    m_value44 = source->m_value44;
    m_fRemainingDuration = 0.0f;
    m_name78 = source->m_name78;
    m_sName = source->m_sName;
    m_name88 = source->m_name88;
    m_flag31 = source->m_flag31;
    m_direction = source->m_direction;
    m_eDamageType = source->m_eDamageType;
    m_padding32 = source->m_padding32;
    m_particleName = source->m_particleName;
    m_name90 = source->m_name90;
    m_pAffixOwner = NULL;
    m_iLevel = source->m_iLevel;
    setOwner(source->m_Owner.getObject(), true);
}

CEffect::CEffect(const CEffect* source)
    : m_iLevel(0), m_eType(static_cast<EEFFECT_TYPE>(7)),
      m_activation(EFFECT_ACTIVATION_DYNAMIC), m_fValue24(-900.0f),
      m_flag30(true), m_bDead(false), m_showStats(true), m_useOwnerLevel(false),
      m_value38(1.0f), m_particle(NULL), m_statModifiers(10),
      m_statModifierValues(10), m_resources(NULL)
{
    initValues();
    clone(source);
    calculateBaseValue(static_cast<ECALCULATETYPES>(0));
}

CEffectDisplayValues CEffect::getVisualCalculatedValues(unsigned int level, bool current)
{
    if (level != m_iLevel && level != static_cast<unsigned int>(-1))
    {
        m_iLevel = level >= 1001 ? 0 : level;
        calculateBaseValue(static_cast<ECALCULATETYPES>(0));
    }
    float maximum = current ? m_fValueC0 : calculateBaseValue(static_cast<ECALCULATETYPES>(1));
    float minimum = current ? m_fValueC0 : calculateBaseValue(static_cast<ECALCULATETYPES>(2));
    bool scaled = m_fValue24 != -900.0f && m_fValue24 != -1000.0f;
    if (scaled && (m_eType == 6 || m_eType == 7 || m_eType == 123 || m_eType == 124))
    {
        maximum = maximum * m_fValue24 * 0.016f;
        minimum = minimum * m_fValue24 * 0.016f;
    }
    CEffectDisplayValues result;
    result.m_duration = m_fValue24;
    result.m_minimum = minimum;
    result.m_maximum = maximum;
    result.m_secondaryMinimum = m_reflectionMinimum;
    result.m_secondaryMaximum = m_reflectionMaximum;
    result.m_value24 = 0;
    result.m_scaled = scaled;
    result.m_effectType = m_eType;
    result.m_effect = this;
    return result;
}

std::wstring CEffect::getDisplayStats(unsigned int level, bool current)
{
    if (!m_showStats)
        return EMPTY_WSTRING;
    CEffectDisplayValues values = getVisualCalculatedValues(level, current);
    return getDisplayStats(values);
}

void CEffect::setGraphs(std::wstring name)
{
    m_name90 = name;
    for (unsigned int i = 0; i < 4; ++i)
    {
        if (!m_flag37)
        {
            std::wstring graph = gEFFECT_TYPE_GRAPHS[m_eType][i];
            if (m_name90 != EMPTY_WSTRING)
                graph = m_name90;
            m_graphs[i] = graph.empty() ? NULL : CGraphManager::getSingleton()->getGraph(graph);
            m_flag37 = true;
        }
    }
}

void CEffect::setFX(const std::wstring& name)
{
    m_particleName = name;
    if (!m_particleName.empty() &&
        (m_particleName.find(L"/") != std::wstring::npos ||
         m_particleName.find(L"\\") != std::wstring::npos))
        CParticlePreloader::getSingleton()->LoadParticle(m_particleName);
}

std::wstring CEffect::getDamageTypeDisplayString(EDAMAGE_TYPES type)
{
    std::wstring result = EMPTY_WSTRING;
    switch (type)
    {
    case DAMAGE_PHYSICAL:
        result = L"";
        break;
    case DAMAGE_MAGICAL:
        {
            static std::wstring g_Magical;
            if (g_Magical.empty())
                g_Magical = CStringTranslate::getSinglton()->getTranslateString(L"Magical");
            result = g_Magical;
        }
        break;
    case DAMAGE_FIRE:
        {
            static std::wstring g_Fire;
            if (g_Fire.empty())
                g_Fire = CStringTranslate::getSinglton()->getTranslateString(L"Fire");
            result = g_Fire;
        }
        break;
    case DAMAGE_ICE:
        {
            static std::wstring g_Ice;
            if (g_Ice.empty())
                g_Ice = CStringTranslate::getSinglton()->getTranslateString(L"Ice");
            result = g_Ice;
        }
        break;
    case DAMAGE_ELECTRIC:
        {
            static std::wstring g_Electric;
            if (g_Electric.empty())
                g_Electric = CStringTranslate::getSinglton()->getTranslateString(L"Electric");
            result = g_Electric;
        }
        break;
    case DAMAGE_POISON:
        {
            static std::wstring g_Poison;
            if (g_Poison.empty())
                g_Poison = CStringTranslate::getSinglton()->getTranslateString(L"Poison");
            result = g_Poison;
        }
        break;
    case DAMAGE_ALL:
        {
            static std::wstring g_All;
            if (g_All.empty())
                g_All = CStringTranslate::getSinglton()->getTranslateString(L"Physical & Elemental");
            result = g_All;
        }
        break;
    default:
        break;
    }
    return result;
}

inline float CEffect::modifyEffectsByCharacter(CCharacter* character)
{
    if (!m_statModifiers.size())
        return 1.0f;
    if (!character)
    {
        CEquipment* equipment = dynamic_cast<CEquipment*>(m_Owner.getObject());
        if (equipment && equipment->m_pInventory)
            character = equipment->m_pInventory->m_pPositionableObject;
    }
    if (!character)
        return 1.0f;
    float result = 1.0f;
    for (unsigned int i = 0; i < m_statModifiers.size(); ++i)
    {
        switch (m_statModifiers[i])
        {
        case 0: result += (static_cast<float>(character->strength()) / 100.0f) * m_statModifierValues[i]; break;
        case 1: result += (static_cast<float>(character->dexterity()) / 100.0f) * m_statModifierValues[i]; break;
        case 2: result += (static_cast<float>(character->defense()) / 100.0f) * m_statModifierValues[i]; break;
        case 3: result += (static_cast<float>(character->magic()) / 100.0f) * m_statModifierValues[i]; break;
        case 4: result += std::max(static_cast<float>(m_iLevel), 1.0f) * m_statModifierValues[i]; break;
        case 5: result += std::max(static_cast<float>(character->m_iUnitLevel), 1.0f) * m_statModifierValues[i]; break;
        }
    }
    return result;
}

float CEffect::calculateBaseValue(ECALCULATETYPES mode)
{
    if ((!m_Owner.getObject() || !m_sourceCharacter.getObject()) && m_pSkillOwner.getObject())
    {
        CSkill* skill = m_pSkillOwner.getObject();
        m_Owner.setObject(skill->m_pOwner);
        m_sourceCharacter.setObject(m_pSkillOwner.getObject()->getOwnerCharacter());
    }
    float first = m_values[0];
    float second = m_values[1];
    if (second == 0.0f)
        second = first;
    float amount = first;
    if (mode == 1)
        amount = std::max(first, second);
    else if (mode == 2)
        amount = std::min(first, second);
    else if (mode == 0)
        amount = UTILITIES::randomBetweenVolatile(std::min(first, second), std::max(first, second));
    if (m_graphs[0])
    {
        float graph = m_graphs[0]->getValue(static_cast<float>(m_iLevel), 0);
        m_fValueC0 = (amount / 100.0f) * graph * modifyEffectsByCharacter(m_sourceCharacter.getObject());
    }
    else
        m_fValueC0 = amount * modifyEffectsByCharacter(m_sourceCharacter.getObject());
    return m_fValueC0;
}

#include "StringUtilities.h"
#include "SkillParser.h"
#include "UnitResourceList.h"
#include "DataGroup.h"
#include <OgreMath.h>
#include <cmath>

std::wstring CEffect::getDisplayStats(CEffectDisplayValues& values)
{
    if (!m_showStats)
        return EMPTY_WSTRING;
    float minimum = values.m_minimum;
    float maximum = values.m_maximum;
    float secondaryMinimum = values.m_secondaryMinimum;
    float secondaryMaximum = values.m_secondaryMaximum;
    unsigned int duration = static_cast<unsigned int>(ceilf(values.m_duration));
    float roundedMaximum = ceilf(maximum);
    float roundedMinimum = ceilf(minimum);
    bool overtime = m_fValue24 != -900.0f && m_fValue24 != -1000.0f;
    bool good = gEFFECT_TYPE_BONUS[m_eType] == 2 || maximum == 0.0f ||
        Ogre::Math::Sign(maximum) == Ogre::Math::Sign(static_cast<float>(gEFFECT_TYPE_MAX_VALUES[m_eType]));
    std::wstring range = getRangeOfValues(minimum, maximum, good);
    std::wstring secondaryRange = getRangeOfValues(secondaryMinimum, secondaryMaximum, true);
    std::wstring result = EMPTY_WSTRING;
    if (overtime)
        result = good ? gEFFECT_TYPE_DESCRIPTIONS_GOOD_OT[m_eType] : gEFFECT_TYPE_DESCRIPTIONS_BAD_OT[m_eType];
    else
        result = good ? gEFFECT_TYPE_DESCRIPTIONS_GOOD[m_eType] : gEFFECT_TYPE_DESCRIPTIONS_BAD[m_eType];
    result = STRINGS::replaceWString(result, L"[VALUE]", range);
    int low = static_cast<int>(fabsf(roundedMinimum));
    result = STRINGS::replaceWString(result, L"[VALUE1]", STRINGS::GetValueAsWString(low));
    result = STRINGS::replaceWString(result, L"[MINVAL]", STRINGS::GetValueAsWString(low));
    int high = static_cast<int>(fabsf(roundedMaximum));
    result = STRINGS::replaceWString(result, L"[VALUE2]", STRINGS::GetValueAsWString(high));
    result = STRINGS::replaceWString(result, L"[MAXVAL]", STRINGS::GetValueAsWString(high));
    result = STRINGS::replaceWString(result, L"\\n", L"\n");
    if (m_eType == 82 || m_eType == 65 || m_eType == 74 || m_eType == 127 ||
        m_eType == 76 || m_eType == 105 || m_eType == 81)
    {
        CDataGroup* data = CSkillParser::getSingleton()->getSkillData(m_sName);
        result = STRINGS::replaceWString(result, L"[NAME]",
            data ? data->GetDataValue(L"DISPLAYNAME", L"???") : L"???");
    }
    else if (m_eType == 73 || m_eType == 57 || m_eType == 67)
    {
        CDataGroup* data = m_resources->getMasterResourceList()->getDataGroupByObjectName(L"MONSTERS", m_sName);
        result = STRINGS::replaceWString(result, L"[NAME]",
            data ? data->GetDataValue(L"DISPLAYNAME", L"???") : L"???");
    }
    else
        result = STRINGS::replaceWString(result, L"[NAME]", m_sName);
    result = STRINGS::replaceWString(result, L"[VALUE3AND4]", secondaryRange);
    std::wstring damageType = getDamageTypeDisplayString(m_eDamageType);
    if (damageType.empty())
    {
        result = STRINGS::replaceWString(result, L"[DMGTYPE] ", L"");
        result = STRINGS::replaceWString(result, L" [DMGTYPE]", L"");
    }
    else
        result = STRINGS::replaceWString(result, L"[DMGTYPE]", damageType);
    if (duration)
        result = STRINGS::replaceWString(result, L"[DURATION]", STRINGS::GetValueAsWString(duration));
    if (result != EMPTY_WSTRING && !good)
        result = L"|cFFff483f" + result + L"|u";
    return result;
}

#include "UnitThemes.h"
#include <queue>

CEffect::CEffect(CDataGroup* data, CBaseUnit* owner)
    : m_eType(static_cast<EEFFECT_TYPE>(7)), m_activation(EFFECT_ACTIVATION_DYNAMIC),
      m_fValue24(-900.0f), m_bFlag28(false), m_flag30(true), m_bDead(false),
      m_useOwnerLevel(false), m_value38(1.0f), m_particle(NULL),
      m_statModifiers(1), m_statModifierValues(1), m_resources(NULL), m_pUnitTheme(NULL)
{
    initValues();
    if (owner)
        m_resources = owner->getResourceManager();
    std::wstring type = STRINGS::StringUpper(data->GetDataValue(L"TYPE", EMPTY_WSTRING));
    for (unsigned int i = 0; i < 145; ++i)
    {
        if (type == gEFFECT_TYPE_NAMES[i])
        {
            m_eType = static_cast<EEFFECT_TYPE>(i);
            break;
        }
    }
    bool forcedMagical = m_eType == 2 || m_eType == 17 || m_eType == 35 ||
        (m_eType >= 37 && m_eType <= 40) || m_eType == 86 || m_eType == 118;
    std::wstring activation = STRINGS::StringUpper(data->GetDataValue(L"ACTIVATION", L"DYNAMIC"));
    for (unsigned int i = 0; i < 3; ++i)
    {
        if (activation == gEffect_Activation_Names[i])
        {
            m_activation = static_cast<EEFFECT_ACTIVATION>(i);
            break;
        }
    }
    std::wstring duration = STRINGS::StringUpper(data->GetDataValue(L"DURATION", EMPTY_WSTRING));
    if (duration.empty())
        duration = L"ALWAYS";
    else
        m_bFlag28 = true;
    if (duration == L"INSTANT")
        m_fValue24 = -900.0f;
    else if (duration == L"0" || duration == L"ALWAYS")
        m_fValue24 = -1000.0f;
    else
    {
        m_fValue24 = STRINGS::GetFloat(duration);
        if (m_fValue24 <= 0.0f)
            m_fValue24 = -1000.0f;
    }
    std::wstring theme = STRINGS::StringUpper(data->GetDataValue(L"UNITTHEME", EMPTY_WSTRING));
    m_pUnitTheme = CUnitThemes::getSingleton()->getTheme(theme);
    m_flag33 = data->GetDataValue(L"SAVE", m_flag33);
    m_useOwnerLevel = data->GetDataValue(L"USEOWNERLEVEL", m_useOwnerLevel);
    m_flag31 = data->GetDataValue(L"EXCLUSIVE", static_cast<bool>(m_flag31));
    m_sName = STRINGS::StringUpper(STRINGS::StringUpper(data->GetDataValue(L"NAME", EMPTY_WSTRING)));
    m_name88 = STRINGS::StringUpper(STRINGS::StringUpper(data->GetDataValue(L"LINK_NAME", EMPTY_WSTRING)));
    setOwner(owner, true);
    if (!owner || !m_useOwnerLevel)
    {
        m_iLevel = data->GetDataValue(L"LEVEL", 0);
        if (m_iLevel == static_cast<unsigned int>(-1) || m_iLevel >= 1001)
            m_iLevel = 0;
        calculateBaseValue(static_cast<ECALCULATETYPES>(0));
    }
    setFX(STRINGS::StringUpper(data->GetDataValue(L"PARTICLE_FX", EMPTY_WSTRING)));
    bool noGraph = data->GetDataValue(L"NOGRAPH", false);
    std::wstring overrideGraph = STRINGS::StringUpper(data->GetDataValue(L"GRAPHOVERRIDE", EMPTY_WSTRING));
    m_name90 = overrideGraph;
    for (int i = 0; i < 4; ++i)
    {
        if (!noGraph)
        {
            m_flag37 = true;
            std::wstring graph = gEFFECT_TYPE_GRAPHS[m_eType][i];
            if (overrideGraph != EMPTY_WSTRING)
                graph = overrideGraph;
            m_graphs[i] = graph.empty() ? NULL : CGraphManager::getSingleton()->getGraph(graph);
        }
        float amount = data->GetDataValue(gEFFECT_TYPE_PROPERTY_TAGS[m_eType][i], -999.0f);
        if (amount == -999.0f)
            amount = data->GetDataValue(L"VALUE" + (i ? STRINGS::GetValueAsWString(i + 1) : L""), -999.0f);
        if (amount != -999.0f)
        {
            m_values[i] = amount;
            if (i == 1)
                m_padding32 = 1;
        }
    }
    std::wstring damage = STRINGS::StringUpper(data->GetDataValue(L"DAMAGE_TYPE", L"PHYSICAL"));
    if (forcedMagical)
        m_eDamageType = DAMAGE_MAGICAL;
    else
    {
        for (unsigned int i = 0; i < 7; ++i)
        {
            if (damage == STRINGS::StringUpper(gDAMAGE_TYPES[i]))
            {
                m_eDamageType = static_cast<EDAMAGE_TYPES>(i);
                break;
            }
        }
    }
    std::wstring modifierNames = STRINGS::StringUpper(data->GetDataValue(L"STATMODIFYNAME", EMPTY_WSTRING));
    if (modifierNames != EMPTY_WSTRING)
    {
        std::wstring percentages = STRINGS::StringUpper(data->GetDataValue(L"STATMODIFYPERCENT", EMPTY_WSTRING));
        std::queue<std::wstring> names;
        std::queue<std::wstring> amounts;
        STRINGS::TokenizeString(&names, modifierNames, L",");
        STRINGS::TokenizeString(&amounts, percentages, L",");
        if (names.empty())
            names.push(modifierNames);
        if (amounts.empty())
            amounts.push(percentages);
        while (!names.empty())
        {
            for (unsigned int i = 0; i < 6; ++i)
            {
                if (names.front() == gEFFECT_STAT_MODIFIER_NAMES[i])
                {
                    std::wstring amount = amounts.empty() ? L"100" : amounts.front();
                    m_statModifiers.add(static_cast<EEFFECT_STAT_MODIFIERS>(i));
                    m_statModifierValues.add(STRINGS::GetFloat(amount) / 100.0f);
                    break;
                }
            }
            names.pop();
            if (!amounts.empty())
                amounts.pop();
        }
    }
    calculateBaseValue(static_cast<ECALCULATETYPES>(0));
    if (m_eType == 52 && m_fValue24 != -900.0f && m_fValue24 != -1000.0f)
        m_flag31 = 1;
}
