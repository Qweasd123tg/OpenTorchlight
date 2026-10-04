#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EffectManager.h"
#include "Affix.h"
#include "BaseUnit.h"
#include "Effect.h"
#include "ResourceManager.h"
#include "TArrayList.h"

bool CEffectManager::hasEffect(EEFFECT_TYPE type)
{
    for (unsigned int i = 0; i < 2; ++i) {
        TArrayList<CEffect*>* effects =
            reinterpret_cast<TArrayList<CEffect*>*>(
                m_EffectData10 + 0x18 + i * sizeof(TArrayList<CEffect*>));

        for (unsigned int j = 0; j < effects->size(); ++j) {
            if (*reinterpret_cast<EEFFECT_TYPE*>(
                    reinterpret_cast<char*>((*effects)[j]) + 0x1c) == type)
                return true;
        }
    }

    return false;
}

float CEffectManager::getEffectValue(EEFFECT_TYPE type, EDAMAGE_TYPES damage)
{
    const float* effectValues =
        reinterpret_cast<const float*>(m_EffectData10 + 0x70);

    if (damage == 7)
        return effectValues[type];

    float result = 0.0f;
    if (effectValues[type] != 0.0f) {
        for (unsigned int pass = 0; pass < 2; ++pass) {
            TArrayList<CEffect*>& effects =
                *reinterpret_cast<TArrayList<CEffect*>*>(
                    m_EffectData10 + 0x18 +
                    pass * sizeof(TArrayList<CEffect*>));

            for (unsigned int index = 0; index < effects.size(); ++index) {
                const unsigned char* effect =
                    reinterpret_cast<const unsigned char*>(effects[index]);

                if (*reinterpret_cast<const int*>(effect + 0x1c) != type)
                    continue;
                if (*reinterpret_cast<const int*>(effect + 0x14) != damage)
                    continue;

                float value =
                    *reinterpret_cast<const float*>(effect + 0xc0);
                float activation =
                    *reinterpret_cast<const float*>(effect + 0x24);
                int effectType =
                    *reinterpret_cast<const int*>(effect + 0x1c);

                if (activation != -900.0f && activation != -1000.0f &&
                    (effectType == 7 || effectType == 6 ||
                     effectType == 124 || effectType == 123))
                    value *= 0.016f;

                result += value;
            }
        }
    }

    return result;
}

float CEffectManager::getEffectValue(EEFFECT_ACTIVATION activation, EEFFECT_TYPE type, EDAMAGE_TYPES damage)
{
    struct CEffectDataView
    {
        void *m_Unknown00;
        unsigned char m_Unknown08[0x0c];
        int m_Damage;
        unsigned char m_Unknown18[4];
        int m_Type;
        unsigned char m_Unknown20[4];
        float m_Unknown24;
        unsigned char m_Unknown28[0xc0 - 0x28];
        float m_Value;
    };

    float value = 0.0f;

    if (reinterpret_cast<const float *>(m_EffectData10 + 0x70)[type] == 0.0f)
        return value;

    TArrayList<CEffect*>& effects =
        *reinterpret_cast<TArrayList<CEffect*>*>(
            m_EffectData10 + 0x18 + activation * sizeof(TArrayList<CEffect*>));

    for (unsigned int i = 0; i < effects.size(); ++i) {
        CEffect* effect = effects[i];
        const CEffectDataView* effectData =
            *reinterpret_cast<CEffectDataView *const *>(effect);
        int effectType = effectData->m_Type;

        if (effectType != type)
            continue;

        if (damage != 7 && effectData->m_Damage != damage)
            continue;

        float effectValue = effectData->m_Value;

        if (effectData->m_Unknown24 != -900.0f &&
            effectData->m_Unknown24 != -1000.0f &&
            (effectType == 7 || effectType == 6 ||
             effectType == 124 || effectType == 123)) {
            effectValue *= 0.016f;
        }

        value += effectValue;
    }

    return value;
}

