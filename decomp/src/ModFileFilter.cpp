#include "EmptyStrings.h"
#include "GameVariables.h"
#include "ModFileFilter.h"

unsigned int CModFileFilter::getNumberOfActiveMods()
{
    unsigned int count = 0;

    for (unsigned int i = 0; i < m_Mods.size(); ++i) {
        const unsigned char* data =
            reinterpret_cast<const unsigned char*>(m_Mods[i]);
        const unsigned int priority =
            static_cast<unsigned int>(data[0x74]) |
            (static_cast<unsigned int>(data[0x75]) << 8) |
            (static_cast<unsigned int>(data[0x76]) << 16) |
            (static_cast<unsigned int>(data[0x77]) << 24);

        if (data[0x70] != 0 && priority < 0x80000000u)
            ++count;
    }

    return count;
}
