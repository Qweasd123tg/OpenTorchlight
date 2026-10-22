#ifndef OTL_WEAPON_TRAIL_H
#define OTL_WEAPON_TRAIL_H
#include "RunicCore.h"
#include <OgreManualObject.h>
#include <OgreEntity.h>
#include <OgreNode.h>
#include <OgreSceneNode.h>
#include <OgreColourValue.h>
#include <string>
#include <list>
class CSceneNodeObject;
class CDataGroup;
class CWeaponTrail : public CRunicCore {
    friend class CCharacter;
public:
    CWeaponTrail(Ogre::SceneManager*, const std::string&, int, float);
    CWeaponTrail(Ogre::SceneManager*, CDataGroup*);
    void init();
    void uninit();
    void fadeOut(float elapsed, bool immediate);
    void update(float, Ogre::Vector3*, Ogre::Vector3*, bool, CSceneNodeObject*);
    virtual ~CWeaponTrail();
    void clear();
    void setActive(bool active);
    void setVisible(bool visible);
    void setWeaponEntity(Ogre::Entity* entity);
    void setWeaponNode(Ogre::Node* node);
    void setSegmentStartInitialColourValue(const Ogre::ColourValue& colour);
    const Ogre::ColourValue& getSegmentStartInitialColourValue() const;
    void setSegmentEndInitialColourValue(const Ogre::ColourValue& colour);
    const Ogre::ColourValue& getSegmentEndInitialColourValue() const;
    bool isActive() const;
    bool isVisible() const;
    void setMaterialName(const std::string& name);
private:
    struct Segment {
        Ogre::Vector3 start;
        Ogre::Vector3 end;
        Ogre::ColourValue startColour;
        Ogre::ColourValue endColour;
        float distance;
    };
    std::list<Segment> m_segments;
    std::string m_name;
    Ogre::ManualObject* m_object;
    Ogre::Entity* m_weaponEntity;
    Ogre::Node* m_weaponNode;
    Ogre::SceneNode* m_parentNode;
    std::string m_material;
    int m_maxSegments;
    Ogre::ColourValue m_startColour;
    Ogre::ColourValue m_endColour;
    float m_width; // +0x74
    bool m_active;
    char m_gap79[3];
    float m_fadeScale; // +0x7c
    Ogre::SceneManager* m_sceneManager; // +0x80
    bool m_fading; // +0x88
    float m_fadeTime;
    Ogre::Vector3 m_positionOffset;
};
#endif
