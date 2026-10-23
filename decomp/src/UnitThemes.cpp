#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "UnitThemeParticle.h"
#include "UnitThemes.h"
#include "TArrayList.h"

CUnitThemes* CUnitThemes::getSingleton()
{
    return reinterpret_cast<CUnitThemes*>(g_pUnitThemes);
}

CUnitThemes::~CUnitThemes()
{
    m_Themes.deleteAll();
    g_pUnitThemes = NULL;
}

CUnitThemes::CUnitThemes(const wchar_t *fileName)
{
    m_sFilename.assign(fileName);
    m_Themes.setGrowBy(10);
    reload();
    if (g_pUnitThemes == NULL)
        g_pUnitThemes = this;
}


#include "MasterResourceManager.h"
#include "Hierarchy.h"

void CUnitThemeParticle::load(CDataGroup* group)
{
    m_wstrFile = group->GetDataValue(L"FILE", EMPTY_WSTRING);
    m_iUnitTypeID = CMasterResourceManager::getSingleton()->m_pHierarchy->getTypeIDByName(
        group->GetDataValue(L"UNITTYPE", L"ANY"));
    m_iCount = group->GetDataValue(L"COUNT", 1);
    m_wstrBone = group->GetDataValue(L"BONE", EMPTY_WSTRING);
    m_bAttaches = group->GetDataValue(L"ATTACHES", true);
    m_bFollows = group->GetDataValue(L"FOLLOWS", !m_bAttaches);
}

#include "FileSystem.h"
#include "StringUtilities.h"
#include "Utilities.h"
#include <vector>

void CUnitThemes::reload()
{
    m_Themes.deleteAll();
    TArrayList<std::wstring> files(25);
    CFileSystem::getSingleton()->getFileList(m_sFilename, files, L"*.dat", false, true, false, false);
    m_Themes.setGrowBy(files.size() + 1);
    for (unsigned int i = 0; i < files.size(); ++i) {
        CDataGroup group(EMPTY_WSTRING, NULL, 20, 10, NULL);
        group.LoadFile(files[i], NULL);
        std::wstring name = STRINGS::StringUpper(group.GetDataValue(L"NAME", EMPTY_WSTRING));
        long long guid = group.GetDataValue(L"GUID", static_cast<long long>(-1));
        if (name == EMPTY_WSTRING) continue;
        CUnitTheme* theme = new CUnitTheme;
        theme->m_particles.setGrowBy(10);
        if (guid == -1) {
            guid = UTILITIES::createUniqueGuid();
            group.SetDataValue(L"GUID", guid);
            group.SaveToFile(files[i]);
        }
        theme->m_iGuid = guid;
        theme->m_sName = name;
        std::vector<CDataGroup*> particles;
        group.GetDataGroupsMatchingName(L"PARTICLE", &particles);
        for (unsigned int j = 0; j < particles.size(); ++j) {
            CUnitThemeParticle* particle = new CUnitThemeParticle;
            particle->m_iCount = 0;
            particle->m_bAttaches = false;
            particle->m_bFollows = false;
            particle->load(particles[j]);
            theme->m_particles.add(particle);
        }
        m_Themes.add(theme);
    }
}
