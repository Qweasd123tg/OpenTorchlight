#ifndef CHARACTER_SAVE_STATE_H
#define CHARACTER_SAVE_STATE_H
#include "RunicCore.h"
#include <OgreVector3.h>
#include <OgreMatrix4.h>
#include <cstdio>
#include "TArrayList.h"
#include <string>
#include <vector>
class CItemSaveState;
class CEffect;
// 0x228-byte save record. Constructors and destruction establish the owning
// containers; untyped gaps retain fields outside this reconstruction.
class CCharacterSaveState : public CRunicCore
{
public:
    CCharacterSaveState();
    virtual ~CCharacterSaveState();
    void save(FILE* file);
    void load(FILE* file, unsigned int version);
    long long m_guid10;
    bool m_flag18;
    unsigned char m_padding19[7];
    long long m_guid20;
    long long m_guid28;
    bool m_flag30, m_flag31, m_flag32, m_flag33;
    unsigned char m_flag34; // +0x34, player cheat marker
    unsigned char m_padding35[3];
    union { int m_value38; float m_scale; }; // +0x38
    unsigned char m_padding3C[4];
    std::wstring m_name; // +0x40
    int m_petMode; // +0x48
    unsigned char m_unrecovered4C[4];
    long long m_guid50, m_guid58;
    int m_value60, m_value64, m_value68;
    Ogre::Vector3 m_position; // +0x6c
    Ogre::Matrix4 m_orientation; // +0x78
    long long m_guidB8, m_guidC0, m_guidC8;
    int m_valueD0, m_valueD4, m_valueD8, m_valueDC;
    float m_hp; // +0xe0
    unsigned int m_valueE4, m_valueE8;
    float m_mana; // +0xec
    int m_maxManaBase; // +0xf0
    int m_maxManaBonus; // +0xf4, native truncates float bonus
    float m_playTime; // +0xf8
    float m_bravery; // +0xfc
    int m_experienceReward; // +0x100
    int m_fameReward; // +0x104
    int m_freeStatPoints; // +0x108
    int m_freeSkillPoints; // +0x10c
    int m_freePerkPoints; // +0x110
    unsigned char m_unrecovered114[4];
    std::wstring m_knownSpells[4]; // +0x118
    int m_spellLevels[4]; // +0x138
    int m_damageDefense[7]; // +0x148
    int m_meleeStat; // +0x164
    int m_rangedStat; // +0x168
    int m_defenseStat; // +0x16c
    int m_magicStat; // +0x170
    int m_value174; // +0x174
    int m_alignment; // +0x178, EAlignment
    float m_transformationTime; // +0x17c
    float m_townTravelTime; // +0x180
    int m_value184;
    std::vector<CItemSaveState*> m_pets; // +0x188
    std::vector<CEffect*> m_items[3]; // +0x1a0
    std::vector<int> m_values; // +0x1e8; serialized as 4-byte values
    long long m_guid200;
    int m_value208;
    bool m_flag20C;
    unsigned char m_padding20D[3];
    TArrayList<std::wstring> m_strings; // +0x210
};
#endif
