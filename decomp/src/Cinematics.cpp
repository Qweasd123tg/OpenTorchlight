#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "Cinematics.h"
#include "DataGroup.h"
#include "RunicCore.h"

CCinematics* CCinematics::getSingleton()
{
    return reinterpret_cast<CCinematics*>(g_pCinematics);
}

class CCinematic
{
public:
    std::wstring m_sName;
    std::wstring m_sText;
    std::wstring m_sImage;
    std::wstring m_sSound;

    void load(CDataGroup* data);
};

void CCinematic::load(CDataGroup* data)
{
    m_sName = data->GetDataValue(L"NAME", L"");
    m_sText = data->GetDataValue(L"TEXT", L"");
    m_sImage = data->GetDataValue(L"IMAGE", L"");
    m_sSound = data->GetDataValue(L"SOUND", L"");
}

CCinematics::CCinematics(const wchar_t* path)
    : CRunicCore(), m_sPath(path), m_lCinematics(10)
{
    if (g_pCinematics == NULL) {
        g_pCinematics = this;
        reload();
    }
}

CCinematic* CCinematics::getCinematic(unsigned int index)
{
    if (index < m_lCinematics.size())
        return m_lCinematics[index];
    return NULL;
}

CCinematic* CCinematics::getCinematic(const wchar_t* name)
{
    std::map<std::wstring, unsigned int>::iterator found = m_mapCinematics.find(name);
    if (found != m_mapCinematics.end())
        return getCinematic(found->second);
    return NULL;
}

CCinematics::~CCinematics()
{
    m_mapCinematics.clear();
    for (unsigned int i = 0; i < m_lCinematics.size(); ++i) {
        if (m_lCinematics[i]) {
            m_lCinematics[i]->~CCinematic();
            Ogre::NedAllocImpl::deallocBytes(m_lCinematics[i]);
            m_lCinematics[i] = NULL;
        }
        m_lCinematics[i] = NULL;
    }
    m_lCinematics.clear();
    g_pCinematics = NULL;
}

#include "FileSystem.h"
#include <new>

void CCinematics::reload()
{
    for (unsigned int i = 0; i < m_lCinematics.size(); ++i) {
        if (m_lCinematics[i]) {
            m_lCinematics[i]->~CCinematic();
            Ogre::NedAllocImpl::deallocBytes(m_lCinematics[i]);
            m_lCinematics[i] = NULL;
        }
        m_lCinematics[i] = NULL;
    }
    m_lCinematics.clear();
    TArrayList<std::wstring> files(10);
    CFileSystem::getSingleton()->getFileList(m_sPath, files, L"*.dat", true, true, false, false);
    m_lCinematics.setGrowBy(files.size() + 1);
    for (unsigned int i = 0; i < files.size(); ++i) {
        CDataGroup group(EMPTY_WSTRING, NULL, 20, 10, NULL);
        group.LoadFile(files[i], static_cast<CTimerStatics*>(NULL));
        CCinematic* cinematic = new (Ogre::NedAllocImpl::allocBytes(sizeof(CCinematic), NULL, 0, NULL)) CCinematic;
        cinematic->load(&group);
        m_mapCinematics[cinematic->m_sName] = m_lCinematics.size();
        m_lCinematics.add(cinematic);
    }
}
