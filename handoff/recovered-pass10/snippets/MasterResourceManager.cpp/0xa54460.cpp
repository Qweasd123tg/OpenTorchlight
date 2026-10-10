void CMasterResourceManager::destroyStash()
{
    if (m_stash) { delete m_stash; m_stash = NULL; }
    m_stash = NULL;
}
