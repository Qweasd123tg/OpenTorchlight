#ifndef AIDEFINES_H
#define AIDEFINES_H

#include <string>

// Shared AI enumerations and their resource names. The tables have internal
// linkage: every including TU constructs its own copy (50 TUs in the original).
// Enumerator names are ours; values follow the table order.

enum EAIFLAG_TYPES
{
    AIFLAG_AWARE,
    AIFLAG_BERSERK,
    AIFLAG_CANNOT_INTERRUPT,
    AIFLAG_FRIGHTEN,
    AIFLAG_NO_LINE_OF_SIGHT,
    AIFLAG_NEVER_CHANGE_TARGET,
    AIFLAG_CANNOT_TARGET,
    AIFLAG_COUNT
};

enum EAISTAT_TYPE
{
    AISTAT_NONE,
    AISTAT_HP,
    AISTAT_MANA,
    AISTAT_HP_PCT,
    AISTAT_MANA_PCT,
    AISTAT_ACTIVE_UNITS,
    AISTAT_TYPE_COUNT
};

enum EAISTAT_LOGIC
{
    AISTAT_LOGIC_BELOW,
    AISTAT_LOGIC_ABOVE,
    AISTAT_LOGIC_COUNT
};

enum EAISTAT_TARGET
{
    AISTAT_TARGET_SELF,
    AISTAT_TARGET_FORMATION,
    AISTAT_TARGET_AREA,
    AISTAT_TARGET_AREAUNITTYPES,
    AISTAT_TARGET_AREAFORMATION,
    AISTAT_TARGET_COUNT
};

static const std::wstring g_AIFLAG_TYPE_NAMES[] =
{
    L"AWARE",
    L"BERSERK",
    L"CANNOT INTERRUPT",
    L"FRIGHTEN",
    L"NO LINE OF SIGHT",
    L"NEVER CHANGE TARGET",
    L"CANNOT TARGET",
};

static const std::wstring g_AISTAT_TYPE_NAMES[] =
{
    L"NONE",
    L"HP",
    L"MANA",
    L"HP PCT",
    L"MANA PCT",
    L"ACTIVE UNITS",
};

static const std::wstring g_AISTAT_LOGIC_NAMES[] =
{
    L"BELOW",
    L"ABOVE",
};

static const std::wstring g_AISTAT_TARGET_NAMES[] =
{
    L"SELF",
    L"FORMATION",
    L"AREA",
    L"AREAUNITTYPES",
    L"AREAFORMATION",
};

#endif
