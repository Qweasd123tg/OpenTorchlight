#include "SoundBank.h"
#include "SoundManager.h"
#include "SoundInstance.h"
#include "ChannelInstance.h"
#include "Utilities.h"
#include <algorithm>
#include <cmath>

void CSoundBank::setRadius(float radius)
{
    m_radius = radius;
    m_dirty = true;
    for (unsigned int i = 0; i < m_samples.size(); ++i)
        m_radii[i] = radius;
}

bool CSoundBank::bankPlaying(int sample)
{
    if (sample >= static_cast<int>(m_samples.size()) || sample < 0)
        return false;
    for (unsigned int i = 0; i < m_sampleIDs.size(); ++i)
        if (m_sampleIDs[i] == sample)
            return true;
    return false;
}

void CSoundBank::queueGlobalSample(int sample, float volume, float pitch)
{
    if (!m_soundManager->m_bUnknown6A9 || !m_soundManager->m_bUnknown6A8)
        return;
    if (sample >= static_cast<int>(m_samples.size()) || sample < 0)
        return;
    if (m_probabilities[sample] >= 0 &&
        UTILITIES::randomIntegerBetweenVolatile(1, 100) >= m_probabilities[sample])
        return;
    if (volume == 0.0f)
        volume = m_volumes[sample];
    else
        volume *= m_volumeScale;
    if (!m_samples[sample].empty()) {
        m_lastVolume = volume;
        unsigned int index = UTILITIES::randomIntegerBetweenVolatile(0, m_samples[sample].size() - 1);
        m_soundManager->queueSound(sample, m_samples[sample][index], m_lastVolume, pitch);
    }
}

void CSoundBank::pause()
{
    for (unsigned int i = 0; i < m_channels.size(); ++i)
        m_soundManager->setPauseSound(m_channels[i], true);
    m_dirty = true;
}

void CSoundBank::resume()
{
    for (unsigned int i = 0; i < m_channels.size(); ++i)
        m_soundManager->setPauseSound(m_channels[i], false);
    m_dirty = true;
}

void CSoundBank::stop(int sample)
{
    for (unsigned int i = 0; i < m_channels.size(); ++i) {
        if (m_sampleIDs[i] == sample) {
            m_soundManager->stopSound(m_channels[i]);
            m_sampleIDs[i] = -1;
        }
    }
    m_dirty = true;
}

float CSoundBank::configureVolumeScale(float radius, const Ogre::Vector3& position)
{
    if (radius == 0.0f)
        return 0.0f;
    float dx = m_soundManager->m_listenerX - position.x;
    float dz = m_soundManager->m_listenerZ - position.z;
    float distance = std::sqrt(dx * dx + 0.0f + dz * dz);
    return 1.0f - std::min(distance, radius) / radius;
}

CSoundBank::CSoundBank(CSoundManager& manager, bool is3D)
    : CRunicCore(), m_soundManager(&manager), m_channels(2), m_sampleIDs(2),
      m_dirty(true), m_volumeScale(1.0f), m_radius(10.0f), m_is3D(is3D),
      m_lastVolume(0.0f), m_loop(false)
{
}

void CSoundBank::stop()
{
    for (unsigned int i = 0; i < m_channels.size(); ++i)
        m_soundManager->stopSound(m_channels[i]);
    m_channels.clear();
    m_sampleIDs.clear();
    m_dirty = true;
}

void CSoundBank::clear()
{
    if (m_loop)
        stop();
    for (unsigned int i = 0; i < m_samples.size(); ++i)
        for (unsigned int j = 0; j < m_samples[i].size(); ++j)
            m_soundManager->releaseSound(m_samples[i][j]);
    m_samples.clear();
}

CSoundBank::~CSoundBank()
{
    if (m_loop)
        stop();
    clear();
}

void CChannelInstance::clear()
{
    m_iUnknown10 = 0;
}

