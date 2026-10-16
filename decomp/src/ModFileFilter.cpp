#include "EmptyStrings.h"
#include "GameVariables.h"
#include "ModFileFilter.h"

unsigned int CModFileFilter::getNumberOfActiveMods()
{
    unsigned int count = 0;

    for (unsigned int i = 0; i < m_Mods.size(); ++i) {
        const unsigned char* data =
            reinterpret_cast<const unsigned char*>(m_Mods[i]);
        const unsigned int priority =
            static_cast<unsigned int>(data[0x74]) |
            (static_cast<unsigned int>(data[0x75]) << 8) |
            (static_cast<unsigned int>(data[0x76]) << 16) |
            (static_cast<unsigned int>(data[0x77]) << 24);

        if (data[0x70] != 0 && priority < 0x80000000u)
            ++count;
    }

    return count;
}

#include "Mod.h"
#include "FileSystem.h"

CModFileFilter* CModFileFilter::getSingleton()
{
    return g_pModFileFilter;
}

unsigned int CModFileFilter::getNumberOfEnabledMods()
{
    unsigned int count = 0;
    for (unsigned int i = 0; i < m_Mods.size(); ++i)
        if (m_Mods[i]->m_bUnknown70)
            ++count;
    return count;
}

std::wstring CModFileFilter::getFilePath(const std::wstring& path, std::string& resourceGroup, CFileInfo& info)
{
    for (unsigned int i = 0; i < m_Mods.size(); ++i)
    {
        if (m_Mods[i]->m_iUnknown74 >= 0 && m_Mods[i]->m_bUnknown70)
        {
            std::wstring file = m_Mods[i]->getModFile(path);
            if (!file.empty())
            {
                resourceGroup = m_Mods[i]->m_sUnknown48;
                info.m_sModName = m_Mods[i]->m_sUnknown10;
                return file;
            }
        }
    }
    return EMPTY_WSTRING;
}

void CModFileFilter::getEnabledModNames(TArrayList<std::wstring>* names)
{
    for (unsigned int i = 0; i < m_Mods.size(); ++i)
        if (m_Mods[i]->m_bUnknown70)
            names->add(m_Mods[i]->m_wUnknown50);
}

void CModFileFilter::getModNames(TArrayList<std::wstring>* names)
{
    for (unsigned int i = 0; i < m_Mods.size(); ++i)
    {
        std::wstring name = m_Mods[i]->m_wUnknown50;
        names->add(name);
    }
}
