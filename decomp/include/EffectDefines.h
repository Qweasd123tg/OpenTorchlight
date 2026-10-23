#ifndef EFFECTDEFINES_H
#define EFFECTDEFINES_H

#include <string>

// Effect activation and stat modifier names. Internal linkage: every including
// TU constructs its own copy. Enumerator names are ours; values follow the
// table order.

enum EEFFECT_ACTIVATION
{
    EFFECT_ACTIVATION_PASSIVE,
    EFFECT_ACTIVATION_DYNAMIC,
    EFFECT_ACTIVATION_TRANSFER,
    EFFECT_ACTIVATION_COUNT
};

// Partial: the effect type values are not recovered yet.
enum EEFFECT_TYPE
{
};

static const std::wstring gEffect_Activation_Names[] =
{
    L"PASSIVE",
    L"DYNAMIC",
    L"TRANSFER",
};

static const std::wstring gEFFECT_STAT_MODIFIER_NAMES[] =
{
    L"MELEE",
    L"RANGED",
    L"DEFENSE",
    L"MAGIC",
    L"LEVEL",
    L"OWNERLEVEL",
};

static const std::string gEFFECT_STAT_MODIFIER_ICON_NAMES[] =
{
    "iconmelee",
    "iconranged",
    "icondefense",
    "iconmagic",
    "iconmagic",
    "iconmagic",
};

static const EEFFECT_TYPE gDAMAGE_DEFENSE_EFFECT_TYPES[] = {
    static_cast<EEFFECT_TYPE>(35), static_cast<EEFFECT_TYPE>(36),
    static_cast<EEFFECT_TYPE>(37), static_cast<EEFFECT_TYPE>(38),
    static_cast<EEFFECT_TYPE>(39), static_cast<EEFFECT_TYPE>(40)
};

// Existing GLOBAL ELF objects. Strings: constructor/assign/stdwstring ABI.
extern std::wstring gEFFECT_TYPE_NAMES[145];
extern std::wstring gEFFECT_TYPE_DESCRIPTIONS_GOOD[145];
extern std::wstring gEFFECT_TYPE_DESCRIPTIONS_GOOD_OT[145];
extern std::wstring gEFFECT_TYPE_DESCRIPTIONS_BAD[145];
extern std::wstring gEFFECT_TYPE_DESCRIPTIONS_BAD_OT[145];
extern std::wstring gEFFECT_TYPE_PROPERTY_TAGS[145][5];
extern std::wstring gEFFECT_TYPE_GRAPHS[145][5];
extern int gEFFECT_TYPE_MIN_VALUES[145];
extern int gEFFECT_TYPE_MAX_VALUES[145];
extern int gEFFECT_TYPE_BONUS[145];


void parseEffects();

#endif
