#ifndef MISSILE_H
#define MISSILE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreQuaternion.h>
#include <OgreVector3.h>
#include <string>
#include "BaseUnit.h"
#include "Character.h"
#include "GameEnums.h"
#include "Particle.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "RunicCore.h"
class CPath;
class iMissile;

class CMissile : public CPositionableObject
{
public:
    virtual ~CMissile();
    virtual long long update(float);
    bool getCollisionSphereVisible();
    void setCollisionSphereVisible(bool);
    bool getAOESphereVisible();
    void setAOESphereVisible(bool);
    int getRateOFire();
    void setRateOFire(float);
    void resetMissile();
    void setRadiusOfMissile(float);
    void setAOERadius(float);
    void placeSphere();
    long long getClosestTarget(const Ogre::Quaternion&, const Ogre::Vector3&);
    void removeArchFromMissile(float);
    void addArchFromMissile(float);
    long long doDamageToCharacter(CCharacter*, const Ogre::Vector3&, float, float);
    long long handleDeathOfMissile(float);
    std::wstring getParticleFile(EMISSILE_PARTICLES);
    void setTarget(CPositionableObject*);
    void initialize();
    void doAOEDamage(CBaseUnit*);
    void calculateLaunchOrientation(const Ogre::Vector3&, const Ogre::Vector3&);
    void killMissile();
    void ricochetMissile(const Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Vector3&);
    void updatePositionByVelocity(float);
    void setParticleFile(EMISSILE_PARTICLES, std::wstring);
    long long handleMissileHitUnit(CBaseUnit*, Ogre::Vector3);
    int checkCollision(Ogre::Vector3, Ogre::Vector3, Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&, CBaseUnit**);
    void fireMissile(CBaseUnit*, Ogre::Vector3, const Ogre::Quaternion&, CPositionableObject*, Ogre::Vector3);
    CMissile(CResourceManager*);
    CMissile(CResourceManager*, const CMissile*);

    // fields
    union {
        struct { CPositionableObject* m_pPositionableObject; CParticle* m_pParticle; CPositionableObject* m_pPositionableObject_110; CPositionableObject* m_pPositionableObject_118; };
        CPositionableObject* m_particles[4];
    };
    std::wstring m_particleFiles[4];
    bool m_bStartAtFullVelocity;
    bool m_bUnknown141;
    bool m_bPiercing;
    bool m_bCanVerticalAim;
    bool m_bUnknown144;
    unsigned char m_gap145[0x3];
    long long m_Unknown148;
    float m_fUnknown150;
    float m_fForceAppliedPerSecond;
    float m_fMaxVelocity;
    float m_fFriction;
    float m_fAOERadius;
    int m_iUnknown164;
    int m_iUnknown168;
    float m_fUnknown16C;
    float m_fUnknown170;
    float m_fUnknown174;
    float m_fRadiusOfMissile;
    int m_iUnknown17C;
    int m_iNumberOfRicochets;
    bool m_bUnknown184;
    bool m_bUnknown185;
    bool m_bTargetsPosition;
    bool m_bCollidesWithObjects;
    bool m_bTrackGround;
    unsigned char m_gap189[0x3];
    unsigned char m_fUnknown18C[0x8] __attribute__((aligned(4)));
    float m_fUnknown194;
    float m_fUnknown198;
    float m_fMissileArchHeight;
    unsigned char m_fUnknown1A0[0x8] __attribute__((aligned(8)));
    float m_fUnknown1A8;
    int m_iUnknown1AC;
    int m_iUnknown1B0;
    float m_fUnknown1B4;
    float m_fDistanceAllowedToTraveled;
    float m_fUnknown1BC;
    float m_fUnknown1C0;
    int m_iUnknown1C4;
    TArrayList<iMissile*> m_Listeners;
    int m_iUnknown1E0;
    float m_fUnknown1E4;
    int m_iUnknown1E8;
    unsigned char m_gap1EC[0x4] __attribute__((aligned(4)));
    void* m_pUnknown1F0;
    int m_iUnknown1F8;
    int m_iUnknown1FC;
    int m_iUnknown200;
    unsigned char m_gap204[0x4] __attribute__((aligned(4)));
    int m_iUnknown208;
    unsigned char m_gap20C[0x4] __attribute__((aligned(4)));
    CPath* m_pPath;
    float m_fUnknown218;
    unsigned char m_gap21C[0x4] __attribute__((aligned(4)));
    CRunicCore* m_pRunicCore;
    int m_iUnknown228;
    unsigned char m_gap22C[0x4] __attribute__((aligned(4)));
    CRunicCore* m_pRunicCore_230;
    int m_iUnknown238;
    unsigned char m_gap23C[0x4] __attribute__((aligned(4)));
    CRunicCore* m_pRunicCore_240;
    int m_iUnknown248;
    unsigned char m_gap24C[0x4] __attribute__((aligned(4)));
    float m_fTargetHomingValue;
    int m_iHomeAfterXSeconds;
    float m_fUnknown258;
    float m_fUnknown25C;
    float m_fTargetingAngle;
    float m_fMaxTurnRate;
    float m_fTurnAcceleration;
    int m_iRandomizedTurnAcceleration;
    float m_fRandomizedTurnUpdate;
    float m_fUnknown274;
    float m_fUnknown278;
    int m_iAOEDamageScale;
    int m_iSoakScale;
    float m_fInherentMinDMGPercent;
    float m_fInherentMaxDMGPercent;
    float m_fInherentKnockback;
    float m_fUnknown290;
    bool m_bUnknown294;
    unsigned char m_gap295[0x3];
    void* m_pUnknown298;
    int m_iUnknown2A0;
    int m_iUnknown2A4;
    int m_iUnknown2A8;
    unsigned char m_gap2AC[0x4] __attribute__((aligned(4)));
    void* m_pUnknown2B0;
    int m_iUnknown2B8;
    int m_iUnknown2BC;
    int m_iUnknown2C0;
    unsigned char m_gap2C4[0x4] __attribute__((aligned(4)));
    std::wstring m_sMissileName;
    int m_iDamageType;
};

#endif
