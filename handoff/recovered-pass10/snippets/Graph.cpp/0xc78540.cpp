void CGraph::clear(unsigned int line)
{
    if (line >= m_iLineCount) return;
    if (m_Lines[line]) m_Lines[line]->removeAllControlPoints();
}
