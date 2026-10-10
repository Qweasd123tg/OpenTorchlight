void CLevel::destroyIcons()
{
    if (m_pCharacters) {
        for (TLinkedListNode<CCharacter*>* node = m_pCharacters->getHead(); node; node = node->m_pNext) {
            node->m_Data->destroyIcons(); node->m_Data->destroyCharacterText();
        }
    }
    if (m_items) {
        for (TLinkedListNode<CItem*>* node = m_items->getHead(); node; node = node->m_pNext) {
            CEquipment* equipment = dynamic_cast<CEquipment*>(node->m_Data);
            if (equipment) equipment->destroyIcon();
            node->m_Data->destroyItemText();
        }
    }
}
