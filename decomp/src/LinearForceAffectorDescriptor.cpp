#include "EmptyStrings.h"
#include "LinearForceAffectorDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "LinearForceWrapper.h"

CLinearForceAffectorDescriptor::CLinearForceAffectorDescriptor()
    : CForceAffectorDescriptor(L"Linear Force", L"This puts a basic force at the root of the particle system", L"gear")
{

}

CLinearForceAffectorDescriptor::~CLinearForceAffectorDescriptor()
{
}

CEditorBaseObject *CLinearForceAffectorDescriptor::CreateObject(CEditorScene *scene)
{
    return new CLinearForceWrapper(scene->getResourceManager());
}
