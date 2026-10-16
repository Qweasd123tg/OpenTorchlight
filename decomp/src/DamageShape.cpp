#include "DamageShape.h"
#include "Hierarchy.h"
#include "MasterResourceManager.h"

void CDamageShape::setDamageOnlyUnitTypeByUnitTypeLoadIndex(unsigned int index)
{
    CHierarchy* hierarchy = CMasterResourceManager::getSingleton()->m_pHierarchy;
    unsigned int type = ~0u;
    if (index < hierarchy->m_types.size()) type = hierarchy->m_types[index];
    m_iUnknown188 = type;
}
unsigned int CDamageShape::getDamageOnlyUnitTypeLoadIndex()
{
    std::wstring name = CMasterResourceManager::getSingleton()->m_pHierarchy->getTypeName(m_iUnknown188);
    CHierarchy* hierarchy = CMasterResourceManager::getSingleton()->m_pHierarchy;
    unsigned int type = hierarchy->getTypeIDByName(name);
    for (unsigned int i = 0; i < hierarchy->m_types.size(); ++i)
        if (hierarchy->m_types[i] == type) return i;
    return ~0u;
}
