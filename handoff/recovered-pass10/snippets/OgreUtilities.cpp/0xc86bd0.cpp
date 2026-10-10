void OGRE_UTILITIES::detachEntityFromParent(Ogre::Entity* entity)
{
    if(entity && entity->getParentSceneNode())entity->getParentSceneNode()->detachObject(entity);
}
