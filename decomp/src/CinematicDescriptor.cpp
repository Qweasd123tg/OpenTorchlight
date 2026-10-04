#include "EmptyStrings.h"
#include "CinematicDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "CinematicObject.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"

CCinematicDescriptor::CCinematicDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CBaseObjectDescriptor(name, group, description)
{
    AddPropertyWithInterpreterFunctions(L"CINEMATIC", L"CINEMATIC", L"Cinematic Name", (void*)Set_setCinematicName, (void*)Get_getCinematicName, getCinematicIDByString, getCinematicStringByID, NULL, VARIABLE_TYPE_STRING, 4);
    AddOutputLogic(OUTPUT_EVENT_INTERACTED);
    AddInputLogic(INPUT_EVENT_PLAY);
}

CCinematicDescriptor::~CCinematicDescriptor()
{
}

void CCinematicDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* param_3)
{
    if (object != NULL) {
        CCinematicObject* cinematic = dynamic_cast<CCinematicObject*>(object);
        if (cinematic != NULL && event == 9) {
            cinematic->play();
        }
    }
}

CEditorBaseObject* CCinematicDescriptor::CreateObject(CEditorScene* scene)
{
    return new CCinematicObject(scene->getResourceManager());
}
