#include "EmptyStrings.h"
#include "ForceAffectorDescriptor.h"

CForceAffectorDescriptor::CForceAffectorDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CAffectorDescriptor(name, group, description)
{
    AddPropertyWithInterpreterFunctions(L"FORCES", L"FORCE APPLICATION", L"This is how the force gets applied to the particels.", (void*)Set_setForceApplication, (void*)Get_getForceApplication, GetForceApplicationIDByString, GetForceApplicationStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddProperty(L"FORCES", L"FORCES", L"The force applied in all axies", (void*)Set_setForceVector, (void*)Get_getForceVector, VARIABLE_TYPE_VECTOR3, 0);
}

CForceAffectorDescriptor::~CForceAffectorDescriptor()
{
}
