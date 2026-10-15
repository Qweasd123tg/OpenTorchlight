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

unsigned int CUnitTriggerDescriptor::GetLoopTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData)
{
    for (unsigned int index = 0; index < 3; ++index)
    {
        if (value == gTRIGGER_LOOP_TYPE_NAMES[index])
            return index;
    }
    return 0;
}
