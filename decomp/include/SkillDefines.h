#ifndef SKILLDEFINES_H
#define SKILLDEFINES_H

#include <string>

// Skill event, target, activation and type names. Internal linkage: every
// including TU constructs its own copy. Enumerator names are ours; values
// follow the table order.

enum ESKILL_ACTIVATION_TYPE
{
    SKILL_ACTIVATION_ANY,
    SKILL_ACTIVATION_PROC,
    SKILL_ACTIVATION_WEAPON,
    SKILL_ACTIVATION_NORMAL,
    SKILL_ACTIVATION_PASSIVE,
    SKILL_ACTIVATION_COUNT
};

static const std::wstring gSKILL_EVENT_TYPE_NAMES[] =
{
    L"EVENT_START",
    L"EVENT_END",
    L"EVENT_TRIGGER",
    L"EVENT_TRIGGER_TWO",
    L"EVENT_UNITHIT",
    L"EVENT_UNITDIE",
    L"EVENT_MISSILEHIT",
    L"EVENT_MISSILEDIE",
    L"EVENT_DIEBYEFFECT",
    L"EVENT_CASTERDIE",
    L"EVENT_UNIT_CREATE",
};

static const std::wstring gSKILL_TARGET_TYPE_NAMES[] =
{
    L"NONE",
    L"POSITION",
    L"TARGET",
    L"SELF",
    L"EVERYBODY",
    L"POSITIONRANDOM",
    L"POSITIONFLEE",
    L"ITEM",
    L"UNIDENTIFIEDITEM",
    L"PETS",
    L"SELFANDPETS",
    L"TARGET_POS",
};

static const std::wstring gSKILL_ACTIVATION_TYPE_NAMES[] =
{
    L"ANY",
    L"PROC",
    L"WEAPON",
    L"NORMAL",
    L"PASSIVE",
};

// Five skill type slots; the last one has no name.
static const std::wstring gSKILL_TYPE_NAMES[5] =
{
    L"SKILL",
    L"OFFENSIVE",
    L"DEFENSIVE",
    L"CHARM",
};

static const std::wstring gSKILL_TYPE_DISPLAY_NAMES[5] =
{
    L"Class Skill",
    L"Offensive Spell",
    L"Defensive Spell",
    L"Charm Spell",
};

static const std::wstring gSKILL_BONE_ATTACHMENT_NAMES[] =
{
    L"",
    L"CENTER",
    L"HEAD",
    L"RIGHTHAND",
    L"LEFTHAND",
    L"RIGHTSHOULDER",
    L"LEFTSHOULDER",
    L"POSITION",
};

#endif
