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

void CSoundManager::releaseSound(CSoundInstance* sound)
{
    if (sound && --sound->m_referenceCount == 0 && !sound->m_stream.isNull())
    {
        m_pendingSounds.remove(sound);
        delete sound;
    }
}

void CSoundManager::stopSound(int index)
{
    m_iUnknown14 = static_cast<int>(static_cast<unsigned int>(m_iUnknown14) - 1u);
    if (m_iUnknown14 == -1) m_iUnknown14 = 0;
    if (index == -1) return;
    if (index > 63) return;
    {
        FMOD::Channel* channel;
        m_iUnknown18->getChannel(index, &channel);
        channel->stop();
        m_channels[index].m_iUnknown10 = 0;
    }
}

void CSoundManager::stopAllSounds()
{
    m_iUnknown14 = 0;
    stopSound(m_iUnknown6F0);
    for (int i = 0; i < 64; ++i)
    {
        FMOD::Channel* channel;
        if (m_iUnknown18->getChannel(i, &channel) == FMOD_OK && channel)
            channel->stop();
        m_channels[i].m_iUnknown10 = 0;
    }
}

void CSoundManager::set3DMinMaxDistance(int index, float minimum, float maximum)
{
    if (index == -1) return;
    if (index > 63) return;
    {
        FMOD::Channel* channel;
        if (m_iUnknown18->getChannel(index, &channel) == FMOD_OK)
            channel->set3DMinMaxDistance(minimum, maximum);
    }
}

bool CSoundManager::isChannelPlaying(int index)
{
    if (index == -1) return 0;
    if (index > 63) return 0;
    {
        FMOD::Channel* channel;
        FMOD_RESULT result = m_iUnknown18->getChannel(index, &channel);
        bool playing = false;
        if (result == FMOD_OK)
        {
            channel->isPlaying(&playing);
            return playing;
        }
    }
    return 0;
}

void CSoundManager::setSoundVolume(int index, float volume)
{
    if (index == -1) return;
    if (index > 63) return;
    {
        FMOD::Channel* channel;
        if (m_iUnknown18->getChannel(index, &channel) == FMOD_OK)
            channel->setVolume(volume);
    }
}

void CSoundManager::setPauseSound(int index, bool paused)
{
    if (index == -1) return;
    if (index > 63) return;
    {
        FMOD::Channel* channel;
        if (m_iUnknown18->getChannel(index, &channel) == FMOD_OK)
            channel->setPaused(paused);
    }
}

#include "SoundInstance.h"
#include <OgreLogManager.h>
#include <OgreStringConverter.h>

CSoundInstance* CSoundManager::findSound(std::wstring& name, SOUND_TYPE type, bool loop, float volume, float)
{
    for (unsigned int i = 0; i < m_pendingSounds.size(); ++i)
        if (m_pendingSounds[i]->m_soundType == type &&
            name == m_pendingSounds[i]->m_soundName &&
            m_pendingSounds[i]->m_loop == loop &&
            volume == m_pendingSounds[i]->m_volume)
            return m_pendingSounds[i];
    return 0;
}

void CSoundManager::queueSound(int bank, CSoundInstance* sound, float volume, float delay)
{
    if (m_fileField2C == bank && isChannelPlaying(m_iUnknown6F0))
        return;
    for (unsigned int i = 0; i < m_soundList0.size(); ++i)
        if (m_soundList0[i] == bank)
            return;
    ++sound->m_referenceCount;
    m_soundList1.push_back(sound);
    m_soundList2.push_back(volume);
    m_soundList3.push_back(delay);
    m_soundList0.push_back(bank);
}

void CSoundManager::releaseUnusedSounds()
{
    stopSound(m_iUnknown6F0);
    m_iUnknown6F0 = -1;
    for (unsigned int i = 0; i < m_soundList1.size(); ++i)
        --m_soundList1[i]->m_referenceCount;
    m_soundList1.clear();
    m_soundList0.clear();
    m_soundList2.clear();
    m_soundList3.clear();
    int released = 0;
    for (unsigned int i = 0; i < m_pendingSounds.size(); ++i) {
        CSoundInstance* sound = m_pendingSounds[i];
        if (static_cast<int>(sound->m_referenceCount) <= 0) {
            m_pendingSounds.remove(sound);
            delete sound;
            ++released;
            i = 0;
        }
    }
    Ogre::LogManager::getSingleton().logMessage("Released sounds : " + Ogre::StringConverter::toString(released));
}
