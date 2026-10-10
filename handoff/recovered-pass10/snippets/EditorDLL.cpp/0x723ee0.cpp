void EditorUndo()
{
    if (!gEditor->isActive()) return;
    gEditor->doUndo();
}