#include "MasterResourceManager.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include "StringUtilities.h"
CSoundInstance* CSoundBank::addSample(int sample,const std::wstring& name,bool loop,bool flag,float volume,float frequency,float variation,float radius,int probability)
{
    if(sample<0)return NULL;
    m_loop=loop;
    CSoundInstance* sound=m_soundManager->createSound(name,static_cast<SOUND_TYPE>(loop?4:3),flag,frequency,variation);
    if(!sound)return NULL;
    if(static_cast<unsigned int>(sample)>=m_samples.size()){
        m_samples.resize(sample+1);m_radii.resize(sample+1,0.0f);m_volumes.resize(sample+1,0.0f);m_probabilities.resize(sample+1,0);
    }
    m_samples[sample].push_back(sound);
    m_radii[sample]=radius==0?m_radius:radius;
    m_volumes[sample]=volume==0?m_volumeScale:volume;
    m_probabilities[sample]=probability;
    return sound;
}
void CSoundBank::addSample(int sample,long long guid)
{
    if(sample<0)return;
    CSoundBankDataInformation* bank=CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
    if(!bank)return;
    CSoundData* data=bank->getSoundDataObjectByGuid(guid);if(!data)return;
    if(!data->m_group){data->m_group=m_soundManager->createSoundGroup(STRINGS::GetValueAsString(guid));data->m_group->setMaxAudible(6);data->m_group->setMaxAudibleBehavior(static_cast<FMOD_SOUNDGROUP_BEHAVIOR>(1));}
    if(data->m_flag2c)m_loop=true;
    for(unsigned i=0;i<data->m_files.size();++i){
        CSoundInstance* sound=addSample(sample,data->m_files[i],data->m_flag2c,false,data->m_float28,data->m_float34,data->m_float30,data->m_float38,data->m_probability);
        if(sound){FMOD::SoundGroup* group=NULL;sound->m_pSound->getSoundGroup(&group);if(data->m_group!=group)sound->m_pSound->setSoundGroup(data->m_group);sound->m_pSoundData=data;}
    }
}

#include <OgreSceneNode.h>
void CSoundBank::update(float, Ogre::SceneNode* node)
{
    for(unsigned i=0;i<m_channels.size();){
        m_soundManager->incrementSoundBank();
        if(m_channels[i]==-1 || !m_soundManager->isChannelPlaying(m_channels[i])){
            if(m_loop)m_soundManager->stopSound(m_channels[i]);
            m_channels.removeAt(i);m_sampleIDs.removeAt(i);i=1;
        } else ++i;
    }
    if(!node || !m_loop)return;
    Ogre::Vector3 listener(m_soundManager->m_listenerX,m_soundManager->m_listenerY,m_soundManager->m_listenerZ);
    Ogre::Vector3 position=node->_getDerivedPosition();
    if(listener.x==0 && listener.z==0 && listener==position)return;
    float volume=configureVolumeScale(m_radius,position)*m_volumeScale;
    if(volume<=0 && m_channels.size()){m_lastVolume=0;stop();return;}
    if(volume>0.001f && !m_channels.size() && m_loop){playSample(0,node,0,m_radius,false);m_dirty=true;}
    if(!m_dirty && listener==m_lastPosition)return;
    m_lastPosition=listener;m_dirty=false;m_lastVolume=volume;
    for(unsigned i=0;i<m_channels.size();++i)m_soundManager->setSoundVolume(m_channels[i],volume);
}

int CSoundBank::playSample(int sample, Ogre::SceneNode* node, float volume,
                           float radius, bool untracked)
{
    if (!m_soundManager->m_bUnknown6A9 || !m_soundManager->m_bUnknown6A8)
        return -1;
    if (sample >= static_cast<int>(m_samples.size()) || sample < 0)
        return -1;
    if (m_probabilities[sample] >= 0 &&
        UTILITIES::randomIntegerBetweenVolatile(1, 100) >= m_probabilities[sample])
        return -1;
    if (volume == 0.0f)
        volume = m_volumes[sample];
    else
        volume *= m_volumeScale;
    if (radius == 0.0f)
        radius = m_radii[sample];
    if (static_cast<unsigned int>(m_samples[sample].size()) == 0)
        return -1;
    float scale = node ? configureVolumeScale(radius, node->_getDerivedPosition()) : 1.0f;
    m_lastVolume = volume * scale;
    unsigned int index = UTILITIES::randomIntegerBetweenVolatile(0, m_samples[sample].size() - 1);
    CSoundInstance* sound = m_samples[sample][index];
    if (m_loop)
        stop();
    else {
        m_channels.clear();
        m_sampleIDs.clear();
    }
    int channel = m_soundManager->playSound(sound, m_loop ? node : NULL, -1, m_lastVolume);
    if (!untracked && channel != -1) {
        m_channels.add(channel);
        m_sampleIDs.add(sample);
    }
    m_dirty = true;
    return channel;
}
