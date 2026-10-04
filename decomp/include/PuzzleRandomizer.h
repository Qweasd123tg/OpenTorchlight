#ifndef PUZZLERANDOMIZER_H
#define PUZZLERANDOMIZER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreCamera.h>
#include <OgreVector3.h>
#include "EditorBaseObject.h"
#include "GameEnums.h"
#include "ResourceManager.h"
#include "iLevelUpdate.h"

class CPuzzleRandomizer : public CEditorBaseObject, public iLevelUpdate
{
public:
    virtual ~CPuzzleRandomizer();
    virtual long long updateLevelObject(float, Ogre::Camera*, const Ogre::Vector3&);
    void addLevelListener();
    void reset();
    void setActiveInputs(unsigned int);
    CPuzzleRandomizer(CResourceManager*);
    void trigger(EPUZZLE_INPUTS);

    // fields
    bool m_bUnknown60;
    unsigned char m_gap61[0x3];
    int m_iActiveInputs;
    bool m_bEnabled;
    unsigned char m_gap69[0x3];
    int m_iUnknown6C;
    unsigned char m_gap70[0x14] __attribute__((aligned(4)));
    bool m_bUnknown84;
    bool m_bUnknown85;
    bool m_bUnknown86;
    bool m_bUnknown87;
    bool m_bUnknown88;
    bool m_bUnknown89;
    unsigned char m_gap8A[0x2];
    int m_iUnknown8C;
    CResourceManager* m_pResourceManager;
};

#endif
