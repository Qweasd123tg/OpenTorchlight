#ifndef TLINKEDLIST_H
#define TLINKEDLIST_H

#include <OgreMemoryAllocatorConfig.h>

#include <cstddef>

// Partial: doubly linked list used by CLevel for its units. The names are ours;
// the layout follows CLevel::addCharacter and CLevel::getCharacterByGuid.
template <class T>
class TLinkedListNode : public Ogre::GeneralAllocatedObject
{
public:
    T m_Data;
    TLinkedListNode<T>* m_pNext;
    TLinkedListNode<T>* m_pPrevious;
};

template <class T>
class TLinkedList : public Ogre::GeneralAllocatedObject
{
public:
    TLinkedListNode<T>* getHead() { return m_pHead; }

private:
    TLinkedListNode<T>* m_pHead;
};

#endif
