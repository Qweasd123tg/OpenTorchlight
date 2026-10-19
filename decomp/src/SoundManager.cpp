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

FMOD_RESULT CSoundManager::fmodFileCloseCallback(void* handle, void*)
{
    static_cast<CSoundInstance*>(handle)->m_stream.setNull();
    return FMOD_OK;
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


CSoundManager::~CSoundManager()
{
    if (m_iUnknown6B8) m_iUnknown6B8->release();
    if (m_iUnknown6C0) m_iUnknown6C0->release();
    stopMusic();
    stopSound(m_iUnknown6F0);
    m_iUnknown6F0 = -1;
    for (unsigned int i = 0; i < m_soundList1.size(); ++i)
        --m_soundList1[i]->m_referenceCount;
    m_soundList1.clear();
    m_soundList0.clear();
    m_soundList2.clear();
    m_soundList3.clear();
    m_pendingSounds.deleteAll();
    if (m_iUnknown6E0) m_iUnknown6E0->release();
    if (m_iUnknown6E8) m_iUnknown6E8->release();
    if (m_iUnknown18) m_iUnknown18->release();
}

void CSoundManager::update(Ogre::SceneNode* node, const Ogre::Vector3& position, float elapsed)
{
    if (!m_bUnknown6A8) return;
    m_iUnknown10 = 0;
    Ogre::Vector3 forward = node->getOrientation().zAxis();
    Ogre::Vector3 up = node->getOrientation().yAxis();
    m_iUnknown18->update();
    m_listenerX = position.x;
    m_listenerY = position.y;
    m_listenerZ = position.z;
    if (m_soundList2.empty())
    {
        if (!isChannelPlaying(m_iUnknown6F0))
        {
            m_queueTimer = 0.0f;
            m_iUnknown6F0 = -1;
        }
    }
    else if (m_iUnknown6F0 == -1 || !isChannelPlaying(m_iUnknown6F0))
    {
        m_queueTimer += elapsed;
        if (m_queueTimer >= m_soundList3[0])
        {
            m_queueTimer = 0.0f;
            stopSound(m_iUnknown6F0);
            m_iUnknown6F0 = playSound(m_soundList1[0],NULL,static_cast<int>(m_soundList2[0]),1.0f);
            --m_soundList1[0]->m_referenceCount;
            m_lastQueuedBank = m_soundList0[0];
            for (int i = 0; i < static_cast<int>(m_soundList0.size()) - 1; ++i)
            {
                m_soundList1[i] = m_soundList1[i+1];
                m_soundList2[i] = m_soundList2[i+1];
                m_soundList0[i] = m_soundList0[i+1];
                m_soundList3[i] = m_soundList3[i+1];
            }
            m_soundList1.pop_back();
            m_soundList2.pop_back();
            m_soundList0.pop_back();
            m_soundList3.pop_back();
        }
    }
}

#include "FileSystem.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
#include <OgreUTFString.h>
#include <OgreLogManager.h>

FMOD_RESULT CSoundManager::fmodFileOpenCallback(const char* filename,int,unsigned int* size,void** handle,void** userData)
{
    CSoundInstance* sound=reinterpret_cast<CSoundInstance*>(const_cast<char*>(filename));
    *handle=sound;
    *userData=NULL;
    std::wstring full=sound->m_soundName;
    std::wstring directory;
    std::wstring name;
    name=FILESYSTEM::GetFileName(full);
    directory=FILESYSTEM::RemoveFileName(full);
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(sound->m_soundName,info,false,true,false);
    sound->m_stream.setNull();
    sound->m_stream=CFileSystem::getSingleton()->getDataStream(info);
    if (!sound->m_stream.isNull()) {
        *size=sound->m_stream->size();
        return FMOD_OK;
    }
    *size=0;
    return static_cast<FMOD_RESULT>(23);
}

void CSoundManager::dumpSounds()
{
    for (unsigned int i=0;i<m_pendingSounds.size();++i)
        Ogre::LogManager::getSingleton().logMessage(static_cast<std::string>(Ogre::UTFString("Sound : ")+Ogre::UTFString(m_pendingSounds[i]->m_soundName)),Ogre::LML_CRITICAL);
}

float CSoundManager::playMusic(std::wstring& name,bool loop)
{
    stopMusic();
    name=STRINGS::StringUpper(name);
    if (name.find(L"MUSIC")!=std::wstring::npos)
        name=name.substr(name.find(L"MUSIC")+5,name.length()-name.find(L"MUSIC")+5);
    while (name[0]==L'.' || name[0]==L'/') name=name.substr(1,name.length()-1);
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(name,info,false,true,false);
    m_iUnknown6D0=createSound(info.m_sPath,static_cast<SOUND_TYPE>(loop?6:5),false,0.0f,0.0f);
    if (!m_iUnknown6D0) return 0.0f;
    m_iUnknown6D0->m_pSound->setSoundGroup(m_iUnknown6E0);
    m_iUnknown6D8=playSound(m_iUnknown6D0,NULL,-1,1.0f);
    if (m_iUnknown6D8==-1) return 0.0f;
    FMOD::Channel* channel;
    if (m_iUnknown18->getChannel(m_iUnknown6D8,&channel)==FMOD_OK)
        channel->setChannelGroup(m_iUnknown6E8);
    if (m_pDynamicPropertyFile) {
        bool musicMute=m_pDynamicPropertyFile->GetInt(KSETTINGS_MUSICMUTE)!=0;
        bool soundMute=m_pDynamicPropertyFile->GetInt(KSETTINGS_SOUNDMUTE)!=0;
        float music=m_pDynamicPropertyFile->GetFloat(KSETTINGS_F_MUSICVOLUME);
        float sound=m_pDynamicPropertyFile->GetFloat(KSETTINGS_F_SOUNDVOLUME);
        updateAudioLevels(sound,music,soundMute,musicMute);
    }
    return getSoundLength(m_iUnknown6D0);
}

#include "FmodErrors.h"

float CSoundManager::getSoundLength(CSoundInstance* instance)
{
    if (instance && instance->m_pSound) {
        unsigned int milliseconds;
        FMOD_RESULT result = instance->m_pSound->getLength(&milliseconds, 1);
        if (result == FMOD_OK)
            return static_cast<float>(milliseconds) / 1000.0f;
        const char* error = FMOD_ErrorString(result);
        std::string prefix("SoundManager::GetSoundLength could not get length  FMOD Error:");
        Ogre::LogManager::getSingleton().logMessage(prefix + error);
    }
    return 0.0f;
}

#include "MasterResourceManager.h"
#include "Console.h"
#include "Utilities.h"
#include <algorithm>
#include <OgreException.h>

int CSoundManager::playSound(CSoundInstance* instance, Ogre::SceneNode* node,
                            int requestedChannel, float volume)
{
    if (!(m_bUnknown6A9 && m_bUnknown6A8) && instance) {
        int type = static_cast<int>(instance->m_soundType);
        if (type != 4 && type != 2 && type != 6 && type != 5)
            return -1;
    }
    if (volume <= 0.0f) {
        if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SOUND_DEBUG))
            CMasterResourceManager::getSingleton()->m_console->addTextNoHistory(
                L"CULLED ZERO VOLUME SOUND : " + instance->m_soundName);
        return -1;
    }
    if (!instance)
        return -1;
    FMOD::Channel* channel;
    if (requestedChannel != -1 && requestedChannel <= 63 && m_channels[requestedChannel].m_iUnknown10 &&
        (static_cast<int>(instance->m_soundType) == 4 || static_cast<int>(instance->m_soundType) == 2 ||
         static_cast<int>(instance->m_soundType) == 6)) {
        if (m_iUnknown18->getChannel(requestedChannel, &channel) == FMOD_OK) {
            bool playing;
            FMOD_RESULT state = channel->isPlaying(&playing);
            ++m_iUnknown14;
            if (state == FMOD_OK && playing && m_channels[requestedChannel].m_iUnknown10 == node)
                return requestedChannel;
            stopSound(requestedChannel);
        }
    }
    FMOD_RESULT result = m_iUnknown18->playSound(FMOD_CHANNEL_FREE, instance->m_pSound, true, &channel);
    if (result != FMOD_OK) {
        const char* error = FMOD_ErrorString(result);
        std::string prefix("SoundManager::PlaySound could not play sound  FMOD Error:");
        Ogre::LogManager::getSingleton().logMessage(prefix + error);
        return -1;
    }
    ++m_iUnknown14;
    int channelIndex;
    channel->getIndex(&channelIndex);
    if (requestedChannel > 63) {
        channel->stop();
        return -1;
    }
    m_channels[channelIndex].m_iUnknown10 = node;
    channel->setVolume(std::min(volume + UTILITIES::randomBetweenVolatile(0.0f, instance->m_volume), 1.0f));
    channel->setPaused(false);
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SOUND_DEBUG)) {
        Ogre::UTFString text(L"PLAYING SOUND : " + instance->m_soundName + L" on channel ");
        text = text + Ogre::UTFString(STRINGS::GetValueAsString(channelIndex));
        CMasterResourceManager::getSingleton()->m_console->addTextNoHistory(text.asWStr());
    }
    return channelIndex;
}

