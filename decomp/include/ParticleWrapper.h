#ifndef PARTICLEWRAPPER_H
#define PARTICLEWRAPPER_H

#include "PositionableObject.h"
#include "iRandomWeight.h"
#include "iResource.h"
#include "iSelected.h"

class CDataGroup;
class CResourceManager;

namespace Ogre
{
    class Entity;
    class SceneNode;
}

namespace ParticleUniverse
{
    class ParticleSystem;
}

class CParticleWrapper : public CPositionableObject, public iResource,
                        public iRandomWeight, public iSelected
{
public:
    virtual ~CParticleWrapper();

    virtual void setVisible(bool visible);
    virtual void editorSelectionChanged(bool selected);
    virtual unsigned int GetRandomWeight();
    virtual void SetRandomWeight(unsigned int weight);
    virtual void resourceInit(CResourceManager* resourceManager,
                              CDataGroup* dataGroup);
    virtual void resourceFreeing();
    virtual void free();
    virtual void stop();
    virtual void start();
    virtual bool isPlaying();

    void hideVisualSphereMesh();
    void updateParticleSystem(float elapsedTime);
    void showVisualSphereMesh();
    void createParticleSystem();

    CParticleWrapper(CResourceManager* resourceManager);

    ParticleUniverse::ParticleSystem* m_pParticleSystem;
    Ogre::SceneNode* m_pVisualSphereNode;
    Ogre::Entity* m_pVisualSphereEntity;
    bool m_bPlaying;
    unsigned int m_iRandomWeight;
};

#endif
