void reloadCinematics()
{
    if (!gEditor->isActive()) return;
    CCinematics::getSingleton()->reload();
}
