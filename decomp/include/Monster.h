#ifndef MONSTER_H
#define MONSTER_H
#include "Character.h"
#include "Randomizer.h"
// Full 0x7f8-byte extent. The base ends at 0x778 and the randomizer starts at 0x780.
class CMonster : public CCharacter
{
public:
    CMonster(CResourceManager* resources,int level);
    virtual ~CMonster();
    virtual void unitInit(CDataGroup*,bool);
    virtual void setPathToFollow(CPathController*);
    virtual void reactToDamage(CCharacter*,bool);
    virtual void updateAI(float,bool);
    virtual void huntAI(float,CLevel&);
    virtual void approachAI(float,CLevel&);
    virtual void attackAI(float,CLevel&);
    virtual bool canAttackWithCurrentWeapon();
    virtual void notifyAISkillComplete();
    void getRangeAI(float,CLevel&);
    int selectOffensiveSkill(bool);
    void idleAINormal(float,CLevel&,bool);
    void idleAIResurrecter(float,CLevel&,bool);
    void idleAIDefender(float,CLevel&,bool);
private:
    std::wstring m_monsterName;
    CRandomizer m_skillRandomizer;
    float m_attackDelay;
    float m_initialAttackDelay;
    bool m_monsterFlag;
};
#endif
