#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "SoundInstance.h"
#include "SoundManager.h"
#include "ChannelInstance.h"
#include "RunicCore.h"

int CSoundManager::getNumberOfChannelsPlaying()
{
    if (m_iUnknown18 != 0) {
        return m_iUnknown14;
    }
    return 0;
}

void CSoundManager::incrementSoundBank()
{
    ++m_iUnknown10;
}

long long CSoundManager::fmodFileCloseCallback(void*, void*)
{
    struct Releaseable
    {
        virtual ~Releaseable() {}
        virtual void release() {}
    };

    if (m_pUnknown20 != 0)
    {
        if (m_pUnknown28 != 0)
        {
            if (--*static_cast<int *>(m_pUnknown28) == 0)
                reinterpret_cast<Releaseable *>(&m_iUnknown18)->release();
        }
        m_pUnknown20 = 0;
        m_pUnknown28 = 0;
    }
    return 0;
}

namespace FMOD
{
    class Sound
    {
    public:
        int getMode(unsigned int* mode);
    };
}

unsigned int CSoundManager::soundLoops(CSoundInstance* sound)
{
    unsigned int mode;

    if (sound != NULL && sound->m_pSound != NULL)
    {
        sound->m_pSound->getMode(&mode);
        return (mode >> 1) & 1;
    }
    return 0;
}

void CSoundManager::stopMusic()
{
    if (m_iUnknown6D0 != 0) {
        if (m_iUnknown6D8 != -1)
            stopSound(m_iUnknown6D8);
        releaseSound((CSoundInstance*)m_iUnknown6D0);
        m_iUnknown6D0 = 0;
    }
}

CSoundManager::CSoundManager(bool b)
    : CRunicCore(),
      m_sUnknown6F8()
{
    m_iUnknown10 = 0;
    m_iUnknown14 = 0;

    m_pUnknown30 = NULL;
    m_iUnknown38 = 0;
    m_pUnknown40 = NULL;
    m_pUnknown48 = NULL;
    m_iUnknown50 = 0;
    m_pUnknown58 = NULL;
    m_iUnknown60 = 0;
    m_iUnknown68 = 0;
    m_pUnknown70 = NULL;
    m_pUnknown78 = NULL;
    m_iUnknown80 = 0;
    m_pUnknown88 = NULL;

    for (unsigned int i = 0; i < sizeof(m_Unknown90); ++i)
        m_Unknown90[i] = 0;
    *reinterpret_cast<int *>(reinterpret_cast<char *>(m_Unknown90) + 0x10) = 25;

    for (int i = 0; i < 64; ++i)
    {
        new (reinterpret_cast<void *>(
            reinterpret_cast<char *>(&m_UnknownA8) + i * sizeof(CChannelInstance)))
            CChannelInstance();
    }

    m_bUnknown6A8 = false;
    m_bUnknown6A9 = false;
    m_pDynamicPropertyFile = NULL;
    m_iUnknown6B8 = 0;
    m_iUnknown6C0 = 0;
    m_bUnknown6C8 = b;
    m_iUnknown6D0 = 0;
    m_iUnknown6F0 = -1;
    m_iUnknown6F4 = 0;

    m_iUnknown18 = 0;
    m_pUnknown20 = NULL;
    m_pUnknown28 = NULL;
    *reinterpret_cast<int *>(
        reinterpret_cast<char *>(&m_pUnknown28) + 4) = -1;
}

extern "C" int FMOD_Memory_GetStats(int *currentAllocated, int *maxAllocated, bool blocking);

int CSoundManager::getMemoryInUse()
{
    int currentAllocated = 0;
    int maxAllocated = 0;

    if (m_iUnknown18 != 0)
        FMOD_Memory_GetStats(&currentAllocated, &maxAllocated, true);

    return currentAllocated;
}
