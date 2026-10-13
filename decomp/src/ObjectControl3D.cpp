#include <OgreRay.h>
#include <OgreCamera.h>
#include "UtilitiesMath.h"
#include "Settings.h"

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

Ogre::Quaternion CObjectControl3D::GetSelectionOrientation()
{
    return Ogre::Quaternion::IDENTITY;
}

#include <cmath>

void CObjectControl3D::ResetScale(TArrayList<CEditorBaseObject*>& objects)
{
    createUndo(objects);
    for (unsigned int i = 0; i < objects.size(); ++i) {
        CPositionableObject* object = dynamic_cast<CPositionableObject*>(objects[i]);
        if (object) {
            object->setScale(1.0f, 1.0f, 1.0f);
            CEditor::getSingleton()->getObjectManager()->markChanged();
        }
    }
    if (m_undo->m_undoData.size()) gEditor->addUndo(m_undo, true);
    else delete m_undo;
    m_undo = NULL;
}

void CObjectControl3D::ResetOrientation(TArrayList<CEditorBaseObject*>& objects)
{
    createUndo(objects);
    for (unsigned int i = 0; i < objects.size(); ++i) {
        CPositionableObject* object = dynamic_cast<CPositionableObject*>(objects[i]);
        if (object) {
            object->getSceneNode()->setOrientation(Ogre::Quaternion::IDENTITY);
            Ogre::Quaternion orientation(object->getSceneNode()->getOrientation());
            orientation.normalise();
            object->setOrientation(orientation);
            CEditor::getSingleton()->getObjectManager()->markChanged();
        }
    }
    if (m_undo->m_undoData.size()) gEditor->addUndo(m_undo, true);
    else delete m_undo;
    m_undo = NULL;
}

void CObjectControl3D::snapObjectsToGround(bool orient, TArrayList<CEditorBaseObject*>& objects)
{
    createUndo(objects);
    for (unsigned int i = 0; i < objects.size(); ++i) {
        CPositionableObject* object = dynamic_cast<CPositionableObject*>(objects[i]);
        if (object) {
            snapObjectToGround(object, orient);
            CEditor::getSingleton()->getObjectManager()->markChanged();
        }
    }
    if (m_undo->m_undoData.size()) gEditor->addUndo(m_undo, true);
    else delete m_undo;
    m_undo = NULL;
}

void CObjectControl3D::ApplyRotationNoise(float amount, TArrayList<CEditorBaseObject*>& objects)
{
    createUndo(objects);
    for (unsigned int i = 0; i < objects.size(); ++i) {
        CPositionableObject* object = dynamic_cast<CPositionableObject*>(objects[i]);
        if (object) {
            float angle = std::fabs(static_cast<float>(static_cast<double>(amount) * (static_cast<double>(Ogre::Math::PI) / 180.0)));
            float randomAngle = Ogre::Math::RangeRandom(-angle, angle);
            object->getSceneNode()->yaw(Ogre::Radian(randomAngle), Ogre::Node::TS_PARENT);
            Ogre::Quaternion orientation(object->getSceneNode()->getOrientation());
            orientation.normalise();
            object->setOrientation(orientation);
            CEditor::getSingleton()->getObjectManager()->markChanged();
        }
    }
    if (m_undo->m_undoData.size()) gEditor->addUndo(m_undo, true);
    else delete m_undo;
    m_undo = NULL;
}

void CObjectControl3D::ApplyNormalNoise(float amount, TArrayList<CEditorBaseObject*>& objects)
{
    createUndo(objects);
    for (unsigned int i = 0; i < objects.size(); ++i) {
        CPositionableObject* object = dynamic_cast<CPositionableObject*>(objects[i]);
        if (object) {
            float angle = std::fabs(static_cast<float>(static_cast<double>(amount) * (static_cast<double>(Ogre::Math::PI) / 180.0)));
            float randomAngle = Ogre::Math::RangeRandom(-angle, angle);
            object->getSceneNode()->roll(Ogre::Radian(randomAngle), Ogre::Node::TS_PARENT);
            randomAngle = Ogre::Math::RangeRandom(-angle, angle);
            object->getSceneNode()->pitch(Ogre::Radian(randomAngle), Ogre::Node::TS_PARENT);
            Ogre::Quaternion orientation(object->getSceneNode()->getOrientation());
            orientation.normalise();
            object->setOrientation(orientation);
            CEditor::getSingleton()->getObjectManager()->markChanged();
        }
    }
    if (m_undo->m_undoData.size()) gEditor->addUndo(m_undo, true);
    else delete m_undo;
    m_undo = NULL;
}

