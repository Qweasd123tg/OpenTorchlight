#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "RandomNames.h"

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

CRandomNames::~CRandomNames()
{
    if (m_pRandomizer) {
        delete m_pRandomizer;
        m_pRandomizer = NULL;
    }
    m_prefixes.deleteAll();
    g_pRandomNames = NULL;
}
