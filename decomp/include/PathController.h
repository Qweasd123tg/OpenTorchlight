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

class CDataGroup;

class CPathController : public CPositionableObject
{
public:
    virtual ~CPathController();
    virtual void setEnabled(bool);
    virtual bool getEnabled();
    virtual void setVisible(bool);
    virtual void positionUpdated(const Ogre::Vector3&);
    float getClosestPctOfPath(const Ogre::Vector3&);
    float caculatePointInFrontOfPlayer(CBaseUnit*);
    long long getNextPointAtPercent(float, CBaseUnit*, bool);
    void childNodeMoved();
    void setUnitInteractWith(std::wstring);
    CPathController(CResourceManager*);
    void caculateSpline();
    void initPathController();
    long long getArrayOfVectors(unsigned int&);
    void setPathName(const std::wstring&);
    void setNumberOfPathPoints(unsigned int);
    void setArrayOfVectors(const float*, unsigned int);
    void initObjectInEditor();

    // fields
    CDataGroup* m_pUnitInteractDataGroup;
    unsigned char m_Unknown108[0x18] __attribute__((aligned(8)));
    void* m_pCategory;
    std::wstring m_sUnitInteractWith;
    bool m_bVisible;
    bool m_bUnknown131;
    bool m_bUnknown132;
    bool m_bEnabled;
    bool m_bUnitRunsOnPath;
    bool m_bWalkToPlayer;
    bool m_bUnknown136;
    bool m_bUnknown137;
    unsigned char m_Unknown138[0x18] __attribute__((aligned(8)));
    unsigned char m_Unknown150[0x18] __attribute__((aligned(8)));
    unsigned char m_Unknown168[0x18] __attribute__((aligned(8)));
    float m_fUnknown180;
    unsigned char m_gap184[0x4] __attribute__((aligned(4)));
    void* m_pPathName;
    int m_iNumberOfPathPoints;
    bool m_bEnableUnitOnStart;
};

#endif
