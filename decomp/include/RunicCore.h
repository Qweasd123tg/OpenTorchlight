#ifndef RUNICCORE_H
#define RUNICCORE_H

#include <OgreMemoryAllocatorConfig.h>

#include "SafePointer.h"
#include "TArrayList.h"

extern int g_iTotalCountOfObjects;

// Common base of engine objects: counts live instances and invalidates the
// TSafePointers that refer to the object when it is destroyed.
class CRunicCore : public Ogre::GeneralAllocatedObject
{
public:
    CRunicCore();
    virtual ~CRunicCore();

    unsigned int addSafePointer(TSafePointer<void*>* pointer);
    void removeSafePointer(TSafePointer<void*>* pointer, unsigned int index);

private:
    TArrayList<TSafePointer<void*>*>* m_pSafePointers;
};

#endif
