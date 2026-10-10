void CGameClient::togglePlayerLight()
{
    if (m_playerLightNode && m_playerLight) {
        if (m_playerLight->getParentSceneNode()) m_playerLightNode->detachObject(m_playerLight);
        else m_playerLightNode->attachObject(m_playerLight);
    }
}
