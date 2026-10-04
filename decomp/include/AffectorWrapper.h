#ifndef AFFECTORWRAPPER_H
#define AFFECTORWRAPPER_H

#include <OgreVector3.h>
#include <string>

#include "PositionableObject.h"
#include "ResourceManager.h"
#include "iSelected.h"

class CParticleTechWrapper;
class ParticleAffector;

#pragma pack(push, 1)

class CAffectorWrapper : public CPositionableObject, public iSelected
{
public:
    virtual ~CAffectorWrapper();

    virtual void setParentGuid(long long parentGuid);
    virtual void setEnabled(bool enabled);
    virtual bool getEnabled();
    virtual void positionUpdated(const Ogre::Vector3& position);
    virtual void editorSelectionChanged(bool selected);

    void enablePositioning(bool enabled);
    void setParentTechniqueWrapper(CParticleTechWrapper* parent);
    void destroyAffector();

    CAffectorWrapper(CResourceManager* resourceManager, std::string name);

    CParticleTechWrapper* m_pParticleTechWrapper;
    ParticleAffector* m_pAffector;
    bool m_bPositioningEnabled;
    bool m_bEnabled;
};

#pragma pack(pop)

#endif
