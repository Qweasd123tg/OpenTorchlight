bool CGameClient::processMenuInput(void* window, float elapsed, bool enabled)
{
    if (m_pGameUI && !m_pGameUI->processInput(this, window, elapsed, enabled)) {
        if (m_mouse.buttonHeld(static_cast<EMouseButton>(0))) m_leftHeld = true;
        if (m_mouse.buttonHeld(static_cast<EMouseButton>(1))) m_rightHeld = true;
        m_inputConsumed = true;
    }
    m_mouse.update(window);
    return true;
}
