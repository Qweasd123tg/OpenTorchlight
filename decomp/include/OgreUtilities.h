#ifndef OGREUTILITIES_H
#define OGREUTILITIES_H

#include <string>

namespace Ogre
{
    class Entity;
    class SceneNode;
}

// Partial: declarations from OgreUtilities.cpp used by recovered TUs.
namespace OGRE_UTILITIES
{
    // Enumerator names are ours; values follow gPRIMITIVE_NAMES.
    enum EPRIMITIVES
    {
        PRIMITIVE_SPHERE,
        PRIMITIVE_BOX,
        PRIMITIVE_PLANE,
        PRIMITIVE_CYLINDER,
        PRIMITIVE_CONE,
        PRIMITIVE_ARROW,
        PRIMITIVE_COUNT
    };

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
