#ifndef CHARACTER_SAVE_STATE_H
#define CHARACTER_SAVE_STATE_H
#include "RunicCore.h"
#include "TArrayList.h"
#include <string>
#include <vector>
class CItemSaveState;
// 0x228-byte save record. Constructors and destruction establish the owning
// containers; untyped gaps retain fields outside this reconstruction.
class CCharacterSaveState : public CRunicCore
{
public:
    CCharacterSaveState();
    virtual ~CCharacterSaveState();
    long long m_guid10;
    bool m_flag18;
    unsigned char m_padding19[7];
    long long m_guid20;
    long long m_guid28;
    bool m_flag30, m_flag31, m_flag32, m_flag33, m_flag34;
    unsigned char m_padding35[3];
    int m_value38;
    unsigned char m_padding3C[4];
    std::wstring m_name; // +0x40
    unsigned char m_unrecovered48[8];
    long long m_guid50, m_guid58;
    int m_value60, m_value64, m_value68;
    unsigned char m_unrecovered6C[0xb8-0x6c];
    long long m_guidB8, m_guidC0, m_guidC8;
    int m_valueD0, m_valueD4, m_valueD8, m_valueDC;
    float m_hp; // +0xe0
    unsigned int m_valueE4, m_valueE8;
    unsigned char m_unrecoveredEC[0x118-0xec];
    std::wstring m_knownSpells[4]; // +0x118
    unsigned char m_unrecovered138[0x184-0x138];
    int m_value184;
    std::vector<CCharacterSaveState*> m_pets; // +0x188
    std::vector<CItemSaveState*> m_items[3]; // +0x1a0
    std::vector<int> m_values; // +0x1e8; serialized as 4-byte values
    long long m_guid200;
    int m_value208;
    bool m_flag20C;
    unsigned char m_padding20D[3];
    TArrayList<std::wstring> m_strings; // +0x210
};
#endif
