#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <map>
#include <string>
#include "GameEnums.h"
#include "RunicCore.h"
class CAchievement;

class CAchievements : public CRunicCore
{
public:
    virtual ~CAchievements();
    static CAchievements* getSingleton();
    CAchievement* getAchievement(EACHIEVEMENTS);
    void synchAchievementsComplete();
    void update(float);
    void cheat();
    CAchievement* getAchievement(std::string);
    CAchievements* getAchievementStatus();
    void setAchievementComplete(CAchievement*);
    CAchievements();

    // fields
    bool m_bUnknown10;
    unsigned char m_gap11[0x7];
    // Named container destructors in CAchievements::~CAchievements establish
    // these member types and offsets (0x18, 0x30 and 0x48).
    TArrayList<CAchievement*> m_completedAchievements;
    TArrayList<CAchievement*> m_achievements;
    std::map<EACHIEVEMENTS, CAchievement*> m_achievementsById;
};

#endif
