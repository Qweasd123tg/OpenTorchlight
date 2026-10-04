#include "EmptyStrings.h"
#include "GameEnums.h"
#include "MusicObject.h"
#include "EditorBaseObject.h"
#include "MasterResourceManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "StringUtilities.h"

void CMusicObject::playAndFadeIn(float fadeTime)
{
}

void CMusicObject::fadeOutAndStop(float)
{
}

#include "SoundManager.h"

void CMusicObject::reset()
{
    if (m_pSoundManager) {
        m_pSoundManager->stopMusic();
        m_pSoundManager->playMusic(m_sMusicFile, m_bLoops);
    }
}

void CMusicObject::stop()
{
    m_bMusicPlaybackActive = false;
    if (m_pSoundManager) {
        m_pSoundManager->stopMusic();
        BroadcastEvent(12);
    }
}

CMusicObject::CMusicObject(CResourceManager* resourceManager)
    : CEditorBaseObject(),
      m_pSoundManager(NULL),
      m_bFadeIn(false),
      m_bFadeOut(false),
      m_bLoops(true),
      m_fRemainingPlayTime(0.0f),
      m_bMusicPlaybackActive(false),
      m_fPlaybackCheckTimer(0.2f),
      m_pResourceManager(resourceManager)
{
    if (m_pResourceManager != NULL &&
        *reinterpret_cast<CSoundManager **>(
            reinterpret_cast<char *>(
                CMasterResourceManager::getSingleton()) + 0x98) != NULL)
    {
        m_pSoundManager = *reinterpret_cast<CSoundManager **>(
            reinterpret_cast<char *>(
                CMasterResourceManager::getSingleton()) + 0x98);
    }
}

CMusicObject::~CMusicObject()
{
}

void CMusicObject::updateMusic(float deltaTime)
{
    if (m_bMusicPlaybackActive)
    {
        m_fPlaybackCheckTimer -= deltaTime;
        if (m_fPlaybackCheckTimer <= 0.0f)
        {
            m_fPlaybackCheckTimer = 0.2f;
            if (!getIsPlaying())
            {
                m_bMusicPlaybackActive = false;
                if (!m_bLoops)
                {
                    playNormalLevelMusic();
                }
            }
        }

        if (!m_bLoops)
        {
            m_fRemainingPlayTime -= deltaTime;
            if (m_fRemainingPlayTime <= 0.0f)
            {
                playNormalLevelMusic();
                m_bMusicPlaybackActive = false;
            }
        }
    }
}

void CMusicObject::setMusicFile(std::wstring musicFile)
{
    m_sMusicFile = STRINGS::StringUpper(musicFile);

    if (m_sMusicFile.length() > 2 &&
        m_sMusicFile[0] != L'.' &&
        m_sMusicFile[1] != L'.' &&
        m_sMusicFile[1] != L':')
    {
        m_sMusicFile = L"../" + m_sMusicFile;
    }

    m_sPlayingMusicFile = m_sMusicFile;
}
