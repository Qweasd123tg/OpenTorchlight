float CGameUI::leftScreenEdge()
{
    float edge = 0.0f;
    for (unsigned int i=0; i<m_submenus.size(); ++i) {
        if (!m_submenus[i]->isRight()) edge = std::max(edge, m_submenus[i]->screenEdge());
    }
    return edge;
}
