#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <stdio.h>
#include <string>
#include "BaseUnit.h"
#include "Character.h"
#include "Level.h"
#include "Player.h"
#include "QuestDefines.h"
#include "QuestDialog.h"
#include "ResourceManager.h"
#include "RunicCore.h"
#include "SoundBank.h"
#include "TArrayList.h"
class CQuest;

class CQuestManager : public CRunicCore
{
public:
    virtual ~CQuestManager();
    static CQuestManager* getSingleton();
    void setPlayer(CPlayer*);
    void update(float);
    long long getPlayerHasQuest(CQuest*);
    void destroyIcons();
    void resetQuestManager(bool);
    CQuestManager* getDetailsForQuest(CQuest*);
    void giveRewardForQuest(CQuest*);
    void populate(CLevel*);
    long long getQuestIsActive(const std::wstring&);
    char getQuestComplete(const std::wstring&);
    long long getQuestByName(const std::wstring&);
    void getQuestNames(TArrayList<std::wstring >&);
    void save(_IO_FILE*);
    long long removeQuest(CQuest*, bool);
    void questEventUpdate(EQUEST_EVENTS, CCharacter*, CBaseUnit*);
    void load(_IO_FILE*, unsigned int, CResourceManager*);
    CQuest* getQuestForNPC(CBaseUnit*);
    int getNPCIcon(CCharacter*);
    long long calculateNPCIcon(CCharacter*);
    void getDialogsForNPC(TArrayList<CQuestDialog*>&, CBaseUnit*, bool);
    void loadQuests();
    void reloadQuests();
    CQuestManager(CResourceManager*);
    long long completeQuest(CQuest*);
    long long giveQuest(CQuest*, CBaseUnit*, bool);
    void resetQuest(CQuest*);

    // fields
    CPlayer* m_pPlayer;
    unsigned char m_Unknown18[0x18] __attribute__((aligned(8)));
    CSoundBank* m_pSoundBank;
    CResourceManager* m_pResourceManager;
    long long m_Unknown40;
    int m_iUnknown48;
    unsigned char m_gap4C[0x4] __attribute__((aligned(4)));
    void* m_pUnknown50;
    void* m_pUnknown58;
    long long m_iUnknown60;
    long long m_iUnknown68;
    long long m_Unknown70;
    int m_iUnknown78;
    unsigned char m_gap7C[0x4] __attribute__((aligned(4)));
    void* m_pUnknown80;
    void* m_pUnknown88;
    long long m_iUnknown90;
    long long m_iUnknown98;
    long long m_UnknownA0;
    int m_iUnknownA8;
    unsigned char m_gapAC[0x4] __attribute__((aligned(4)));
    void* m_pUnknownB0;
    long long m_iUnknownB8;
    long long m_iUnknownC0;
    long long m_iUnknownC8;
};

#endif
