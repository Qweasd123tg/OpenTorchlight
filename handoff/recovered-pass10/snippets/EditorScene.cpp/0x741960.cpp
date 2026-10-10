void CEditorScene::InitScene(CResourceManager* manager, unsigned int flags)
{
    if (manager && !m_pUnknown178) {
        setResourceManager(manager);
        m_iUnknown188 = flags;
        m_pUnknown170 = CMasterResourceManager::getSingleton()->m_pSettings;
        m_pUnknown178 = getResourceManager()->getSceneManager();
        createDescriptors();
        setVisible(true);
    }
}
