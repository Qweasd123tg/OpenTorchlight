void CDynamicLine::createVertexDeclaration()
{
    mRenderOp.vertexData->vertexDeclaration->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION, 0);
}
