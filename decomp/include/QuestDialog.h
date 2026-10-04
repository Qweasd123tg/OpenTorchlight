#ifndef QUESTDIALOG_H
#define QUESTDIALOG_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <stdio.h>
#include <string>
#include "BaseUnit.h"
#include "DataGroup.h"
#include "RunicCore.h"
class CQuest;

class CQuestDialog : public CRunicCore
{
public:
    virtual ~CQuestDialog();
    long long dialogIsForNPC(CBaseUnit*);
    void reinitialize();
    void load(_IO_FILE*);
    void save(_IO_FILE*);
    CQuestDialog* getDialog(bool);
    void giveOrRemoveItems(CBaseUnit*);
    void cleanUp();
    void stopDialogSound();
    void populate();
    void playDialogSound();
    CQuestDialog(CQuest*);
    long long parseDialogTag(const std::wstring&, CDataGroup*);

    // fields
    CQuest* m_pQuest;
    unsigned char m_Unknown18[0x18] __attribute__((aligned(8)));
    unsigned char m_Unknown30[0x18] __attribute__((aligned(8)));
    unsigned char m_Unknown48[0x18] __attribute__((aligned(8)));
    std::wstring m_sUnknown60;
    long long m_iUnknown68;
    int m_iUnknown70;
    bool m_bUnknown74;
    bool m_bUnknown75;
    bool m_bUnknown76;
    bool m_bUnknown77;
    bool m_bUnknown78;
    bool m_bUnknown79;
    bool m_bUnknown7A;
    bool m_bUnknown7B;
    unsigned char m_gap7C[0x4] __attribute__((aligned(4)));
    unsigned char m_Unknown80[0x18] __attribute__((aligned(8)));
    void* m_pUnknown98;
    std::wstring m_sUnknownA0;
};

#endif
