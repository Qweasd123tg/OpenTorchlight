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
