#ifndef UNITSPAWNERDESCRIPTORNAMES_H
#define UNITSPAWNERDESCRIPTORNAMES_H

#include <string>
#include "TArrayList.h"

static TArrayList<std::wstring> gParticleFiles(10);
static TArrayList<std::wstring> gMissileFiles(10);

static const std::wstring gSPAWN_TYPE_NAMES[] =
{
    L"Monsters",
    L"Items",
    L"Particle",
    L"Spawn Class",
    L"Missiles",
    L"Unit Type",
    L"Props",
};

#endif
