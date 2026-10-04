#include "EmptyStrings.h"
#include "JetAffectorDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "JetWrapper.h"

CJetAffectorDescriptor::CJetAffectorDescriptor()
    : CAffectorDescriptor(L"Jet", L"This is a basic accelerator for your particles", L"gear")
{
    AddProperty(L"PROPERTIES", L"ACCELERATION", L"This is the rate of acceleration", (void*)Set_setDynamicPropAcceleration, (void*)Get_getDynamicPropAcceleration, VARIABLE_TYPE_FLOAT, 16);
}

CJetAffectorDescriptor::~CJetAffectorDescriptor()
{
}

CEditorBaseObject* CJetAffectorDescriptor::CreateObject(CEditorScene* scene)
{
    return new CJetWrapper(scene->getResourceManager());
}
