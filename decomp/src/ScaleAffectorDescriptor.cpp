#include "EmptyStrings.h"
#include "ScaleAffectorDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "ScaleWrapper.h"

CScaleAffectorDescriptor::CScaleAffectorDescriptor()
    : CAffectorDescriptor(L"Scale", L"Scales particles", L"gear")
{
    AddProperty(L"SCALES", L"FIXED", L"Fixed sized for particle( uses X ).", (void*)Set_setUnifiedScale, (void*)Get_getUnifiedScale, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"SCALES", L"X", L"X scale", (void*)Set_setDynamicPropXScale, (void*)Get_getDynamicPropXScale, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"SCALES", L"Y", L"Y scale", (void*)Set_setDynamicPropYScale, (void*)Get_getDynamicPropYScale, VARIABLE_TYPE_FLOAT, 16);
    AddProperty(L"SCALES", L"Z", L"Z scale", (void*)Set_setDynamicPropZScale, (void*)Get_getDynamicPropZScale, VARIABLE_TYPE_FLOAT, 16);
}

CScaleAffectorDescriptor::~CScaleAffectorDescriptor()
{
}

CEditorBaseObject* CScaleAffectorDescriptor::CreateObject(CEditorScene* scene)
{
    return new CScaleWrapper(scene->getResourceManager());
}
