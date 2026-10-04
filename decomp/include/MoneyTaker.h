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

public:
    // Inline accessors behind the descriptors' property functions.
    void setAmount(int value) { m_iAmount = value; }
    int getAmount() const { return m_iAmount; }
};

#endif
