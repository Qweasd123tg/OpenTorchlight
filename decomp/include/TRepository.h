#ifndef TREPOSITORY_H
#define TREPOSITORY_H

#include <OgreMemoryAllocatorConfig.h>

#include <map>

// Partial: shared value table of CDataGroup/CDataValue (DataGroup.cpp,
// DataValue.cpp). Values are stored once and referenced by ID; m_RefCounts
// counts the users of every ID.
template <class T>
class TRepository : public Ogre::GeneralAllocatedObject
{
public:
    TRepository(T defaultValue) : m_iNextID(0), m_DefaultValue(defaultValue) {}

    void clear()
    {
        m_IDs.clear();
        m_Values.clear();
        m_RefCounts.clear();
        m_iNextID = 0;
    }

private:
    unsigned int m_iNextID;
    std::map<unsigned int, T> m_Values;
    std::map<T, unsigned int> m_IDs;
    std::map<unsigned int, unsigned short> m_RefCounts;
    T m_DefaultValue;
};

#endif
