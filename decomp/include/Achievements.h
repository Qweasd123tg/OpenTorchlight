#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <string>
#include "GameEnums.h"
#include "RunicCore.h"
class CAchievement;

class CAchievements : public CRunicCore
{
public:
    virtual ~CAchievements();
    static CAchievements* getSingleton();
    long long getAchievement(EACHIEVEMENTS);
    void synchAchievementsComplete();
    void update(float);
    void cheat();
    long long getAchievement(std::string);
    CAchievements* getAchievementStatus();
    void setAchievementComplete(CAchievement*);
    CAchievements();

    // fields
    bool m_bUnknown10;
    unsigned char m_gap11[0x7];
    unsigned char m_Unknown18[0x18] __attribute__((aligned(8)));
    unsigned char m_Unknown30[0x18] __attribute__((aligned(8)));
    long long m_Unknown48;
    int m_iUnknown50;
    unsigned char m_gap54[0x4] __attribute__((aligned(4)));
    void* m_pUnknown58;
    long long m_iUnknown60;
    long long m_iUnknown68;
    long long m_iUnknown70;
};

#endif
