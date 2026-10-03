#include "EmptyStrings.h"
#include "AIStatWatcher.h"
#include "AIManager.h"
#include "AISkill.h"
#include "Character.h"
#include "OgreUtilities.h"
#include "AnimationDefines.h"
#include "DataGroup.h"
#include "DataValue.h"
#include "Hierarchy.h"
#include "Level.h"
#include "MasterResourceManager.h"
#include "StringUtilities.h"

CAIStatWatcher::CAIStatWatcher(CDataGroup* dataGroup, CAIManager* aiManager)
    : m_pAIManager(aiManager), m_pCharacter(NULL), m_eStat(AISTAT_NONE), m_eLogic(AISTAT_LOGIC_BELOW),
      m_Flags(2), m_Skills(2), m_FlaggedUnits(5), m_SkilledUnits(5), m_eTarget(AISTAT_TARGET_SELF),
      m_eTargetUnitType((UNITTYPES::EUNITTYPES)0), m_eTargetAlignment(ALIGNMENT_ALL), m_fTargetArea(10.0f),
      m_fDuration(0.0f), m_fValue(0.0f), m_bOnlyOnce(false), m_bTriggered(false), m_bEnableOnEvent(true),
      m_bIncludeLiving(true), m_bIncludeDead(false)
{
    m_pCharacter = aiManager->getCharacter();

    m_eStat = (EAISTAT_TYPE)STRINGS::getStringIndex(
        STRINGS::StringUpper(dataGroup->GetDataValue(L"STAT", g_AISTAT_TYPE_NAMES[m_eStat])), g_AISTAT_TYPE_NAMES,
        AISTAT_TYPE_COUNT, m_eStat, false);
    m_eLogic = (EAISTAT_LOGIC)STRINGS::getStringIndex(
        STRINGS::StringUpper(dataGroup->GetDataValue(L"LOGIC", g_AISTAT_LOGIC_NAMES[m_eLogic])), g_AISTAT_LOGIC_NAMES,
        AISTAT_LOGIC_COUNT, m_eLogic, false);

    std::vector<CDataValue*> flags;
    dataGroup->GetDataValuesMatchingName(L"FLAG", &flags);
    for (unsigned int i = 0; i < flags.size(); i++)
    {
        EAIFLAG_TYPES flag = (EAIFLAG_TYPES)STRINGS::getStringIndex(
            STRINGS::StringUpper(flags[i]->GetValueAsString()), g_AIFLAG_TYPE_NAMES, AIFLAG_COUNT, 0, false);
        m_Flags.add(flag);
    }

    std::vector<CDataValue*> skills;
    dataGroup->GetDataValuesMatchingName(L"SKILL", &skills);
    for (unsigned int i = 0; i < skills.size(); i++)
    {
        CAISkill* skill = new CAISkill(skills[i]->GetValueAsString());
        if (skill != NULL)
            m_Skills.add(skill);
    }

    m_eTarget = (EAISTAT_TARGET)STRINGS::getStringIndex(
        STRINGS::StringUpper(dataGroup->GetDataValue(L"TARGET", g_AISTAT_TARGET_NAMES[m_eTarget])),
        g_AISTAT_TARGET_NAMES, AISTAT_TARGET_COUNT, m_eTarget, false);
    m_eTargetAlignment = (EAlignment)STRINGS::getStringIndex(
        STRINGS::StringUpper(dataGroup->GetDataValue(L"TARGET_ALIGNMENT", KALIGNMENT_STRINGS[m_eTargetAlignment])),
        KALIGNMENT_STRINGS, ALIGNMENT_COUNT, m_eTargetAlignment, false);
    m_eTargetUnitType = CMasterResourceManager::getSingleton()->m_pHierarchy->getTypeIDByName(
        dataGroup->GetDataValue(L"TARGETUNITTYPE", L"ANY"));
    m_fTargetArea = dataGroup->GetDataValue(L"TARGETAREA", m_fTargetArea);
    m_fValue = dataGroup->GetDataValue(L"VALUE", 0.0f);
    m_fDuration = dataGroup->GetDataValue(L"DURATION", 0.0f);
    m_bOnlyOnce = dataGroup->GetDataValue(L"ONLYONCE", m_bOnlyOnce);
    m_bEnableOnEvent = dataGroup->GetDataValue(L"ENABLE_ON_EVENT", m_bEnableOnEvent);
    m_bIncludeLiving = dataGroup->GetDataValue(L"INCLUDE_LIVING", m_bIncludeLiving);
    m_bIncludeDead = dataGroup->GetDataValue(L"INCLUDE_DEAD", m_bIncludeDead);
    // A watcher without a threshold fires only once.
    if (!m_bOnlyOnce)
        m_bOnlyOnce = m_fValue == 0.0f;

    STRINGS::StringConvertToNarrow(dataGroup->GetDataValue(L"ANIMATION", EMPTY_WSTRING), m_sAnimation);
    m_sAnimation = STRINGS::StringUpper(m_sAnimation);
}

CAIStatWatcher::~CAIStatWatcher()
{
    m_Skills.deleteAll();
}

void CAIStatWatcher::addSkill()
{
    if (m_bTriggered && m_bOnlyOnce)
        return;

    bool added = false;
    for (unsigned int i = 0; i < m_Skills.size(); i++)
    {
        if (!m_pAIManager->hasAISkill(m_Skills[i]))
        {
            m_pAIManager->addAISkill(m_Skills[i], m_fDuration);
            added = true;
        }
    }
    if (added && m_sAnimation != EMPTY_STRING)
        m_pCharacter->setAIPlayAnimation(m_sAnimation, false, 0.1f, 1.0f);
    m_bTriggered = true;
}

