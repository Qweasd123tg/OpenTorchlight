void reloadAffixes()
{
    if (!gEditor->isActive()) return;
    CMasterResourceManager::getSingleton()->m_effectGroups->reload();
}
