#ifndef OTL_PARTICLE_UNIVERSE_PLUGIN_H
#define OTL_PARTICLE_UNIVERSE_PLUGIN_H
#include <OgrePlugin.h>
namespace ParticleUniverse {
// Native RTTI places Ogre::Plugin at zero; allocation at 0xa5e674 is 0xc8.
// This interface owns no recovered PU implementation or field operation.
class ParticleUniversePlugin : public Ogre::Plugin
{
public:
    ParticleUniversePlugin();
    virtual ~ParticleUniversePlugin();
    virtual const Ogre::String& getName() const;
    virtual void install();
    virtual void initialise();
    virtual void shutdown();
    virtual void uninstall();
private:
    unsigned char m_unrecovered08[0xc0];
};
}
#endif
