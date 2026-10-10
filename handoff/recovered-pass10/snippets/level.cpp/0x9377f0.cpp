void CLevel::deleteOpenPortals()
{
    if (m_items) {
        for (TLinkedListNode<CItem*>* node = m_items->getHead(); node; node = node->m_pNext) {
            if (node->m_Data->ISA(static_cast<UNITTYPES::EUNITTYPES>(43)) || node->m_Data->ISA(static_cast<UNITTYPES::EUNITTYPES>(171))) node->m_Data->m_bBaseUnitFlag190 = true;
        }
    }
    updateAutomapIcons();
}