CSoundInstance* CSoundManager::createSound(std::wstring name, SOUND_TYPE type, bool,
                                         float volume, float variance)
{
    if (!m_bUnknown6A8)
        return NULL;
    if (static_cast<int>(type) != 5 && static_cast<int>(type) != 6) {
        CSoundInstance* existing = findSound(name, type, false, volume, variance);
        if (existing) {
            ++existing->m_referenceCount;
            return existing;
        }
    }
    CSoundInstance* instance = new CSoundInstance;
    instance->m_soundName = name;
    instance->m_soundType = type;
    instance->m_loop = false;
    instance->m_volume = volume;
    instance->m_volumeVariance = 0;
    unsigned int flags = STRINGS::StringUpper(name).find(L".OGG") == std::wstring::npos ? 0x20 : 0x40;
    FMOD::Sound* sound;
    FMOD_RESULT result;
    switch (static_cast<int>(type)) {
    case 1: flags |= 0x1000010; break;
    case 2: flags |= 0x1000012; break;
    case 3: flags |= 0x1000009; break;
    case 4: flags |= 0x100000a; break;
    case 5: flags |= 0x1000008; break;
    case 6: flags |= 0x100000a; break;
    default:
        delete instance;
        Ogre::LogManager::getSingleton().logMessage(static_cast<std::string>(
            Ogre::UTFString("SoundManager::CreateSound could not load sound '") +
            Ogre::UTFString(name) + Ogre::UTFString("' (invalid soundType)")));
        return NULL;
    }
    if (static_cast<int>(type) == 5 || static_cast<int>(type) == 6)
        result = m_iUnknown18->createStream(reinterpret_cast<const char*>(instance), flags, NULL, &sound);
    else
        result = m_iUnknown18->createSound(reinterpret_cast<const char*>(instance), flags, NULL, &sound);
    if (result != FMOD_OK) {
        delete instance;
        Ogre::LogManager::getSingleton().logMessage(static_cast<std::string>(
            Ogre::UTFString("SoundManager::CreateSound could not load sound '") +
            Ogre::UTFString(name) + Ogre::UTFString("'  FMOD Error:") + Ogre::UTFString(FMOD_ErrorString(result))));
        return NULL;
    }
    instance->m_pSound = sound;
    ++instance->m_referenceCount;
    m_pendingSounds.add(instance);
    Ogre::LogManager::getSingleton().logMessage("Total sounds loaded: " + Ogre::StringConverter::toString(m_pendingSounds.size()));
    return instance;
}

