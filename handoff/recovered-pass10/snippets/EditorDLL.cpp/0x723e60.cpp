void EditorGetUndoRedoCounts(unsigned int& undo, unsigned int& redo)
{
    if (!gEditor->isActive()) return;
    undo = gEditor->getUndoSize();
    redo = gEditor->getRedoSize();
}
