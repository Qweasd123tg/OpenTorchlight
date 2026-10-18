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

#include <OgreSceneManager.h>
#include "FileSystem.h"
#include "StringUtilities.h"
Ogre::Entity* OGRE_UTILITIES::createEntity(Ogre::SceneManager* sceneManager,const std::wstring& meshName,EQUERYMASK queryMask,const char* name)
{
    if(!sceneManager)return NULL;
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(meshName,info,false,true,false);
    if(!info.m_bExists)return NULL;
    std::string unique=STRINGS::uniqueName(std::string(name));
    Ogre::Entity* entity=sceneManager->createEntity(unique,info.m_sResourceName);
    if(entity)entity->setQueryFlags(queryMask);
    return entity;
}
Ogre::Entity* OGRE_UTILITIES::createEntity(Ogre::SceneManager* sceneManager,EPRIMITIVES primitive,EQUERYMASK queryMask,const char* name)
{
    if(!sceneManager)return NULL;
    std::wstring mesh;
    switch(primitive){
    case PRIMITIVE_SPHERE:mesh=L"sphere.mesh";break;
    case PRIMITIVE_BOX:mesh=L"box.mesh";break;
    case PRIMITIVE_PLANE:mesh=L"plane.mesh";break;
    case PRIMITIVE_CYLINDER:mesh=L"cylinder.mesh";break;
    case PRIMITIVE_CONE:mesh=L"cone.mesh";break;
    case PRIMITIVE_ARROW:mesh=L"arrow.mesh";break;
    default:break;
    }
    return createEntity(sceneManager,L"media/models/primitives/"+mesh,queryMask,name);
}
