void EditorDeleteAllObjectsInScene(unsigned int index)
{
    if (!gEditor->isActive()) return;
    CEditorScene* scene = gEditor->GetEditorScene(index);
    if (scene) gEditor->getObjectManager()->EditorDeleteAllObjectsInScene(scene);
}
