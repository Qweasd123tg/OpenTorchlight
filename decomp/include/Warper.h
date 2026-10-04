#ifndef WARPER_H
#define WARPER_H

#include <string>
#include "PositionableObject.h"

class CResourceManager;

// Sends every client to another dungeon level.
class CWarper : public CPositionableObject
{
public:
    CWarper(CResourceManager* resourceManager);
    virtual ~CWarper();
    virtual void setEnabled(bool enabled) { m_bWarperEnabled = enabled; }
    virtual bool getEnabled() { return m_bWarperEnabled; }

    void createEntity();
    void activate();

    int getLevelDelta() { return m_iLevelDelta; }
    void setLevelDelta(int levelDelta) { m_iLevelDelta = levelDelta; }
    int getLevelDepth() { return m_iLevelDepth; }
    void setLevelDepth(int levelDepth) { m_iLevelDepth = levelDepth; }
    bool getWaypoint() { return m_bWaypoint; }
    void setWaypoint(bool waypoint) { m_bWaypoint = waypoint; }
    std::wstring getDungeon() { return m_sDungeon; }
    void setDungeon(const std::wstring& dungeon) { m_sDungeon = dungeon; }
    std::wstring getWarpName() { return m_sWarpName; }
    void setWarpName(const std::wstring& warpName) { m_sWarpName = warpName; }

private:
    int m_iLevelDelta;
    int m_iLevelDepth;
    bool m_bWarperEnabled;
    bool m_bWaypoint;
    std::wstring m_sDungeon;
    std::wstring m_sWarpName;
    CResourceManager* m_pResourceManager;
};

#endif
