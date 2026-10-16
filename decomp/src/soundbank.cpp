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
