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

#include <cmath>
Ogre::Vector3 CObjectControl3D::getWorkingPlanePosition()
{
    if (m_models.size()<20) return Ogre::Vector3::ZERO;
    Ogre::Vector3 position=getCameraPlaneIntersect(m_workingPlane);
    if (static_cast<float>(fmod(position.x,m_planeScale))>m_planeScale*0.5f)
        position.x+=m_planeScale-static_cast<float>(fmod(position.x,m_planeScale));
    else position.x-=static_cast<float>(fmod(position.x,m_planeScale));
    if (static_cast<float>(fmod(position.z,m_planeScale))>m_planeScale*0.5f)
        position.z+=m_planeScale-static_cast<float>(fmod(position.z,m_planeScale));
    else position.z-=static_cast<float>(fmod(position.z,m_planeScale));
    return position;
}

#include "PositionableObject.h"
void CObjectControl3D::resnapObjects(TArrayList<CEditorBaseObject*>& objects,bool resetOrientation)
{
    for (unsigned int i=0;i<objects.size();++i) {
        CPositionableObject* object=dynamic_cast<CPositionableObject*>(objects[i]);
        if (!object) continue;
        Ogre::Vector3 position=object->getPosition(false);
        float remainder=static_cast<float>(std::fmod(static_cast<double>(position.x),static_cast<double>(m_planeScale)));
        if (remainder>m_planeScale*0.5f) position.x+=m_planeScale-remainder;
        else position.x-=remainder;
        remainder=static_cast<float>(std::fmod(static_cast<double>(position.y),static_cast<double>(m_positionVerticalSnap)));
        if (remainder>m_positionVerticalSnap*0.5f) position.y+=m_positionVerticalSnap-remainder;
        else position.y-=remainder;
        remainder=static_cast<float>(std::fmod(static_cast<double>(position.z),static_cast<double>(m_planeScale)));
        if (remainder>m_planeScale*0.5f) position.z+=m_planeScale-remainder;
        else position.z-=remainder;
        object->setPosition(position);
        if (resetOrientation) object->setOrientation(Ogre::Quaternion::IDENTITY);
    }
    CEditor::getSingleton()->getObjectManager()->markChanged();
}

#include "PositionableObject.h"
Ogre::Vector3 CObjectControl3D::getGroupRotationPoint(TArrayList<CEditorBaseObject*>& objects)
{
    Ogre::Vector3 point=m_selectedPivot;
    float nearest=10000.0f;
    for (unsigned int i=0;i<objects.size();++i) {
        CPositionableObject* object=dynamic_cast<CPositionableObject*>(objects[i]);
        if (!object) continue;
        Ogre::Vector3 position=object->getPosition(true);
        float distance=(position-m_selectedPivot).squaredLength();
        if (distance<nearest) {
            nearest=distance;
            point=position;
        }
    }
    float remainder=std::fmod(point.x,m_planeScale);
    if (remainder>=m_planeScale*0.5f) point.x+=m_planeScale-remainder;
    else point.x-=remainder;
    remainder=std::fmod(point.z,m_planeScale);
    if (remainder>m_planeScale*0.5f) point.z+=m_planeScale-remainder;
    else point.z-=remainder;
    return point;
}

#include "Descriptor.h"
void CObjectControl3D::createUndo(TArrayList<CEditorBaseObject*>& objects)
{
    if (m_undo) return;
    m_undo=new CUndo;
    for (unsigned int i=0;i<objects.size();++i) {
        if (!objects[i]) continue;
        if (objects[i]->getDescriptor()->HasProperty(L"FORWARD")) m_undo->AddUndoProperty(objects[i],L"FORWARD");
        if (objects[i]->getDescriptor()->HasProperty(L"RIGHT")) m_undo->AddUndoProperty(objects[i],L"RIGHT");
        if (objects[i]->getDescriptor()->HasProperty(L"UP")) m_undo->AddUndoProperty(objects[i],L"UP");
        if (objects[i]->getDescriptor()->HasProperty(L"POSITION")) m_undo->AddUndoProperty(objects[i],L"POSITION");
        if (objects[i]->getDescriptor()->HasProperty(L"SCALE X")) m_undo->AddUndoProperty(objects[i],L"SCALE X");
        if (objects[i]->getDescriptor()->HasProperty(L"SCALE Y")) m_undo->AddUndoProperty(objects[i],L"SCALE Y");
        if (objects[i]->getDescriptor()->HasProperty(L"SCALE Z")) m_undo->AddUndoProperty(objects[i],L"SCALE Z");
    }
}

#include <cstring>
#include "ResourceManager.h"
#include "iEditorResourceManager.h"
#include <OgreEntity.h>
#include <OgreSceneManager.h>
CObjectControl3D::CObjectControl3D(CResourceManager* resources)
    : m_editorEnabled(false),m_mouseHandler(NULL),m_boxModel(NULL),m_sceneManager(NULL),m_resources(resources),
      m_boxSelecting(false),m_flag58(false),m_flag59(false),m_previousLeftDown(false),m_flag5b(false),m_dragPivot(0.f,0.f,0.f),m_dragType(7),m_dragDirection(0.f,0.f,0.f),
      m_dragPlane(),m_selectedPivot(0.f,0.f,0.f),m_controlOffset(0.f,0.f,0.f),m_models(),m_viewDelta(0.f,0.f,0.f),
      m_planeScale(.001f),m_positionVerticalSnap(.001f),m_orientationSnap(.001f),m_chunkSize(4.f),m_chunkWidth(0.f),m_chunkDepth(0.f),
      m_chunkCount(0),m_snapToGroundBias(0.f),m_workingHeight(0.f),m_workingPlane(),m_keys(),m_mouse(),m_undo(NULL),m_controlsNode(NULL)
{
    m_previousMouse.x=0;m_previousMouse.y=0;
    m_dragMouse.x=0;m_dragMouse.y=0;
    m_mouseHandler=new CMouseHandler(CEditor::getSingleton()->getEditorResourceManager()->getWindowHandle());
    m_dragPlane=Ogre::Plane(Ogre::Vector3(0.f,0.f,0.f),Ogre::Vector3(1.f,0.f,0.f),Ogre::Vector3(0.f,1.f,0.f));
    m_controlsNode=gEditor->getResourceManager()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
    m_controlsNode->setPosition(0.f,0.f,0.f);
    InitControls();
}

