#ifndef MUSICOBJECT_H
#define MUSICOBJECT_H

#include <string>

#include "EditorBaseObject.h"
#include "ResourceManager.h"

class CSoundManager;

class CMusicObject : public CEditorBaseObject
{
public:
    virtual ~CMusicObject();

    void playAndFadeIn(float fadeTime);
    void fadeOutAndStop(float fadeTime);
    void reset();
    void stop();

    CMusicObject(CResourceManager* resourceManager);

    bool getIsPlaying();
    void playNormalLevelMusic();
    void updateMusic(float deltaTime);
    void setMusicFile(std::wstring musicFile);
    void play();

    CSoundManager* m_pSoundManager;
    std::wstring m_sMusicFile;
    std::wstring m_sPlayingMusicFile;
    bool m_bFadeIn;
    bool m_bFadeOut;
    bool m_bLoops;
    unsigned char m_gap73[1];
    float m_fRemainingPlayTime;
    bool m_bMusicPlaybackActive;
    unsigned char m_gap79[3];
    float m_fPlaybackCheckTimer;
    CResourceManager* m_pResourceManager;

public:
    // Inline accessors behind the descriptors' property functions.
    void setLoops(bool value) { m_bLoops = value; }
    bool getLoops() const { return m_bLoops; }
};

#endif
