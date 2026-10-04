#ifndef QUESTDIALOG_H
#define QUESTDIALOG_H

#include <stdio.h>
#include <string>

#include "BaseUnit.h"
#include "DataGroup.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CQuest;
class CQuestDialogItem;
class CSoundBank;

class CQuestDialog : public CRunicCore
{
public:
    virtual ~CQuestDialog();

    bool dialogIsForNPC(CBaseUnit* pUnit);
    void reinitialize();
    void load(_IO_FILE* pFile);
    void save(_IO_FILE* pFile);
    CQuestDialog* getDialog(bool bRandom);
    void giveOrRemoveItems(CBaseUnit* pUnit);
    void cleanUp();
    void stopDialogSound();
    void populate();
    void playDialogSound();
    CQuestDialog(CQuest* pQuest);
    bool parseDialogTag(const std::wstring& sTag, CDataGroup* pDataGroup);

    CQuest* m_pQuest;

    TArrayList<std::wstring> m_dialogText;
    TArrayList<CQuestDialogItem*> m_dialogItemsToGive;
    TArrayList<CQuestDialogItem*> m_dialogItemsToRemove;

    std::wstring m_sNPCName;
    CDataGroup* m_pNPCDataGroup;
    int m_iDialogType;

    bool m_bIconAboveHead;
    bool m_bFloatyText;
    bool m_bDialogInitialized;
    bool m_bItemsGiven;
    bool m_bMakePetOnAccept;
    bool m_bRemoveAsPetOnComplete;
    bool m_bDestroyPet;
    bool m_bLookAtPlayer;

    unsigned char m_reserved7C[4];

    union
    {
        CSoundBank* m_pSoundBank;
        unsigned char m_reservedSoundStorage[0x18];
    };

    std::wstring m_sThemeOverride;
    std::wstring m_sSoundName;
};

#endif