void CObjectControl3D::showControls(bool show)
{
    for(unsigned int i=0;i<m_models.size();++i){
        if(i<6)m_models[i]->getEntity()->setQueryFlags(show?gEditor->m_iUnknown68:1);
        if(i<7)m_models[i]->setVisible(show);
    }
    if(show){
        Ogre::Camera*camera=CEditor::getSingleton()->getCamera();
        float distance=camera?(camera->getPosition()-m_selectedPivot).length():1.f;
        m_controlsNode->getScale();
        m_controlsNode->setPosition(m_selectedPivot);
        m_controlsNode->setScale(distance/25.f,distance/25.f,distance/25.f);
    }
    if(m_boxSelecting){
        Ogre::Vector3 end=getMousePlaneInstersect(m_mouseHandler->MousePosition(),Ogre::Plane(Ogre::Vector3::ZERO,Ogre::Vector3::UNIT_Z,Ogre::Vector3::UNIT_X));
        m_models[7]->setVisible(true);
        m_models[7]->setPosition((m_boxStart+end)*.5f);
        m_models[7]->setScale(m_boxStart.x-end.x,0.f,m_boxStart.z-end.z);
    }else m_models[7]->setVisible(false);
}

void CObjectControl3D::updateBoundingBox(TArrayList<CEditorBaseObject*>& objects)
{
    m_selectedPivot=getSelectedPivot(objects);
    m_selectionCount=0;
    bool first=true;
    int extent=1;
    Ogre::Vector3 minimum(0.f,0.f,0.f),maximum(0.f,0.f,0.f);
    for(unsigned int i=0;i<objects.size();++i){
        CPositionableObject*object=dynamic_cast<CPositionableObject*>(objects[i]);
        if(!object||!object->getSceneNode())continue;
        if(!m_sceneManager)configureSceneManager(object);
        if(!m_sceneManager)continue;
        const Ogre::AxisAlignedBox&box=object->getSceneNode()->_getWorldAABB();
        if(extent!=1)continue;
        ++m_selectionCount;
        if(first){
            first=false;
            if(box.isNull()){extent=0;continue;}
            if(box.isInfinite()){extent=2;continue;}
            minimum=box.getMinimum();maximum=box.getMaximum();
        }else{
            if(box.isNull())continue;
            if(box.isInfinite()){extent=2;continue;}
            minimum.makeFloor(box.getMinimum());maximum.makeCeil(box.getMaximum());
        }
    }
    if(m_selectionCount&&extent==1&&m_boxModel){
        m_boxModel->setPosition((minimum+maximum)*.5f);
        m_boxModel->setScale(maximum.x-minimum.x,maximum.y-minimum.y,maximum.z-minimum.z);
    }
}

#include "Descriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"

void CObjectControl3D::cloneObjectsIfNeedBe(TArrayList<CEditorBaseObject*>& objects)
{
    if ((m_dragType < 1 || m_dragType > 6) && GetAsyncKeyState(16) >= 0) return;
    if (GetAsyncKeyState(16) >= 0) return;
    if ((!m_previousLeftDown && m_mouseHandler->MouseLeftButtonDown()) ||
        m_keys.keyPressed(37) || m_keys.keyPressed(39) ||
        m_keys.keyPressed(38) || m_keys.keyPressed(40)) {
        CEditorObjectManager* manager = CEditor::getSingleton()->getObjectManager();
        unsigned int count = objects.size();
        if (m_undo) { delete m_undo; m_undo = NULL; }
        m_undo = new CUndo;
        TArrayList<CEditorBaseObject*> clones(10);
        for (unsigned int i = 0; i < count; ++i) {
            if (!(objects[i]->getDescriptor()->m_iFlags & 8)) continue;
            CEditorBaseObject* clone = objects[i]->getSceneOwner()->CreateObjectByDescriptor(
                objects[i]->getDescriptor(), objects[i], NULL, true);
            if (clone) {
                m_undo->AddNewObject(clone);
                manager->EditorObjectCreated(clone);
                clones.add(clone);
                manager->EditorObjectDeselected(objects[i]);
            }
        }
        if (m_undo->m_undoData.size()) gEditor->addUndo(m_undo, true);
        else delete m_undo;
        m_undo = NULL;
        for (unsigned int i = 0; i < clones.size(); ++i)
            manager->EditorObjectSelected(clones[i]);
    }
}
#include <OgreEntity.h>

