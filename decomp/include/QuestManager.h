#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <stdio.h>
#include <map>
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
    bool getPlayerHasQuest(CQuest*);
    void destroyIcons();
    void resetQuestManager(bool);
    std::wstring getDetailsForQuest(CQuest*);
    void giveRewardForQuest(CQuest*);
    void populate(CLevel*);
    bool getQuestIsActive(const std::wstring&);
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
    TArrayList<CQuest*> m_Unknown18;
    CSoundBank* m_pSoundBank;
    CResourceManager* m_pResourceManager;
    std::map<std::wstring, CQuest*> m_Unknown40;
    std::map<std::wstring, bool> m_Unknown70;
    std::map<CDataGroup*, TArrayList<CQuest*>*> m_UnknownA0;
};

#endif
