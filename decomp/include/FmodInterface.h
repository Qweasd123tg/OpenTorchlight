#ifndef OTL_FMOD_INTERFACE_H
#define OTL_FMOD_INTERFACE_H
// Partial FMOD Ex 4.36.21 interface. Methods are resolved from the original library.
enum FMOD_RESULT { FMOD_OK = 0 };
// Original playSound passes -1 in the FMOD_CHANNELINDEX argument.
enum FMOD_CHANNELINDEX { FMOD_CHANNEL_FREE = -1 };
struct FMOD_CREATESOUNDEXINFO;
enum FMOD_SOUNDGROUP_BEHAVIOR { FMOD_SOUNDGROUP_BEHAVIOR_FAIL = 0, FMOD_SOUNDGROUP_BEHAVIOR_MUTE = 1 };
namespace FMOD {
class SoundGroup;
class ChannelGroup;
class DSP { public: FMOD_RESULT release(); };
class Sound { public: FMOD_RESULT getSoundGroup(SoundGroup**); FMOD_RESULT setSoundGroup(SoundGroup*); FMOD_RESULT getMode(unsigned int*); FMOD_RESULT getLength(unsigned int*, unsigned int); FMOD_RESULT release(); };
class SoundGroup { public: FMOD_RESULT setMaxAudible(int); FMOD_RESULT setMaxAudibleBehavior(FMOD_SOUNDGROUP_BEHAVIOR); FMOD_RESULT release(); FMOD_RESULT setVolume(float); };
class ChannelGroup { public: FMOD_RESULT release(); FMOD_RESULT setVolume(float); FMOD_RESULT setMute(bool); };
class Channel { public:
    FMOD_RESULT getIndex(int*);
    FMOD_RESULT setChannelGroup(ChannelGroup*);
    FMOD_RESULT setMute(bool);
    FMOD_RESULT stop();
    FMOD_RESULT set3DMinMaxDistance(float,float);
    FMOD_RESULT isPlaying(bool*);
    FMOD_RESULT setVolume(float);
    FMOD_RESULT setPaused(bool);
};
class System { public:
    FMOD_RESULT release();
    FMOD_RESULT playSound(FMOD_CHANNELINDEX,Sound*,bool,Channel**);
    FMOD_RESULT createSound(const char*,unsigned int,FMOD_CREATESOUNDEXINFO*,Sound**);
    FMOD_RESULT createStream(const char*,unsigned int,FMOD_CREATESOUNDEXINFO*,Sound**);
    FMOD_RESULT update();
    FMOD_RESULT createSoundGroup(const char*,SoundGroup**);
    FMOD_RESULT getMasterSoundGroup(SoundGroup**);
    FMOD_RESULT getMasterChannelGroup(ChannelGroup**);
    FMOD_RESULT getChannel(int,Channel**);
};
}
#endif
