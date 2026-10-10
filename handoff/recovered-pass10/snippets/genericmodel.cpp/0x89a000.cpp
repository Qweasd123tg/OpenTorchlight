void CGenericModel::setHighlighted(bool highlighted)
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_renderableStates.size()); ++i) m_renderableStates[i].highlighted = highlighted;
}
