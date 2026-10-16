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
bool CPuzzleRandomizer::updateLevelObject(float, Ogre::Camera*, const Ogre::Vector3&)
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

#include "Utilities.h"
#include <OgreLogManager.h>

void CPuzzleRandomizer::setActiveInputs(unsigned int count)
{
    if (count < 2) count = 2;
    else if (count >= 6) count = 3;
    m_iActiveInputs = count;
    for (unsigned int i = 0; i < 6; ++i) {
        m_inputOrder[i] = i;
        m_inputTriggered[i] = false;
    }
    for (unsigned int pass = 0; pass < 5; ++pass) {
        for (unsigned int i = 0; i < static_cast<unsigned int>(m_iActiveInputs); ++i) {
            unsigned int index = UTILITIES::randomIntegerBetweenVolatile(0, m_iActiveInputs - 1);
            unsigned int value = m_inputOrder[i];
            m_inputOrder[i] = m_inputOrder[index];
            m_inputOrder[index] = value;
        }
    }
}

CPuzzleRandomizer::~CPuzzleRandomizer()
{
}

CPuzzleRandomizer::CPuzzleRandomizer(CResourceManager* resources)
    : CEditorBaseObject(), iLevelUpdate(), m_bUnknown60(false), m_iActiveInputs(3),
      m_bEnabled(true), m_iUnknown8C(0), m_pResourceManager(resources)
{
    for (unsigned int i = 0; i < 6; ++i) {
        m_inputOrder[i] = i;
        m_inputTriggered[i] = false;
    }
    setActiveInputs(m_iActiveInputs);
}

void CPuzzleRandomizer::trigger(EPUZZLE_INPUTS input)
{
    if (m_bUnknown60 || !m_bEnabled)
        return;
    if (static_cast<unsigned int>(input) >= static_cast<unsigned int>(m_iActiveInputs)) {
        Ogre::LogManager::getSingleton().logMessage("A trigger occured on the puzzle object but the puzzle object has fewer inputs allowed then was triggered.", Ogre::LML_CRITICAL, false);
        return;
    }
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_iActiveInputs); ++i) {
        if (!m_inputTriggered[i]) {
            if (static_cast<unsigned int>(input) != m_inputOrder[i]) {
                addLevelListener();
                m_iUnknown8C = 1;
                return;
            }
            m_inputTriggered[i] = true;
            if (i != static_cast<unsigned int>(m_iActiveInputs - 1))
                return;
            break;
        }
    }
    addLevelListener();
    m_bUnknown60 = true;
    m_iUnknown8C = 2;
}
