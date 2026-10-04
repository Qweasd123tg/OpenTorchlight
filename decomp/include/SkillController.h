#ifndef SKILLCONTROLLER_H
#define SKILLCONTROLLER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <string>
#include "Player.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "RunicCore.h"

class CSkillController : public CPositionableObject
{
public:
    virtual ~CSkillController();
    CPlayer* getSkillTarget();
    CSkillController(CResourceManager*);
    void setUnitInteractWith(std::wstring);
    bool configureUnit();
    void stopSkill();
    void startSkill();
    bool initSkillController();
    void unlearnSkill();
    void learnSkill();
    float update(float);

    // fields
    CResourceManager* m_pResourceManager;
    long long m_iUnknown108;
    CRunicCore* m_pRunicCore;
    int m_iUnknown118;
    unsigned char m_gap11C[0x4] __attribute__((aligned(4)));
    void* m_pCategory;
    std::wstring m_sUnitInteractWith;
    void* m_pSkillName;
    CRunicCore* m_pRunicCore_138;
    int m_iUnknown140;
    unsigned char m_gap144[0x4] __attribute__((aligned(4)));
    bool m_bSkillLearnOnStart;
    bool m_bSkillUnlearnOnStop;
    bool m_bUnknown14A;
    bool m_bUnknown14B;
    bool m_bForceStop;
    bool m_bPlayerAsTarget;
    bool m_bUseUnitTarget;
    unsigned char m_gap14F[0x1];
    int m_iLevelOfSkill;
};

#endif
