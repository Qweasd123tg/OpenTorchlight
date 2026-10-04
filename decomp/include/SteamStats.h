#ifndef STEAMSTATS_H
#define STEAMSTATS_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "DescriptorProp.h"
#include "GameEnums.h"
#include "Player.h"
#include "RunicCore.h"
class iStatListener;

class CSteamStats : public CRunicCore
{
public:
    virtual ~CSteamStats();
    void reloadPlayerData(CPlayer*);
    void update(float);
    void forceStatsToSave();
    void setStatInt(ESTATS, unsigned int);
    void incrementStat(ESTATS, int);
    void setStatFloat(ESTATS, float);
    int getStatInt(ESTATS);
    int getStatFloat(ESTATS);
    int getPlayerStatInt(ESTATS);
    long long getPlayerStatFloat(ESTATS);
    static CSteamStats* getSingleton();
    long long StoreStats();
    void statModified(ESTATS, UNIONDATA32BIT);
    void updateStatListeners();
    void checkForLocalUpdates(float);
    void addStatListener(ESTATS, iStatListener*);
    CSteamStats();

    // fields
    bool m_bUnknown10;
    bool m_bUnknown11;
    unsigned char m_gap12[0x2];
    float m_fUnknown14;
    float m_fUnknown18;
    bool m_bUnknown1C;
    unsigned char m_gap1D[0x3];
    long long m_iUnknown20;
    bool m_bUnknown28;
    unsigned char m_gap29[0x7];
    unsigned char m_Unknown30[0x18] __attribute__((aligned(8)));
    long long m_Unknown48;
    int m_iUnknown50;
    unsigned char m_gap54[0x4] __attribute__((aligned(4)));
    void* m_pUnknown58;
    void* m_pUnknown60;
    long long m_iUnknown68;
    long long m_iUnknown70;
    unsigned char m_Unknown78[0x18] __attribute__((aligned(8)));
    long long m_iUnknown90;
    CPlayer* m_pPlayer;
};

#endif
