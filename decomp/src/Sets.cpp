#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "Sets.h"
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
