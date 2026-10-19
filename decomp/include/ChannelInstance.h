#ifndef CHANNELINSTANCE_H
#define CHANNELINSTANCE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "RunicCore.h"
namespace Ogre { class SceneNode; }

class CChannelInstance : public CRunicCore
{
public:
    CChannelInstance() : CRunicCore(), m_iUnknown10(0) {}
    virtual ~CChannelInstance();
    void clear();

    // fields
    Ogre::SceneNode* m_iUnknown10; // +0x10, native playSound stores its node argument
};

#endif
