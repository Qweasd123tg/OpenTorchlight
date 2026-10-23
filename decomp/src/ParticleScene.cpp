#include "EmptyStrings.h"
#include "ParticleScene.h"
#include "EditorScene.h"

#include "ResourceManager.h"

void CParticleScene::createDescriptors()
{
    if (!m_pResourceManager->getEditorIsRunning())
        return;

    AddDescriptor(L"Group");
    AddDescriptor(L"Logic Group");
    AddDescriptor(L"Timeline");
    AddDescriptor(L"Sound");
    AddDescriptor(L"Camera Shake");
    AddDescriptor(L"Particle");
    AddDescriptor(L"Emitter");
    AddDescriptor(L"Align");
    AddDescriptor(L"Line");
    AddDescriptor(L"Linear Force");
    AddDescriptor(L"Sine Force");
    AddDescriptor(L"Vortext");
    AddDescriptor(L"Gravity Well");
    AddDescriptor(L"Jet");
    AddDescriptor(L"Scale");
    AddDescriptor(L"Geometry Rotator");
    AddDescriptor(L"Texture Rotate");
    AddDescriptor(L"Texture Animation");
    AddDescriptor(L"Color");
    AddDescriptor(L"Box Collision");
    AddDescriptor(L"Plane Collision");
    AddDescriptor(L"Sphere Collision");
}

CParticleScene::~CParticleScene()
{
}

CParticleScene::CParticleScene()
    : CEditorScene(L"Particle Creator")
{
}

#include "Descriptor.h"
#include "DescriptorManager.h"
#include "ParticleTechWrapper.h"

void CParticleScene::fireEvent(EEDITOR_EVENTS event, long long objectId)
{
    switch (event) {
    case EDITOR_EVENT_STOP:
    case EDITOR_EVENT_PLAY: {
        CDescriptor* descriptor = getDescriptorManager()->GetDescriptor(L"Particle", false);
        if (descriptor != NULL) {
            for (unsigned int i = 0; i < descriptor->getObjectCount(); ++i) {
                if (objectId != -1 && descriptor->getObject(i)->getGuid() != objectId)
                    continue;
                CEditorBaseObject* object = descriptor->getObject(i);
                if (object == NULL)
                    continue;
                CParticleTechWrapper* technique = dynamic_cast<CParticleTechWrapper*>(object);
                if (technique == NULL || technique->HasBaseObjectFlag(static_cast<EEDITOROBJECT_FLAG>(2)))
                    continue;
                technique->forceStop();
                if (event == EDITOR_EVENT_PLAY)
                    technique->setActivated(true);
            }
        }
        break;
    }
    default:
        break;
    }
}
