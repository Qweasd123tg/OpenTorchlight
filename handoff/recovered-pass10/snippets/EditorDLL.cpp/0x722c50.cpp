void EditorSetMonsterAutoSpawn(wchar_t* name)
{
    if (!gEditor->isActive()) return;
    gEditor->m_sUnknown198 = name;
}
