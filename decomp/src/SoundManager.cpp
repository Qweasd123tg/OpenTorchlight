#include "EmptyStrings.h"
#include "SoundInstance.h"
#include "SoundManager.h"
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
    : CRunicCore(), m_iUnknown10(0), m_iUnknown14(0), m_fileField2C(-1),
      m_pendingSounds(25), m_bUnknown6A8(false), m_bUnknown6A9(false),
      m_pDynamicPropertyFile(NULL), m_iUnknown6B8(0), m_iUnknown6C0(0),
      m_bUnknown6C8(b), m_iUnknown6D0(NULL), m_iUnknown6F0(-1), m_iUnknown6F4(0),
      m_sUnknown6F8()
{
    m_iUnknown18 = NULL;
    m_fileField20 = 0;
    m_fileField24 = 0;
    m_fileField28 = 0;
    for (unsigned int i=0; i<64; ++i) m_channels[i].m_iUnknown10=0;
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


// Imported source candidates; historical status is not fresh acceptance.
FMOD_RESULT CSoundManager::fmodFileReadCallback(void* handle, void* buffer, unsigned int length, unsigned int* bytesRead, void* userData)
{
    *bytesRead = static_cast<CSoundInstance*>(handle)->m_stream->read(buffer, length);
    return *bytesRead ? FMOD_OK : static_cast<FMOD_RESULT>(22);
}

FMOD_RESULT CSoundManager::fmodFileSeekCallback(void* handle, unsigned int position, void* userData)
{
    if (handle && !static_cast<CSoundInstance*>(handle)->m_stream.isNull()) {
        static_cast<CSoundInstance*>(handle)->m_stream->seek(position);
        return FMOD_OK;
    }
    return static_cast<FMOD_RESULT>(20);
}

std::wstring CSoundManager::getMusicFilePlaying()
{
    if (m_iUnknown6D0) return m_iUnknown6D0->m_soundName;
    return EMPTY_WSTRING;
}

FMOD::SoundGroup* CSoundManager::createSoundGroup(std::string name)
{
    if (!m_iUnknown18) return NULL;
    FMOD::SoundGroup* group;
    m_iUnknown18->createSoundGroup(name.c_str(), &group);
    return group;
}

void CSoundManager::updateAudioLevels(float soundVolume, float musicVolume, bool soundMute, bool musicMute)
{
    if (!m_bUnknown6A8) return;
    FMOD::SoundGroup* sounds;
    if (m_iUnknown18->getMasterSoundGroup(&sounds) == FMOD_OK) sounds->setVolume(soundVolume);
    FMOD::ChannelGroup* channels;
    if (m_iUnknown18->getMasterChannelGroup(&channels) == FMOD_OK) { channels->setVolume(soundVolume); channels->setMute(soundMute); }
    if (m_iUnknown6D0) {
        m_iUnknown6E0->setVolume(musicVolume);
        if (m_iUnknown6D8) {
            FMOD::Channel* channel;
            m_iUnknown18->getChannel(m_iUnknown6D8, &channel);
            channel->setMute(musicMute);
        }
    }
}

void CSoundInstance::clear()
{
    m_soundName.clear();
    m_stream.setNull();
    m_pSound->release();
    m_pSound = NULL;
    m_soundType = static_cast<SOUND_TYPE>(0);
    m_referenceCount = 0;
    m_pSoundData = NULL;
}

 CSoundInstance::~CSoundInstance()
{
    if (m_pSound) { m_pSound->release(); m_pSound = NULL; }
}
