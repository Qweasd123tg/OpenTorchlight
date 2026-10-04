#include "EmptyStrings.h"
#include "JetAffectorDescriptor.h"

CJetAffectorDescriptor::CJetAffectorDescriptor()
    : CAffectorDescriptor(L"Jet", L"This is a basic accelerator for your particles", L"gear")
{
    AddProperty(L"PROPERTIES", L"ACCELERATION", L"This is the rate of acceleration", (void*)Set_setDynamicPropAcceleration, (void*)Get_getDynamicPropAcceleration, VARIABLE_TYPE_FLOAT, 16);
}

CJetAffectorDescriptor::~CJetAffectorDescriptor()
{
}
