#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "RandomNames.h"

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
