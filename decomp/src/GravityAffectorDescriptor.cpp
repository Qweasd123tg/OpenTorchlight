#include "EmptyStrings.h"
#include "GravityAffectorDescriptor.h"

CGravityAffectorDescriptor::CGravityAffectorDescriptor()
    : CAffectorDescriptor(L"Gravity Well", L"This will effect your particles as if they were in a vortex", L"gear")
{
    AddProperty(L"PROPERTIES", L"GRAVITY", L"This affector applies Newton's law of universal gravitation. The distance between a particle and the GravityAffector is important in the calculation of the gravity. Therefor, this affector needs to have its position set.", (void*)Set_setGravity, (void*)Get_getGravity, VARIABLE_TYPE_FLOAT, 0);
}

CGravityAffectorDescriptor::~CGravityAffectorDescriptor()
{
}
