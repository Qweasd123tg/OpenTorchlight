#ifndef AFFECTORWRAPPER_H
#define AFFECTORWRAPPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreVector3.h>
#include <string>
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "iSelected.h"
class CParticleTechWrapper;

class CAffectorWrapper : public CPositionableObject, public iSelected
{
public:
    virtual ~CAffectorWrapper();
    virtual void setParentGuid(long long);
    virtual void setEnabled(bool);
    virtual bool getEnabled();
    virtual void positionUpdated(const Ogre::Vector3&);
    virtual void editorSelectionChanged(bool);
    void enablePositioning(bool);
    void setParentTechniqueWrapper(CParticleTechWrapper*);
    void destroyAffector();
    CAffectorWrapper(CResourceManager*, std::string);

    // fields
    CParticleTechWrapper* m_pParticleTechWrapper;
    void* m_pUnknown110;
    bool m_bUnknown118;
    bool m_bEnabled;
};

#endif
