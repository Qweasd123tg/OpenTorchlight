void reloadQuests()
{
    if (!gEditor->isActive()) return;
    CQuestManager::getSingleton()->reloadQuests();
}
