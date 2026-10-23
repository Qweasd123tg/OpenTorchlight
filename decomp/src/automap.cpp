
#include "Automap.h"
#include <OgreBillboardSet.h>
#include <map>
#include <string>

void CAutomap::setRevealed(int x, int z, float value)
{
    int index = z * m_iMapGridWidth + x;
    if (index < m_iMapGridWidth * m_iMapGridHeight && x >= 0 && z >= 0)
        if (value > m_pRevealedTiles[index])
        {
            m_pRevealedTiles[index] = value;
            m_bTilesChanged = true;
        }
}

void CAutomap::setFullscreen(bool fullscreen)
{
    m_bFullscreen = fullscreen;
    m_bTilesChanged = true;
    if (m_bVisible)
    {
        setVisible(false);
        setVisible(true);
    }
    zoom(0.0f);
}

void CAutomap::clear()
{
    for (int i = 0; i < m_iMapGridWidth * m_iMapGridHeight; ++i)
        m_pRevealedTiles[i] = 0.0f;
    m_bTilesChanged = true;
}

float CAutomap::getRevealed(int x, int z)
{
    int index = z * m_iMapGridWidth + x;
    if (index < m_iMapGridWidth * m_iMapGridHeight && x >= 0 && z >= 0)
        return m_pRevealedTiles[index];
    return 0.0f;
}

void CAutomap::setPetPosition(const Ogre::Vector3& position)
{
    m_pPetBillboard->setPosition(position);
}

void CAutomap::setPetVisible(bool visible)
{
    if (!visible)
        m_pPetBillboard->setPosition(1000.0f, -1000.0f, 1000.0f);
}

void CAutomap::clearNPCIcons()
{
    for (unsigned int i = 0; i < m_vNPCBillboards.size(); ++i)
        m_pTileBillboardSet->removeBillboard(m_vNPCBillboards[i]);
    m_vNPCBillboards.clear();
    m_vNPCRevealValues.clear();
    m_hiddenNPCBillboards.clear();
    m_bTilesChanged = true;
}

void CAutomap::setNPCBillboardVisible(Ogre::Billboard* billboard, bool visible)
{
    int index = m_hiddenNPCBillboards.find(billboard);
    if (visible)
    {
        if (index != -1)
        {
            m_hiddenNPCBillboards.remove(billboard);
            m_bTilesChanged = true;
        }
    }
    else if (index == -1)
    {
        m_hiddenNPCBillboards.add(billboard);
        m_bTilesChanged = true;
    }
}

void CAutomap::finalize()
{
    m_iMapGridWidth = int((m_maximumX - m_minimumX) * 0.25f);
    if (m_iMapGridWidth > 4)
        m_iMapGridWidth += 4;
    m_iMapGridHeight = int((m_maximumZ - m_minimumZ) * 0.25f);
    if (m_iMapGridWidth > 4)
        m_iMapGridHeight += 4;
    if (m_pRevealedTiles)
        delete[] m_pRevealedTiles;
    m_pRevealedTiles = new float[m_iMapGridWidth * m_iMapGridHeight];
    clear();
    if (m_bFullMap)
    {
        for (int i = 0; i < m_iMapGridWidth * m_iMapGridHeight; ++i)
            m_pRevealedTiles[i] = 1.0f;
        unsigned int count = m_vMapTileBillboards.size();
        for (unsigned int i = 0; i < count; ++i)
            m_vMapTileBillboards[i]->setColour(Ogre::ColourValue(1, 1, 1, 1));
        count = m_vNPCBillboards.size();
        for (unsigned int i = 0; i < count; ++i)
            m_vNPCBillboards[i]->setColour(Ogre::ColourValue(1, 1, 1, 1));
        m_vMapTileBillboards.clear();
        m_vNPCBillboards.clear();
    }
}

void CAutomap::setPlayerPosition(const Ogre::Vector3& position)
{
    m_pPlayerBillboard->setPosition(position);
    float x = (position.x - m_minimumX) * 0.25f - 3.0f;
    float z = (position.z - m_minimumZ) * 0.25f - 3.0f;
    for (int i = int(x); float(i) < x + 6.0f; ++i)
        for (int j = int(z); float(j) < z + 6.0f; ++j)
            if (float(i) > x && float(j) > z &&
                float(i) < x + 5.0f && float(j) < z + 5.0f)
                setRevealed(i, j, 1.0f);
            else
                setRevealed(i, j, 0.6f);
}

