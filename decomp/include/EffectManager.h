#ifndef EFFECTMANAGER_H
#define EFFECTMANAGER_H
#include "RunicCore.h"
#include "EffectDefines.h"
#include "Constants.h"
#include "TArrayList.h"
#include "SafePointer.h"
#include <string>
class CBaseUnit;
class CCharacter;
class CAffix;
class CCharacter;
class CEffect;
class CSkill;
class CResourceManager;
class CDataGroup;
class CUnitTheme;
// Partial: complete size/vtable; declarations and active theme list needed by BaseUnit.
class CEffectManager : public CRunicCore
{
public:
    void notifyOfDeletion(CCharacter* character);
    void clearAllUnitReferences();
    CAffix* cloneAffix(CAffix* affix, unsigned int level, CBaseUnit* source, float scale);
    CEffect* getEffect(EEFFECT_TYPE type);
    CEffect* getEffect(const std::wstring& name, unsigned int index);
    bool hasEffectFromSkill(const CSkill* skill);
    void getEffects(TArrayList<CEffect*>* effects);

    void transferEffects(CCharacter*, EEFFECT_ACTIVATION, EEFFECT_TYPE);

    void recalculateEffects();

    CEffectManager(CBaseUnit* owner);
    virtual ~CEffectManager();
    CAffix* addAffix(CAffix* affix,unsigned int level,CBaseUnit* source,float scale);
    CAffix* addAffix(const std::wstring& name,unsigned int level,CBaseUnit* source,CResourceManager* resources,float scale);
    CEffect* addNewEffect(CEffect* effect);
    CEffect* cloneEffect(CBaseUnit* source,CEffect* effect);
    void cloneEffects(CBaseUnit* source, TArrayList<CEffect*>* effects);
    bool removeEffect(const std::wstring& name, bool flag);
    bool removeEffect(CEffect* effect, bool flag);
    bool deleteAffix(const std::wstring& name);
    void removeNonSavedEffects();
    bool deleteAffix(CAffix*);
    void clearOutDescriptions();
    void deleteDeadEffects();
    bool hasEffect(EEFFECT_TYPE type);
    bool hasEffect(EEFFECT_TYPE type, const std::wstring& name);
    bool hasEffect(const std::wstring& name);
    float getEffectValue(EEFFECT_TYPE type, EDAMAGE_TYPES damage);
    float getEffectValue(EEFFECT_ACTIVATION activation, EEFFECT_TYPE type, EDAMAGE_TYPES damage);
    float getEffectValue(EEFFECT_TYPE type, const std::wstring& name);
    void updateAffixes(float elapsed);
    void calculateEffectValues();
    void clearOutAffixEffects();
    void clearEffects(bool);
    void addAffixEffectsBackIn();
    const std::wstring& getVisualDescription(EEFFECT_ACTIVATION,unsigned int,bool,bool);
    unsigned int createEffects(CDataGroup* data,bool flag);
    void createEffect(CDataGroup* data, bool flag);
    CAffix* getAffix(const std::wstring& name);
    TArrayList<CUnitTheme*>* getUnitThemes() { return &m_UnitThemes; }
    TArrayList<CEffect*>& getActiveEffects(unsigned int group) { return m_Effects[group]; }
    TSafePointer<CBaseUnit>& getOwnerReference() { return m_Owner; }
    TArrayList<CAffix*>& getAffixes() { return m_Affixes; }
private:
    friend class CEquipment;
    friend class CInventory;
    TArrayList<CAffix*> m_Affixes; // +0x10
    TArrayList<CEffect*> m_Effects[3]; // +0x28
    TSafePointer<CBaseUnit> m_Owner; // +0x70
    float m_EffectValues[145]; // +0x80
    unsigned char m_padding2C4[4];
    TArrayList<CUnitTheme*> m_UnitThemes;
    std::wstring m_EffectString2E0;
    std::wstring m_EffectString2E8;
    std::wstring m_EffectString2F0;
};
#endif
