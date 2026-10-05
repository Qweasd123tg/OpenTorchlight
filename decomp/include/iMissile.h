#ifndef IMISSILE_H
#define IMISSILE_H

#include <OgreVector3.h>

class CCharacter;
class CMissile;
class CPositionableObject;

// Missile notifications implemented by Character and Equipment. The application
// callback returns bool: CMissile::doDamageToCharacter tests AL after slot +0x20.
class iMissile
{
public:
    virtual ~iMissile() {}

    virtual void missileBeingFired(CMissile* missile) = 0;
    virtual void missileDieing(CMissile* missile) = 0;
    virtual bool missileApplyingEffects(CMissile* missile, CCharacter* target, const Ogre::Vector3* position,
                                        float damageScale, float effectScale) = 0;
    virtual bool getCharacterCanBeHarmedByMissile(CMissile* missile, CCharacter* target) = 0;
    virtual bool missileValidateTargetBeforeLaunch(CMissile* missile, CPositionableObject* target,
                                                   Ogre::Vector3& position) = 0;
};

#endif
