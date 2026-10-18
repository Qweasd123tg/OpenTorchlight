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

#include "Layout.h"

void CUnitSpawner::stopAllParticles()
{
    for(unsigned int i=0;i<m_spawnLayouts.size();++i) static_cast<CLayout*>(m_spawnLayouts[i])->stop(false);
}
void CUnitSpawner::reset()
{
    m_reset188=0; m_reset1a0=0; m_reset184=0; m_reset18c=0;
    for(unsigned int i=0;i<m_spawnLayouts.size();++i) {
        static_cast<CLayout*>(m_spawnLayouts[i])->stop(false);
        m_spawnLayouts[i]->setVisible(false);
    }
}
void CUnitSpawner::clear()
{
    for(unsigned int i=0;i<m_spawnLayouts.size();++i) {
        static_cast<CLayout*>(m_spawnLayouts[i])->stop(false);
        m_spawnLayouts[i]->setVisible(false);
    }
}
