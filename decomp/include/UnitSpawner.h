#ifndef UNITSPAWNER_H
#define UNITSPAWNER_H
#include "Shape.h"
#include "TArrayList.h"
#include "SafePointer.h"
#include <string>
class CCharacter;
class CGenericModel;
class iUnitSpawner;
class CEditorScene;
#include "iRandomWeight.h"
#include "iUnitObserver.h"
class CBaseUnit;
// Three original vtable groups; +0x234 is still opaque.
class CUnitSpawner : public CShape, public iRandomWeight, public iUnitObserver
{
    friend class CUnitSpawnerDescriptor;
    friend class CSkillEvent;
public:
    void setResourceSpawn(std::wstring name);
    bool spawnUnitByIndex(unsigned int index);
    void spawn();
    void update(float elapsed);
    CUnitSpawner(CResourceManager* resources);
    void createUnitsInMemory();
    void createParticleSystemAt(const std::wstring& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, unsigned int index);
    void createAndFireMissile(const std::wstring& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation);
    void hideAndDisableUnits(bool hide);
    void destroyUnits();
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
    bool m_unitsGiveXP; // +0x178
    bool m_unitsGiveLoot;
    bool m_spawnInCenter;
    bool m_spawnOnCreate;
    bool m_useSpawnAnimation;
    bool m_requiresLOS;
    bool m_mustSpawn;
    unsigned char m_gap17f[1];
    float m_spawnDuration; // +0x180
    union { int m_reset184; float m_time184; };
    union { int m_reset188; float m_time188; };
    int m_reset18c;
    unsigned int m_numberOfUnitsToCreate; // +0x190
    unsigned int m_pulseNumber;
    unsigned int m_counter198;
    unsigned int m_maxMonstersAtATime;
    union { int m_reset1a0; float m_time1a0; };
    int m_spawnLevelOverrideDelta;
    unsigned int m_randomWeight;
    unsigned char m_gap1ac[4];
    std::wstring m_category; // +0x1b0
    std::wstring m_resourceSpawn;
    bool m_editorSpawning; // +0x1c0
    bool m_spawning;
    bool m_targetPlayer;
    bool m_hasSpawnAnimation;
    bool m_destroyMeshOnDeath;
    unsigned char m_gap1c5[3];
    unsigned int m_unitsToCreateInMemory; // +0x1c8
    float m_time1cc;
    TArrayList<CEditorScene*> m_spawnLayouts; // +0x1d0
    TArrayList<TSafePointer<CBaseUnit>*> m_spawnedUnits; // +0x1e8
    TArrayList<TSafePointer<CCharacter>*> m_spawnedCharacters; // +0x200
    TArrayList<iUnitSpawner*> m_spawnListeners; // +0x218
    bool m_snapToGround; // +0x230
    unsigned char m_gap231[3];
    unsigned char m_unrecovered234[4];
    CGenericModel* m_editorPreview; // +0x238

};
typedef char check_unit_spawner_size[sizeof(CUnitSpawner)==0x240?1:-1];
#endif
