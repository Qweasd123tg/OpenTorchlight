#include "PuzzleRandomizer.h"
#include "Level.h"

void CPuzzleRandomizer::addLevelListener()
{
    if (m_pResourceManager && m_pResourceManager->getLevel())
        m_pResourceManager->getLevel()->addUpdateObject(this);
}
void CPuzzleRandomizer::reset()
{
    m_bEnabled = true;
    m_bUnknown60 = false;
    m_bUnknown84 = false;
    m_bUnknown85 = false;
    m_bUnknown86 = false;
    m_bUnknown87 = false;
    m_bUnknown88 = false;
    m_bUnknown89 = false;
    addLevelListener();
    m_iUnknown8C = 3;
}
long long CPuzzleRandomizer::updateLevelObject(float, Ogre::Camera*, const Ogre::Vector3&)
{
    switch (m_iUnknown8C)
    {
    case 2:
        BroadcastEvent(55);
        m_iUnknown8C = 0;
        return 0;
    case 3:
        BroadcastEvent(9);
        m_iUnknown8C = 0;
        return 0;
    case 1:
        BroadcastEvent(54);
        reset();
        return 1;
    }
    m_iUnknown8C = 0;
    return 0;
}
