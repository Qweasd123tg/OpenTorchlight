#ifndef AUTOMAP_H
#define AUTOMAP_H

#include <OgreBillboard.h>
#include <OgreSceneManager.h>
#include <OgreVector3.h>

#include <string>

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
    int getRevealed(int x, int z);
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
    Ogre::SceneNode* m_pSceneRoot;
    Ogre::BillboardSet* m_pTileBillboardSet;
    Ogre::BillboardSet* m_pStaticTileBillboardSet;
    Ogre::SceneNode* m_pTileSceneNode;
    Ogre::SceneNode* m_pStaticTileSceneNode;
    Ogre::Camera* m_pCamera;
    void* m_pReserved;

    unsigned char m_ViewportState[0x18] __attribute__((aligned(8)));
    bool m_bVisible;
    unsigned char m_gap69[7];
    Ogre::Billboard* m_pPlayerBillboard;

    unsigned char m_PetIconAndBoundsState[0x18] __attribute__((aligned(8)));
    int m_iMapGridWidth;
    int m_iMapGridHeight;
    float* m_pRevealedTiles;
    bool m_bTilesChanged;
    bool m_bFullscreen;
    bool m_bFullMap;
    unsigned char m_gapA3[5];

    TArrayList<Ogre::Billboard*> m_vMapTileBillboards;
    TArrayList<float> m_vMapTileRevealValues;
    TArrayList<Ogre::Billboard*> m_vNPCBillboards;
    TArrayList<float> m_vNPCRevealValues;

    unsigned char m_HiddenNPCBillboardListState[0x18]
        __attribute__((aligned(8)));

    Ogre::SceneNode* m_pCullQuad;
    Ogre::Rectangle2D* m_pCullQuadBounds;

    void* m_pCullMaterialControl;
    Ogre::Material* m_pCullMaterial;
    void* m_pCullMaterialRefCount;
    int m_iCullMaterialState;
    unsigned char m_gap14C[4];

    Ogre::SceneNode* m_pOverlayQuad;
    Ogre::Rectangle2D* m_pOverlayQuadBounds;

    void* m_pOverlayMaterialControl;
    Ogre::Material* m_pOverlayMaterial;
    void* m_pOverlayMaterialRefCount;
    int m_iOverlayMaterialState;
};

#endif
