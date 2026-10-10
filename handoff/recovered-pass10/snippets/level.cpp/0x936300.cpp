void CLevel::restartLevel()
{
    for (TLinkedListNode<CCharacter*>* node = m_pCharacters->getHead(); node; node = node->m_pNext) node->m_Data->levelResetting();
}
