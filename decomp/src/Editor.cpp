#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include "Editor.h"
#include "EditorDLL.h"
#include "EditorObjectManager.h"
#include "GameClient.h"
#include "POV.h"
#include "ResourceManager.h"
#include "Settings.h"
#include "Undo.h"
#include "iEditorResourceManager.h"

void CEditor::SetMouseWheelDelta(int delta)
{
    m_iMouseWheelDelta = delta;
}

void CEditor::SetPovVelocityMult(float multiplier)
{
    if (m_pCameraController) m_pCameraController->m_fUnknown144 = multiplier;
}

void CEditor::SetRenderWindowHasFocus(bool focused)
{
    if (m_pCameraController) m_pCameraController->m_bUnknown178 = focused;
    m_bRenderWindowHasFocus = focused;
}

CEditorScene* CEditor::GetEditorScene(unsigned int index)
{
    if (index < m_EditorScenes.size()) return m_EditorScenes[index];
    return NULL;
}

unsigned int CEditor::getUndoSize()
{
    return m_Undos.size();
}

void CEditor::doUndo()
{
    if (m_Undos.size() > 0) {
        CUndo* undo = m_Undos.back();
        m_Undos.pop_back();
        undo->DoAsUndo();
        delete undo;
    }
}

unsigned int CEditor::getRedoSize()
{
    return m_Redos.size();
}

void CEditor::doRedo()
{
    if (m_Redos.size() > 0) {
        CUndo* undo = m_Redos.back();
        m_Redos.pop_back();
        undo->DoAsRedo();
        delete undo;
    }
}

void CEditor::deleteAllUndos()
{
    for (std::list<CUndo*>::iterator it = m_Redos.begin(); it != m_Redos.end(); ++it) {
        if (*it) { delete *it; *it = NULL; }
    }
    for (std::list<CUndo*>::iterator it = m_Undos.begin(); it != m_Undos.end(); ++it) {
        if (*it) { delete *it; *it = NULL; }
    }
}

void CEditor::FlyToPositionLookingAtPos(Ogre::Vector3 position, Ogre::Vector3 target)
{
    if (m_pCameraController) m_pCameraController->FlyTo(position, target);
}

void CEditor::keyEvent(unsigned int event, unsigned int code)
{
    if (m_pObjectManager) m_pObjectManager->keyEvent(event, code);
}

void CEditor::mouseEvent(unsigned int event, unsigned int code)
{
    if (m_pObjectManager) m_pObjectManager->mouseEvent(event, code);
}

CGameClient* CEditor::getGameClient()
{
    return m_pEditorResourceManager->getGameClient();
}

void CEditor::SetBackgroundColor(float red,float green,float blue)
{
    if (m_pEditorResourceManager) {
        Ogre::Viewport* viewport = m_pEditorResourceManager->getRenderWindow()->getViewport(0);
        if (viewport) viewport->setBackgroundColour(Ogre::ColourValue(red, green, blue));
    }
}

void CEditor::flushKeyManager()
{
    if (getGameClient()) getGameClient()->getKeyManager()->flushAll();
    if (m_pObjectManager) m_pObjectManager->flushKeyManager();
}

CEditorScene* CEditor::GetEditorScene(std::wstring name)
{
    return GetEditorScene(GetEditorSceneIDByName(name.c_str()));
}
