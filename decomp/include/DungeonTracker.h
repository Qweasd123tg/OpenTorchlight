#ifndef DUNGEON_TRACKER_H
#define DUNGEON_TRACKER_H
#include <string>
#include <vector>
#include <stdio.h>
// Save order and layout are recovered from CDungeonTracker::save.
class CDungeonTracker
{
public:
    void save(FILE* file);
    std::wstring m_name;
    int m_value8;
    int m_rank;
    int m_value10;
    std::vector<int> m_levels;
};
#endif
