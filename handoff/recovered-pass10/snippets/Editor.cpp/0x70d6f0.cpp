void CEditor::deleteAllUndos()
{
    for (std::list<CUndo*>::iterator it = m_Redos.begin(); it != m_Redos.end(); ++it) {
        if (*it) { delete *it; *it = NULL; }
    }
    for (std::list<CUndo*>::iterator it = m_Undos.begin(); it != m_Undos.end(); ++it) {
        if (*it) { delete *it; *it = NULL; }
    }
}
