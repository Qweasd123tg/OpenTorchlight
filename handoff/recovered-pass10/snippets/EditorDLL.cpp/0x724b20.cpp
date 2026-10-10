void EditorSetChunkTemplateExits(int value)
{
    if (!gEditor->isActive()) return;
    gEditor->getObjectManager()->EditorSetChunkTemplateExits(value);
}
