#include "EmptyStrings.h"
#include "DescriptorLoadConfiguration.h"

long long CDescriptorLoadConfiguration::getRemappedID(long long id)
{
    if (id == -1LL)
        return -1LL;

    std::map<long long, long long>::iterator found = m_Remaps.find(id);
    if (found == m_Remaps.end())
        return -1LL;

    return found->second;
}

CDescriptorLoadConfiguration::CDescriptorLoadConfiguration()
    : m_iVersion(-1), m_bFlag14(false), m_iValue18(0),
      m_iParentGuid(-1), m_pValue40(NULL)
{
}

CDescriptorLoadConfiguration::~CDescriptorLoadConfiguration()
{
}
