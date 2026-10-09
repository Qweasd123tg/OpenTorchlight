
#include "Automap.h"
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
