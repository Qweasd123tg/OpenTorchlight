void OGRE_UTILITIES::removeChildFromParentNode(Ogre::SceneNode* node)
{
    if(node && node->getParentSceneNode())node->getParentSceneNode()->removeChild(node);
}
