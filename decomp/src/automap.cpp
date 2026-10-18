
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
