#include "EmptyStrings.h"
#include "ColorAffectorDescriptor.h"

CColorAffectorDescriptor::CColorAffectorDescriptor()
    : CAffectorDescriptor(L"Color", L"This will effect the color of your partcles", L"gear")
{
    AddProperty(L"PROPERTIES", L"COLOR OVER TIME", L"Affects the color of the particles over time.", (void*)Set_setColors, (void*)Get_getColors, VARIABLE_TYPE_FLOAT, 32);
}

CColorAffectorDescriptor::~CColorAffectorDescriptor()
{
}
