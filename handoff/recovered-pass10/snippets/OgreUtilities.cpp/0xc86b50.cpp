void OGRE_UTILITIES::attachEntityToSceneNode(Ogre::Entity* entity, Ogre::SceneNode* node)
{
    if(!node || !entity)return;
    if(entity->getParentSceneNode())entity->getParentSceneNode()->detachObject(entity);
    node->attachObject(entity);
}
