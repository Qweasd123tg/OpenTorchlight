#ifndef UNITTYPES_H
#define UNITTYPES_H

// Partial: unit type IDs from media/unittypes.hie (the UNITTYPES hierarchy).
// Only the IDs used by recovered code are listed.
namespace UNITTYPES
{
    enum EUNITTYPES
    {
        CONSUMABLE = 1,
        WEAPON = 8,
        SWORD = 11,
        HELMET = 12,
        ARMOR = 13,
        CHEST_ARMOR = 15,
        BOOTS = 16,
        BELT = 18,
        SHOULDER_ARMOR = 20,
        SHIELD = 21,
        GLOVES = 23,
        MONSTER = 27,
        PLAYER = 28,
        BREAKABLE = 29,
        TAKEABLE = 31,
        INTERACTABLE = 32,
        POTION = 33,
        BOW = 36,
        TRINKET = 39,
        SCROLL = 42,
        AXE = 44,
        UNIQUE = 54,
        MAGIC = 55,
        STAFF = 61,
        MACE = 89,
        PISTOL = 90,
        WAND = 98,
        QUESTITEM = 103,
        POLEARM = 105,
        CROSSBOW = 110,
        RIFLE = 116,
        SOCKETABLE = 120,
        GAMBLER = 127,
        RANDOMMAGIC_SOCKETABLE = 160,
        SHAREDSTASH = 170
    };
}

#endif
