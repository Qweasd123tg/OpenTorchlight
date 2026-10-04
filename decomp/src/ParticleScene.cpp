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
