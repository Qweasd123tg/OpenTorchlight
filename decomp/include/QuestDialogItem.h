#ifndef QUESTDIALOGITEM_H
#define QUESTDIALOGITEM_H

#include "RunicCore.h"

class CDataGroup;
class CPlayer;
class CQuestDialog;

class CQuestDialogItem : public CRunicCore
{
public:
    virtual ~CQuestDialogItem();

    CQuestDialogItem(CQuestDialog* pQuestDialog);

    void dialogComplete(CPlayer* pPlayer);
    void parseDialogItemGroup(CDataGroup* pDataGroup, bool bGive);

    CDataGroup* m_pDataGroup;
    CQuestDialog* m_pQuestDialog;
    bool m_bGive;
    bool m_bGold;
    unsigned char m_gap22[2];
    int m_iCount;
};

#endif
