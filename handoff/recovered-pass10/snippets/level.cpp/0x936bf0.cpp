void CLevel::killAll()
{
    for (TLinkedListNode<CCharacter*>* node = m_pCharacters->getHead(); node; node = node->m_pNext) {
        CCharacter* character = node->m_Data;
        if (character && !dynamic_cast<CPlayer*>(character)) {
            if (character->alignment() == static_cast<EAlignment>(2) || node->m_Data->alignment() == static_cast<EAlignment>(4)) node->m_Data->die(NULL, NULL, 0.0f, false);
        }
    }
}
