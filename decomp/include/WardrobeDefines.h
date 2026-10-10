#ifndef WARDROBEDEFINES_H
#define WARDROBEDEFINES_H

#include <string>

enum EWardrobeSlot
{
    WARDROBE_CHEST, WARDROBE_GLOVES, WARDROBE_BOOTS, WARDROBE_HELMET, WARDROBE_SHOULDERS
};

// Wardrobe slot names. Internal linkage: every including TU constructs its
// own copy.

static const std::wstring KWardrobeSlotNames[] =
{
    L"CHEST",
    L"GLOVES",
    L"BOOTS",
    L"HELMET",
    L"SHOULDERS",
};

static const std::wstring KWardrobeSlotNames2[] =
{
    L"",
    L"",
    L"",
    L"FACE",
    L"",
};

#endif
