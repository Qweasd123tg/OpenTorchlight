#include <algorithm>
#include <cmath>
#include "LevelTemplateData.h"
#include "Utilities.h"

CChunk* CLevelTemplateData::getRandomChunk(unsigned int index)
{
    return m_chunks[m_chunkRandomizers[index]->getRandom()];
}

CLevelLayout* CLevelTemplateData::getRandomLayout()
{
    if (!m_layoutRandomizer || !m_layoutRandomizer->hasChoices()) return NULL;
    return m_layouts[m_layoutRandomizer->getRandom()];
}

void CLevelTemplateData::resetOdds()
{
    for (unsigned int i = 0; i < m_chunkRandomizers.size(); ++i) {
        int count = static_cast<int>(m_chunkRandomizers[i]->getChoiceCount());
        for (int j = 0; j < count; ++j) {
            int choice = m_chunkRandomizers[i]->getChoice(j);
            m_chunkRandomizers[i]->setChoiceOdds(choice, m_chunks[choice]->m_odds);
        }
    }
}

unsigned int CLevelTemplateData::getNumberOfUnitsToCreate(ELEVELLAYOUT_CREATION creation, unsigned int area)
{
    float minimum = m_countRanges[creation].minimum;
    float maximum = m_countRanges[creation].maximum;
    if (!(minimum <= 0.0f) || !(maximum <= 0.0f)) {
        float low = maximum < minimum ? maximum : minimum;
        float high = maximum > minimum ? maximum : minimum;
        return UTILITIES::randomIntegerBetween(static_cast<int>(low), static_cast<int>(high));
    }
    minimum = m_densityRanges[creation].minimum;
    maximum = m_densityRanges[creation].maximum;
    if (!(minimum <= 0.0f) && !(maximum <= 0.0f)) {
        float scale = static_cast<float>(area) / 6.5f;
        float low = maximum < minimum ? maximum : minimum;
        float high = maximum > minimum ? maximum : minimum;
        return static_cast<unsigned int>(::ceilf(UTILITIES::randomBetween(low * scale, high * scale)));
    }
    return 0;
}
