#ifndef DUNGEON_TRACKER_H
#define DUNGEON_TRACKER_H
#include <string>
#include <OgreMemoryAllocatorConfig.h>
#include <vector>
#include <stdio.h>
// Save order and layout are recovered from CDungeonTracker::save.
class CDungeonTracker : public Ogre::GeneralAllocatedObject
{
public:
    void save(FILE* file);
    void load(FILE* file, unsigned int version);
    std::wstring m_name;
    int m_value8;
    int m_rank;
    int m_value10;
    std::vector<int> m_levels;
};
#endif
