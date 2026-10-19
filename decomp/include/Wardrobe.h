#ifndef OTL_WARDROBE_H
#define OTL_WARDROBE_H
#include "RunicCore.h"
#include "WardrobeDefines.h"
#include <OgreTexture.h>
#include <string>
class CInventory;
class CCharacter;
class CGenericModel;
namespace Ogre { class SceneManager; class Entity; class Mesh; class Image; }
class CWardrobe : public CRunicCore {
    friend class CCharacter;
    Ogre::SceneManager* m_sceneManager;
    CGenericModel* m_model;
    CGenericModel* m_paperdollModel;
    Ogre::Entity* m_originalEntity;
    std::wstring m_baseTextureName;
    Ogre::TexturePtr m_texture;
    Ogre::Image* m_baseImage;
    Ogre::Image* m_images[5];
public:
    CWardrobe(CCharacter*, Ogre::SceneManager*, Ogre::SceneManager*, CGenericModel*, CGenericModel*,
              std::wstring, std::wstring, std::wstring, std::wstring, std::wstring, std::wstring);
    virtual ~CWardrobe();
    void update(CInventory*);
    void setBaseTexture(EWardrobeSlot,std::wstring);
    std::wstring m_meshes[5];
    std::wstring m_textures[5];
private:
    Ogre::Mesh* m_mesh;
    Ogre::Mesh* m_paperdollMesh;
    Ogre::Entity* m_entity;
    Ogre::Entity* m_paperdollEntity;
    CCharacter* m_character;
    Ogre::SceneManager* m_paperdollSceneManager;
};
typedef char check_wardrobe_size[sizeof(CWardrobe)==0x108?1:-1];
#endif
