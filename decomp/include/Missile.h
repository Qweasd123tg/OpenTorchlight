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
    virtual bool update(float);
    bool getCollisionSphereVisible();
    void setCollisionSphereVisible(bool);
    bool getAOESphereVisible();
    void setAOESphereVisible(bool);
    float getRateOFire();
    void setRateOFire(float);
    void resetMissile();
    void setRadiusOfMissile(float);
    void setAOERadius(float);
    void placeSphere();
    CCharacter* getClosestTarget(const Ogre::Quaternion&, const Ogre::Vector3&);
    void removeArchFromMissile(float);
    void addArchFromMissile(float);
    bool doDamageToCharacter(CCharacter*, const Ogre::Vector3&, float, float);
    bool handleDeathOfMissile(float);
    std::wstring getParticleFile(EMISSILE_PARTICLES);
    void setTarget(CPositionableObject*);
    void initialize();
    void doAOEDamage(CBaseUnit*);
    void calculateLaunchOrientation(const Ogre::Vector3&, const Ogre::Vector3&);
    void killMissile();
    Ogre::Vector3 ricochetMissile(const Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Vector3&, const Ogre::Vector3&);
    Ogre::Vector3 updatePositionByVelocity(float);
    void setParticleFile(EMISSILE_PARTICLES, std::wstring);
    bool handleMissileHitUnit(CBaseUnit*, Ogre::Vector3);
    int checkCollision(Ogre::Vector3, Ogre::Vector3, Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&, CBaseUnit**);
    void fireMissile(CBaseUnit*, Ogre::Vector3, const Ogre::Quaternion&, CPositionableObject*, Ogre::Vector3);
    CMissile(CResourceManager*);
    CMissile(CResourceManager*, const CMissile*);

    // fields
    union {
        struct { CParticle* m_pPositionableObject; CParticle* m_pParticle; CParticle* m_pPositionableObject_110; CParticle* m_pPositionableObject_118; };
        CParticle* m_particles[4];
    };
    std::wstring m_particleFiles[4];
    bool m_bStartAtFullVelocity;
    bool m_bUnknown141;
    bool m_bPiercing;
    bool m_bCanVerticalAim;
    bool m_bUnknown144;
    unsigned char m_gap145[0x3];
    Ogre::Vector3 m_resetVector148 __attribute__((aligned(8)));
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
    Ogre::Vector3 m_targetPosition;
    float m_fUnknown198;
    float m_fMissileArchHeight;
    Ogre::Vector3 m_resetVector1A0 __attribute__((aligned(8)));
    float m_fLifetime;
    float m_fLifetimeRemaining;
    float m_fUnknown1B4;
    float m_fDistanceAllowedToTraveled;
    float m_fUnknown1BC;
    float m_fUnknown1C0;
    float m_iUnknown1C4;
    TArrayList<iMissile*> m_Listeners;
    Ogre::Vector3 m_previousVelocityPosition;
    unsigned char m_gap1EC[0x4] __attribute__((aligned(4)));
    TArrayList<Ogre::SceneNode*> m_sceneNodes;
    int m_iUnknown208;
    unsigned char m_gap20C[0x4] __attribute__((aligned(4)));
    CPath* m_pPath;
    float m_fUnknown218;
    unsigned char m_gap21C[0x4] __attribute__((aligned(4)));
    TSafePointer<CBaseUnit> m_owner;
    TSafePointer<CPositionableObject> m_target;
    TSafePointer<CCharacter> m_targetCharacter;
    float m_fTargetHomingValue;
    float m_fHomeAfterXSeconds;
    float m_fUnknown258;
    float m_fUnknown25C;
    float m_fTargetingAngle;
    float m_fMaxTurnRate;
    float m_fTurnAcceleration;
    float m_fRandomizedTurnAcceleration;
    float m_fRandomizedTurnUpdate;
    float m_fUnknown274;
    float m_fUnknown278;
    float m_fAOEDamageScale;
    float m_fSoakScale;
    float m_fInherentMinDMGPercent;
    float m_fInherentMaxDMGPercent;
    float m_fInherentKnockback;
    float m_fUnknown290;
    bool m_bUnknown294;
    unsigned char m_gap295[0x3];
    TArrayList<CBaseUnit*> m_collisionUnits;
    TArrayList<bool> m_collisionStates;
    std::wstring m_sMissileName;
    int m_iDamageType;
};

#endif
