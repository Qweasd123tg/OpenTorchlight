#include "EmptyStrings.h"
#include "AllDescriptorsScene.h"
#include "LayoutScene.h"
#include "ResourceManager.h"

CAllDescriptorsScene::~CAllDescriptorsScene()
{
}

CAllDescriptorsScene::CAllDescriptorsScene()
    : CLayoutScene()
{
}

void CAllDescriptorsScene::createDescriptors()
{
    if (!m_pResourceManager->getEditorIsRunning())
        return;
    CLayoutScene::createDescriptors();
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
