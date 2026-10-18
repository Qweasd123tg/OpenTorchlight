#include "EmptyStrings.h"
#include "TeleportDescriptor.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "Teleport.h"

CTeleportDescriptor::CTeleportDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, true, true, true, false)
{
    AddProperty(L"PROPERTIES", L"ENABLED", L"Sets the teleport enabled or disabled.", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
    AddInputLogic(INPUT_EVENT_ACTIVATE_TELEPORT);
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    AddOutputLogic(OUTPUT_EVENT_ACTIVATED);
}

CTeleportDescriptor::~CTeleportDescriptor()
{
}

CEditorBaseObject* CTeleportDescriptor::CreateObject(CEditorScene* scene)
{
    return new CTeleport(scene->getResourceManager());
}

void CTeleportDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject*)
{
    CTeleport* teleport = dynamic_cast<CTeleport*>(object);
    CPositionableObject* positionable = dynamic_cast<CPositionableObject*>(object);
    if (!teleport)
        return;
    switch (event) {
    case 2:
        teleport->setEnabled(true);
        break;
    case 3:
        teleport->setEnabled(false);
        break;
    case 38:
        if (positionable) {
            teleport->setVisible(true);
            const Ogre::Vector3& forward = positionable->getForward();
            teleport->activate(positionable->getPosition(true), forward);
            teleport->setVisible(false);
        }
        break;
    }
}
