#ifndef UNITSPAWNER_H
#define UNITSPAWNER_H
#include "Shape.h"
#include "iRandomWeight.h"
#include "iUnitObserver.h"
class CBaseUnit;
// Partial: full size and three vtable groups, original addSpawnedUnit is called.
class CUnitSpawner : public CShape, public iRandomWeight, public iUnitObserver
{
public:
    virtual ~CUnitSpawner();
    virtual void unitStateChange(CBaseUnit* unit, EUNIT_STATES state);
    virtual unsigned int GetRandomWeight();
    virtual void SetRandomWeight(unsigned int weight);
    void addSpawnedUnit(CBaseUnit* unit);
private:
    unsigned char m_SpawnerData178[0x240-0x178];
};
#endif
