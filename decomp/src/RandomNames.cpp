#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "RandomNames.h"
#include "DataGroup.h"
#include "Utilities.h"

class CRandomName : public Ogre::GeneralAllocatedObject
{
public:
    int m_weight;
    int m_index;
    TArrayList<std::wstring> m_prefixes;
    TArrayList<std::wstring> m_suffixes;
    std::wstring m_name;
    int m_chance;
};

CRandomNames* CRandomNames::getSingleton()
{
    return (CRandomNames*)g_pRandomNames;
}

void CRandomNames::load(const wchar_t* filename)
{
    m_pRandomizer = new CRandomizer(RANDOMIZER_NORMAL);

    CDataGroup data(EMPTY_WSTRING, NULL, 20, 10, NULL);
    data.LoadFile(filename, NULL);

    std::vector<CDataGroup*> groups;
    unsigned int count = data.GetDataGroupsMatchingName(L"NAME", &groups);
    for (unsigned int i = 0; i < count; i++) {
        CRandomName* name = new CRandomName();
        name->m_prefixes.setGrowBy(10);
        name->m_suffixes.setGrowBy(10);
        m_prefixes.add(name);
        CDataGroup* group = groups[i];
        int weight = group->GetDataValue(L"WEIGHT", 1);
        m_pRandomizer->addChoice(i, weight);

        std::vector<CDataValue*> values;
        group->GetDataValuesMatchingName(L"PREFIX", &values);
        name->m_chance = group->GetDataValue(L"CENTERCHANCE", 0);
        name->m_name = group->GetDataValue(L"CENTER", L"'");
        name->m_prefixes.setGrowBy(values.size() + 1);
        for (unsigned int j = 0; j < values.size(); j++)
            name->m_prefixes.add(values[j]->GetValueString(true));
        values.clear();

        group->GetDataValuesMatchingName(L"SUFFIX", &values);
        name->m_suffixes.setGrowBy(values.size() + 1);
        for (unsigned int j = 0; j < values.size(); j++)
            name->m_suffixes.add(values[j]->GetValueString(true));
    }
    groups.clear();

    CDataGroup* title = data.GetDataGroupByName(L"TITLE", false);
    if (title) {
        m_nCenterChance = title->GetDataValue(L"CHANCE", 100);

        std::vector<CDataValue*> values;
        title->GetDataValuesMatchingName(L"PREFIX", &values);
        for (unsigned int j = 0; j < values.size(); j++)
            m_suffixes.add(values[j]->GetValueString(true));
        values.clear();

        title->GetDataValuesMatchingName(L"SUFFIX", &values);
        m_center.setGrowBy(values.size() + 1);
        for (unsigned int j = 0; j < values.size(); j++)
            m_center.add(values[j]->GetValueString(true));
    }
    groups.clear();
}

CRandomNames::CRandomNames(const wchar_t* filename)
    : m_prefixes(10),
      m_suffixes(10),
      m_center(10),
      m_pRandomizer(NULL),
      m_nCenterChance(100)
{
    load(filename);

    if (!g_pRandomNames)
        g_pRandomNames = this;
}

std::wstring CRandomNames::generateName(bool withTitle)
{
    std::wstring result(L"");
    CRandomName* name = m_prefixes[m_pRandomizer->getRandom()];
    int prefix = UTILITIES::randomIntegerBetween(0, name->m_prefixes.size() - 1);
    int suffix = UTILITIES::randomIntegerBetween(0, name->m_suffixes.size() - 1);
    if (name->m_chance > 0 && UTILITIES::randomIntegerBetween(0, 100) <= name->m_chance)
        result = name->m_prefixes[prefix] + name->m_name + name->m_suffixes[suffix];
    else
        result = name->m_prefixes[prefix] + name->m_suffixes[suffix];

    if (withTitle && UTILITIES::randomIntegerBetween(0, 100) <= m_nCenterChance && m_center.size() != 0)
        result = result + L" " + m_center[UTILITIES::randomIntegerBetween(0, m_center.size() - 1)];
    return result;
}

CRandomNames::~CRandomNames()
{
    if (m_pRandomizer) {
        delete m_pRandomizer;
        m_pRandomizer = NULL;
    }
    m_prefixes.deleteAll();
    g_pRandomNames = NULL;
}
