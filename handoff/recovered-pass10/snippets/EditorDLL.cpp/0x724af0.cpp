void EditorSetChunkTemplateExit(int index, float x, float y, float z)
{
    if (!gEditor->isActive()) return;
    gEditor->getObjectManager()->EditorSetChunkTemplateExit(index, x, y, z);
}
