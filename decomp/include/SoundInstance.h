#ifndef SOUNDINSTANCE_H
#define SOUNDINSTANCE_H

#include "RunicCore.h"

#include <string>
#include <OgreDataStream.h>
#include "GameEnums.h"

class CSoundData;
class SoundObject;

namespace FMOD
{
    class Sound;
}

class CSoundInstance : public CRunicCore
{
public:
    virtual ~CSoundInstance();

    void clear();

    std::wstring m_soundName;
    Ogre::DataStreamPtr m_stream;
    SOUND_TYPE m_soundType;
    bool m_loop; // +0x3c
    FMOD::Sound* m_pSound;
    unsigned int m_referenceCount;
    float m_volume; // +0x4c
    float m_volumeVariance; // +0x50
    unsigned char m_gap54[4];
    CSoundData* m_pSoundData;
};

#endif
