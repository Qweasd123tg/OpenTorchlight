#include "WeaponTrail.h"
#include "DataGroup.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
#include "SceneNodeObject.h"
#include <algorithm>
#include <OgreMaterialManager.h>
#include <OgrePass.h>
#include <OgreTechnique.h>
#include <OgreVertexIndexData.h>
#include <OgreSceneManager.h>



// Imported source candidates; historical status is not fresh acceptance.
void CWeaponTrail::clear()
{
}

void CWeaponTrail::setVisible(bool visible)
{
    m_object->setVisible(visible);
    if (visible) m_object->setRenderQueueGroup(91);
}

void CWeaponTrail::setWeaponEntity(Ogre::Entity* entity)
{
    m_weaponEntity = entity;
    if (entity) m_weaponNode = entity->getParentNode();
    else { m_weaponNode = NULL; m_weaponEntity = NULL; }
}

void CWeaponTrail::setWeaponNode(Ogre::Node* node)
{
    m_weaponNode = node;
    m_weaponEntity = NULL;
}

void CWeaponTrail::setSegmentStartInitialColourValue(const Ogre::ColourValue& colour)
{
    m_startColour = colour;
}

const Ogre::ColourValue& CWeaponTrail::getSegmentStartInitialColourValue() const
{
    return m_startColour;
}

void CWeaponTrail::setSegmentEndInitialColourValue(const Ogre::ColourValue& colour)
{
    m_endColour = colour;
}

const Ogre::ColourValue& CWeaponTrail::getSegmentEndInitialColourValue() const
{
    return m_endColour;
}

bool CWeaponTrail::isActive() const
{
    return m_active;
}

bool CWeaponTrail::isVisible() const
{
    return !m_segments.empty();
}

void CWeaponTrail::setMaterialName(const std::string& name)
{
    m_material = name;
    if (m_object) m_object->setMaterialName(0, m_material);
}

void CWeaponTrail::setActive(bool active)
{
    m_active=active;
    if(!active) { m_weaponEntity=NULL;m_weaponNode=NULL; }
    m_fadeScale=1;
    m_segments.clear();
    m_fading=false;
}

void CWeaponTrail::uninit()
{
    m_active = false;
    m_parentNode->detachObject(m_object);
    m_sceneManager->getRootSceneNode()->removeAndDestroyChild(m_parentNode->getName());
    m_object->setVisible(false);
    m_sceneManager->destroyManualObject(m_object);
}

