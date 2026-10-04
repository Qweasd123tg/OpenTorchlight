#ifndef PROPERTYNODE_H
#define PROPERTYNODE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreMatrix4.h>
#include <OgreVector3.h>
#include "Character.h"
#include "Item.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "iLevelUpdatedCharacter.h"

class CPropertyNode : public CPositionableObject, public iLevelUpdatedCharacter
{
public:
    virtual ~CPropertyNode();
    virtual void setEnabled(bool);
    virtual void positionUpdated(const Ogre::Vector3&);
    virtual void orientationUpdated(const Ogre::Matrix4&);
    virtual void scaleUpdated(const Ogre::Vector3&);
    virtual void characterUpdatedInLevel(float, CCharacter*);
    virtual void itemUpdatedInLevel(float, CItem*);
    void setPropertyNodeType(unsigned int);
    void createEntity();
    void activate();
    void killOrMoveBaseUnits();
    void updatePathNodes();
    void jumpDownLogic();
    CPropertyNode(CResourceManager*);
    void updateBoundingBox();

    // fields
    int m_iUnknown108;
    unsigned int m_iPropertyNodeType;
    bool m_bUnknown110;
    bool m_bUnknown111;
    bool m_bUnknown112;
    unsigned char m_gap113[0x1];
    int m_iUnknown114;
    bool m_bUnknown118;
    unsigned char m_gap119[0x7];
    int m_iUnknown120;
    int m_iUnknown124;
    int m_iUnknown128;
    int m_iUnknown12C;
    int m_iUnknown130;
    int m_iUnknown134;
    int m_iUnknown138;
    unsigned char m_gap13C[0x4] __attribute__((aligned(4)));
    long long m_iUnknown140;
    void* m_pUnknown148;
    bool m_bUnknown150;
};

#endif
