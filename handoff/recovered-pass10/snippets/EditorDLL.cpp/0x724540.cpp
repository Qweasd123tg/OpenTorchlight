void reloadUnitThemes()
{
    if (!gEditor->isActive()) return;
    CUnitThemes::getSingleton()->reload();
}