int CObjectControl3D::configureDragType()
{
    if (m_models.empty() || !m_models[0]->getEntity() || !m_models[0]->getVisible()) return 0;
    Ogre::Camera* camera=CEditor::getSingleton()->getCamera();
    if(!camera)return 0;
    POINT point=m_mouseHandler->MousePosition();
    CSettings* settings=CEditor::getSingleton()->getSettings();
    int height=settings->GetInt(KSETTINGS_WIN_HEIGHT);
    int width=settings->GetInt(KSETTINGS_WIN_WIDTH);
    Ogre::Vector3 direction=MATH::screenToWorldRay(camera,float(point.x),float(point.y),float(width),float(height));
    Ogre::Ray ray(camera->getPosition(),direction);
    m_dragDirection=Ogre::Vector3::ZERO;
    m_controlOffset=Ogre::Vector3::ZERO;
    int closest=-1;
    float distance=10000.f;
    for(int i=0;i<int(m_models.size())-1;++i){
        if(i>5)continue;
        std::pair<bool,float> hit=Ogre::Math::intersects(ray,m_models[i]->getEntity()->getWorldBoundingBox(false));
        if(hit.first && hit.second<distance){distance=hit.second;closest=i;}
    }
    if(closest>=0 && closest<=5){
        int type;
        switch(closest){
        case 0:m_dragPlane=Ogre::Plane(m_dragPivot,m_dragPivot+Ogre::Vector3(1,0,0),m_dragPivot+Ogre::Vector3(0,1,0));type=4;break;
        case 1:m_dragPlane=Ogre::Plane(m_dragPivot,m_dragPivot+Ogre::Vector3(1,0,0),m_dragPivot+Ogre::Vector3(0,0,1));type=5;break;
        case 2:m_dragPlane=Ogre::Plane(m_dragPivot,m_dragPivot+Ogre::Vector3(0,1,0),m_dragPivot+Ogre::Vector3(0,0,1));type=6;break;
        case 3:m_dragPlane=Ogre::Plane(m_dragPivot,m_dragPivot+Ogre::Vector3(1,0,0),m_dragPivot+Ogre::Vector3(0,0,1));type=1;break;
        case 4:m_dragPlane=Ogre::Plane(m_dragPivot,m_dragPivot+Ogre::Vector3(0,1,0),m_dragPivot+Ogre::Vector3(0,0,1));type=2;break;
        default:m_dragPlane=Ogre::Plane(m_dragPivot,m_dragPivot+Ogre::Vector3(1,0,0),m_dragPivot+Ogre::Vector3(0,0,1));type=3;break;
        }
        float intersection=Ogre::Math::intersects(ray,m_dragPlane).second;
        m_controlOffset=camera->getPosition()+direction*intersection;
        m_dragDirection=m_controlOffset-m_selectedPivot;
        return type;
    }
    m_dragPlane=Ogre::Plane();
    m_dragDirection=Ogre::Vector3::ZERO;
    m_controlOffset=Ogre::Vector3::ZERO;
    return 0;
}

void CObjectControl3D::update(float elapsed,TArrayList<CEditorBaseObject*>& objects,bool)
{
    m_selectedPivot=getSelectedPivot(objects);
    bool focused=CEditor::getSingleton()->m_bRenderWindowHasFocus;
    m_mouse.capture();
    m_keys.capture();
    if(focused && objects.size() && !m_undo &&
       (m_mouseHandler->MouseLeftButtonDown() || m_keys.keyPressed(37) ||
        m_keys.keyPressed(39) || m_keys.keyPressed(38) || m_keys.keyPressed(40)))
        createUndo(objects);
    if(m_undo && (!focused || !m_mouseHandler->MouseLeftButtonDown())){
        if(m_undo->m_undoData.size())gEditor->addUndo(m_undo,true);
        else delete m_undo;
        m_undo=NULL;
    }
    m_mouseHandler->MouseCenterButtonDown();
    bool show=false;
    if(objects.size() && m_editorEnabled){
        updateBoundingBox(objects);
        if(m_selectionCount){
            show=true;
            if(focused && !(gEditor->getFlags()&2)){
                cloneObjectsIfNeedBe(objects);
                manipulateSelectedItems(elapsed,objects);
            }
        }
    }
    if(m_boxModel){m_boxModel->setVisible(show);showControls(show);}
    m_previousLeftDown=m_mouseHandler->MouseLeftButtonDown();
}

#include "iEditorResourceManager.h"
#include "iCollision.h"
#include "CollisionModel.h"
#include "CollisionList.h"
#include "PositionableObject.h"
#include <OgreEntity.h>

void CObjectControl3D::snapObjectToGround(CPositionableObject* object,bool orient)
{
    iEditorResourceManager* resources=CEditor::getSingleton()->getEditorResourceManager();
    if(!object || !resources || !resources->getSceneManager())return;
    Ogre::Ray ray(object->getPosition(false),Ogre::Vector3(0,-1,0));
    CEditorObjectManager* manager=CEditor::getSingleton()->getObjectManager();
    CEditor::getSingleton();
    CPositionableObject* closest=NULL;
    float distance=10000.f,height=0.f;
    Ogre::Vector3 normal=Ogre::Vector3::ZERO;
    CEditorObjectManager::ObjectMap& objects=*manager->getObjects();
    for(CEditorObjectManager::ObjectMap::iterator i=objects.begin();i!=objects.end();++i){
        if(!i->second)continue;
        CPositionableObject* candidate=dynamic_cast<CPositionableObject*>(i->second);
        if(!candidate)continue;
        if(candidate->getEntity()){
            candidate->getEntity()->getQueryFlags();
            if(candidate==object || !candidate->getVisible())continue;
        }
        Ogre::AxisAlignedBox box=candidate->getSceneNode()->_getWorldAABB();
        if(!Ogre::Math::intersects(ray,box).first)continue;
        iCollision* collision=dynamic_cast<iCollision*>(candidate);
        if(!collision)continue;
        Ogre::Matrix4 inverse=candidate->getOrientation().inverse();
        Ogre::Vector3 start=inverse*(ray.getOrigin()-candidate->getPosition(false));
        Ogre::Vector3 end=inverse*(ray.getOrigin()+ray.getDirection()*distance-candidate->getPosition(false));
        Ogre::Vector3 hit=Ogre::Vector3::ZERO,hitNormal=Ogre::Vector3::ZERO;
        float hitDistance=0.f;
        if(collision->getCollisionMesh()->getCollisionList()->rayCollision(start,end,hit,hitNormal,hitDistance) && hitDistance<distance){
            closest=candidate;height=candidate->getPosition(false).y+hit.y;normal=hitNormal;distance=hitDistance;
        }
    }
    if(!closest)return;
    object->setY(height+m_snapToGroundBias);
    if(orient){
        Ogre::Vector3 right=normal.crossProduct(object->getForward());
        Ogre::Vector3 forward=right.crossProduct(normal);
        Ogre::Quaternion orientation;
        orientation.FromAxes(right,normal,forward);
        object->setOrientation(orientation);
    }
}

