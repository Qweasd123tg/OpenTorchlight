#include <algorithm>
#include <cmath>
#include "LevelTemplateData.h"
#include "Utilities.h"

CChunk* CLevelTemplateData::getRandomChunk(unsigned int index)
{
    return m_chunks[m_chunkRandomizers[index]->getRandom()];
}
