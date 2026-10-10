CCharacter* CLevel::getRandomMonster()
{
    int count = 0;
    for (TLinkedListNode<CCharacter*>* node = m_pCharacters->getHead(); node; node = node->m_pNext) ++count;
    int selected = UTILITIES::randomIntegerBetween(0, count);
    for (TLinkedListNode<CCharacter*>* node = m_pCharacters->getHead(); node; node = node->m_pNext) {
        if (--selected < 0) return node->m_Data;
    }
    return NULL;
}