void CObjectControl3D::ApplyScaleNoise(float amount, bool uniform, TArrayList<CEditorBaseObject*>& objects)
{
    createUndo(objects);
    float magnitude = std::fabs(amount);
    float minimum = -magnitude;
    for (unsigned int i = 0; i < objects.size(); ++i) {
        CPositionableObject* object = dynamic_cast<CPositionableObject*>(objects[i]);
        if (!object) continue;
        float x, y, z;
        if (uniform) {
            float delta = Ogre::Math::RangeRandom(minimum, magnitude);
            x = object->getScaleX();
            y = object->getScaleY();
            z = object->getScaleZ();
            object->setScale(x + delta, delta + y, delta + z);
        } else {
            float low = minimum < 0.0f ? 0.0f : minimum;
            x = object->getScaleX();
            float dx = Ogre::Math::RangeRandom(low, magnitude);
            y = object->getScaleY();
            float dy = Ogre::Math::RangeRandom(low, magnitude);
            z = object->getScaleZ();
            float dz = Ogre::Math::RangeRandom(low, magnitude);
            object->setScale(x + dx, y + dy, z + dz);
        }
        CEditor::getSingleton()->getObjectManager()->markChanged();
    }
    if (m_undo->m_undoData.size()) gEditor->addUndo(m_undo, true);
    else delete m_undo;
    m_undo = NULL;
}

Ogre::Vector3 CObjectControl3D::getSelectedPivot(TArrayList<CEditorBaseObject*>& objects)
{
    Ogre::Vector3 result(0.0f, 0.0f, 0.0f);
    unsigned int count = 0;
    for (unsigned int i = 0; i < objects.size(); ++i) {
        CPositionableObject* object = dynamic_cast<CPositionableObject*>(objects[i]);
        if (!object) continue;
        ++count;
        result += object->getPosition(true);
    }
    if (count) result *= 1.0f / static_cast<float>(count);
    return result;
}

void CObjectControl3D::UpdateWorkingPlane()
{
    m_workingPlane = Ogre::Plane(Ogre::Vector3(0.0f, m_workingHeight, 0.0f),
        Ogre::Vector3(1.0f, m_workingHeight, 0.0f), Ogre::Vector3(0.0f, m_workingHeight, 1.0f));
    if (m_models.size() > 19) {
        m_models[8]->setVisible((gEditor->getFlags() & 512) != 0);
        Ogre::Vector3 position(getWorkingPlanePosition());
        m_models[8]->setPosition(position);
        float scale = m_planeScale < 1.0f ? 1.0f : m_planeScale;
        m_models[8]->setScale(scale, 0.001f, scale);
    }
}

void CObjectControl3D::UpdateChunkTemplate()
{
    if (m_models.size() <= 19) return;
    for (unsigned int i = 10; i < 20; ++i) m_models[i]->setVisible(false);
    if (m_chunkDepth == 0.0f) {
        m_models[9]->setVisible(false);
        return;
    }
    m_models[9]->setVisible(true);
    m_models[9]->setPosition(Ogre::Vector3(0.0f, 0.0f,
        m_chunkDepth * 0.5f + m_chunkSize * -0.5f));
    m_models[9]->setScale(m_chunkWidth, 0.001f, m_chunkDepth);
    for (int i = 0; i < m_chunkCount; ++i) {
        m_models[i + 10]->setVisible(true);
        Ogre::Vector3 position = m_chunkPositions[i];
        m_models[i + 10]->setPosition(position);
        m_models[i + 10]->setScale(m_chunkSize, 0.001f, m_chunkSize);
    }
}

Ogre::Vector3 CObjectControl3D::getMousePlaneInstersect(POINT point, Ogre::Plane plane)
{
    Ogre::Camera* camera = CEditor::getSingleton()->getCamera();
    if (!camera) return Ogre::Vector3::ZERO;
    m_mouseHandler->MousePosition();
    CSettings* settings = CEditor::getSingleton()->getSettings();
    int height = settings->GetInt(KSETTINGS_WIN_HEIGHT);
    int width = settings->GetInt(KSETTINGS_WIN_WIDTH);
    Ogre::Vector3 direction = MATH::screenToWorldRay(camera, static_cast<float>(point.x),
        static_cast<float>(point.y), static_cast<float>(width), static_cast<float>(height));
    Ogre::Ray ray(camera->getPosition(), direction);
    std::pair<bool, float> hit = ray.intersects(plane);
    return camera->getPosition() + direction * hit.second;
}

Ogre::Vector3 CObjectControl3D::getCameraPlaneIntersect(Ogre::Plane plane)
{
    Ogre::Camera* camera = CEditor::getSingleton()->getCamera();
    if (!camera) return Ogre::Vector3::ZERO;
    CSettings* settings = CEditor::getSingleton()->getSettings();
    int height = settings->GetInt(KSETTINGS_WIN_HEIGHT);
    int width = settings->GetInt(KSETTINGS_WIN_WIDTH);
    int centerHeight = settings->GetInt(KSETTINGS_WIN_HEIGHT);
    int centerWidth = settings->GetInt(KSETTINGS_WIN_WIDTH);
    Ogre::Vector3 direction = MATH::screenToWorldRay(camera, centerWidth * 0.5f,
        centerHeight * 0.5f, static_cast<float>(width), static_cast<float>(height));
    Ogre::Ray ray(camera->getPosition(), direction);
    std::pair<bool, float> hit = ray.intersects(plane);
    return camera->getPosition() + direction * hit.second;
}
