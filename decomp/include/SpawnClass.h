#ifndef SPAWNCLASS_H
#define SPAWNCLASS_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "Character.h"
#include "DataGroup.h"
#include "RunicCore.h"
#include "TArrayList.h"
class CSpawnClassData;
class CSpawningData : public CRunicCore
{
public:
    virtual ~CSpawningData();
    int m_odds; // +0x10; non-positive weights use 100 in layout selection.
    int m_rarityOverride;
    int m_flags;
    int m_minCount;
    int m_maxCount;
    int m_levelBonus;
    float m_magicFind;
private:
    unsigned char m_unrecovered2c[4];
};

typedef char check_spawning_data_size[sizeof(CSpawningData) == 0x30 ? 1 : -1];

// Source name for the original unnamed 16-byte pair in addSpawnClassData.
struct SpawnClassEntry
{
    CSpawningData* data;
    CSpawnClassData* spawnClassData;
};

class CSpawnClass : public CRunicCore
{
public:
    virtual ~CSpawnClass();
    int calculateNumberOfChoices(CCharacter*, int, int, int, int);
    CSpawnClass(const wchar_t*);
    int rollSpawnClass(TArrayList<CDataGroup*>&, TArrayList<bool>*, CCharacter*, CCharacter*, int, unsigned int, int, int, int, int);
    void addSpawnClassData(CDataGroup*, CSpawnClassData*);

    // fields
    TArrayList<SpawnClassEntry*> m_entries;
    std::wstring m_name;
    int m_iUnknown30;
};

#endif
