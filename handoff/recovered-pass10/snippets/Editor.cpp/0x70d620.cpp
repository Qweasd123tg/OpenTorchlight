CEditorScene* CEditor::GetEditorScene(unsigned int index)
{
    if (index < m_EditorScenes.size()) return m_EditorScenes[index];
    return NULL;
}
