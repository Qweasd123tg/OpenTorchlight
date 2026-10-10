void OGRE_UTILITIES::addChildSceneNode(Ogre::SceneNode* parent, Ogre::SceneNode* child)
{
    if(!child || !parent)return;
    if(child->getParentSceneNode())child->getParentSceneNode()->removeChild(child);
    parent->addChild(child);
}
