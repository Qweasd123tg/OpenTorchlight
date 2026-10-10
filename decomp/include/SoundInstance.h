#ifndef SOUNDINSTANCE_H
#define SOUNDINSTANCE_H

#include "RunicCore.h"

#include <string>
#include <OgreDataStream.h>
#include "GameEnums.h"

class SoundData;
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
    FMOD::Sound* m_pSound;
    unsigned int m_referenceCount;
    unsigned char m_gap4c[12];
    SoundData* m_pSoundData;
};

#endif
