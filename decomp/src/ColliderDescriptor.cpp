#include "EmptyStrings.h"
#include "ColliderDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"

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

CEditorBaseObject* CColliderDescriptor::CreateObject(CEditorScene* scene)
{
    return 0;
}

std::wstring CColliderDescriptor::GetParticleIntersectionTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData)
{
    const std::wstring* types =
        reinterpret_cast<const std::wstring*>(gPARTICLE_INTERSECTION_TYPE);

    if (1 < index)
        return types[0];
    else
        return types[index];
}

unsigned int CColliderDescriptor::GetParticleCollisionTypeIDByString(
    CEditorScene* scene,
    CEditorBaseObject* object,
    const std::wstring& value,
    void* userData)
{
    const std::wstring* collisionTypes =
        reinterpret_cast<const std::wstring*>(gPARTICLE_COLLISION_TYPE);

    for (unsigned int i = 0; i < 3; ++i) {
        if (value == collisionTypes[i]) {
            return i;
        }
    }

    return 0;
}
