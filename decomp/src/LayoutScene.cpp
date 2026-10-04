#include "EmptyStrings.h"
#include "LayoutScene.h"
#include "Descriptor.h"
#include "DescriptorManager.h"
#include "ResourceManager.h"
#include "SoundObject.h"
#include "GameVariables.h"

CLayoutScene::CLayoutScene()
    : CEditorScene(L"Layout")
{
}

void CLayoutScene::fireEvent(EEDITOR_EVENTS event, long long guid)
{
    switch (event) {
    case EDITOR_EVENT_STOP:
    case EDITOR_EVENT_PLAY: {
        CDescriptor* pDescriptor = getDescriptorManager()->GetDescriptor(L"Sound", false);
        if (pDescriptor != NULL) {
            for (unsigned int i = 0; i < pDescriptor->getObjectCount(); i++) {
                CEditorBaseObject* pObject = pDescriptor->getObject(i);
                if (pObject == NULL)
                    continue;
                CSoundObject* pSound = dynamic_cast<CSoundObject*>(pObject);
                if (pSound == NULL)
                    continue;
                if (event == EDITOR_EVENT_PLAY)
                    pSound->play();
                else
                    pSound->stop();
            }
        }
        break;
    }
    default:
        break;
    }
}

void CLayoutScene::createDescriptors()
{
    if (!m_pResourceManager->getEditorIsRunning())
        return;

    AddDescriptor(L"Group");
    AddDescriptor(L"Monster");
    AddDescriptor(L"Unit Spawner");
    AddDescriptor(L"Layout Link");
    AddDescriptor(L"Layout Link Particle");
    AddDescriptor(L"Layout Link Timeline");
    AddDescriptor(L"Generic Model");
    AddDescriptor(L"Room Piece");
    AddDescriptor(L"Sound");
    AddDescriptor(L"Music");
    AddDescriptor(L"Missile");
    AddDescriptor(L"Light");
    AddDescriptor(L"Image");
    AddDescriptor(L"Button");
    AddDescriptor(L"Timeline");
    AddDescriptor(L"Logic Group");
    AddDescriptor(L"Player Sphere Trigger");
    AddDescriptor(L"Player Box Trigger");
    AddDescriptor(L"Unit Trigger");
    AddDescriptor(L"Counter");
    AddDescriptor(L"Random Choice");
    AddDescriptor(L"Warper");
    AddDescriptor(L"Path");
    AddDescriptor(L"Teleport");
    AddDescriptor(L"Timer");
    AddDescriptor(L"Output Incrementor");
    AddDescriptor(L"Camera Shake");
    AddDescriptor(L"Property Node");
    AddDescriptor(L"Damage Shape");
    AddDescriptor(L"Puzzle Input");
    AddDescriptor(L"Interactive");
    AddDescriptor(L"Camera Controller");
    AddDescriptor(L"Game State Controller");
    AddDescriptor(L"Quest Controller");
    AddDescriptor(L"Skill Controller");
    AddDescriptor(L"Pathing");
    AddDescriptor(L"Animation Controller");
    AddDescriptor(L"Skip Cutscene");
    AddDescriptor(L"Cinematic");
    AddDescriptor(L"Money Taker");
    AddDescriptor(L"Dungeon Object");
    AddDescriptor(L"Waypoint Activator");
}

CLayoutScene::~CLayoutScene()
{
}
