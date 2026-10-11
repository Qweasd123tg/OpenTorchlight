#ifndef OTL_GAMEUI_TEXT_EVENT_LIST_H
#define OTL_GAMEUI_TEXT_EVENT_LIST_H
#include "TextEvent.h"
#include "TLinkedList.h"
namespace gameui_create_detail {
// Exact inlined one-pointer list shell. Do not expand the shared partial list
// declaration or initialize bytes the original leaves untouched.
struct TextEventList : Ogre::GeneralAllocatedObject {
    TLinkedListNode<CTextEvent*>* head;
    TextEventList():head(NULL){}
    // Pool nodes and their event pointees are owned independently of windows.
    inline __attribute__((always_inline)) ~TextEventList() {
        TLinkedListNode<CTextEvent*>* node=head;
        while(node) {
            TLinkedListNode<CTextEvent*>* next=node->m_pNext;
            node->m_pPrevious=NULL;
            node->m_pNext=NULL;
            delete node->m_Data;
            delete node;
            node=next;
        }
        head=NULL;
    }
    inline __attribute__((always_inline)) void clearNodes() {
        TLinkedListNode<CTextEvent*>* node=head;
        while(node) {
            TLinkedListNode<CTextEvent*>* next=node->m_pNext;
            node->m_pPrevious=NULL;
            node->m_pNext=NULL;
            delete node;
            node=next;
        }
        head=NULL;
    }
    inline __attribute__((always_inline)) void prepend(CTextEvent* event) {
        TLinkedListNode<CTextEvent*>* node=new TLinkedListNode<CTextEvent*>;
        node->m_Data=event;node->m_pNext=NULL;node->m_pPrevious=NULL;
        if(!head) {head=node;node->m_pNext=NULL;head->m_pPrevious=NULL;}
        else {node->m_pNext=head;head->m_pPrevious=node;head=node;}
    }
};
typedef char event_list_size[sizeof(TextEventList)==8?1:-1];
typedef char event_node_size[sizeof(TLinkedListNode<CTextEvent*>)==0x18?1:-1];
}
#endif
