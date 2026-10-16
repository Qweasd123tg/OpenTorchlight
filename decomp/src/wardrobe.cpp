#include "Wardrobe.h"
#include "FileSystem.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
#include "OgreUtilities.h"
#include <OgreImage.h>
#include <OgreEntity.h>
#include <OgreMesh.h>
#include <OgreMeshManager.h>
#include <OgreSceneManager.h>
#include <OgreTextureManager.h>
#include <OgreResourceGroupManager.h>

void CWardrobe::setBaseTexture(EWardrobeSlot slot, std::wstring texture)
{
    m_textures[slot] = texture;
    if (m_images[slot]) {
        delete m_images[slot];
        m_images[slot] = 0;
    }
    CFileInfo file;
    CFileSystem::getSingleton()->getFileInfo(texture, file, false, true, false);
    if (file.m_bExists) {
        m_images[slot] = new Ogre::Image;
        m_images[slot]->load(file.m_sResourceName, file.m_sResourceGroup.empty()
            ? Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME : file.m_sResourceGroup);
    }
}

CWardrobe::~CWardrobe()
{
    if (m_baseImage) {
        delete m_baseImage;
        m_baseImage = 0;
    }
    for (int i = 0; i < 5; ++i) {
        if (m_images[i]) {
            delete m_images[i];
            m_images[i] = 0;
        }
    }
    if (m_entity) {
        OGRE_UTILITIES::detachEntityFromParent(m_entity);
        m_entity->_deinitialise();
        m_sceneManager->destroyEntity(m_entity);
        m_entity = 0;
    }
    if (m_paperdollEntity) {
        OGRE_UTILITIES::detachEntityFromParent(m_paperdollEntity);
        m_paperdollEntity->_deinitialise();
        m_paperdollSceneManager->destroyEntity(m_paperdollEntity);
        m_paperdollEntity = 0;
    }
    if (m_mesh) {
        m_mesh->unload();
        Ogre::ResourcePtr resource = Ogre::MeshManager::getSingleton().getByName(m_mesh->getName());
        Ogre::MeshManager::getSingleton().remove(resource);
        m_mesh = 0;
    }
    if (m_paperdollMesh) {
        m_paperdollMesh->unload();
        Ogre::ResourcePtr resource = Ogre::MeshManager::getSingleton().getByName(m_paperdollMesh->getName());
        Ogre::MeshManager::getSingleton().remove(resource);
        m_paperdollMesh = 0;
    }
    if (!m_texture.isNull()) {
        m_texture->unload();
        Ogre::ResourcePtr resource = Ogre::TextureManager::getSingleton().getByName(m_texture->getName());
        Ogre::TextureManager::getSingleton().remove(resource);
        m_texture.setNull();
    }
    m_originalEntity = 0;
    Ogre::MeshManager::getSingleton().unloadUnreferencedResources(true);
}

CWardrobe::CWardrobe(CCharacter* character, Ogre::SceneManager* manager,
    Ogre::SceneManager* paperdollManager, CGenericModel* model, CGenericModel* paperdoll,
    std::wstring base, std::wstring chest, std::wstring boots, std::wstring gloves,
    std::wstring helmet, std::wstring shoulders)
    : m_sceneManager(manager), m_model(model), m_paperdollModel(paperdoll),
      m_originalEntity(0), m_baseTextureName(base), m_baseImage(0),
      m_character(character)
{
    m_paperdollSceneManager = manager;
    m_mesh = 0;
    m_paperdollMesh = 0;
    m_entity = 0;
    m_paperdollEntity = 0;
    for (int i = 0; i < 5; ++i) m_images[i] = 0;
    CFileInfo baseFile, chestFile, glovesFile, bootsFile;
    m_textures[WARDROBE_CHEST] = chest;
    m_textures[WARDROBE_GLOVES] = gloves;
    m_textures[WARDROBE_BOOTS] = boots;
    CFileSystem::getSingleton()->getFileInfo(base, baseFile, false, true, false);
    CFileSystem::getSingleton()->getFileInfo(chest, chestFile, false, true, false);
    CFileSystem::getSingleton()->getFileInfo(boots, bootsFile, false, true, false);
    CFileSystem::getSingleton()->getFileInfo(gloves, glovesFile, false, true, false);
    std::wstring directory = FILESYSTEM::RemoveFileName(base);
    if (baseFile.m_bExists) {
        m_baseImage = new Ogre::Image;
        m_baseImage->load(baseFile.m_sResourceName, baseFile.m_sResourceGroup.empty()
            ? Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME : baseFile.m_sResourceGroup);
    }
    if (chestFile.m_bExists) {
        m_images[WARDROBE_CHEST] = new Ogre::Image;
        m_images[WARDROBE_CHEST]->load(chestFile.m_sResourceName, chestFile.m_sResourceGroup.empty()
            ? Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME : chestFile.m_sResourceGroup);
    }
    if (bootsFile.m_bExists) {
        m_images[WARDROBE_BOOTS] = new Ogre::Image;
        m_images[WARDROBE_BOOTS]->load(bootsFile.m_sResourceName, bootsFile.m_sResourceGroup.empty()
            ? Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME : bootsFile.m_sResourceGroup);
    }
    if (glovesFile.m_bExists) {
        m_images[WARDROBE_GLOVES] = new Ogre::Image;
        m_images[WARDROBE_GLOVES]->load(glovesFile.m_sResourceName, glovesFile.m_sResourceGroup.empty()
            ? Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME : glovesFile.m_sResourceGroup);
    }
    if (!helmet.empty()) m_meshes[WARDROBE_HELMET] = helmet;
    if (!shoulders.empty()) m_meshes[WARDROBE_SHOULDERS] = shoulders;
    if (m_baseImage) {
        Ogre::PixelFormat format = m_baseImage->getFormat();
        int mipmaps = m_baseImage->getNumMipmaps();
        unsigned height = m_baseImage->getHeight();
        unsigned width = m_baseImage->getWidth();
        m_texture = Ogre::TextureManager::getSingleton().createManual(
            STRINGS::uniqueName("wtex_"), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            Ogre::TEX_TYPE_2D, width, height, 1, mipmaps, format, Ogre::TU_DEFAULT);
        m_texture->setNumMipmaps(5);
    }
    update(0);
}
