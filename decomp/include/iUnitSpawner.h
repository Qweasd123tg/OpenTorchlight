#ifndef IUNITSPAWNER_H
#define IUNITSPAWNER_H
class CUnitSpawner;
class CPositionableObject;
class iUnitSpawner
{
public:
    virtual ~iUnitSpawner();
    virtual void unitSpawnedFromUnitSpawner(CUnitSpawner* spawner, CPositionableObject* unit) = 0;
};
#endif
