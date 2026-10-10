void CGameUI::requestSetGameState(EGameState state, EMenu menu)
{
    m_requestedGameState = state;
    m_requestedMenu = menu;
}