#include "MasterResourceManager.h"
#include "Settings.h"
#include <OgreCamera.h>
#include <algorithm>
extern unsigned int KSETTINGS_F_AUTOMAP_ZOOM;
void CAutomap::zoom(float delta)
{
    m_zoom += delta;
    m_zoom = m_zoom>60.0f?60.0f:std::max(m_zoom,20.0f);
    float extent=m_zoom, aspect=1.0f;
    if(m_bFullscreen){extent*=5.0f;aspect=m_fullMapHeight/m_fullMapWidth;}
    m_pCamera->setFrustumExtents(-extent,extent,extent*aspect,-extent*aspect);
    CMasterResourceManager::getSingleton()->m_pSettings->SetFloat(KSETTINGS_F_AUTOMAP_ZOOM,m_zoom);
}
void CAutomap::update(const Ogre::Vector3& position,float elapsed)
{
    m_pCamera->setPosition(position+Ogre::Vector3::UNIT_Y*m_zoom*(m_bFullscreen?5.0f:1.0f));
    if(!m_bTilesChanged || !m_bVisible)return;
    m_bTilesChanged=false;
    for(unsigned i=0;i<m_vMapTileBillboards.size();++i){
        if(m_vMapTileRevealValues[i]==100.0f)continue;
        float x=(m_vMapTileBillboards[i]->getPosition().x-m_minimumX)*.25f;
        float z=(m_vMapTileBillboards[i]->getPosition().z-m_minimumZ)*.25f;
        int ix=int(x),iz=int(z);
        float target=getRevealed(ix,iz);
        if(!m_bFullMap && m_iMapGridWidth>3 && !(target>0)){
            if(m_vMapTileRevealValues[i]!=0){m_vMapTileBillboards[i]->setColour(Ogre::ColourValue(0,0,0,0));m_vMapTileRevealValues[i]=0;}
        }else if(m_vMapTileRevealValues[i]!=target){
            m_vMapTileRevealValues[i]+=elapsed+elapsed;
            m_vMapTileRevealValues[i]=std::min(m_vMapTileRevealValues[i],getRevealed(ix,iz));
            if(m_vMapTileRevealValues[i]!=getRevealed(ix,iz))m_bTilesChanged=true;
            m_vMapTileBillboards[i]->setColour(Ogre::ColourValue(1,1,1,m_vMapTileRevealValues[i]));
        }
    }
    for(unsigned i=0;i<m_vNPCBillboards.size();++i){
        float x=m_vNPCBillboards[i]->getPosition().x;
        float minX=m_minimumX;
        float z=m_vNPCBillboards[i]->getPosition().z;
        float minZ=m_minimumZ;
        bool hidden=m_hiddenNPCBillboards.find(m_vNPCBillboards[i])!=-1;
        if(!hidden && !m_bFullMap && m_iMapGridWidth>3 && getRevealed(int((x-minX)*.25f),int((z-minZ)*.25f))==0)hidden=true;
        if(hidden){if(m_vNPCRevealValues[i]!=0){m_vNPCBillboards[i]->setColour(Ogre::ColourValue(0,0,0,0));m_vNPCRevealValues[i]=0;}}
        else if(m_vNPCRevealValues[i]!=1){m_vNPCRevealValues[i]+=elapsed+elapsed;m_vNPCRevealValues[i]=std::min(m_vNPCRevealValues[i],1.0f);if(m_vNPCRevealValues[i]!=1)m_bTilesChanged=true;m_vNPCBillboards[i]->setColour(Ogre::ColourValue(1,1,1,m_vNPCRevealValues[i]));}
    }
}

#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <OgreRenderTarget.h>
#include "OgreUtilities.h"
void CAutomap::setVisible(bool visible)
{
    if(visible==m_bVisible)return;
    m_bTilesChanged=true;
    if(!visible){
        if(m_viewport){CMasterResourceManager::getSingleton()->m_renderTarget->removeViewport(2);m_viewport=NULL;}
    }else{
        if(!m_viewport){
            float width=float(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_RES_WIDTH));
            float height=float(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_RES_HEIGHT));
            m_viewport=CMasterResourceManager::getSingleton()->m_renderTarget->addViewport(m_pCamera,2,0,0,1,1);
            float ratio=CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_YRATIO);
            if(m_bFullscreen){
                float w=m_fullMapWidth*ratio,h=m_fullMapHeight*ratio;
                m_viewport->setDimensions((width*.5f+w*-.5f)/width,(height*.5f+h*-.5f)/height,w/width,h/height);
                m_pCullQuad->setVisible(false,true);m_pOverlayQuad->setVisible(false,true);
            }else{
                float size=m_panelSize*ratio;
                m_viewport->setDimensions((width-size)/width,0.0f/height,size/width,size/height);
                m_pCullQuad->setVisible(true,true);m_pOverlayQuad->setVisible(true,true);
            }
            m_viewport->setBackgroundColour(Ogre::ColourValue(0,0,0,1));
            m_viewport->setClearEveryFrame(true,2);
            int actualWidth=m_viewport->getActualWidth(),actualHeight=m_viewport->getActualHeight();
            m_pCamera->setAspectRatio(float(actualWidth)/float(actualHeight));
            m_viewport->setCamera(m_pCamera);
        }
        zoom(0);
    }
    m_bVisible=visible;
}
CAutomap::~CAutomap()
{
    if(m_pRevealedTiles)delete[] m_pRevealedTiles;
    m_hiddenNPCBillboards.clear();
    setVisible(false);
    m_pPlayerBillboard=NULL;m_pPetBillboard=NULL;
    m_pSceneManager->destroyCamera(m_pCamera);
    OGRE_UTILITIES::removeChildFromParentNode(m_pTileSceneNode);
    m_pTileSceneNode->detachObject(m_pTileBillboardSet);
    m_pSceneManager->destroyBillboardSet(m_pTileBillboardSet);
    OGRE_UTILITIES::removeChildFromParentNode(m_pCullQuad);
    OGRE_UTILITIES::removeChildFromParentNode(m_pOverlayQuad);
    m_pCullQuad->detachAllObjects();m_pOverlayQuad->detachAllObjects();
    OGRE_UTILITIES::removeChildFromParentNode(m_pStaticTileSceneNode);
    m_pStaticTileSceneNode->detachObject(m_pStaticTileBillboardSet);
    m_pSceneManager->destroyBillboardSet(m_pStaticTileBillboardSet);
}