void CWeaponTrail::init()
{
    m_object = m_sceneManager->createManualObject(m_name);
    m_object->estimateVertexCount(m_maxSegments * 2);
    m_object->setDynamic(true);
    m_object->setRenderQueueGroup(91);
    m_object->begin("WeaponTrail", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
    for (int i = 0; i < m_maxSegments; ++i) {
        m_object->position(0.0f, 0.0f, i * -0.25f);
        m_object->textureCoord(0.0f, 0.0f);
        m_object->colour(1.0f, 0.0f, 0.0f, 1.0f);
        m_object->position(0.0f, 1.0f, i * -0.25f);
        m_object->textureCoord(1.0f, 0.0f);
        m_object->colour(1.0f, 0.0f, 0.0f, 1.0f);
    }
    m_object->end();
    m_parentNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
    m_parentNode->attachObject(m_object);
    m_object->setVisible(false);
}

CWeaponTrail::CWeaponTrail(Ogre::SceneManager* sceneManager, const std::string& name,
                         int maxSegments, float width)
    : m_name(name), m_object(NULL), m_maxSegments(maxSegments), m_width(width),
      m_active(false), m_fadeScale(1.0f), m_sceneManager(sceneManager), m_fading(false),
      m_fadeTime(0.5f), m_positionOffset(0.0f, 0.0f, 0.0f)
{
    m_startColour = Ogre::ColourValue(1.0f, 1.0f, 1.0f, 1.0f);
    m_endColour = Ogre::ColourValue(1.0f, 1.0f, 1.0f, 1.0f);
    setWeaponEntity(NULL);
    init();
}

CWeaponTrail::~CWeaponTrail()
{
    uninit();
}

CWeaponTrail::CWeaponTrail(Ogre::SceneManager* sceneManager, CDataGroup* data)
    : m_name(STRINGS::uniqueName("wt")), m_object(NULL), m_maxSegments(20),
      m_width(1.0f), m_active(false), m_fadeScale(1.0f), m_sceneManager(sceneManager),
      m_fading(false), m_fadeTime(0.5f)
{
    if (data && data->GetGroupName() == L"WEAPONTRAIL") {
        m_maxSegments = data->GetDataValue(L"MAXSEGMENTS", m_maxSegments);
        m_fadeTime = data->GetDataValue(L"FADETIME", 0.5f);
        m_width = data->GetDataValue(L"WIDTH", 1.0f);
        std::string texture = STRINGS::StringConvertToNarrow(
            data->GetDataValue(L"TEXTURE", L"").c_str());
        std::string materialName("");
        if (texture != "") {
            materialName = STRINGS::StringUpper(FILESYSTEM::GetFileName(texture));
            if (!Ogre::MaterialManager::getSingleton().resourceExists(materialName)) {
                Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
                    materialName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
                material->setReceiveShadows(false);
                material->setLightingEnabled(false);
                Ogre::Pass* pass = material->getTechnique(0)->getPass(0);
                pass->setDepthCheckEnabled(true);
                pass->setSelfIllumination(0.0f, 0.0f, 0.0f);
                pass->setDepthWriteEnabled(false);
                material->setSceneBlending(Ogre::SBT_ADD);
                material->setCullingMode(Ogre::CULL_NONE);
                pass->createTextureUnitState(texture, 0);
            }
        }
        setWeaponEntity(NULL);
        init();
        if (materialName != "")
            setMaterialName(materialName);
    }
}

void CWeaponTrail::fadeOut(float elapsed, bool rebuild)
{
    m_fadeScale -= elapsed / m_fadeTime;
    if (m_fadeScale <= 0.0f) {
        setVisible(false);
        setActive(false);
        return;
    }
    m_object->setVisible(true);
    if (rebuild && m_active) {
        m_object->beginUpdate(0);
        int count = 0;
        float totalDistance = 0.0f;
        Ogre::Vector3 previous;
        for (std::list<Segment>::iterator i = m_segments.begin(); i != m_segments.end(); ++i) {
            if (count)
                totalDistance += (i->end - previous).length();
            i->distance = totalDistance;
            previous = i->end;
            ++count;
        }
        if (totalDistance == 0.0f && count)
            totalDistance = 0.01f;
        int vertices = count * 2;
        if (count) {
            for (std::list<Segment>::iterator i = m_segments.begin(); i != m_segments.end(); ++i) {
                float coordinate = std::max(1.0f - i->distance / totalDistance, 0.01f);
                m_object->position(i->start);
                m_object->textureCoord(0.0f, coordinate);
                m_object->colour(i->startColour * m_fadeScale);
                m_object->position(i->end);
                m_object->textureCoord(1.0f, coordinate);
                m_object->colour(i->endColour * m_fadeScale);
            }
        }
        Ogre::Vector3 tail = Ogre::Vector3::ZERO;
        if (!m_segments.empty()) tail = m_segments.back().start;
        while (vertices < m_maxSegments * 2) {
            m_object->position(tail);
            ++vertices;
        }
        m_object->end();
    }
}

void CWeaponTrail::update(float elapsed, Ogre::Vector3* position, Ogre::Vector3* direction,
                         bool updateWhileFading, CSceneNodeObject* owner)
{
    if (!m_active && m_segments.empty()) return;
    if (m_fading) {
        fadeOut(elapsed, !updateWhileFading);
        if (!updateWhileFading) return;
    }
    if ((!position && !m_weaponNode) || !m_object) return;
    m_object->setVisible(true);
    if (m_segments.size() >= static_cast<unsigned int>(m_maxSegments))
        m_segments.pop_back();
    if (m_active) {
        Segment segment;
        segment.startColour = m_startColour;
        segment.endColour = m_endColour;
        if (m_weaponNode) {
            segment.start = m_weaponNode->_getDerivedPosition();
            Ogre::Vector3 previousPosition = m_weaponNode->getPosition();
            m_weaponNode->translate(Ogre::Vector3(0.0f, m_width, 0.0f), Ogre::Node::TS_LOCAL);
            segment.end = m_weaponNode->_getDerivedPosition();
            m_weaponNode->setPosition(previousPosition);
            if (owner && !m_weaponEntity) {
                Ogre::Quaternion orientation = owner->getSceneNode()->_getDerivedOrientation();
                Ogre::Vector3 origin = owner->getSceneNode()->_getDerivedPosition();
                segment.end = orientation * segment.end + origin;
                segment.start = orientation * segment.start + origin;
            }
            Ogre::Vector3 offset = segment.end - segment.start;
            offset.normalise();
            offset *= m_positionOffset;
            segment.end += offset;
            segment.start += offset;
        } else {
            Ogre::Vector3 offset = (*direction * m_width) * 0.5f;
            segment.start = *position - offset;
            segment.end = *position + offset;
        }
        m_segments.push_front(segment);
    }
    m_object->beginUpdate(0);
    int count = 0;
    float totalDistance = 0.0f;
    Ogre::Vector3 previous;
    for (std::list<Segment>::iterator i = m_segments.begin(); i != m_segments.end(); ++i) {
        if (count)
            totalDistance += (i->end - previous).length();
        i->distance = totalDistance;
        previous = i->end;
        ++count;
    }
    if (totalDistance == 0.0f && count)
        totalDistance = 0.01f;
    int vertices = count * 2;
    if (count) {
        for (std::list<Segment>::iterator i = m_segments.begin(); i != m_segments.end(); ++i) {
            float coordinate = std::max(1.0f - i->distance / totalDistance, 0.01f);
            m_object->position(i->start);
            m_object->textureCoord(0.0f, coordinate);
            m_object->colour(i->startColour * m_fadeScale);
            m_object->position(i->end);
            m_object->textureCoord(1.0f, coordinate);
            m_object->colour(i->endColour * m_fadeScale);
        }
    }
    Ogre::Vector3 tail = Ogre::Vector3::ZERO;
    if (!m_segments.empty()) tail = m_segments.back().start;
    while (vertices < m_maxSegments * 2) {
        m_object->position(tail);
        ++vertices;
    }
    m_object->end();
}
