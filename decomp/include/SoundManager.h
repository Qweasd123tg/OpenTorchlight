#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreSceneNode.h>
#include <OgreVector3.h>
#include <string>
#include "FmodInterface.h"
#include <vector>
#include "TArrayList.h"
#include "ChannelInstance.h"
#include "DynamicPropertyFile.h"
#include "GameEnums.h"
#include "RunicCore.h"
#include "Settings.h"
class CSoundInstance;

class CSoundManager : public CRunicCore
{
public:
    virtual ~CSoundManager();
    static FMOD_RESULT fmodFileReadCallback(void*, void*, unsigned int, unsigned int*, void*);
    static FMOD_RESULT fmodFileSeekCallback(void*, unsigned int, void*);
    void releaseSound(CSoundInstance*);
    int getNumberOfChannelsPlaying();
    void incrementSoundBank();
    static FMOD_RESULT fmodFileCloseCallback(void*, void*);
    unsigned int soundLoops(CSoundInstance*);
    CSoundInstance* findSound(std::wstring&, SOUND_TYPE, bool, float, float);
    void stopSound(int);
    void stopMusic();
    void stopAllSounds();
    void set3DMinMaxDistance(int, float, float);
    bool isChannelPlaying(int);
    void setSoundVolume(int, float);
    void setPauseSound(int, bool);
    std::wstring getMusicFilePlaying();
    CSoundManager(bool);
    FMOD::SoundGroup* createSoundGroup(std::string);
    int getMemoryInUse();
    void updateAudioLevels(float, float, bool, bool);
    void queueSound(int, CSoundInstance*, float, float);
    static FMOD_RESULT fmodFileOpenCallback(const char*, int, unsigned int*, void**, void**);
    void releaseUnusedSounds();
    float getSoundLength(CSoundInstance*);
    int playSound(CSoundInstance*, Ogre::SceneNode*, int, float);
    void update(Ogre::SceneNode*, const Ogre::Vector3&, float);
    CSoundInstance* createSound(std::wstring, SOUND_TYPE, bool, float, float);
    float playMusic(std::wstring&, bool);
    void dumpSounds();
    void initialize(CSettings*);

    // fields
    int m_iUnknown10;
    int m_iUnknown14;
    FMOD::System* m_iUnknown18;
    union { void* m_pUnknown20; struct { int m_fileField20; int m_fileField24; }; struct { float m_listenerX; float m_listenerY; }; };
    union { void* m_pUnknown28; struct { int m_fileField28; int m_fileField2C; }; struct { float m_listenerZ; int m_lastQueuedBank; }; };
    std::vector<int> m_soundList0;
    std::vector<CSoundInstance*> m_soundList1;
    std::vector<float> m_soundList2;
    std::vector<float> m_soundList3;
    TArrayList<CSoundInstance*> m_pendingSounds;
    CChannelInstance m_channels[64];
    bool m_bUnknown6A8;
    bool m_bUnknown6A9;
    unsigned char m_gap6AA[0x6];
    CDynamicPropertyFile* m_pDynamicPropertyFile;
    FMOD::DSP* m_iUnknown6B8;
    FMOD::ChannelGroup* m_iUnknown6C0;
    bool m_bUnknown6C8;
    unsigned char m_gap6C9[0x7];
    CSoundInstance* m_iUnknown6D0;
    int m_iUnknown6D8;
    unsigned char m_gap6DC[0x4] __attribute__((aligned(4)));
    FMOD::SoundGroup* m_iUnknown6E0;
    FMOD::ChannelGroup* m_iUnknown6E8;
    int m_iUnknown6F0;
    union { int m_iUnknown6F4; float m_queueTimer; };
    std::wstring m_sUnknown6F8;
};

#endif