#include <algorithm>
#include <cmath>

Ogre::Billboard* CAutomap::addTile(int type, const Ogre::Vector3& position,
                                  const Ogre::Vector3& direction,
                                  bool animated, bool npc)
{
    Ogre::Billboard* billboard = m_pTileBillboardSet->createBillboard(position, Ogre::ColourValue::White);
    m_minimumX = std::min(position.x, m_minimumX);
    m_maximumX = std::max(position.x, m_maximumX);
    m_minimumZ = std::min(position.z, m_minimumZ);
    m_maximumZ = std::max(position.z, m_maximumZ);
    --type;
    if (type >= 34)
        type = 5;
    float top = KAutomapTileY[type] * 0.001953125f;
    float left = KAutomapTileX[type] * 0.001953125f;
    float size = KAutomapSize[type];
    float extent = size * 0.001953125f;
    billboard->setTexcoordRect(left + 0.005f, top + 0.005f,
                               left + extent - 0.005f, top + extent - 0.005f);
    float rotation = static_cast<float>(std::atan2(static_cast<double>(direction.x),
                                                  static_cast<double>(direction.z)));
    rotation += static_cast<float>(KAutomapTileRotation[type] * 0.01745329252);
    billboard->setRotation(Ogre::Radian(rotation));
    float dimension = 4.0f * KAutomapTileScale[type] * size * 0.03125f;
    billboard->setDimensions(dimension, dimension);
    if (npc) {
        m_vNPCBillboards.push_back(billboard);
        if (animated) {
            billboard->setColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 0.0f));
            m_vNPCRevealValues.push_back(0.0f);
        } else {
            m_vNPCRevealValues.push_back(1.0f);
        }
    } else if (animated) {
        billboard->setColour(Ogre::ColourValue(0.0f, 0.0f, 0.0f, 0.0f));
        m_vMapTileBillboards.push_back(billboard);
        m_vMapTileRevealValues.push_back(0.0f);
    }
    return billboard;
}

#include "FileSystem.h"
#include <OgreMaterialManager.h>
#include <OgreTechnique.h>
#include <OgrePass.h>
#include <OgreTextureUnitState.h>
#include <OgreResourceGroupManager.h>

void CAutomap::setFullMap(std::wstring textureName, float width, float height,
                          Ogre::Vector3& position, Ogre::Vector3& direction,
                          float angle)
{
    m_bFullMap = true;
    if (Ogre::MaterialManager::getSingleton().resourceExists("AutomapStatic")) {
        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("AutomapStatic");
        CFileInfo info;
        CFileSystem::getSingleton()->getFileInfo(textureName, info, false, true, false);
        material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(info.m_sResourceName, Ogre::TEX_TYPE_2D);
    } else {
        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("AutomapStatic", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
        material->setReceiveShadows(false);
        material->setLightingEnabled(false);
        Ogre::Pass* pass = material->getTechnique(0)->getPass(0);
        pass->setDepthCheckEnabled(true);
        pass->setSelfIllumination(0.0f, 0.0f, 0.0f);
        pass->setDepthWriteEnabled(false);
        material->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        material->setCullingMode(Ogre::CULL_NONE);
        CFileInfo info;
        CFileSystem::getSingleton()->getFileInfo(textureName, info, false, true, false);
        pass->createTextureUnitState(info.m_sResourceName)->setTextureFiltering(Ogre::FO_LINEAR, Ogre::FO_LINEAR, Ogre::FO_NONE);
    }
    m_pStaticTileBillboardSet->setMaterialName("AutomapStatic");
    m_pStaticTileBillboardSet->setDefaultWidth(width);
    m_pStaticTileBillboardSet->setDefaultHeight(height);
    Ogre::Billboard* billboard = m_pStaticTileBillboardSet->createBillboard(position, Ogre::ColourValue::White);
    billboard->setTexcoordRect(1.0f, 0.0f, 0.0f, 1.0f);
    billboard->setDimensions(width, height);
    float rotation = static_cast<float>(std::atan2(static_cast<double>(direction.x), static_cast<double>(direction.z)));
    rotation += static_cast<float>(angle * 0.01745329252);
    billboard->setRotation(Ogre::Radian(rotation));
    billboard->setColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f, 1.0f));
    m_vMapTileBillboards.push_back(billboard);
    m_vMapTileRevealValues.push_back(100.0f);
    m_bTilesChanged = true;
}
