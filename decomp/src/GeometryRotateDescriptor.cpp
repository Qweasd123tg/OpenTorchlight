#include "EmptyStrings.h"
#include "GeometryRotateDescriptor.h"

CGeometryRotateDescriptor::CGeometryRotateDescriptor()
    : CAffectorDescriptor(L"Geometry Rotator", L"Rotates geometry", L"gear")
{
    AddProperty(L"ROTATION", L"ROTATION SPEED", L"This is the speed at which the particles rotate", (void*)Set_setDynamicPropRotationSpeed, (void*)Get_getDynamicPropRotationSpeed, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"ROTATION", L"USE OWN ROTATION", L"Making this true will mean the rotation speed will be based off the speed that the particle is currently rotating at. (Rotation speed from the emitter)", (void*)Set_setUseOwnRotationSpeed, (void*)Get_getUseOwnRotationSpeed, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"ROTATION", L"AXIS OF ROTATION", L"The axis of the rotation.", (void*)Set_setRotationAxis, (void*)Get_getRotationAxis, VARIABLE_TYPE_VECTOR3, 0);
}

CGeometryRotateDescriptor::~CGeometryRotateDescriptor()
{
}
