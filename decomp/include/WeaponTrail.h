#ifndef OTL_WEAPON_TRAIL_H
#define OTL_WEAPON_TRAIL_H
#include "RunicCore.h"
#include <OgreManualObject.h>
#include <OgreEntity.h>
#include <OgreNode.h>
#include <OgreColourValue.h>
#include <string>
class CWeaponTrail : public CRunicCore {
public:
    virtual ~CWeaponTrail();
    void clear();
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
    char m_Unrecovered74[4];
    bool m_active;
    char m_Unrecovered79[0x9c-0x79];
};
#endif
