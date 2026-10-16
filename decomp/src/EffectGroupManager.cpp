#include "EmptyStrings.h"
#include "EffectGroupManager.h"
#include "Affix.h"
#include "RunicCore.h"
#include "StringUtilities.h"
#include "TArrayList.h"

void CEffectGroupManager::clean()
{
    for (std::map<unsigned int, TArrayList<CAffix*>*>::iterator it = m_mapAffixesByUnitType.begin();
         it != m_mapAffixesByUnitType.end(); ++it)
    {
        if (it->second != NULL)
        {
            delete it->second;
            it->second = NULL;
        }
    }
    m_mapAffixesByUnitType.clear();

    for (std::map<std::wstring, CAffix*>::iterator it = m_mapAffixes.begin();
         it != m_mapAffixes.end(); ++it)
    {
        if (it->second != NULL)
        {
            delete it->second;
            it->second = NULL;
        }
    }
    m_mapAffixes.clear();
}

CEffectGroupManager::~CEffectGroupManager()
{
    clean();
}

CAffix* CEffectGroupManager::getAffix(const std::wstring& name)
{
    std::map<std::wstring, CAffix*>::iterator i;
    {
        std::wstring upperName = STRINGS::StringUpper(name);
        i = m_mapAffixes.find(upperName);
    }
    if (i != m_mapAffixes.end())
        return i->second;
    return NULL;
}

CEffectGroupManager::CEffectGroupManager(const wchar_t* path)
    : CRunicCore(), m_sPath(path)
{
    reload();
}

void CEffectGroupManager::getAffixNames(TArrayList<std::wstring>& affixNames)
{
    for (std::map<std::wstring, CAffix*>::iterator i = m_mapAffixes.begin();
         i != m_mapAffixes.end(); ++i)
        affixNames.add(i->first);
}
