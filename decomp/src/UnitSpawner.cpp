#include "EditorScene.h"
#include "EmptyStrings.h"
#include "GameVariables.h"
#include "Particle.h"
#include "UnitSpawner.h"
#include "iMissile.h"


// Imported source candidates; historical status is not fresh acceptance.
void CUnitSpawner::stop()
{
    m_editorSpawning=false;
    m_spawning=false;
}

bool CUnitSpawner::getParticlesStillVisible()
{
    for(unsigned int i=0;i<m_spawnLayouts.size();++i)if(m_spawnLayouts[i]->getNumberOfParticlesUpdating())return true;
    return false;
}
