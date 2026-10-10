void reloadRecipes()
{
    if (!gEditor->isActive()) return;
    CRecipes::getSingleton()->reload();
}
