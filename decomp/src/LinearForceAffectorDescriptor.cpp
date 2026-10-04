#include "EmptyStrings.h"
#include "LinearForceAffectorDescriptor.h"

CLinearForceAffectorDescriptor::CLinearForceAffectorDescriptor()
    : CForceAffectorDescriptor(L"Linear Force", L"This puts a basic force at the root of the particle system", L"gear")
{

}

CLinearForceAffectorDescriptor::~CLinearForceAffectorDescriptor()
{
}
