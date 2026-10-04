#include "EmptyStrings.h"
#include "MoneyTakerDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "MoneyTaker.h"

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

void CMoneyTakerDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* param)
{
    if (object != NULL) {
        CMoneyTaker* moneyTaker = dynamic_cast<CMoneyTaker*>(object);
        if (moneyTaker != NULL && event == 0x4f) {
            moneyTaker->takeMoney();
        }
    }
}

CEditorBaseObject* CMoneyTakerDescriptor::CreateObject(CEditorScene* scene)
{
    return new CMoneyTaker(scene->getResourceManager());
}
