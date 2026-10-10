void CEditor::doUndo()
{
    if (m_Undos.size() > 0) {
        CUndo* undo = m_Undos.back();
        m_Undos.pop_back();
        undo->DoAsUndo();
        delete undo;
    }
}
