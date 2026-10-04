#include "EmptyStrings.h"
#include "MoneyTakerDescriptor.h"

CMoneyTakerDescriptor::CMoneyTakerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddProperty(L"MONEY TAKER", L"AMOUNT", L"Amount to take", (void*)Set_setAmount, (void*)Get_getAmount, VARIABLE_TYPE_INTEGER, 0);
    AddOutputLogic(OUTPUT_EVENT_MONEY_TAKEN);
    AddOutputLogic(OUTPUT_EVENT_INSUFFICIENT_FUNDS);
    AddInputLogic(INPUT_EVENT_TAKE_MONEY);
}

CMoneyTakerDescriptor::~CMoneyTakerDescriptor()
{
}
