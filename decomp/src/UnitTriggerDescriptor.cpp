#include "UnitTriggerDescriptor.h"
#include "UnitTriggerDescriptorNames.h"

void CUnitTriggerDescriptor::update(float value)
{
}

CUnitTriggerDescriptor::~CUnitTriggerDescriptor()
{
}

std::wstring CUnitTriggerDescriptor::GetLoopTypeStringByID(
    CEditorScene*,
    CEditorBaseObject*,
    unsigned int index,
    void*)
{
    if (index > 2)
        return gTRIGGER_LOOP_TYPE_NAMES[0];
    return gTRIGGER_LOOP_TYPE_NAMES[index];
}
