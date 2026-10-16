#include "Cinematics.h"
#include "Cinematic.h"
#include "CinematicObject.h"
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
    CCinematicObject* cinematic = dynamic_cast<CCinematicObject*>(object);
    if (cinematic == NULL)
        return;
    if (event == 9) {
        cinematic->play();
    }
}

CEditorBaseObject* CCinematicDescriptor::CreateObject(CEditorScene* scene)
{
    return new CCinematicObject(scene->getResourceManager());
}

std::wstring CCinematicDescriptor::getCinematicStringByID(CEditorScene*, CEditorBaseObject*, unsigned int index, void*)
{
    std::wstring name = EMPTY_WSTRING;
    unsigned int count = CCinematics::getSingleton()->m_lCinematics.size();
    if (index < count)
        name = CCinematics::getSingleton()->getCinematic(index)->m_sName;
    else if (count != 0)
        name = CCinematics::getSingleton()->getCinematic(0u)->m_sName;
    else
        name = EMPTY_WSTRING;
    return name;
}
unsigned int CCinematicDescriptor::getCinematicIDByString(CEditorScene*, CEditorBaseObject* object, const std::wstring&, void*)
{
    CCinematicObject* cinematic = dynamic_cast<CCinematicObject*>(object);
    unsigned int count = CCinematics::getSingleton()->m_lCinematics.size();
    for (unsigned int index = 0; index < count; ++index) {
        if (CCinematics::getSingleton()->getCinematic(index)->m_sName == std::wstring(cinematic->m_sCinematicName))
            return index;
    }
    return 0;
}