void CSoundManager::initialize(CSettings* settings)
{
    m_pDynamicPropertyFile = settings;
    const char* sourceFile = "/builddir/Torchlight/TorchlightMacPort_09b/Projects_9156/Delvers/Delvers/sound/SoundManager.cpp";
    if (m_bUnknown6C8) {
        FMOD_RESULT result = FMOD::System_Create(&m_iUnknown18);
        if (result != FMOD_OK)
            throw Ogre::InternalErrorException(7, "FMOD error! (" + Ogre::StringConverter::toString(static_cast<int>(result)) + "): " + FMOD_ErrorString(result),
                "SoundManager::Initialize", sourceFile, 291);
        if (m_iUnknown18->init(64, 0, NULL) != FMOD_OK)
            return;
        result = m_iUnknown18->setFileSystem(&CSoundManager::fmodFileOpenCallback,
            &CSoundManager::fmodFileCloseCallback, &CSoundManager::fmodFileReadCallback,
            &CSoundManager::fmodFileSeekCallback, NULL, NULL, 2048);
        if (result != FMOD_OK)
            throw Ogre::InternalErrorException(7, "FMOD error! (" + Ogre::StringConverter::toString(static_cast<int>(result)) + "): " + FMOD_ErrorString(result),
                "SoundManager::Initialize", sourceFile, 310);
        m_iUnknown18->createSoundGroup("Music", &m_iUnknown6E0);
        m_iUnknown18->createChannelGroup("MusicChannel", &m_iUnknown6E8);
        m_bUnknown6A8 = true;
    }
    if (m_pDynamicPropertyFile) {
        int musicMuted = m_pDynamicPropertyFile->GetInt(KSETTINGS_MUSICMUTE);
        int soundMuted = m_pDynamicPropertyFile->GetInt(KSETTINGS_SOUNDMUTE);
        float musicVolume = m_pDynamicPropertyFile->GetFloat(KSETTINGS_F_MUSICVOLUME);
        float soundVolume = m_pDynamicPropertyFile->GetFloat(KSETTINGS_F_SOUNDVOLUME);
        updateAudioLevels(soundVolume, musicVolume, soundMuted != 0, musicMuted != 0);
    }
    Ogre::LogManager::getSingleton().logMessage("SoundManager Initialized");
}
