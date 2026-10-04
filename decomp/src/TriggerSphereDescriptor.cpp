#include "EmptyStrings.h"
#include "TriggerSphereDescriptor.h"

CTriggerSphereDescriptor::CTriggerSphereDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CTriggerDescriptor(name, group, description)
{
    AddProperty(L"PROPERTIES", L"RADIUS", L"Sets the radius of the sphere.", (void*)Set_setRadius, (void*)Get_getRadius, VARIABLE_TYPE_FLOAT, 0);
}

CTriggerSphereDescriptor::~CTriggerSphereDescriptor()
{
}
