#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include "OgreUtilities.h"


// Imported source candidates; historical status is not fresh acceptance.
void OGRE_UTILITIES::attachEntityToSceneNode(Ogre::Entity* entity, Ogre::SceneNode* node)
{
    if(!node || !entity)return;
    if(entity->getParentSceneNode())entity->getParentSceneNode()->detachObject(entity);
    node->attachObject(entity);
}

void OGRE_UTILITIES::detachEntityFromParent(Ogre::Entity* entity)
{
    if(entity && entity->getParentSceneNode())entity->getParentSceneNode()->detachObject(entity);
}

void OGRE_UTILITIES::removeChildFromParentNode(Ogre::SceneNode* node)
{
    if(node && node->getParentSceneNode())node->getParentSceneNode()->removeChild(node);
}

void OGRE_UTILITIES::addChildSceneNode(Ogre::SceneNode* parent, Ogre::SceneNode* child)
{
    if(!child || !parent)return;
    if(child->getParentSceneNode())child->getParentSceneNode()->removeChild(child);
    parent->addChild(child);
}
