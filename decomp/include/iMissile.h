#ifndef IMISSILE_H
#define IMISSILE_H

#include <OgreVector3.h>

class CCharacter;
class CMissile;
class CPositionableObject;

// Receives missile notifications (implemented by CCharacter). Return types are
// not verified yet.
class iMissile
{
public:
    virtual ~iMissile() {}

    virtual void missileBeingFired(CMissile* missile) = 0;
    virtual void missileDieing(CMissile* missile) = 0;
    virtual void missileApplyingEffects(CMissile* missile, CCharacter* target, const Ogre::Vector3* position,
                                        float damageScale, float effectScale) = 0;
    virtual bool getCharacterCanBeHarmedByMissile(CMissile* missile, CCharacter* target) = 0;
    virtual bool missileValidateTargetBeforeLaunch(CMissile* missile, CPositionableObject* target,
                                                   Ogre::Vector3& position) = 0;
};

#endif
