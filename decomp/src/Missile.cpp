#include "EmptyStrings.h"
#include "GameVariables.h"
#include "Missile.h"
#include "Particle.h"
#include "iMissile.h"


// Imported source candidates; historical status is not fresh acceptance.
bool CMissile::getCollisionSphereVisible()
{
    return false;
}

bool CMissile::getAOESphereVisible()
{
    return false;
}

void CMissile::setCollisionSphereVisible(bool visible)
{
}

void CMissile::setAOESphereVisible(bool visible)
{
}

void CMissile::setRadiusOfMissile(float radius)
{
    m_fRadiusOfMissile=radius;
}

void CMissile::setAOERadius(float radius)
{
    m_fAOERadius=radius;
}

std::wstring CMissile::getParticleFile(EMISSILE_PARTICLES particle)
{
    if(m_particles[particle])return m_particleFiles[particle];
    return EMPTY_WSTRING;
}
