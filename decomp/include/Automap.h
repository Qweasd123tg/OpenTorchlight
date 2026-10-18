#ifndef AUTOMAP_H
#define AUTOMAP_H

#include <OgreBillboard.h>
#include <OgreMaterial.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>

#include <string>
#include <vector>

#include "ResourceManager.h"
#include "RunicCore.h"
#include "TArrayList.h"

namespace Ogre
{
    class Camera;
    class Rectangle2D;
    class SceneNode;
    class Viewport;
}

class CAutomap : public CRunicCore
{
public:
    virtual ~CAutomap();

    void clear();
    void setRevealed(int x, int z, float value);
    float getRevealed(int x, int z);
    void clearNPCIcons();
    void setNPCBillboardVisible(Ogre::Billboard* billboard, bool visible);
    void finalize();
    void setPetPosition(const Ogre::Vector3& position);
    void setPlayerPosition(const Ogre::Vector3& position);
    void setPetVisible(bool visible);
    void update(const Ogre::Vector3& position, float elapsed);
    void zoom(float delta);
    void setVisible(bool visible);
    void setFullscreen(bool fullscreen);
    Ogre::Billboard* addTile(int type, const Ogre::Vector3& position,
                             const Ogre::Vector3& direction,
                             bool animated, bool npc);
    CAutomap(CResourceManager* resourceManager,
             Ogre::SceneManager* sceneManager);
    void setFullMap(std::wstring textureName, float width, float height,
                    Ogre::Vector3& position, Ogre::Vector3& direction,
                    float alpha);

    CResourceManager* m_pResourceManager;
    Ogre::SceneManager* m_pSceneManager; // +0x18, original constructor argument
    Ogre::BillboardSet* m_pTileBillboardSet;
    Ogre::BillboardSet* m_pStaticTileBillboardSet;
    Ogre::SceneNode* m_pTileSceneNode;
    Ogre::SceneNode* m_pStaticTileSceneNode;
    Ogre::Camera* m_pCamera;
    void* m_pReserved;

    union {
        unsigned char m_ViewportState[0x18] __attribute__((aligned(8)));
        struct {
            Ogre::Viewport* m_viewport; // +0x50
            float m_zoom; // +0x58
            float m_panelSize; // +0x5c
            float m_fullMapWidth; // +0x60
            float m_fullMapHeight; // +0x64
        };
    };
    bool m_bVisible;
    unsigned char m_gap69[7];
    Ogre::Billboard* m_pPlayerBillboard;

    Ogre::Billboard* m_pPetBillboard;
    float m_maximumX;
    float m_maximumZ;
    float m_minimumX;
    float m_minimumZ;
    int m_iMapGridWidth;
    int m_iMapGridHeight;
    float* m_pRevealedTiles;
    bool m_bTilesChanged;
    bool m_bFullscreen;
    bool m_bFullMap;
    unsigned char m_gapA3[5];

    std::vector<Ogre::Billboard*> m_vMapTileBillboards;
    std::vector<float> m_vMapTileRevealValues;
    std::vector<Ogre::Billboard*> m_vNPCBillboards;
    std::vector<float> m_vNPCRevealValues;
    TArrayList<Ogre::Billboard*> m_hiddenNPCBillboards;

    Ogre::SceneNode* m_pCullQuad;
    Ogre::Rectangle2D* m_pCullQuadBounds;

    Ogre::MaterialPtr m_cullMaterial; // +0x130, original shared owner

    Ogre::SceneNode* m_pOverlayQuad;
    Ogre::Rectangle2D* m_pOverlayQuadBounds;

    Ogre::MaterialPtr m_overlayMaterial; // +0x160, original shared owner
};

#endif
