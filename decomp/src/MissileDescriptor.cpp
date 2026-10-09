#include "EditorScene.h"
#include "Missile.h"
#include "EmptyStrings.h"
#include "MissileDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"

CMissileDescriptor::CMissileDescriptor()
    : CPositionableObjectDescriptor(L"Missile", L"MISSILE", L"missile", true, false, false, false, false)
{
    AddProperty(L"PARTICLES", L"RELEASE", L"Release Particle", (void*)Set_setParticleFileKMISSILE_PARTICLE_RELEASE, (void*)Get_getParticleFileKMISSILE_PARTICLE_RELEASE, VARIABLE_TYPE_STRING, 512);
    AddProperty(L"PARTICLES", L"ACTIVE", L"Active particle", (void*)Set_setParticleFileKMISSILE_PARTICLE_ALIVE, (void*)Get_getParticleFileKMISSILE_PARTICLE_ALIVE, VARIABLE_TYPE_STRING, 512);
    AddProperty(L"PARTICLES", L"HIT", L"Hit Particle", (void*)Set_setParticleFileKMISSILE_PARTICLE_HIT, (void*)Get_getParticleFileKMISSILE_PARTICLE_HIT, VARIABLE_TYPE_STRING, 512);
    AddProperty(L"PARTICLES", L"DIE", L"Die Particle", (void*)Set_setParticleFileKMISSILE_PARTICLE_DIE, (void*)Get_getParticleFileKMISSILE_PARTICLE_DIE, VARIABLE_TYPE_STRING, 512);
    AddProperty(L"PROPERTIES", L"NUM RICOCHETS", L"Number of Ricochets", (void*)Set_setNumberOfRicochets, (void*)Get_getNumberOfRicochets, VARIABLE_TYPE_UNSIGNED_INTEGER, 0);
    AddProperty(L"PROPERTIES", L"MAX DISTANCE", L"The distance allowed to travel before killing the missile.", (void*)Set_setDistanceAllowedToTraveled, (void*)Get_getDistanceAllowedToTraveled, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"RADIUS", L"Radius of the missile", (void*)Set_setRadiusOfMissile, (void*)Get_getRadiusOfMissile, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"AOE RAIDUS", L"The radius of the explosion.", (void*)Set_setAOERadius, (void*)Get_getAOERadius, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"MAX VELOCITY", L"Max velocity of the missile", (void*)Set_setMaxVelocity, (void*)Get_getMaxVelocity, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"FRICTION", L"Friction of the missile", (void*)Set_setFriction, (void*)Get_getFriction, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"FORCE", L"Force applied per second", (void*)Set_setForceAppliedPerSecond, (void*)Get_getForceAppliedPerSecond, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"FULL VELOCITY", L"If true the missile starts at full velocity", (void*)Set_setStartAtFullVelocity, (void*)Get_getStartAtFullVelocity, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"MISSILE NAME", L"Unique Name of the missile to use for refing", (void*)Set_setMissileName, (void*)Get_getMissileName, VARIABLE_TYPE_STRING, 0);
    AddProperty(L"PROPERTIES", L"HOMING SPEED", L"A number between 0-1 that says how fast the missile can turn towards the target. 0 - no follow and 1 being fast follow.", (void*)Set_setTargetHomingValue, (void*)Get_getTargetHomingValue, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"TARGETING ANGLE", L"The angle the missile can target enemies.", (void*)Set_setTargetingAngle, (void*)Get_getTargetingAngle, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"EDITOR_ONLY", L"REPEAT RATE", L"Repeat rate inside the editor for shooting the missile", (void*)Set_setRateOFire, (void*)Get_getRateOFire, VARIABLE_TYPE_FLOAT, 256);
    AddProperty(L"EDITOR_ONLY", L"COLLISION RADIUS", L"Will turn on and off the collision radius.", (void*)Set_setCollisionSphereVisible, (void*)Get_getCollisionSphereVisible, VARIABLE_TYPE_BOOL, 256);
    AddProperty(L"EDITOR_ONLY", L"AOE RADIUS", L"Will turn on and off the AOE radius.", (void*)Set_setAOESphereVisible, (void*)Get_getAOESphereVisible, VARIABLE_TYPE_BOOL, 256);
    AddProperty(L"PROPERTIES", L"TRACK GROUND", L"Tracks the ground.", (void*)Set_setTrackGround, (void*)Get_getTrackGround, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"TARGET POSITION", L"Missile will go to the target and end.", (void*)Set_setTargetsPosition, (void*)Get_getTargetsPosition, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"COLLIDES WITH OBJECTS", L"Missile will collide with units", (void*)Set_setCollidesWithObjects, (void*)Get_getCollidesWithObjects, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"ARCH HEIGHT", L"The height of the arch the missile will use.", (void*)Set_setMissileArchHeight, (void*)Get_getMissileArchHeight, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"HOME AFTER X SECONDS", L"The amount of time before homing kicks in.", (void*)Set_setHomeAfterXSeconds, (void*)Get_getHomeAfterXSeconds, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"PIERCING", L"Pierces units.", (void*)Set_setPiercing, (void*)Get_getPiercing, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"MAX TURN RATE", L"Max turn rate", (void*)Set_setMaxTurnRate, (void*)Get_getMaxTurnRate, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"TURN ACCELERATION", L"turn acceleration", (void*)Set_setTurnAcceleration, (void*)Get_getTurnAcceleration, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"TURN RANDOMIZATION", L"Randomized turn acceleration", (void*)Set_setRandomizedTurnAcceleration, (void*)Get_getRandomizedTurnAcceleration, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"RANDOMIZATION RATE", L"Randomized turn rate", (void*)Set_setRandomizedTurnUpdate, (void*)Get_getRandomizedTurnUpdate, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"AOE DAMAGE SCALE", L"AOE scale of base damage", (void*)Set_setAOEDamageScale, (void*)Get_getAOEDamageScale, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"DAMAGE SOAK SCALE", L"scale damage soak on impact", (void*)Set_setSoakScale, (void*)Get_getSoakScale, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"VERTICAL AIMING", L"Can aim up or down vertically", (void*)Set_setCanVerticalAim, (void*)Get_getCanVerticalAim, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"DAMAGE", L"MIN PERCENT DAMAGE", L"Min Percent of the damage graph", (void*)Set_setInherentMinDMGPercent, (void*)Get_getInherentMinDMGPercent, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"DAMAGE", L"MAX PERCENT DAMAGE", L"Max Percent of the damage graph", (void*)Set_setInherentMaxDMGPercent, (void*)Get_getInherentMaxDMGPercent, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"DAMAGE", L"FORCE", L"Force of missile", (void*)Set_setInherentKnockback, (void*)Get_getInherentKnockback, VARIABLE_TYPE_FLOAT, 0);
    AddPropertyWithInterpreterFunctions(L"DAMAGE", L"DAMAGE TYPE", L"The type of damage used", (void*)Set_setDamageType, (void*)Get_getDamageType, GetDamageTypeIDByString, GetDamageTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
}

CMissileDescriptor::~CMissileDescriptor()
{
}

void CMissileDescriptor::update(float)
{
}

CEditorBaseObject* CMissileDescriptor::CreateObject(CEditorScene* scene)
{
    return new CMissile(scene->getResourceManager());
}
