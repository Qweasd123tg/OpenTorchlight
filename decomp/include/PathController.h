#ifndef PATHCONTROLLER_H
#define PATHCONTROLLER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreVector3.h>
#include <string>
#include "BaseUnit.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "SafePointer.h"

class CDataGroup;
class CCharacter;
class CPathNode;

class CPathController : public CPositionableObject
{
public:
    virtual ~CPathController();
    virtual void setEnabled(bool);
    virtual bool getEnabled();
    virtual void setVisible(bool);
    virtual void positionUpdated(const Ogre::Vector3&);
    float getClosestPctOfPath(const Ogre::Vector3&);
    Ogre::Vector3 caculatePointInFrontOfPlayer(CBaseUnit*);
    Ogre::Vector3 getNextPointAtPercent(float, CBaseUnit*, bool);
    void childNodeMoved();
    void setUnitInteractWith(std::wstring);
    CPathController(CResourceManager*);
    void caculateSpline();
    void initPathController();
    float* getArrayOfVectors(unsigned int&);
    void setPathName(const std::wstring&);
    void setNumberOfPathPoints(unsigned int);
    void setArrayOfVectors(const float*, unsigned int);
    void initObjectInEditor();

    // fields
    CDataGroup* m_pUnitInteractDataGroup;
    TArrayList<TSafePointer<CCharacter>*> m_units;
    std::wstring m_pCategory;
    std::wstring m_sUnitInteractWith;
    bool m_bVisible;
    bool m_bUnknown131;
    bool m_bUnknown132;
    bool m_bEnabled;
    bool m_bUnitRunsOnPath;
    bool m_bWalkToPlayer;
    bool m_bUnknown136;
    bool m_bUnknown137;
    TArrayList<CPathNode*> m_pathNodes;
    TArrayList<float> m_pathCoordinates; // +0x150
    TArrayList<float> m_pathDistances; // +0x168
    float m_fUnknown180;
    unsigned char m_gap184[0x4] __attribute__((aligned(4)));
    std::wstring m_pathName; // +0x188
    int m_iNumberOfPathPoints;
    bool m_bEnableUnitOnStart;

public:
    // Inline accessors behind the descriptors' property functions.
    void setEnableUnitOnStart(bool value) { m_bEnableUnitOnStart = value; }
    void setUnitRunsOnPath(bool value) { m_bUnitRunsOnPath = value; }
    void setWalkToPlayer(bool value) { m_bWalkToPlayer = value; }
    bool getWalkToPlayer() const { return m_bWalkToPlayer; }
    bool getUnitRunsOnPath() const { return m_bUnitRunsOnPath; }
    bool getEnableUnitOnStart() const { return m_bEnableUnitOnStart; }
    int getNumberOfPathPoints() const { return m_iNumberOfPathPoints; }
};

#endif
