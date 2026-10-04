#ifndef TARRAYLIST_H
#define TARRAYLIST_H

#include <OgreMemoryAllocatorConfig.h>

#include <cstddef>

// Growable array used throughout the engine. Layout and members from the
// out-of-line instantiations TArrayList<T>::add / ~TArrayList in the original.
template <class T>
class TArrayList : public Ogre::GeneralAllocatedObject
{
public:
    TArrayList(unsigned int growBy = 2)
        : m_pData(NULL), m_nCount(0), m_nCapacity(0), m_nGrowBy(growBy)
    {
    }

    ~TArrayList()
    {
        if (m_pData)
        {
            delete[] m_pData;
            m_pData = NULL;
        }
    }

    void add(T item)
    {
        if (m_nCount >= m_nCapacity)
        {
            if (m_pData == NULL)
            {
                m_nCapacity = m_nGrowBy;
                m_pData = new T[m_nGrowBy];
            }
            else
            {
                unsigned int capacity = m_nCapacity + m_nGrowBy;
                T* data = new T[capacity];
                for (unsigned int i = 0; i < m_nCapacity; i++)
                    data[i] = m_pData[i];
                if (m_pData)
                    delete[] m_pData;
                m_pData = data;
                m_nCapacity = capacity;
            }
        }
        m_pData[m_nCount] = item;
        m_nCount++;
    }

    // Unordered removal: the last element takes the freed slot.
    void removeAt(unsigned int index)
    {
        if (index < m_nCount)
        {
            m_nCount--;
            m_pData[index] = m_pData[m_nCount];
        }
    }

    void clear()
    {
        m_nCount = 0;
        m_nCapacity = 0;
        if (m_pData)
            delete[] m_pData;
        m_pData = NULL;
    }

    // Deletes the pointed-to elements, then clears the list.
    void deleteAll()
    {
        for (unsigned int i = 0; i < m_nCount; i++)
        {
            if (m_pData[i])
            {
                delete m_pData[i];
                m_pData[i] = NULL;
            }
            m_pData[i] = NULL;
        }
        clear();
    }

    void setGrowBy(unsigned int growBy)
    {
        if (growBy == 0)
            growBy = 1;
        m_nGrowBy = growBy;
    }

    T& operator[](unsigned int index)
    {
        if (index >= m_nCapacity)
            return m_pData[0];
        return m_pData[index];
    }

    const T& operator[](unsigned int index) const
    {
        if (index >= m_nCapacity)
            return m_pData[0];
        return m_pData[index];
    }

    unsigned int size() const { return m_nCount; }

    // Index of the first element equal to item, -1 if there is none.
    int find(T item)
    {
        for (unsigned int i = 0; i < m_nCount; i++)
        {
            if (m_pData[i] == item)
                return i;
        }
        return -1;
    }

    // Unordered removal of the first element equal to item.
    void remove(T item)
    {
        for (unsigned int i = 0; i < m_nCount; i++)
        {
            if (m_pData[i] == item)
            {
                removeAt(i);
                return;
            }
        }
    }

private:
    T* m_pData;
    unsigned int m_nCount;
    unsigned int m_nCapacity;
    unsigned int m_nGrowBy;
};

#endif
