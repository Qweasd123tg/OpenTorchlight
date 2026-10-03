#ifndef LEVEL_H
#define LEVEL_H

#include "RunicCore.h"

class CCharacter;

// Partial: members are declared as level.cpp is recovered.
class CLevel : public CRunicCore
{
public:
    CCharacter* getCharacterByGuid(long long guid);
};

#endif
