#ifndef QUEST_H
#define QUEST_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <stdio.h>
#include <string>
#include "BaseUnit.h"
#include "QuestUnitData.h"
#include "DataGroup.h"
#include "Level.h"
#include "Player.h"
#include "QuestController.h"
#include "QuestDefines.h"
#include "QuestDialog.h"
#include "QuestManager.h"
#include "ResourceManager.h"
#include "RunicCore.h"
#include "TArrayList.h"
class CQuestRequirements;
class CQuestRewards;

bool dialogIsForNPC(CBaseUnit*, TArrayList<CQuestDialog*>&);

class CQuest : public CRunicCore
{
public:
    virtual ~CQuest();
    CPlayer* getPlayer();
    void setQuestAcceptDialogInteracted(bool);
    void caculateRewards(CDataGroup*);
    int getDungeonMaxFloor();
    long long getQuestHasRandomPieces();
    int getQuestRewardFame();
    int getQuestRewardXP();
    int getQuestRewardGold();
    std::wstring getQuestRewardString();
    void setQuestAccepted(bool);
    void setIsComplete(bool);
    long long isComplete(bool);
    void questEventUpdate(EQUEST_EVENTS, CBaseUnit*, CBaseUnit*);
    void cleanUpDialog(TArrayList<CQuestDialog*>&);
    void destroyIcons();
    void populate(CLevel*);
    void addQuestControllerListerner(CQuestController*);
    void removeQuestControllerListerner(CQuestController*);
    long long getQuestDialog(CBaseUnit*);
    int getQuestIsValidForNPC(CBaseUnit*);
    void getAllNPCUnitDataInvolvedInQuest(TArrayList<CDataGroup*>&);
    CQuest(CResourceManager*, CQuestManager*);
    void getQuestStrings(CDataGroup*, const std::wstring&, TArrayList<CQuestDialog*>&);
    void save(_IO_FILE*);
    void reinitializeQuest(bool, bool);
    void load(_IO_FILE*, CResourceManager*, unsigned int);
    std::wstring replaceStringTags(const std::wstring&);
    std::wstring getQuestDetails();
    void initializeQuestWithNPC(CBaseUnit*);
    unsigned int calculateUnitsFromTag(CDataGroup*, TArrayList<TArrayList<CQuestUnitData*>*>*, TArrayList<CQuestUnitData*>*, unsigned int);
    long long loadQuestData(const std::wstring&);
    void cleanUp(bool);
    void giveRewardForQuest();

    // fields
    long long m_Unknown10;
    int m_iUnknown18;
    int m_iUnknown1C;
    int m_iUnknown20;
    bool m_complete;
    unsigned char m_gap25;
    bool m_questAccepted;
    unsigned char m_gap27;
    bool m_bUnknown28;
    bool m_bUnknown29;
    bool m_bUnknown2A;
    bool m_bUnknown2B;
    bool m_bUnknown2C;
    bool m_bUnknown2D;
    unsigned char m_gap2E[0x2];
    std::wstring m_pUnknown30;
    std::wstring m_pUnknown38;
    std::wstring m_pUnknown40;
    std::wstring m_pUnknown48;
    std::wstring m_sUnknown50;
    std::wstring m_sUnknown58;
    TArrayList<CQuestDialog*> m_acceptDialogs;
    TArrayList<CQuestDialog*> m_Unknown78;
    TArrayList<CQuestDialog*> m_Unknown90;
    TArrayList<CQuestDialog*> m_UnknownA8;
    CQuestDialog* m_pQuestDialog;
    TArrayList<std::wstring> m_UnknownC8;
    TArrayList<std::wstring> m_UnknownE0;
    TArrayList<bool> m_UnknownF8[2];
    CQuestRewards* m_pQuestRewards;
    TArrayList<TArrayList<CQuestUnitData*>*> m_Unknown130;
    TArrayList<TArrayList<CQuestUnitData*>*> m_Unknown148;
    TArrayList<TArrayList<CQuestUnitData*>*> m_Unknown160;
    TArrayList<TArrayList<CQuestUnitData*>*> m_Unknown178;
    TArrayList<TArrayList<CQuestUnitData*>*> m_Unknown190;
    int m_iUnknown1A8;
    int m_iUnknown1AC;
    TArrayList<TSafePointer<CQuestController>*> m_Unknown1B0;
    long long m_iUnknown1C8;
    CQuestManager* m_pQuestManager;
    CResourceManager* m_pResourceManager;
    CQuestRequirements* m_pQuestRequirements;
    long long m_iUnknown1E8;
    TArrayList<std::wstring> m_Unknown1F0;
    bool m_bUnknown208;
    bool m_bUnknown209;
    bool m_bUnknown20A;
    bool m_bUnknown20B;
    int m_iUnknown20C;
    bool m_bUnknown210;
};

std::wstring getAcquireTags(CQuestUnitData*, std::wstring, unsigned int, std::wstring&);

#endif
