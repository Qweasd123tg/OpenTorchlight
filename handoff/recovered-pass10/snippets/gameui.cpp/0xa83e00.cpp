void CGameUI::setCursorState(ECursorState state)
{
    if (m_cursorState != state)
    {
        m_cursorState = state;
        updateHardwareCursor();
    }
}
