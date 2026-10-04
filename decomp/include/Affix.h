#ifndef AFFIX_H
#define AFFIX_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreVector3.h>
#include <string>
#include "BaseUnit.h"
#include "Effect.h"
#include "EffectDefines.h"
#include "EffectManager.h"
#include "RunicCore.h"
#include "Skill.h"

class CAffix : public CRunicCore
{
public:
    virtual ~CAffix();
    void fillOutStatBonuses(float (&) [6], bool);
    void setSaves(bool);
    void setDirection(const Ogre::Vector3*);
    void effectDeleted(CEffect*);
    long long updateAffixDuration(float);
    long long effectHasDuration(EEFFECT_TYPE);
    long long effectExists(EEFFECT_TYPE);
    long long canBeAppliedToUnitType(unsigned int);
    void setPercent(char);
    void setLevel(unsigned int);
    void setOwner(CBaseUnit*);
    void setSkillOwner(CSkill*);
    void clearEffectsFromOwner();
    void addEffectsToEffectManager(CEffectManager*);
    void clone(const CAffix*);
    CAffix* getDisplayStats(unsigned int);
    void parseAffixGroup();
    CAffix(const std::wstring&);
    CAffix(CAffix*, unsigned int);

    // fields
    void* m_pUnknown10;
    CRunicCore* m_pRunicCore;
    int m_iUnknown20;
    unsigned char m_gap24[0x4] __attribute__((aligned(4)));
    CRunicCore* m_pRunicCore_28;
    int m_iUnknown30;
    unsigned char m_gap34[0x4] __attribute__((aligned(4)));
    CEffectManager* m_pEffectManager;
    int m_iUnknown40;
    unsigned char m_gap44[0x4] __attribute__((aligned(4)));
    std::wstring m_sUnknown48;
    std::wstring m_sUnknown50;
    std::wstring m_sUnknown58;
    std::wstring m_sUnknown60;
    int m_iUnknown68;
    int m_iUnknown6C;
    char m_Unknown70;
    unsigned char m_gap71[0x3];
    int m_iUnknown74;
    int m_iUnknown78;
    unsigned int m_iUnknown7C;
    bool m_bUnknown80;
    unsigned char m_gap81[0x7];
    void* m_pUnknown88;
    int m_iUnknown90;
    int m_iUnknown94;
    int m_iUnknown98;
    unsigned char m_gap9C[0x4] __attribute__((aligned(4)));
    bool m_bUnknownA0;
    unsigned char m_gapA1[0x3];
    float m_fUnknownA4;
    bool m_bUnknownA8;
    unsigned char m_gapA9[0x3];
    int m_iUnknownAC;
    void* m_pUnknownB0;
    int m_iUnknownB8;
    int m_iUnknownBC;
    int m_iUnknownC0;
};

#endif
