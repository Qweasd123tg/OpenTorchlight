#ifndef AFFIX_H
#define AFFIX_H

#include <string>
#include <OgreVector3.h>

#include "EffectDefines.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CAffix;
class CBaseUnit;
class CEffect;
class CEffectManager;
class CSkill;

class CAffix : public CRunicCore
{
public:
    virtual ~CAffix();

    void fillOutStatBonuses(float (&fStatBonuses)[6], bool bTakeHighest);
    void setSaves(bool bSaves);
    void setDirection(const Ogre::Vector3 *pDirection);
    void effectDeleted(CEffect *pEffect);

    bool updateAffixDuration(float fElapsedTime);
    bool effectHasDuration(EEFFECT_TYPE eEffectType);
    bool effectExists(EEFFECT_TYPE eEffectType);
    bool canBeAppliedToUnitType(unsigned int uiUnitType);

    void setPercent(char cPercent);
    void setLevel(unsigned int uiLevel);
    void setOwner(CBaseUnit *pOwner);
    void setSkillOwner(CSkill *pSkillOwner);

    void clearEffectsFromOwner();
    void addEffectsToEffectManager(CEffectManager *pEffectManager);
    void clone(const CAffix *pAffix);
    std::wstring getDisplayStats(unsigned int uiLevel);
    void parseAffixGroup();

    CAffix(const std::wstring &wsAffixName);
    CAffix(CAffix *pAffix, unsigned int uiLevel);

    CAffix *m_pOriginalAffix;

    CSkill *m_pSkillOwner;
    int m_iSkillOwnerSafePointerId;

    CBaseUnit *m_pOwner;
    int m_iOwnerSafePointerId;

    CEffectManager *m_pEffectManager;
    int m_iEffectManagerSafePointerId;

    std::wstring m_sAffixFileName;
    std::wstring m_sDisplayName;
    std::wstring m_sPrefix;
    std::wstring m_sSuffix;

    int m_iMinSpawnRange;
    int m_iMaxSpawnRange;
    char m_cLevelPercent;
    int m_iRank;
    int m_iSlotsOccupy;
    unsigned int m_uiLevel;

    bool m_bTemporary;
    TArrayList<CEffect *> m_Effects;

    bool m_bDataFileInitialized;
    float m_fDuration;
    bool m_bHasDuration;
    int m_iWeight;

    TArrayList<unsigned int> m_ApplicableUnitTypes;
};

#endif