CEditorBaseObject* CObjectControl3D::getObjectUnderMouse()
{
    Ogre::Camera* camera=CEditor::getSingleton()->getCamera();
    iEditorResourceManager* resources=CEditor::getSingleton()->getEditorResourceManager();
    if(!camera || !resources || !resources->getSceneManager())return NULL;
    POINT point=m_mouseHandler->MousePosition();
    CSettings* settings=CEditor::getSingleton()->getSettings();
    int height=settings->GetInt(KSETTINGS_WIN_HEIGHT);
    int width=settings->GetInt(KSETTINGS_WIN_WIDTH);
    Ogre::Vector3 direction=MATH::screenToWorldRay(camera,float(point.x),float(point.y),float(width),float(height));
    Ogre::Ray ray(camera->getPosition(),direction);
    CEditorObjectManager* manager=CEditor::getSingleton()->getObjectManager();
    CEditor::getSingleton();
    CPositionableObject* closest=NULL;
    float distance=10000.f;
    CEditorObjectManager::ObjectMap& objects=*manager->getObjects();
    for(CEditorObjectManager::ObjectMap::iterator i=objects.begin();i!=objects.end();++i){
        if(!i->second)continue;
        CPositionableObject* candidate=dynamic_cast<CPositionableObject*>(i->second);
        if(!candidate)continue;
        if(candidate->getEntity()){
            if(!(candidate->getEntity()->getQueryFlags()&gEditor->m_iUnknown68) || !candidate->getVisible())continue;
        }
        Ogre::AxisAlignedBox box=candidate->getSceneNode()->_getWorldAABB();
        if(!Ogre::Math::intersects(ray,box).first)continue;
        iCollision* collision=dynamic_cast<iCollision*>(candidate);
        if(!collision)continue;
        Ogre::Matrix4 inverse=candidate->getOrientation().inverse();
        Ogre::Vector3 start=inverse*(ray.getOrigin()-candidate->getPosition(false));
        Ogre::Vector3 end=inverse*(ray.getOrigin()+ray.getDirection()*distance-candidate->getPosition(false));
        Ogre::Vector3 hit=Ogre::Vector3::ZERO,normal=Ogre::Vector3::ZERO;
        float hitDistance=0.f;
        if(!collision->getCollisionMesh()->getCollisionList())continue;
        if(collision->getCollisionMesh()->getCollisionList()->rayCollision(start,end,hit,normal,hitDistance) && hitDistance<distance){
            distance=hitDistance;closest=candidate;
        }
    }
    return closest;
}
#include <OgreSceneManager.h>
#include <OgreSceneQuery.h>

#include "iEditorResourceManager.h"
#include "iCollision.h"
#include "CollisionModel.h"
#include "CollisionList.h"
#include "PositionableObject.h"
#include <OgreEntity.h>

void CObjectControl3D::doObjectPick()
{
    Ogre::Camera* camera=CEditor::getSingleton()->getCamera();
    iEditorResourceManager* resources=CEditor::getSingleton()->getEditorResourceManager();
    if(!camera || !resources || !resources->getSceneManager())return;
    POINT point=m_mouseHandler->MousePosition();
    CSettings* settings=CEditor::getSingleton()->getSettings();
    int height=settings->GetInt(KSETTINGS_WIN_HEIGHT);
    int width=settings->GetInt(KSETTINGS_WIN_WIDTH);
    Ogre::Vector3 direction=MATH::screenToWorldRay(camera,float(point.x),float(point.y),float(width),float(height));
    Ogre::Ray ray(camera->getPosition(),direction);
    CEditorObjectManager* manager=CEditor::getSingleton()->getObjectManager();
    CEditor::getSingleton();
    CPositionableObject* closest=NULL;
    float distance=10000.f;
    CEditorObjectManager::ObjectMap& objects=*manager->getObjects();
    for(CEditorObjectManager::ObjectMap::iterator i=objects.begin();i!=objects.end();++i){
        if(!i->second)continue;
        CPositionableObject* candidate=dynamic_cast<CPositionableObject*>(i->second);
        if(!candidate)continue;
        if(candidate->getEntity()){
            if(!(candidate->getEntity()->getQueryFlags()&gEditor->m_iUnknown68) || !candidate->getVisible())continue;
        }
        Ogre::AxisAlignedBox box=candidate->getSceneNode()->_getWorldAABB();
        if(!Ogre::Math::intersects(ray,box).first)continue;
        iCollision* collision=dynamic_cast<iCollision*>(candidate);
        if(!collision)continue;
        Ogre::Matrix4 inverse=candidate->getOrientation().inverse();
        Ogre::Vector3 start=inverse*(ray.getOrigin()-candidate->getPosition(false));
        Ogre::Vector3 end=inverse*(ray.getOrigin()+ray.getDirection()*distance-candidate->getPosition(false));
        Ogre::Vector3 hit=Ogre::Vector3::ZERO,normal=Ogre::Vector3::ZERO;
        float hitDistance=0.f;
        if(collision->getCollisionMesh()->getCollisionList()->rayCollision(start,end,hit,normal,hitDistance) && hitDistance<distance){
            distance=hitDistance;closest=candidate;
        }
    }
    unsigned int mask=gEditor->m_iUnknown68&~0x30u;
    if(mask){
        Ogre::RaySceneQuery* query=resources->getSceneManager()->createRayQuery(
            Ogre::Ray(camera->getPosition(),direction),Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK);
        query->setSortByDistance(true,1);
        query->setQueryMask(mask);
        query->execute();
        Ogre::RaySceneQueryResult result=query->getLastResults();
        if(!result.empty() && result[0].distance<distance && result[0].movable){
            for(CEditorObjectManager::ObjectMap::iterator i=objects.begin();i!=objects.end();++i){
                if(!i->second)continue;
                CPositionableObject* candidate=dynamic_cast<CPositionableObject*>(i->second);
                if(candidate && candidate->getEntity()==result[0].movable)closest=candidate;
            }
        }
        resources->getSceneManager()->destroyQuery(query);
    }
    if(closest){
        if(GetAsyncKeyState(17)>=0)manager->ClearSelectedObjects();
        if(manager->getSelectedObjects()->find(closest)==-1)manager->EditorObjectSelected(closest);
        else manager->EditorObjectDeselected(closest);
    }else if(GetAsyncKeyState(17)>=0)manager->ClearSelectedObjects();
}

