#ifndef UNITTYPES_H
#define UNITTYPES_H

// Partial: unit type IDs from media/unittypes.hie (the UNITTYPES hierarchy).
// Only the IDs used by recovered code are listed.
namespace UNITTYPES
{
    enum EUNITTYPES
    {
        CONSUMABLE = 1,
        MONSTER = 27,
        PLAYER = 28,
        BREAKABLE = 29,
        TAKEABLE = 31,
        INTERACTABLE = 32,
        UNIQUE = 54,
        MAGIC = 55,
        QUESTITEM = 103,
        SOCKETABLE = 120,
        RANDOMMAGIC_SOCKETABLE = 160,
        SHAREDSTASH = 170
    };
}

#endif
