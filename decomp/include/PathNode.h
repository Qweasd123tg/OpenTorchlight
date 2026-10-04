#ifndef PATHNODE_H
#define PATHNODE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreVector3.h>
#include <string>
#include "PathController.h"
#include "PositionableObject.h"
#include "ResourceManager.h"
class CTextEvent;

class CPathNode : public CPositionableObject
{
public:
    virtual ~CPathNode();
    virtual void setVisible(bool);
    virtual void positionUpdated(const Ogre::Vector3&);
    void setText(const std::wstring&);
    CPathNode(CPathController*, CResourceManager*);

    // fields
    CPathController* m_pPathController;
    CTextEvent* m_pTextEvent;
    std::wstring m_sUnknown110;
    long long m_iUnknown118;
    long long m_iUnknown120;
};

#endif
