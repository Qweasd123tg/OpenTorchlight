void CGameClient::setWindowActive(bool active)
{
    if (!active && m_pPlayer) {
        m_pPlayer->stopPathing();
        m_pPlayer->m_moveInputHeld = false;
        m_keys.flushAll(); m_mouse.flushAll();
        m_leftHeld = false; m_rightHeld = false; m_inputConsumed = true;
        if (m_pGameUI) m_pGameUI->setWindowActive(false);
    }
}
