#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <string>

#include "UnitTypes.h"

// Partial: the unit type hierarchy (media/unittypes.hie); members are declared
// as Hierarchy.cpp is recovered.
class CHierarchy
{
public:
    UNITTYPES::EUNITTYPES getTypeIDByName(const std::wstring& name);
};

#endif
