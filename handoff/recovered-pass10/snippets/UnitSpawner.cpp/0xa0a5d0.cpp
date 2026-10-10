bool CUnitSpawner::getParticlesStillVisible()
{
    for(unsigned int i=0;i<m_spawnLayouts.size();++i)if(m_spawnLayouts[i]->getNumberOfParticlesUpdating())return true;
    return false;
}
