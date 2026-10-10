void CGameClient::clearSceneManagerPassMaps()
{
    m_pendingPassClear = false;
    if (m_root) {
        Ogre::SceneManagerEnumerator::SceneManagerIterator it = m_root->getSceneManagerIterator();
        while (it.hasMoreElements()) {
            Ogre::SceneManager* scene = it.getNext();
            if (scene) { Ogre::RenderQueue* queue = scene->getRenderQueue(); if (queue) queue->clear(true); }
        }
        Ogre::Pass::processPendingPassUpdates();
    }
}
