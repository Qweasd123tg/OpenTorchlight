#include "EmptyStrings.h"
#include "ColliderDescriptor.h"

CColliderDescriptor::CColliderDescriptor(const wchar_t* name)
    : CAffectorDescriptor(name, L"Collision for particles", L"gear")
{
    AddPropertyWithInterpreterFunctions(L"COLLISION", L"TYPE", L"The type of collision to use.", (void*)Set_setCollisionType, (void*)Get_getCollisionType, GetParticleCollisionTypeIDByString, GetParticleCollisionTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddPropertyWithInterpreterFunctions(L"COLLISION", L"INTERSECTION TYPE", L"This is the type of intersection used when comparing particles for collision.", (void*)Set_setIntersectionType, (void*)Get_getIntersectionType, GetParticleIntersectionTypeIDByString, GetParticleIntersectionTypeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddProperty(L"COLLISION", L"FRICTION", L"How much friction to apply when collision occurs.", (void*)Set_setFriction, (void*)Get_getFriction, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"COLLISION", L"BOUNCYNESS", L"How much bounce the particle has on impact.", (void*)Set_setBouncyness, (void*)Get_getBouncyness, VARIABLE_TYPE_FLOAT, 0);
}

CColliderDescriptor::~CColliderDescriptor()
{
}
