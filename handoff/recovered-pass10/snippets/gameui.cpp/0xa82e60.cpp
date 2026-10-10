float CGameUI::rightScreenEdge()
{
    float edge = 10000.0f;
    for (unsigned int i=0; i<m_submenus.size(); ++i) {
        if (m_submenus[i]->isRight()) edge = std::min(edge, m_submenus[i]->screenEdge());
    }
    return edge;
}
