#include "EmptyStrings.h"
#include "PlaneColliderDescriptor.h"

CPlaneColliderDescriptor::CPlaneColliderDescriptor()
    : CColliderDescriptor(L"Plane Collision")
{
    AddProperty(L"NORMAL", L"NORMAL", L"Normal by X,Y,Z", (void*)Set_setNormal, (void*)Get_getNormal, VARIABLE_TYPE_VECTOR3, 0);
    AddProperty(L"VISUAL PLANE", L"SHOW PLANE", L"Shows or hides the plane.", (void*)Set_setShowPlane, (void*)Get_getShowPlane, VARIABLE_TYPE_BOOL, 0);
}

CPlaneColliderDescriptor::~CPlaneColliderDescriptor()
{
}
