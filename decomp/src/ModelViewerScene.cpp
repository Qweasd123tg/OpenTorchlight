#include "EmptyStrings.h"
#include "ModelViewerScene.h"
#include "ResourceManager.h"

CModelViewerScene::CModelViewerScene()
    : CEditorScene(L"Mesh Viewer")
{
}

CModelViewerScene::~CModelViewerScene()
{
}

void CModelViewerScene::createDescriptors()
{
    if (!m_pResourceManager->getEditorIsRunning())
        return;

    AddDescriptor(L"Generic Model");
    AddDescriptor(L"Layout Link");
    AddDescriptor(L"Monster");
}
