#ifndef QUESTDEFINES_H
#define QUESTDEFINES_H

#include <string>

#include "QuestEventTypes.h"

// Quest type names. Internal linkage: every including TU constructs its own
// copy.

static const std::wstring gQUEST_TYPE_NAMES[] =
{
    L"",
    L"FIND",
    L"KILL NUM",
    L"KILL BOSS",
};

static const std::wstring gQUEST_DIALOG_TYPE_NAMES[] =
{
    L"ERROR",
    L"INTRO",
    L"RETURN",
    L"COMPLETE",
    L"PASSIVE",
    L"DETAILS",
};

#endif