extern "C" CAffix* getNewAffixByNameThunk(CResourceManager*, const std::wstring&, unsigned int)
    __asm__("_ZN16CResourceManager17getNewAffixByNameERKSbIwSt11char_traitsIwESaIwEEj");

extern "C" void clearOutDescriptionsThunk(CEffectManager*)
    __asm__("_ZN14CEffectManager20clearOutDescriptionsEv");

CAffix* CEffectManager::addAffix(const std::wstring& name, unsigned int level, CBaseUnit* source, CResourceManager* resources, float scale)
{
    CAffix* affix = NULL;

    if (resources != NULL) {
        affix = getNewAffixByNameThunk(resources, name, level);
        addAffix(affix, level, source, scale);
        clearOutDescriptionsThunk(this);
    }
    return affix;
}

bool CEffectManager::removeEffect(const std::wstring& name, bool flag)
{
    extern void clearOutDescriptionsThunk(CEffectManager*)
        asm("_ZN14CEffectManager20clearOutDescriptionsEv");

    bool removed = false;
    TArrayList<CEffect*>* effectLists =
        reinterpret_cast<TArrayList<CEffect*>*>(m_EffectData10 + 0x18);

    for (int listIndex = 0; listIndex < 3; ++listIndex) {
        TArrayList<CEffect*>& effects = effectLists[listIndex];

        for (unsigned int index = 0; index < effects.size(); ++index) {
            CEffect* effect = effects[index];
            const std::wstring& effectName =
                *reinterpret_cast<const std::wstring*>(
                    reinterpret_cast<const unsigned char*>(effect) + 0x80);

            if (effectName == name) {
                if (flag && effect != NULL)
                    delete effect;

                effects.removeAt(index);
                removed = true;
                --index;
            }
        }
    }

    if (removed)
        clearOutDescriptionsThunk(this);

    return removed;
}

float CEffectManager::getEffectValue(EEFFECT_TYPE type, const std::wstring& name)
{
    typedef TArrayList<CEffect*> EffectList;

    struct EffectLayout {
        unsigned char unknown00[0x1c];
        int effectType;
        unsigned char unknown20[4];
        float adjustment;
        unsigned char unknown28[0x58];
        std::wstring effectName;
        unsigned char unknownb0[0x10];
        float value;
    };

    float result = 0.0f;
    const float* effectValues =
        reinterpret_cast<const float*>(m_EffectData10 + 0x70);

    if (effectValues[type] != 0.0f) {
        for (unsigned int listIndex = 0; listIndex < 2; ++listIndex) {
            EffectList& effects = *reinterpret_cast<EffectList*>(
                m_EffectData10 + 0x18 + listIndex * sizeof(EffectList));

            for (unsigned int i = 0; i < effects.size(); ++i) {
                const EffectLayout* effect =
                    reinterpret_cast<const EffectLayout*>(effects[i]);

                if (effect->effectType == type && effect->effectName == name) {
                    float value = effect->value;

                    if (effect->adjustment != -14700.0f &&
                        effect->adjustment != -100000.0f) {
                        if (type == 7 || type == 6 ||
                            type == 124 || type == 123) {
                            value *= 0.01f;
                        }
                    }

                    result += value;
                }
            }
        }
    }

    return result;
}

bool CEffectManager::hasEffect(const std::wstring& name)
{
    for (unsigned int i = 0; i < 2; ++i)
    {
        TArrayList<CEffect*>* effects =
            reinterpret_cast<TArrayList<CEffect*>*>(m_EffectData10 + 0x18 + i * sizeof(TArrayList<CEffect*>));

        for (unsigned int j = 0; j < effects->size(); ++j)
        {
            const std::wstring* effectName =
                reinterpret_cast<const std::wstring*>(
                    reinterpret_cast<const char*>((*effects)[j]) + 0x80);

            if (*effectName == name)
                return true;
        }
    }
    return false;
}
