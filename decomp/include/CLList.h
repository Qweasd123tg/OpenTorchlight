#ifndef CLLIST_H
#define CLLIST_H

#include "TLinkedList.h"

// The original owning list stores only its head; node names remain ours.
template <class T>
class CLList : public Ogre::GeneralAllocatedObject
{
public:
    typedef TLinkedListNode<T> Node;

    CLList() : m_pHead(NULL) {}
    ~CLList() { destroy(); }

    void destroy();

    // Preserve pointer access in the already recovered list users.
    operator Node*() const { return m_pHead; }
    Node* operator->() const { return m_pHead; }
    CLList& operator=(Node* head) { m_pHead = head; return *this; }

private:
    Node* m_pHead;
};

template <class T>
void CLList<T>::destroy()
{
    Node* node = m_pHead;
    while (node != NULL)
    {
        Node* next = node->m_pNext;
        node->m_pPrevious = NULL;
        node->m_pNext = NULL;
        delete node->m_Data;
        delete node;
        node = next;
    }
    m_pHead = NULL;
}

#endif
