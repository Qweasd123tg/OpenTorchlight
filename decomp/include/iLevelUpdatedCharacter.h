#ifndef ILEVELUPDATEDCHARACTER_H
#define ILEVELUPDATEDCHARACTER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "Character.h"
#include "Item.h"

class iLevelUpdatedCharacter
{
public:
    virtual ~iLevelUpdatedCharacter();
    virtual void characterUpdatedInLevel(float, CCharacter*) = 0;
    virtual void itemUpdatedInLevel(float, CItem*) = 0;

    // fields
};

#endif
