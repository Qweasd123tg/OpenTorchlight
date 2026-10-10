void reloadMissiles()
{
    if (!gEditor->isActive()) return;
    CMissilePreloader::getSinglelton()->reloadMissiles();
}
