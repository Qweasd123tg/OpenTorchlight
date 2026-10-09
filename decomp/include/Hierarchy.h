#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <string>

#include "UnitTypes.h"

// Partial: the unit type hierarchy (media/unittypes.hie); members are declared
// as Hierarchy.cpp is recovered.
class CHierarchy
{
public:
    // Typed parameters from the original symbol; Boolean tail contract from CResourceManager::ISA.
    bool ISA(unsigned int type, unsigned int parent);
    UNITTYPES::EUNITTYPES getTypeIDByName(const std::wstring& name);
};

#endif