#include "iEditorResourceManager.h"
#include <OgreEntity.h>
#include <OgreSceneManager.h>

void CObjectControl3D::InitControls()
{
    for(unsigned int i=0;i<20;++i){
        m_models.push_back(new CGenericModel(m_resources,NULL,L"",L"",false));
        m_models[i]->setVisible(false);
    }
    for(unsigned int i=0;i<6;++i){
        m_models[i]->loadPrefabType(i<3?OGRE_UTILITIES::PRIMITIVE_BOX:OGRE_UTILITIES::PRIMITIVE_ARROW);
        m_models[i]->setDirection(i==3?Ogre::Vector3(1,0,0):i==4?Ogre::Vector3(0,1,0):Ogre::Vector3(0,0,1));
        const char* material=i==0?"ControlBlue":i==1?"ControlGreen":i==2?"ControlRed":"ControlWhite";
        m_models[i]->getEntity()->setMaterialName(material);
        m_models[i]->getEntity()->setCastShadows(false);
        m_models[i==1?0:i]->getEntity()->setRenderQueueGroup(90);
        m_models[i]->sceneNodeSetParent(m_controlsNode,false);
    }
    m_models[8]->loadPrefabType(OGRE_UTILITIES::PRIMITIVE_BOX);
    m_models[8]->setDirection(Ogre::Vector3(0,0,1));
    m_models[8]->getEntity()->setMaterialName("ControlBlue");
    m_models[8]->getEntity()->setCastShadows(false);
    m_models[8]->getEntity()->setRenderQueueGroup(90);
    m_models[8]->setVisible(true);
    m_models[8]->getEntity()->setQueryFlags(1);
    m_models[6]->loadModel(L"media/models/crosshair/crosshair.mesh",L"",false,false,false);
    m_models[6]->getEntity()->setMaterialName("WireFrame");
    m_models[6]->getEntity()->setCastShadows(false);
    m_models[6]->getEntity()->setRenderQueueGroup(90);
    m_models[6]->getEntity()->setQueryFlags(1);
    m_models[6]->sceneNodeSetParent(m_controlsNode,false);
    m_models[7]->loadPrefabType(OGRE_UTILITIES::PRIMITIVE_BOX);
    m_models[7]->setDirection(Ogre::Vector3(0,0,1));
    m_models[7]->getEntity()->setMaterialName("ControlPurple");
    m_models[7]->getEntity()->setCastShadows(false);
    m_models[7]->getEntity()->setRenderQueueGroup(90);
    m_models[9]->loadPrefabType(OGRE_UTILITIES::PRIMITIVE_BOX);
    m_models[9]->setDirection(Ogre::Vector3(0,0,1));
    m_models[9]->getEntity()->setMaterialName("WireframeYellow");
    m_models[9]->getEntity()->setCastShadows(false);
    m_models[9]->getEntity()->setRenderQueueGroup(90);
    m_models[9]->setVisible(true);
    m_models[9]->getEntity()->setQueryFlags(1);
    for(unsigned int i=10;i<20;++i){
        m_models[i]->loadPrefabType(OGRE_UTILITIES::PRIMITIVE_BOX);
        m_models[i]->setDirection(Ogre::Vector3(0,0,1));
        m_models[i]->getEntity()->setMaterialName("WireframeBlue");
        m_models[i]->getEntity()->setCastShadows(false);
        m_models[i]->setVisible(true);
        m_models[i]->getEntity()->setRenderQueueGroup(90);
        m_models[i]->getEntity()->setQueryFlags(1);
    }
    m_models[8]->setScale(4.f,0.f,4.f);
    UpdateWorkingPlane();
    Ogre::Camera* camera=CEditor::getSingleton()->getCamera();
    if(camera)(camera->getPosition()-m_selectedPivot).length();
    Ogre::Vector3 origin=Ogre::Vector3::ZERO;
    m_models[0]->setScale(.75f,.75f,.001f);
    float firstRadius=m_models[0]->getEntity()->getBoundingRadius();
    float secondRadius=m_models[0]->getEntity()->getBoundingRadius();
    m_models[0]->setPosition(origin.x+secondRadius/1.8f,origin.y+firstRadius/1.8f,origin.z);
    m_models[1]->setScale(.75f,.001f,.75f);
    firstRadius=m_models[1]->getEntity()->getBoundingRadius();
    secondRadius=m_models[1]->getEntity()->getBoundingRadius();
    m_models[1]->setPosition(origin.x+secondRadius/1.8f,origin.y,origin.z+firstRadius/1.8f);
    m_models[2]->setScale(.001f,.75f,.75f);
    firstRadius=m_models[2]->getEntity()->getBoundingRadius();
    secondRadius=m_models[2]->getEntity()->getBoundingRadius();
    m_models[2]->setPosition(origin.x,origin.y+secondRadius/1.8f,origin.z+firstRadius/1.8f);
    for(unsigned int i=3;i<6;++i){m_models[i]->setScale(.75f,.75f,.75f);m_models[i]->setPosition(origin.x,origin.y,origin.z);}
    m_models[6]->setPosition(origin.x,origin.y,origin.z);
    OGRE_UTILITIES::addChildSceneNode(gEditor->getEditorResourceManager()->getSceneManager()->getRootSceneNode(),m_controlsNode);
    showControls(false);
}

