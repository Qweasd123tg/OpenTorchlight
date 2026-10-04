#include "EmptyStrings.h"
#include "SineForceAffectorDescriptor.h"

CSineForceAffectorDescriptor::CSineForceAffectorDescriptor()
    : CForceAffectorDescriptor(L"Sine Force", L"This will create sine wave force on all the particles released", L"gear")
{
    AddProperty(L"SINE WAVE FREQUENCY", L"MIN", L"The sine wave will choose a number between the min and max", (void*)Set_setFrequencyMin, (void*)Get_getFrequencyMin, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"SINE WAVE FREQUENCY", L"MAX", L"The sine wave will choose a number between the min and max", (void*)Set_setFrequencyMax, (void*)Get_getFrequencyMax, VARIABLE_TYPE_FLOAT, 0);
}

CSineForceAffectorDescriptor::~CSineForceAffectorDescriptor()
{
}
