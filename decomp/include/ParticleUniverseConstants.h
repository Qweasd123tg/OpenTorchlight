#ifndef PARTICLEUNIVERSECONSTANTS_H
#define PARTICLEUNIVERSECONSTANTS_H

#include <OgreString.h>
#include <OgreVector3.h>

// Internal-linkage constants of the ParticleUniverse headers, recovered from the
// static initializers of the original TUs that include them (126 TUs). Replace
// with the matching ParticleUniverse release header once it is identified.
namespace ParticleUniverse
{
    static const Ogre::Vector3 HALFSCALE = Ogre::Vector3::UNIT_SCALE * 0.5;

    static const Ogre::String ALIAS = "1";
    static const Ogre::String SYSTEM = "2";
    static const Ogre::String TECHNIQUE = "3";
    static const Ogre::String RENDERER = "4";
    static const Ogre::String EMITTER = "5";
    static const Ogre::String AFFECTOR = "6";
    static const Ogre::String OBSERVER = "7";
    static const Ogre::String HANDLER = "8";
    static const Ogre::String BEHAVIOUR = "9";
    static const Ogre::String EXTERN = "10";
    static const Ogre::String DYNAMIC_ATTRIBUTE = "11";
    static const Ogre::String DEPENDENCY = "12";
}

#endif
