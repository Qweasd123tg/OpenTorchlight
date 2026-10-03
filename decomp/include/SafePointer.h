#ifndef SAFEPOINTER_H
#define SAFEPOINTER_H

#include <cstddef>

// Weak reference registered in the pointee's CRunicCore safe-pointer list;
// the pointee clears it on destruction.
template <class T>
class TSafePointer
{
public:
    TSafePointer() : m_pObject(NULL), m_nIndex(0xFFFFFFFF) {}

    ~TSafePointer()
    {
        if (m_pObject)
            m_pObject->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(this), m_nIndex);
        m_pObject = NULL;
        m_nIndex = 0xFFFFFFFF;
    }

    void setObject(T* object)
    {
        if (m_pObject == object)
            return;
        if (m_pObject)
            m_pObject->removeSafePointer(reinterpret_cast<TSafePointer<void*>*>(this), m_nIndex);
        m_pObject = NULL;
        if (object)
            m_nIndex = object->addSafePointer(reinterpret_cast<TSafePointer<void*>*>(this));
        m_pObject = object;
    }

    T* getObject() const { return m_pObject; }

    void invalidate()
    {
        m_pObject = NULL;
        m_nIndex = 0xFFFFFFFF;
    }

    void setIndex(unsigned int index) { m_nIndex = index; }

private:
    T* m_pObject;
    unsigned int m_nIndex;
};

#endif
