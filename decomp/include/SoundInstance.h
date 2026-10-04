#ifndef SOUNDINSTANCE_H
#define SOUNDINSTANCE_H

#include "RunicCore.h"

#include <string>

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
    SoundObject* m_pSoundObject;
    int m_iSoundObjectRefCount;
    int* m_pSoundObjectRefCount;
    unsigned char m_gap30[0x8] __attribute__((aligned(8)));
    bool m_bLooping;
    FMOD::Sound* m_pSound;
    bool m_bPlaying;
    unsigned char m_gap4C[0xC] __attribute__((aligned(4)));
    SoundData* m_pSoundData;
};

#endif
