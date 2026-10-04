#ifndef SKILLCONTROLLER_H
#define SKILLCONTROLLER_H

#include <string>

#include "Player.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "RunicCore.h"

class CDataGroup;

class CSkillController : public CPositionableObject
{
public:
    virtual ~CSkillController();

    CPlayer* getSkillTarget();
    CSkillController(CResourceManager* resourceManager);

    void setUnitInteractWith(std::wstring unitInteractWith);
    bool configureUnit();
    void stopSkill();
    void startSkill();
    bool initSkillController();
    void unlearnSkill();
    void learnSkill();
    float update(float deltaTime);

    CResourceManager* m_pResourceManager;             // 0x100
    CDataGroup* m_pUnitInteractDataGroup;              // 0x108
    CRunicCore* m_pRunicCore;                          // 0x110
    int m_iRunicCoreSafePointerId;                     // 0x118
    unsigned char m_gap11C[4];                         // 0x11C

    std::wstring m_sCategory;                          // 0x120
    std::wstring m_sUnitInteractWith;                  // 0x128
    std::wstring m_sSkillName;                         // 0x130

    CRunicCore* m_pSecondaryRunicCore;                 // 0x138
    int m_iSecondaryRunicCoreSafePointerId;            // 0x140
    unsigned char m_gap144[4];                         // 0x144

    bool m_bLearnSkillOnStart;                         // 0x148
    bool m_bUnlearnSkillOnStop;                        // 0x149
    bool m_bSkillStartRequested;                       // 0x14A
    bool m_bSkillStopRequested;                        // 0x14B
    bool m_bForceStop;                                 // 0x14C
    bool m_bUsePlayerAsTarget;                         // 0x14D
    bool m_bUseUnitTarget;                             // 0x14E
    unsigned char m_gap14F[1];                         // 0x14F

    int m_iSkillLevel;                                 // 0x150

public:
    // Inline accessors behind the descriptors' property functions.
    void setSkillLearnOnStart(bool value) { m_bLearnSkillOnStart = value; }
    void setSkillUnlearnOnStop(bool value) { m_bUnlearnSkillOnStop = value; }
    void setForceStop(bool value) { m_bForceStop = value; }
    void setUseUnitTarget(bool value) { m_bUseUnitTarget = value; }
    void setPlayerAsTarget(bool value) { m_bUsePlayerAsTarget = value; }
    void setLevelOfSkill(int value) { m_iSkillLevel = value; }
    int getLevelOfSkill() const { return m_iSkillLevel; }
    bool getUseUnitTarget() const { return m_bUseUnitTarget; }
    bool getPlayerAsTarget() const { return m_bUsePlayerAsTarget; }
    bool getForceStop() const { return m_bForceStop; }
    bool getSkillUnlearnOnStop() const { return m_bUnlearnSkillOnStop; }
    bool getSkillLearnOnStart() const { return m_bLearnSkillOnStart; }
};

#endif
