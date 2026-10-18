#ifndef UNITSPAWNER_H
#define UNITSPAWNER_H
#include "Shape.h"
#include "TArrayList.h"
class CEditorScene;
#include "iRandomWeight.h"
#include "iUnitObserver.h"
class CBaseUnit;
// Partial: full size and three vtable groups, original addSpawnedUnit is called.
class CUnitSpawner : public CShape, public iRandomWeight, public iUnitObserver
{
public:
    void reset();
    void clear();
    void stopAllParticles();
    void stop();
    bool getParticlesStillVisible();
    virtual ~CUnitSpawner();
    virtual void unitStateChange(CBaseUnit* unit, EUNIT_STATES state);
    virtual unsigned int GetRandomWeight();
    virtual void SetRandomWeight(unsigned int weight);
    void addSpawnedUnit(CBaseUnit* unit);
private:
    unsigned char m_SpawnerData178[0x184-0x178];
    int m_reset184;
    int m_reset188;
    int m_reset18c;
    unsigned char m_SpawnerData190[0x1a0-0x190];
    int m_reset1a0;
    unsigned char m_SpawnerData1a4[0x1c0-0x1a4];
    bool m_editorSpawning;
    bool m_spawning;
    unsigned char m_gap1c2[0xe];
    TArrayList<CEditorScene*> m_spawnLayouts;
    unsigned char m_gap1e8[0x240-0x1e8];
};
#endif
