#include "EmptyStrings.h"
#include "AlignDescriptor.h"

CAlignDescriptor::CAlignDescriptor()
    : CAffectorDescriptor(L"Align", L"This will align particles with the last particle released", L"gear")
{
    AddProperty(L"PROPERTIES", L"TO VELOCITY", L"Will align to the velocity of the particle. If false will align to its orientation.", (void*)Set_setAlignByVelocity, (void*)Get_getAlignByVelocity, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"PROPERTIES", L"STRETCH", L"Will Stretch particles.", (void*)Set_setAllowStretch, (void*)Get_getAllowStretch, VARIABLE_TYPE_BOOL, 0);
}

CAlignDescriptor::~CAlignDescriptor()
{
}
