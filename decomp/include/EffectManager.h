#ifndef EFFECTMANAGER_H
#define EFFECTMANAGER_H
#include "RunicCore.h"
#include "EffectDefines.h"
#include "Constants.h"
#include "TArrayList.h"
#include <string>
class CBaseUnit;
class CUnitTheme;
// Partial: complete size/vtable; declarations and active theme list needed by BaseUnit.
class CEffectManager : public CRunicCore
{
public:
    CEffectManager(CBaseUnit* owner);
    virtual ~CEffectManager();
    bool removeEffect(const std::wstring& name, bool flag);
    bool deleteAffix(const std::wstring& name);
    bool hasEffect(EEFFECT_TYPE type);
    bool hasEffect(EEFFECT_TYPE type, const std::wstring& name);
    bool hasEffect(const std::wstring& name);
    float getEffectValue(EEFFECT_TYPE type, EDAMAGE_TYPES damage);
    float getEffectValue(EEFFECT_ACTIVATION activation, EEFFECT_TYPE type, EDAMAGE_TYPES damage);
    float getEffectValue(EEFFECT_TYPE type, const std::wstring& name);
    void updateAffixes(float elapsed);
    TArrayList<CUnitTheme*>& getUnitThemes() { return m_UnitThemes; }
private:
    unsigned char m_EffectData10[0x2c8-0x10];
    TArrayList<CUnitTheme*> m_UnitThemes;
    std::wstring m_EffectString2E0;
    std::wstring m_EffectString2E8;
    std::wstring m_EffectString2F0;
};
#endif
