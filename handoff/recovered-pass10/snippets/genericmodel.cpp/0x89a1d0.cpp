void CGenericModel::setRenderBehind(bool behind)
{
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_NETBOOK_MODE) == 1) return;
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_renderableStates.size()); ++i) m_renderableStates[i].renderBehind = behind;
}
