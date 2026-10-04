#ifndef DAMAGESHAPE_H
#define DAMAGESHAPE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreCamera.h>
#include <OgreVector3.h>
#include "Character.h"
#include "Item.h"
#include "ResourceManager.h"
#include "Shape.h"
#include "iLevelUpdate.h"
#include "iLevelUpdatedCharacter.h"

class CDamageShape : public CShape, public iLevelUpdate, public iLevelUpdatedCharacter
{
public:
    virtual ~CDamageShape();
    virtual void setEnabled(bool);
    virtual long long updateLevelObject(float, Ogre::Camera*, const Ogre::Vector3&);
    virtual void characterUpdatedInLevel(float, CCharacter*);
    virtual void itemUpdatedInLevel(float, CItem*);
    virtual void getCanDoDamage(CCharacter*, float, const Ogre::Vector3&);
    virtual void doDamageToCharacter(float, CCharacter*, float);
    virtual void doDamageToItem(float, CItem*, float);
    void doInstantDamage();
    void setDamageOnlyUnitTypeByUnitTypeLoadIndex(unsigned int);
    unsigned int getDamageOnlyUnitTypeLoadIndex();
    CDamageShape(CResourceManager*);

    // fields
    long long m_iUnknown178;
    bool m_bUnknown180;
    unsigned char m_gap181[0x3];
    int m_iDamageType;
    int m_iUnknown188;
    int m_iAlignmentTypAllowedToDamage;
    float m_fUnknown190;
    float m_fUpdateInEditor;
    float m_fDelayTimer;
    float m_fTimer;
    int m_iDelayTimer;
    bool m_bLoopsForEver;
    bool m_bUpdateInEditor;
    bool m_bUnknown1A6;
    bool m_bDamageOverTime;
    bool m_bTargetOnlyDead;
    unsigned char m_gap1A9[0x3];
    int m_iNumLoops;
    int m_iUpdateInEditor;
    float m_fMinDamage;
    float m_fMaxDamage;
    float m_fUnknown1BC;
    float m_fUnknown1C0;
    float m_fUnknown1C4;
    unsigned char m_Unknown1C8[0x18] __attribute__((aligned(8)));
    unsigned char m_Unknown1E0[0x18] __attribute__((aligned(8)));
    int m_iTotalNumberOfTargets;
    unsigned char m_gap1FC[0x4] __attribute__((aligned(4)));
};

#endif
