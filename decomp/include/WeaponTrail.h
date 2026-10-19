#ifndef OTL_WEAPON_TRAIL_H
#define OTL_WEAPON_TRAIL_H
#include "RunicCore.h"
#include <OgreManualObject.h>
#include <OgreEntity.h>
#include <OgreNode.h>
#include <OgreColourValue.h>
#include <string>
class CSceneNodeObject;
class CWeaponTrail : public CRunicCore {
    friend class CCharacter;
public:
    CWeaponTrail(Ogre::SceneManager*, const std::string&, int, float);
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
    struct SegmentLink { SegmentLink* next; SegmentLink* previous; } m_segments;
    char m_Unrecovered20[8];
    Ogre::ManualObject* m_object;
    Ogre::Entity* m_weaponEntity;
    Ogre::Node* m_weaponNode;
    char m_Unrecovered40[8];
    std::string m_material;
    char m_Unrecovered50[4];
    Ogre::ColourValue m_startColour;
    Ogre::ColourValue m_endColour;
    float m_duration; // +0x74
    bool m_active;
    char m_gap79[3];
    float m_fadeScale; // +0x7c
    Ogre::SceneManager* m_sceneManager; // +0x80
    bool m_fading; // +0x88
    char m_Unrecovered89[0x9c-0x89];
};
#endif