#include <OgreEntity.h>
#include <OgreMaterialManager.h>
#include <OgreTechnique.h>
#include <OgrePass.h>
#include "iEditorResourceManager.h"

void CObjectControl3D::updateControls(float)
{
    if (gEditor->getFlags() & 2) return;
    bool visible = getManipulationType() != 3;
    m_controlsNode->setVisible(visible, true);
    Ogre::Camera* camera = CEditor::getSingleton()->getCamera();
    float scale = (camera ? (camera->getPosition() - m_selectedPivot).length() : 1.f) * 20.f;
    const Ogre::Vector3& previousScale = m_controlsNode->getScale();
    // Original frame update adds the distance and swaps the previous Y/Z scale.
    m_controlsNode->setScale(previousScale.x + scale, previousScale.z + scale, previousScale.y + scale);
    Ogre::MaterialPtr yellow = Ogre::MaterialManager::getSingleton().getByName("WireframeYellow");
    Ogre::MaterialPtr blue = Ogre::MaterialManager::getSingleton().getByName("WireframeBlue");
    Ogre::MaterialPtr orange = Ogre::MaterialManager::getSingleton().getByName("ControlOrange");
    if (gEditor->getFlags() & 128)
    {
        if (!yellow.isNull())
        {
            yellow->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
            Ogre::Pass* pass = yellow->getTechnique(0)->getPass(0);
            pass->setSelfIllumination(1, 1, 0);
            pass->setDiffuse(Ogre::ColourValue(1, 1, .2f, .3f));
            pass->setAmbient(Ogre::ColourValue(1, 1, .2f, .3f));
        }
        if (!blue.isNull())
        {
            blue->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
            Ogre::Pass* pass = blue->getTechnique(0)->getPass(0);
            pass->setSelfIllumination(0, 0, 1);
            pass->setDiffuse(Ogre::ColourValue(.2f, .2f, 1, .3f));
            pass->setAmbient(Ogre::ColourValue(.2f, .2f, 1, .3f));
        }
        if (!orange.isNull())
        {
            orange->setSceneBlending(Ogre::SBT_TRANSPARENT_COLOUR);
            Ogre::Pass* pass = orange->getTechnique(0)->getPass(0);
            pass->setSelfIllumination(.8f, .4f, .2f);
            pass->setAmbient(Ogre::ColourValue(0, 0, 0, 1));
            pass->setDiffuse(Ogre::ColourValue(0, 0, 0, 1));
        }
    }
    else
    {
        Ogre::MaterialPtr materials[3] = {yellow, blue, orange};
        for (unsigned int i = 0; i < 3; ++i)
        {
            if (materials[i].isNull()) continue;
            materials[i]->setSceneBlending(Ogre::SBT_MODULATE);
            materials[i]->setSceneBlending(Ogre::SBF_ONE, Ogre::SBF_ONE);
            Ogre::Pass* pass = materials[i]->getTechnique(0)->getPass(0);
            pass->setDiffuse(Ogre::ColourValue(0, 0, 0, 0));
            pass->setAmbient(Ogre::ColourValue(0, 0, 0, 0));
            pass->setSelfIllumination(Ogre::ColourValue(0, 0, 0, 0));
        }
    }
    m_viewDelta = Ogre::Vector3::ZERO;
    if (!m_mouseHandler) return;
    if (m_mouseHandler->MouseLeftButtonDown() || m_mouseHandler->MouseRightButtonDown())
    {
        bool wasLeft = m_flag58;
        bool wasRight = m_flag59;
        m_flag58 = (m_mouseHandler->MouseLeftButtonDown() & m_mouseHandler->MouseIsInWindow()) != 0;
        m_flag59 = (m_mouseHandler->MouseRightButtonDown() & m_mouseHandler->MouseIsInWindow()) != 0;
        if (!wasLeft && m_flag58)
        {
            m_dragType = configureDragType();
            m_dragMouse = m_mouseHandler->MousePosition();
            m_dragPivot = m_selectedPivot;
        }
        if (!wasRight && m_flag59 && GetAsyncKeyState(16) < 0)
        {
            m_boxSelecting = true;
            m_boxStart = getMousePlaneInstersect(m_mouseHandler->MousePosition(),
                Ogre::Plane(Ogre::Vector3::ZERO, Ogre::Vector3::UNIT_X, Ogre::Vector3::UNIT_Z));
        }
    }
    else if (m_flag58 || !m_mouseHandler->MouseIsInWindow())
    {
        if (gEditor->m_bRenderWindowHasFocus && m_flag58 && m_mouseHandler->MouseIsInWindow() && m_dragType == 0)
            doObjectPick();
        m_controlOffset = Ogre::Vector3::ZERO;
        m_dragType = 0;
        m_flag58 = false;
    }
    else if (m_flag59 || !m_mouseHandler->MouseIsInWindow())
    {
        if (m_boxSelecting)
        {
            gEditor->m_pObjectManager->ClearSelectedObjects();
            m_boxEnd = getMousePlaneInstersect(m_mouseHandler->MousePosition(),
                Ogre::Plane(Ogre::Vector3::ZERO, Ogre::Vector3::UNIT_X, Ogre::Vector3::UNIT_Z));
            CEditorObjectManager::ObjectMap* objects = gEditor->m_pObjectManager->getObjects();
            CEditorObjectManager::ObjectMap::iterator it = objects->begin();
            if (m_models.size() <= 19)
            {
                m_boxSelecting = false;
                return;
            }
            const Ogre::AxisAlignedBox& box = m_models[7]->getSceneNode()->_getWorldAABB();
            Ogre::AxisAlignedBox selection;
            if (box.isInfinite()) selection.setInfinite();
            else if (!box.isNull()) selection.setExtents(box.getMinimum().x, -10000.f, box.getMinimum().z,
                box.getMaximum().x, 10000.f, box.getMaximum().z);
            unsigned int mask = gEditor->m_iUnknown68;
            for (; it != objects->end(); ++it)
            {
                if (!it->second) continue;
                CPositionableObject* object = dynamic_cast<CPositionableObject*>(it->second);
                if (!object || !selection.intersects(object->getSceneNode()->_getWorldAABB())) continue;
                Ogre::Entity* entity = object->getEntity();
                if (entity && (entity->getQueryFlags() & mask) == entity->getQueryFlags() && object->getVisible())
                    gEditor->m_pObjectManager->EditorObjectSelected(object);
            }
            m_boxSelecting = false;
        }
        m_flag59 = false;
    }
    else
    {
        camera = CEditor::getSingleton()->getCamera();
        iEditorResourceManager* resources = CEditor::getSingleton()->m_pEditorResourceManager;
        if (!camera || !resources || !resources->getSceneManager()) return;
        POINT point = m_mouseHandler->MousePosition();
        CSettings* settings = CEditor::getSingleton()->m_pSettings;
        float height = settings->GetInt(KSETTINGS_WIN_HEIGHT);
        float width = settings->GetInt(KSETTINGS_WIN_WIDTH);
        Ogre::Vector3 direction = MATH::screenToWorldRay(camera, point.x, point.y, width, height);
        Ogre::Ray ray(camera->getPosition(), direction);
        int closest = -1;
        float distance = 10000.f;
        for (int i = 0; i < static_cast<int>(m_models.size()) - 1; ++i)
        {
            if (i > 5) continue;
            std::pair<bool, float> hit = Ogre::Math::intersects(ray, m_models[i]->getEntity()->getWorldBoundingBox(false));
            if (hit.first && hit.second < distance) { closest = i; distance = hit.second; }
        }
        if (visible && m_models.size() > 19)
        {
            m_models[0]->getEntity()->setMaterialName("ControlBlue");
            m_models[1]->getEntity()->setMaterialName("ControlGreen");
            m_models[2]->getEntity()->setMaterialName("ControlRed");
            m_models[3]->getEntity()->setMaterialName("ControlWhite");
            m_models[4]->getEntity()->setMaterialName("ControlWhite");
            m_models[5]->getEntity()->setMaterialName("ControlWhite");
            m_models[8]->getEntity()->setMaterialName("ControlBlue");
            m_models[6]->getEntity()->setMaterialName("Wireframe");
            m_models[7]->getEntity()->setMaterialName("ControlPurple");
            if (static_cast<unsigned int>(closest) <= 7)
                m_models[closest]->getEntity()->setMaterialName("ControlYellow");
        }
    }
    UpdateWorkingPlane();
    UpdateChunkTemplate();
    m_previousMouse = m_mouseHandler->MousePosition();
}

