#include "EmptyStrings.h"
#include "LineAffectorDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "LineWrapper.h"

CLineAffectorDescriptor::CLineAffectorDescriptor()
    : CAffectorDescriptor(L"Line", L"This is a basic accelerator for your particles", L"gear")
{
    AddProperty(L"PROPERTIES", L"DEVIATION", L"The deviation along the line", (void*)Set_setMaxDeviation, (void*)Get_getMaxDeviation, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"TIME STEP", L"The Time over release", (void*)Set_setTimeStep, (void*)Get_getTimeStep, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"DRIFT", L"The amount of drift allowed", (void*)Set_setDrift, (void*)Get_getDrift, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"END POSITION", L"The end position for the line", (void*)Set_setEnd, (void*)Get_getEnd, VARIABLE_TYPE_VECTOR3, 0);
}

CLineAffectorDescriptor::~CLineAffectorDescriptor()
{
}

CEditorBaseObject* CLineAffectorDescriptor::CreateObject(CEditorScene* scene)
{
    return new CLineWrapper(scene->getResourceManager());
}
