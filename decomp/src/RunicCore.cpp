#include "EmptyStrings.h"
#include "RunicCore.h"

int g_iTotalCountOfObjects;

CRunicCore::CRunicCore()
    : m_pSafePointers(NULL)
{
    g_iTotalCountOfObjects++;
}

void CRunicCore::removeSafePointer(TSafePointer<void*>* pointer, unsigned int index)
{
    TArrayList<TSafePointer<void*>*>* pointers = m_pSafePointers;
    if (index == 0xFFFFFFFF || pointers == NULL || index >= pointers->size())
        return;

    m_pSafePointers->removeAt(index);
    if (index < m_pSafePointers->size())
        (*m_pSafePointers)[index]->setIndex(index);
}

unsigned int CRunicCore::addSafePointer(TSafePointer<void*>* pointer)
{
    if (m_pSafePointers == NULL)
        m_pSafePointers = new TArrayList<TSafePointer<void*>*>();

    m_pSafePointers->add(pointer);
    return m_pSafePointers->size() - 1;
}

CRunicCore::~CRunicCore()
{
    if (m_pSafePointers)
    {
        for (unsigned int i = 0; i < m_pSafePointers->size(); i++)
            (*m_pSafePointers)[i]->invalidate();

        delete m_pSafePointers;
        m_pSafePointers = NULL;
    }
}
