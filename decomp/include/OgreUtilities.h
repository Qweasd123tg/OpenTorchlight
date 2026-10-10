#ifndef OGREUTILITIES_H
#define OGREUTILITIES_H

#include <string>
#include "OgreUtilityEnums.h"

namespace Ogre
{
    class Entity;
    class SceneNode;
}

// Partial: declarations from OgreUtilities.cpp used by recovered TUs.
namespace OGRE_UTILITIES
{
    static const std::wstring gPRIMITIVE_NAMES[] =
    {
        L"SPHERE",
        L"BOX",
        L"PLANE",
        L"CYLINDER",
        L"CONE",
        L"ARROW",
    };

    void attachEntityToSceneNode(Ogre::Entity* entity, Ogre::SceneNode* node);
    void detachEntityFromParent(Ogre::Entity* entity);
    void removeChildFromParentNode(Ogre::SceneNode* node);
    void addChildSceneNode(Ogre::SceneNode* parent, Ogre::SceneNode* child);
}

#endif
