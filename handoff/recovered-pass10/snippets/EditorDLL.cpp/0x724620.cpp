void reloadModFileFilter()
{
    if (!gEditor->isActive()) return;
    CFileSystem::getSingleton()->reload();
}
