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
