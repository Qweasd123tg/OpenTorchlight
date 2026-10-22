#include "EmptyStrings.h"
#include "ColorWrapper.h"
#include <OgreColourValue.h>
#include <vector>

namespace ParticleUniverse {
class ColourAffector
{
public:
    void clearColours();
    void addColour(float time, const Ogre::ColourValue& colour);
    void getColourList(std::vector<float>& times, std::vector<Ogre::ColourValue>& colours);
};
}

CColorWrapper::CColorWrapper(CResourceManager* resources)
    : CAffectorWrapper(resources, "Colour"), m_colors(10)
{
    reinterpret_cast<ParticleUniverse::ColourAffector*>(m_pAffector)->addColour(
        0.0f, Ogre::ColourValue(1.0f, 1.0f, 1.0f, 1.0f));
}

void CColorWrapper::setColors(float* colors, unsigned int numberOfColors)
{
    if (!colors)
        return;

    reinterpret_cast<ParticleUniverse::ColourAffector*>(m_pAffector)->clearColours();
    for (unsigned int i = 0; i < numberOfColors; i += 5)
    {
        Ogre::ColourValue colour(colors[i + 1], colors[i + 2], colors[i + 3], colors[i + 4]);
        reinterpret_cast<ParticleUniverse::ColourAffector*>(m_pAffector)->addColour(colors[i], colour);
    }
}

float* CColorWrapper::getColors(unsigned int& numberOfColors)
{
    std::vector<Ogre::ColourValue> colours;
    std::vector<float> times;
    reinterpret_cast<ParticleUniverse::ColourAffector*>(m_pAffector)->getColourList(times, colours);

    m_colors.clear();
    for (unsigned int i = 0; i < times.size(); ++i)
    {
        m_colors.add(times[i]);
        m_colors.add(colours[i].r);
        m_colors.add(colours[i].g);
        m_colors.add(colours[i].b);
        m_colors.add(colours[i].a);
    }
    numberOfColors = m_colors.size();
    return &m_colors[0];
}

CColorWrapper::~CColorWrapper()
{
}

// The non-virtual thunk is compiler-generated and has no C++98 source definition.
