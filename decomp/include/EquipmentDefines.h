#ifndef EQUIPMENTDEFINES_H
#define EQUIPMENTDEFINES_H

#include <string>

// Equipment slot bones and icons. Internal linkage: every including TU
// constructs its own copy.

static const std::string KEQUIP_LOCATION_BONES[] =
{
    "tag_righthand",
    "tag_lefthand",
    "",
    "Bip01 Head",
    "",
    "Bip01 L Clavicle",
    "",
    "",
    "",
    "",
    "",
    "tag_leftarm",
};

static const std::string KEQUIP_LOCATION_BONES_SECONDARY[] =
{
    "",
    "",
    "",
    "",
    "",
    "Bip01 R Clavicle",
    "",
    "",
    "",
    "",
    "",
    "",
};

static const std::string KEquipmentIconName[] =
{
    "EquipLeftHand",
    "EquipRightHand",
    "EquipGloves",
    "EquipHelm",
    "EquipChest",
    "EquipShoulder",
    "EquipBoots",
    "EquipBelt",
    "EquipRing1",
    "EquipRing2",
    "EquipAmulet",
    "",
};

#endif
