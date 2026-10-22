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

// Reconstructed include context: AIStatWatcher has no completion-name table
// in the original TU. Other includers retain their internal-linkage copy.
#ifndef OTL_AISTATWATCHER_OMIT_QUEST_COMPLETE_NAMES
static const std::wstring g_QUEST_COMPLETE_TYPE_NAMES[2] =
{
    L"COMPLETE_ON_QUEST_ACCEPT",
    L"COMPLETE_ON_QUEST_COMPLETE",
};

#endif // OTL_AISTATWATCHER_OMIT_QUEST_COMPLETE_NAMES

#endif
