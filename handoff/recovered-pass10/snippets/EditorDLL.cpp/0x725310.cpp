void EditorWindowHasFocus(bool value)
{
    if (!gEditor->isActive()) return;
    gEditor->SetRenderWindowHasFocus(value);
}
