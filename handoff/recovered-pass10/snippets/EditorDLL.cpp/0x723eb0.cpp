void EditorRedo()
{
    if (!gEditor->isActive()) return;
    gEditor->doRedo();
}
