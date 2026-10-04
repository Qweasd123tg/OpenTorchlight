#ifndef SHAPE_H
#define SHAPE_H
#include "PositionableObject.h"
// Partial: full 0x168-byte primary base used by UnitSpawner's RTTI.
class CShape : public CPositionableObject
{
public:
    virtual ~CShape();
    virtual void setBoxSize(const Ogre::Vector3& size);
private:
    unsigned char m_ShapeData100[0x168-0x100];
};
#endif
