#ifndef IDAMAGESHAPE_H
#define IDAMAGESHAPE_H

namespace Ogre { class Vector3; }
class CDamageShape;
class CCharacter;
class CItem;

class iDamageShape
{
public:
    virtual ~iDamageShape();
    virtual bool getCharacterCanBeAffectedByDamageShape(CDamageShape*, CCharacter*) = 0;
    virtual bool characterEffectedByDamageShape(CDamageShape*, CCharacter*, Ogre::Vector3*) = 0;
    virtual bool itemEffectedByDamageShape(CDamageShape*, CItem*) = 0;
};

#endif
