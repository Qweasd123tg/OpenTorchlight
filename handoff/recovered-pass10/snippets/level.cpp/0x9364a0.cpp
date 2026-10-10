void CLevel::updateCharacterAnimation(float elapsed, float scale, CPlayer* player)
{
    float scaled = scale * elapsed;
    for (TLinkedListNode<CCharacter*>* node = m_activeCharacters->getHead(); node; node = node->m_pNext) {
        if (node->m_Data == player) player->updateAnimation(elapsed);
        else node->m_Data->updateAnimation(scaled);
    }
    for (TLinkedListNode<CItem*>* node = m_activeItems->getHead(); node; node = node->m_pNext) node->m_Data->updateAnimation(scaled);
}
