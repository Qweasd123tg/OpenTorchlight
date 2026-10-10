#include <OgreSceneNode.h>
#include <algorithm>
#include "Editor.h"
#include "EditorObjectManager.h"
#include "GenericModel.h"
#include "MouseHandler.h"
#include "ObjectControl3D.h"
#include "OgreUtilities.h"
#include "Undo.h"

void CObjectControl3D::doCameraMovement(float)
{
}

int CObjectControl3D::getManipulationType()
{
    if (CEditor::getSingleton()->getFlags() & 8) return 0;
    if (CEditor::getSingleton()->getFlags() & 16) return 1;
    if (CEditor::getSingleton()->getFlags() & 32) return 2;
    if (CEditor::getSingleton()->getFlags() & 64) return 3;
    return 0;
}

void CObjectControl3D::flushKeyManager()
{
    m_keys.flushAll();
}

void CObjectControl3D::mouseEvent(unsigned int event, unsigned int value)
{
    m_mouse.mouseEvent(event, value);
}

void CObjectControl3D::keyEvent(unsigned int event, unsigned int value)
{
    m_keys.keyEvent(event, value);
}

void CObjectControl3D::configureSceneManager(CPositionableObject* object)
{
    if (!object || m_sceneManager)
        return;
    if (object->getSceneNode())
    {
        m_sceneManager = object->getSceneNode()->getCreator();
        if (m_sceneManager)
        {
            m_boxModel = new CGenericModel(m_resources, NULL, OGRE_UTILITIES::PRIMITIVE_BOX);
            m_boxModel->setQueryMask(OGRE_UTILITIES::QUERY_MASK_DEFAULT);
            m_boxModel->setVisible(true);
            m_boxModel->setWireframe(true);
            m_boxModel->setScale(0.001f, 0.001f, 0.001f);
        }
    }
}

CObjectControl3D::~CObjectControl3D()
{
    if (m_undo)
    {
        delete m_undo;
        m_undo = NULL;
    }
    for (unsigned int i = 0; i < m_models.size(); ++i)
    {
        if (m_models[i])
        {
            delete m_models[i];
            m_models[i] = NULL;
        }
    }
    OGRE_UTILITIES::removeChildFromParentNode(m_controlsNode);
    if (m_boxModel)
    {
        delete m_boxModel;
        m_boxModel = NULL;
    }
    m_sceneManager = NULL;
    if (m_mouseHandler)
    {
        delete m_mouseHandler;
        m_mouseHandler = NULL;
    }
}
