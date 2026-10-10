void EditorSetMouseWheelDelta(int value)
{
    if (!gEditor->isActive()) return;
    gEditor->SetMouseWheelDelta(value);
}