void CAIStatWatcher::removeFlag()
{
    CLevel* level = m_pAIManager->getLevel();
    for (unsigned int i = 0; i < m_FlaggedUnits.size(); i++)
    {
        CCharacter* unit = level->getCharacterByGuid(m_FlaggedUnits[i]);
        if (unit != NULL)
        {
            for (unsigned int j = 0; j < m_Flags.size(); j++)
            {
                if (unit->getAIManager() != NULL)
                    unit->getAIManager()->removeAIFlag(m_Flags[j]);
            }
        }
    }
    m_FlaggedUnits.clear();
}

void CAIStatWatcher::removeSkill()
{
    for (unsigned int i = 0; i < m_Skills.size(); i++)
    {
        if (m_pCharacter->getAIManager() != NULL)
            m_pCharacter->getAIManager()->removeAISkill(m_Skills[i]);
    }
}

void CAIStatWatcher::getTargets(TArrayList<CCharacter*>& targets)
{
    if (m_eTarget == AISTAT_TARGET_SELF)
    {
        targets.add(m_pCharacter);
    }
    else if (m_eTarget == AISTAT_TARGET_FORMATION || m_eTarget == AISTAT_TARGET_AREAFORMATION)
    {
        TArrayList<long long>& formation = m_pAIManager->getFormationUnits();
        for (unsigned int i = 0; i < formation.size(); i++)
        {
            CCharacter* unit = m_pCharacter->getLevel()->getCharacterByGuid(formation[i]);
            if (unit == NULL)
                continue;
            if (m_eTarget == AISTAT_TARGET_FORMATION)
                targets.add(unit);
            else if (unit->getPosition(true).distance(m_pCharacter->getPosition(true)) <= m_fTargetArea)
                targets.add(unit);
        }
    }
    else if (m_eTarget == AISTAT_TARGET_AREA || m_eTarget == AISTAT_TARGET_AREAUNITTYPES)
    {
        for (TLinkedListNode<CCharacter*>* node = m_pCharacter->getLevel()->getCharacters()->getHead(); node != NULL;
             node = node->m_pNext)
        {
            if (node->m_Data->getPosition(true).distance(m_pCharacter->getPosition(true)) <= m_fTargetArea &&
                (m_eTarget == AISTAT_TARGET_AREA || node->m_Data->ISA(m_eTargetUnitType)))
                targets.add(node->m_Data);
        }
    }
}

void CAIStatWatcher::addFlag()
{
    if (m_bTriggered && m_bOnlyOnce)
        return;

    TArrayList<CCharacter*> targets(m_pAIManager->getFormationUnits().size() + 1);
    getTargets(targets);
    for (unsigned int i = 0; i < targets.size(); i++)
    {
        bool added = false;
        for (unsigned int j = 0; j < m_Flags.size(); j++)
        {
            if (targets[i]->getAIManager() != NULL && !targets[i]->getAIManager()->hasAIFlag(m_Flags[j]))
            {
                targets[i]->getAIManager()->addAIFlag(m_Flags[j], m_fDuration);
                added = true;
            }
        }
        if (added)
        {
            m_FlaggedUnits.add(targets[i]->getGuid());
            if (m_sAnimation != EMPTY_STRING)
                targets[i]->setAIPlayAnimation(m_sAnimation, false, 0.1f, 1.0f);
        }
    }
    m_bTriggered = true;
}

void CAIStatWatcher::update(float elapsed)
{
    if (m_bOnlyOnce && !m_pCharacter->alive())
        return;

    float value;
    switch (m_eStat)
    {
    case AISTAT_NONE:
        return;
    case AISTAT_HP:
        value = (float)m_pCharacter->HP();
        break;
    case AISTAT_MANA:
        value = (float)m_pCharacter->mana();
        break;
    case AISTAT_HP_PCT:
        value = (float)m_pCharacter->HP() / (float)m_pCharacter->maxHP() * 100.0f;
        break;
    case AISTAT_MANA_PCT:
        value = (float)m_pCharacter->mana() / (float)m_pCharacter->maxMana() * 100.0f;
        break;
    case AISTAT_ACTIVE_UNITS:
        if (m_pCharacter->getResourceManager()->getGameClient() == NULL)
        {
            value = 0.0f;
        }
        else
        {
            TArrayList<CCharacter*> units(10);
            m_pCharacter->getLevel()->getActiveCharactersAtPosition(m_pCharacter->getPosition(false),
                                                                    m_eTargetUnitType, m_eTargetAlignment,
                                                                    m_fTargetArea, m_bIncludeLiving, m_bIncludeDead,
                                                                    units);
            value = (float)units.size();
        }
        break;
    default:
        value = 0.0f;
        break;
    }

    bool conditionMet = false;
    switch (m_eLogic)
    {
    case AISTAT_LOGIC_BELOW:
        conditionMet = value <= m_fValue;
        break;
    case AISTAT_LOGIC_ABOVE:
        conditionMet = value >= m_fValue;
        break;
    default:
        break;
    }

    if (conditionMet)
    {
        if (m_bEnableOnEvent)
        {
            addFlag();
            addSkill();
        }
        else
        {
            removeFlag();
            removeSkill();
        }
    }
    else if (m_fDuration == 0.0f)
    {
        // Without a duration the flags and skills last only while the
        // condition holds.
        if (m_bEnableOnEvent)
        {
            removeFlag();
            removeSkill();
        }
        else
        {
            addFlag();
            addSkill();
        }
    }
}
