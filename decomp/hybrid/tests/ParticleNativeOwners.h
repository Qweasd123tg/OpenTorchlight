#ifndef OTL_PARTICLE_NATIVE_OWNERS_H
#define OTL_PARTICLE_NATIVE_OWNERS_H
namespace Ogre { class SceneManager; class Camera; }
class CResourceManager;
struct ParticleNativeOwners {
    CResourceManager* resources;
    Ogre::SceneManager* scene;
    Ogre::Camera* camera;
    void* owner;
};
// The implementation uses the existing native owners in a separate TU. This
// keeps the unused Graph/Player declarations out of the PU SDK test TU.
ParticleNativeOwners particleNativeOwners(unsigned profile);
#endif
