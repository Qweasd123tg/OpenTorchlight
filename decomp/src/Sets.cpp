#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Sets.h"
#include "Set.h"
#include "DataGroup.h"
#include "FileSystem.h"
#include "EffectGroupManager.h"
#include "RunicCore.h"

CSet* CSets::getSet(unsigned int index)
{
    if (index >= m_sets.size())
        return 0;

    return m_sets[index];
}

CSets* CSets::getSingleton()
{
    return static_cast<CSets*>(g_pSets);
}

CSet* CSets::getSet(const wchar_t* name)
{
    std::map<std::wstring, unsigned int, std::less<std::wstring> >::iterator i =
        m_setIndices.find(std::wstring(name));

    if (i != m_setIndices.end() && i->second < m_sets.size())
        return m_sets[i->second];

    return NULL;
}

CSets::CSets(const wchar_t* path, CEffectGroupManager* effectGroupManager)
    : CRunicCore(), m_path(path), m_sets(10)
{
    reload(effectGroupManager);

    if (g_pSets == 0)
        g_pSets = this;
}

void CSets::getSetNames(TArrayList<std::wstring>& setNames)
{
    for (std::map<std::wstring, unsigned int>::iterator i = m_setIndices.begin();
         i != m_setIndices.end(); ++i)
        setNames.add(i->first);
}

void CSet::load(CDataGroup* group, CEffectGroupManager* effectGroupManager)
{
    std::vector<CDataGroup*> affixGroups;

    m_sName = group->GetDataValue(L"NAME", L"");
    m_sDisplayName = group->GetDataValue(L"DISPLAYNAME", L"");

    unsigned int count = group->GetDataGroupsMatchingName(L"AFFIX", &affixGroups);
    m_Affixes.setGrowBy(count + 1);

    for (unsigned int i = 0; i < count; i++)
    {
        CDataGroup* affixGroup = affixGroups[i];
        std::wstring affixName = affixGroup->GetDataValue(L"AFFIX", L"");
        int requiredCount = affixGroup->GetDataValue(L"COUNT", 1);
        int level = affixGroup->GetDataValue(L"AFFIXLEVEL", 1);

        CAffix* affix = effectGroupManager->getAffix(affixName);
        if (affix != NULL)
        {
            CSetAffix* setAffix = new CSetAffix;
            setAffix->m_pAffix = new CAffix(affix, level);
            setAffix->m_iRequiredCount = requiredCount;
            setAffix->m_sAffixName = affixName;
            setAffix->m_iLevel = level;
            m_Affixes.add(setAffix);
        }
    }

    affixGroups.clear();
}

CSets::~CSets()
{
    m_setIndices.clear();
    m_sets.deleteAll();
    g_pSets = NULL;
}

void CSets::reload(CEffectGroupManager* effectGroupManager)
{
    m_sets.deleteAll();

    TArrayList<std::wstring> files(10);
    CFileSystem::getSingleton()->getFileList(m_path, files, L"*.dat", true, true, false, false);

    for (unsigned int i = 0; i < files.size(); i++)
    {
        CDataGroup group(EMPTY_WSTRING, NULL, 20, 10, NULL);
        group.LoadFile(files[i], NULL);

        CSet* set = new CSet();
        set->load(&group, effectGroupManager);

        m_setIndices[set->m_sName] = m_sets.size();
        m_sets.add(set);
    }
}
