#ifndef EFFECTMANAGER_H
#define EFFECTMANAGER_H
#include "RunicCore.h"
#include "EffectDefines.h"
#include "Constants.h"
#include "TArrayList.h"
#include <string>
class CBaseUnit;
class CAffix;
class CEffect;
class CResourceManager;
class CDataGroup;
class CUnitTheme;
// Partial: complete size/vtable; declarations and active theme list needed by BaseUnit.
class CEffectManager : public CRunicCore
{
public:
    CEffectManager(CBaseUnit* owner);
    virtual ~CEffectManager();
    CAffix* addAffix(CAffix* affix,unsigned int level,CBaseUnit* source,float scale);
    CAffix* addAffix(const std::wstring& name,unsigned int level,CBaseUnit* source,CResourceManager* resources,float scale);
    CEffect* addNewEffect(CEffect* effect);
    CEffect* cloneEffect(CBaseUnit* source,CEffect* effect);
    bool removeEffect(const std::wstring& name, bool flag);
    bool deleteAffix(const std::wstring& name);
    bool deleteAffix(CAffix*);
    void clearOutDescriptions();
    bool hasEffect(EEFFECT_TYPE type);
    bool hasEffect(EEFFECT_TYPE type, const std::wstring& name);
    bool hasEffect(const std::wstring& name);
    float getEffectValue(EEFFECT_TYPE type, EDAMAGE_TYPES damage);
    float getEffectValue(EEFFECT_ACTIVATION activation, EEFFECT_TYPE type, EDAMAGE_TYPES damage);
    float getEffectValue(EEFFECT_TYPE type, const std::wstring& name);
    void updateAffixes(float elapsed);
    void calculateEffectValues();
    void clearOutAffixEffects();
    void addAffixEffectsBackIn();
    const std::wstring& getVisualDescription(EEFFECT_ACTIVATION,unsigned int,bool,bool);
    unsigned int createEffects(CDataGroup* data,bool flag);
    CAffix* getAffix(const std::wstring& name);
    TArrayList<CUnitTheme*>* getUnitThemes() { return &m_UnitThemes; }
    // Partial layout: the affix list occupies the beginning of the opaque region.
    TArrayList<CAffix*>& getAffixes() { return *reinterpret_cast<TArrayList<CAffix*>*>(m_EffectData10); }
private:
    friend class CEquipment;
    unsigned char m_EffectData10[0x2c8-0x10];
    TArrayList<CUnitTheme*> m_UnitThemes;
    std::wstring m_EffectString2E0;
    std::wstring m_EffectString2E8;
    std::wstring m_EffectString2F0;
};
#endif
