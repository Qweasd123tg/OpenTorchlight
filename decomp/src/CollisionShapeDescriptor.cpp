#include "EmptyStrings.h"
#include "CollisionShapeDescriptor.h"

CCollisionShapeDescriptor::CCollisionShapeDescriptor()
    : CShapeDescriptor(L"Collision Shape", L"Occupies collision path nodes", L"spawn", false, false, false)
{
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddOutputLogic(OUTPUT_EVENT_ENABLED);
    AddOutputLogic(OUTPUT_EVENT_DISABLED);
    AddProperty(L"PROPERTIES", L"ENABLED", L"If true the collision shape will occupy path nodes", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
}

CCollisionShapeDescriptor::~CCollisionShapeDescriptor()
{
}