#include "Descriptor.h"
#include "RoomPiece.h"
#include <cmath>

void CObjectControl3D::manipulateSelectedItems(float, TArrayList<CEditorBaseObject*>& objects)
{
    if (!m_dragType || m_dragPlane == Ogre::Plane())
    {
        Ogre::Camera* camera = CEditor::getSingleton()->getCamera();
        if (!camera) return;
        Ogre::Vector3 forward = MATH::screenToWorldRay(camera, .5f, .5f, 1, 1);
        forward.y = 0;
        forward.normalise();
        Ogre::Vector3 right = forward.crossProduct(Ogre::Vector3::UNIT_Y);
        if (Ogre::Math::Abs(right.x) > Ogre::Math::Abs(right.z))
        {
            if (right.x < 0) { forward = Ogre::Vector3(-0.f, -0.f, 1); right = Ogre::Vector3(-1, -0.f, -0.f); }
            else { forward = Ogre::Vector3(0, 0, -1); right = Ogre::Vector3(1, 0, 0); }
        }
        else if (right.z < 0) { forward = Ogre::Vector3(-1, -0.f, -0.f); right = Ogre::Vector3(-0.f, -0.f, -1); }
        else { forward = Ogre::Vector3(1, 0, 0); right = Ogre::Vector3(0, 0, 1); }
        Ogre::Vector3 pivot = getGroupRotationPoint(objects);
        if (!m_keys.keyPressed(78)) m_keys.keyPressed(110);
        for (unsigned int i = 0; i < objects.size(); ++i)
        {
            CEditorBaseObject* base = objects[i];
            if (!base) continue;
            CPositionableObject* object = dynamic_cast<CPositionableObject*>(base);
            if (!object) continue;
            Ogre::Vector3 position = object->getPosition(false);
            if (m_keys.keyPressed(36)) snapObjectToGround(object, GetAsyncKeyState(17) < 0);
            if (GetAsyncKeyState(17) < 0)
            {
                for (unsigned int key = 37; key <= 39; key += 2)
                {
                    if (!m_keys.keyPressed(key)) continue;
                    Ogre::Radian angle(key == 37 ? m_orientationSnap : -m_orientationSnap);
                    object->getSceneNode()->yaw(angle, Ogre::Node::TS_WORLD);
                    Ogre::Quaternion orientation = object->getSceneNode()->getOrientation();
                    orientation.normalise();
                    object->setOrientation(orientation);
                    if (objects.size() > 1)
                    {
                        Ogre::Matrix3 rotation;
                        rotation.FromAxisAngle(Ogre::Vector3::UNIT_Y, -angle);
                        object->setPosition((object->getPosition(false) - pivot) * rotation + pivot);
                    }
                    CEditor::getSingleton()->m_pObjectManager->markChanged();
                }
                if (m_keys.keyPressed(40))
                {
                    position.y = object->getY() - m_positionVerticalSnap;
                    object->setPosition(position);
                    CEditor::getSingleton()->m_pObjectManager->markChanged();
                }
                if (m_keys.keyPressed(38))
                {
                    position.y = object->getY() + m_positionVerticalSnap;
                    object->setPosition(position);
                    CEditor::getSingleton()->m_pObjectManager->markChanged();
                }
            }
            else
            {
                if (m_keys.keyPressed(37))
                {
                    position -= right * m_planeScale;
                    object->setPosition(position);
                    CEditor::getSingleton()->m_pObjectManager->markChanged();
                }
                if (m_keys.keyPressed(39))
                {
                    position += right * m_planeScale;
                    object->setPosition(position);
                    CEditor::getSingleton()->m_pObjectManager->markChanged();
                }
                if (m_keys.keyPressed(40))
                {
                    position -= forward * m_planeScale;
                    object->setPosition(position);
                    CEditor::getSingleton()->m_pObjectManager->markChanged();
                }
                if (m_keys.keyPressed(38))
                {
                    position += forward * m_planeScale;
                    object->setPosition(position);
                    CEditor::getSingleton()->m_pObjectManager->markChanged();
                }
            }
        }
        return;
    }
    Ogre::Camera* camera = CEditor::getSingleton()->getCamera();
    if (!camera) return;
    POINT mouse = m_mouseHandler->MousePosition();
    CSettings* settings = CEditor::getSingleton()->m_pSettings;
    int height = settings->GetInt(KSETTINGS_WIN_HEIGHT);
    int width = settings->GetInt(KSETTINGS_WIN_WIDTH);
    Ogre::Vector3 direction = MATH::screenToWorldRay(camera, mouse.x, mouse.y, width, height);
    Ogre::Ray ray(camera->getPosition(), direction);
    float distance = Ogre::Math::intersects(ray, m_dragPlane).second;
    Ogre::Vector3 point = camera->getPosition() + direction * distance;
    getGroupRotationPoint(objects);
    for (unsigned int i = 0; i < objects.size(); ++i)
    {
        CEditorBaseObject* base = objects[i];
        if (!base) continue;
        CPositionableObject* object = dynamic_cast<CPositionableObject*>(base);
        if (!object) continue;
        Ogre::Vector3 position = m_selectedPivot;
        float scale = object->getScaleX();
        if (getManipulationType() == 0 && GetAsyncKeyState(17) >= 0)
        {
            if (!(object->getDescriptor()->m_iFlags & 0x400)) continue;
            if (m_dragType == 1 || m_dragType == 4 || m_dragType == 5)
                position.x += point.x - m_selectedPivot.x - m_dragDirection.x;
            if (m_dragType == 2 || m_dragType == 4 || m_dragType == 6)
                position.y += point.y - m_selectedPivot.y - m_dragDirection.y;
            if (m_dragType == 3 || m_dragType == 5 || m_dragType == 6)
                position.z += point.z - m_selectedPivot.z - m_dragDirection.z;
            Ogre::Vector3 delta = position - m_selectedPivot;
            float values[3] = {delta.x, delta.z, delta.y};
            for (unsigned int axis = 0; axis < 3; ++axis)
            {
                float step = axis == 2 ? m_positionVerticalSnap : m_planeScale;
                float remainder = fmodf(values[axis], step);
                if (remainder > step * .5f) values[axis] += step - remainder;
                else values[axis] -= fmodf(values[axis], (values[axis] < 0 ? -1.f : 1.f) * step);
            }
            object->setPosition(object->getPosition(false) + Ogre::Vector3(values[0], values[2], values[1]));
            CEditor::getSingleton()->m_pObjectManager->markChanged();
        }
        else if (getManipulationType() == 1)
        {
            if (object->getDescriptor()->m_iFlags & 0x200) continue;
            CRoomPiece* room = dynamic_cast<CRoomPiece*>(object);
            if (room && !room->getRoomPieceIsScalable()) continue;
            if (m_dragType == 1 && point.x > 0) scale += (point.x - m_controlOffset.x) / point.x;
            else if (m_dragType == 2 && point.y > 0) scale += (point.y - m_controlOffset.y) / point.y;
            else if (m_dragType == 3 && point.z > 0) scale += (point.z - m_controlOffset.z) / point.z;
            object->setScale(std::max(scale, 0.f));
            CEditor::getSingleton()->m_pObjectManager->markChanged();
        }
        else if (getManipulationType() == 2 || GetAsyncKeyState(17) < 0)
        {
            if (!(object->getDescriptor()->m_iFlags & 0x800)) continue;
            if (m_dragType < 4 || m_dragType > 6) continue;
            float x = m_dragType == 6 ? point.z - position.z : point.x - position.x;
            float y = m_dragType == 4 ? position.y - point.y :
                m_dragType == 5 ? point.z - position.z : point.y - position.y;
            float length = std::sqrt(static_cast<float>(std::pow(static_cast<double>(x), 2)) +
                                     static_cast<float>(std::pow(static_cast<double>(y), 2)));
            float angle = Ogre::Math::PI - Ogre::Math::ASin(y / (x < 0 ? -length : length)).valueRadians();
            if (x < 0) angle += Ogre::Math::PI;
            angle -= fmodf(angle, m_orientationSnap);
            Ogre::Quaternion orientation = object->getOrientation().extractQuaternion();
            float current = m_dragType == 4 ? orientation.getRoll(true).valueRadians() :
                m_dragType == 5 ? orientation.getYaw(true).valueRadians() : orientation.getPitch(true).valueRadians();
            Ogre::Radian delta(fmodf(angle - current, Ogre::Math::TWO_PI));
            if (m_dragType == 4) object->getSceneNode()->roll(delta, Ogre::Node::TS_PARENT);
            else if (m_dragType == 5) object->getSceneNode()->yaw(delta, Ogre::Node::TS_PARENT);
            else object->getSceneNode()->pitch(delta, Ogre::Node::TS_PARENT);
            orientation = object->getSceneNode()->getOrientation();
            orientation.normalise();
            object->setOrientation(orientation);
            CEditor::getSingleton()->m_pObjectManager->markChanged();
        }
    }
    m_controlOffset = point;
}
