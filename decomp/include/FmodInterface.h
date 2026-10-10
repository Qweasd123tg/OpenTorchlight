#ifndef OTL_FMOD_INTERFACE_H
#define OTL_FMOD_INTERFACE_H
// Partial FMOD Ex 4.36.21 interface. Methods are resolved from the original library.
enum FMOD_RESULT { FMOD_OK = 0 };
namespace FMOD {
class Sound { public: FMOD_RESULT getMode(unsigned int*); FMOD_RESULT release(); };
class SoundGroup { public: FMOD_RESULT setVolume(float); };
class ChannelGroup { public: FMOD_RESULT setVolume(float); FMOD_RESULT setMute(bool); };
class Channel { public: FMOD_RESULT setMute(bool); };
class System { public:
    FMOD_RESULT createSoundGroup(const char*,SoundGroup**);
    FMOD_RESULT getMasterSoundGroup(SoundGroup**);
    FMOD_RESULT getMasterChannelGroup(ChannelGroup**);
    FMOD_RESULT getChannel(int,Channel**);
};
}
#endif
