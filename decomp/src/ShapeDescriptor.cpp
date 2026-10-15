#include "ShapeDescriptor.h"
#include "ShapeDescriptorNames.h"

CShapeDescriptor::~CShapeDescriptor()
{
}

std::wstring CShapeDescriptor::GetSpawnDirectionStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 4)
        return gSHAPE_DIRECTION_NAMES[0];
    return gSHAPE_DIRECTION_NAMES[index];
}

std::wstring CShapeDescriptor::GetSpawnShapeStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 4)
        return gSHAPE_NAMES[0];
    return gSHAPE_NAMES[index];
}

std::wstring CShapeDescriptor::GetSpawnOrderStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 2)
        return gPOINT_ORDER_NAMES[0];
    return gPOINT_ORDER_NAMES[index];
}

unsigned int CShapeDescriptor::GetSpawnOrderIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    for (unsigned int index = 0; index < 3; ++index)
    {
        if (gPOINT_ORDER_NAMES[index] == value)
            return index;
    }
    return 0;
}

unsigned int CShapeDescriptor::GetSpawnDirectionIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    for (unsigned int index = 0; index < 5; ++index)
    {
        if (gSHAPE_DIRECTION_NAMES[index] == value)
            return index;
    }
    return 0;
}

unsigned int CShapeDescriptor::GetSpawnShapeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    for (unsigned int index = 0; index < 5; ++index)
    {
        if (gSHAPE_NAMES[index] == value)
            return index;
    }
    return 0;
}

CShapeDescriptor::CShapeDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description, bool option1, bool option2, bool option3)
    : CPositionableObjectDescriptor(name, group, description, true, option3, option3, option3, false)
{
    AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"SHAPE", L"Shape of the spawner", (void*)Set_setShape, (void*)Get_getShape, GetSpawnShapeIDByString, GetSpawnShapeStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    if (option1)
        AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"RELEASE ORDER", L"order in which the units get spawned", (void*)Set_setPointOrder, (void*)Get_getPointOrder, GetSpawnOrderIDByString, GetSpawnOrderStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    if (option2)
        AddPropertyWithInterpreterFunctions(L"PROPERTIES", L"DIRECTION", L"The direction the units will face once spawned.", (void*)Set_setShapeDirection, (void*)Get_getShapeDirection, GetSpawnDirectionIDByString, GetSpawnDirectionStringByID, NULL, VARIABLE_TYPE_UNSIGNED_INTEGER, 4);
    AddProperty(L"BOX SIZE", L"SIZE", L"The size of the box ( X = width, Y = height, Z = length )", (void*)Set_setBoxSize, (void*)Get_getBoxSize, VARIABLE_TYPE_VECTOR3, 0);
    AddProperty(L"RADIUS", L"USE MAX ONLY", L"When true it will use only the max radius.", (void*)Set_setUseMaxRadiusOnly, (void*)Get_getUseMaxRadiusOnly, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"RADIUS", L"MIN RADIUS", L"The min radius for the spawner.", (void*)Set_setMinRadius, (void*)Get_getMinRadius, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"RADIUS", L"MAX RADIUS", L"The max radius for the spawner.", (void*)Set_setMaxRadius, (void*)Get_getMaxRadius, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"ANGLE", L"ANGLE", L"The angle to spawn units at.", (void*)Set_setAngleOfRelease, (void*)Get_getAngleOfRelease, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"ANGLE", L"ANGLE OFFSET", L"Angle minus the offset", (void*)Set_setAngleOffset, (void*)Get_getAngleOffset, VARIABLE_TYPE_FLOAT, 16);
}
