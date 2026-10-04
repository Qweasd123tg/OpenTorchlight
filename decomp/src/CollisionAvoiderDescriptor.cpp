#include "EmptyStrings.h"
#include "CollisionAvoiderDescriptor.h"

CCollisionAvoiderDescriptor::CCollisionAvoiderDescriptor()
    : CColliderDescriptor(L"Avoid Sphere")
{
    AddProperty(L"SIZE", L"RADIUS", L"Radius of the sphere.", (void*)Set_setRadius, (void*)Get_getRadius, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"VISUAL SPHERE", L"SHOW SPHERE", L"Shows or hides the sphere.", (void*)Set_setShowSphere, (void*)Get_getShowSphere, VARIABLE_TYPE_BOOL, 0);
}

CCollisionAvoiderDescriptor::~CCollisionAvoiderDescriptor()
{
}
