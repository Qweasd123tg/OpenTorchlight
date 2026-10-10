void EditorSetPOVVelocityMult(float value)
{
    if (!gEditor->isActive()) return;
    gEditor->SetPovVelocityMult(value);
}
