#ifndef MONEYTAKER_H
#define MONEYTAKER_H

#include "EditorBaseObject.h"
class CResourceManager;

class CMoneyTaker : public CEditorBaseObject
{
public:
    CMoneyTaker(CResourceManager* resourceManager);
    virtual ~CMoneyTaker();
    void takeMoney();

private:
    int m_iAmount;
    CResourceManager* m_pResourceManager;
};

#endif
