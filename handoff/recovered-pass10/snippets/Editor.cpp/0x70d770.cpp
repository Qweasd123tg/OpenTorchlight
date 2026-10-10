void CEditor::doRedo()
{
    if (m_Redos.size() > 0) {
        CUndo* undo = m_Redos.back();
        m_Redos.pop_back();
        undo->DoAsRedo();
        delete undo;
    }
}
