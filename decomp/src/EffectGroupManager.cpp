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

#include "FileSystem.h"
#include "Randomizer.h"

void CEffectGroupManager::rollAndCreateRandomAffixes(
    unsigned int unitType, unsigned int affixLevel,
    unsigned int effectCost, TArrayList<CAffix*>& result)
{
    TArrayList<CAffix*>* affixes;
    std::map<unsigned int, TArrayList<CAffix*>*>::iterator found =
        m_mapAffixesByUnitType.find(unitType);
    if (found != m_mapAffixesByUnitType.end())
        affixes = found->second;
    else
    {
        affixes = new TArrayList<CAffix*>(10);
        m_mapAffixesByUnitType[unitType] = affixes;
        for (std::map<std::wstring, CAffix*>::iterator i = m_mapAffixes.begin();
             i != m_mapAffixes.end(); ++i)
        {
            if (i->second->canBeAppliedToUnitType(unitType) && i->second->m_iWeight != 0)
                affixes->add(i->second);
        }
    }
    if (affixes == NULL)
        return;
    CRandomizer randomizer(RANDOMIZER_NORMAL);
    for (unsigned int i = 0; i < affixes->size(); ++i)
    {
        if ((*affixes)[i]->m_iMinSpawnRange <= static_cast<int>(affixLevel) &&
            (*affixes)[i]->m_iMaxSpawnRange > static_cast<int>(affixLevel))
            randomizer.addChoice(i, (*affixes)[i]->m_iWeight);
    }
    int remaining = effectCost;
    while (randomizer.hasChoices() && remaining > 0)
    {
        int choice = randomizer.getRandom();
        randomizer.removeChoice(choice);
        CAffix* affix = new CAffix((*affixes)[choice], affixLevel);
        if (affix->m_iSlotsOccupy > remaining && randomizer.hasChoices())
            delete affix;
        else
        {
            result.add(affix);
            remaining -= affix->m_iSlotsOccupy;
        }
    }
}

void CEffectGroupManager::reload()
{
    clean();
    TArrayList<std::wstring> files(250);
    CFileSystem::getSingleton()->getFileList(m_sPath, files, L"*.dat", true, true, false, false);
    for (unsigned int i = 0; i < files.size(); ++i)
    {
        CAffix* affix = new CAffix(files[i]);
        if (m_mapAffixes.find(affix->m_sDisplayName) == m_mapAffixes.end())
            m_mapAffixes[affix->m_sDisplayName] = affix;
        else
            delete affix;
    }
}
