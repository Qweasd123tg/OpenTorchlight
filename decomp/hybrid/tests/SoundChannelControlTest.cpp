#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
#include "SoundManager.h"
TL_ORIGINAL(void,oldStop,(CSoundManager*,int),"_ZN13CSoundManager9stopSoundEi")
extern "C" void newStop(CSoundManager*,int) __asm__("_ZN13CSoundManager9stopSoundEi");
TL_ORIGINAL(void,oldDistance,(CSoundManager*,int,float,float),"_ZN13CSoundManager19set3DMinMaxDistanceEiff")
extern "C" void newDistance(CSoundManager*,int,float,float) __asm__("_ZN13CSoundManager19set3DMinMaxDistanceEiff");
TL_ORIGINAL(long long,oldPlaying,(CSoundManager*,int),"_ZN13CSoundManager16isChannelPlayingEi")
extern "C" long long newPlaying(CSoundManager*,int) __asm__("_ZN13CSoundManager16isChannelPlayingEi");
TL_ORIGINAL(void,oldVolume,(CSoundManager*,int,float),"_ZN13CSoundManager14setSoundVolumeEif")
extern "C" void newVolume(CSoundManager*,int,float) __asm__("_ZN13CSoundManager14setSoundVolumeEif");
TL_ORIGINAL(void,oldPause,(CSoundManager*,int,bool),"_ZN13CSoundManager13setPauseSoundEib")
extern "C" void newPause(CSoundManager*,int,bool) __asm__("_ZN13CSoundManager13setPauseSoundEib");
extern "C" char getChannelImport[] __asm__("_ZN4FMOD6System10getChannelEiPPNS_7ChannelE");
extern "C" char stopImport[] __asm__("_ZN4FMOD7Channel4stopEv");
extern "C" char distanceImport[] __asm__("_ZN4FMOD7Channel19set3DMinMaxDistanceEff");
extern "C" char playingImport[] __asm__("_ZN4FMOD7Channel9isPlayingEPb");
extern "C" char volumeImport[] __asm__("_ZN4FMOD7Channel9setVolumeEf");
extern "C" char pauseImport[] __asm__("_ZN4FMOD7Channel9setPausedEb");
namespace {
struct Case {unsigned operation,index,status,value;};
const Case* input; autotest::Capture* capture;
void* expectedSystem; void* expectedChannel; unsigned gets,controls;
void number(unsigned n){capture->add(&n,4);}
void invalid(){capture->issue=autotest::Capture::InvalidReport;}
FMOD_RESULT getChannel(FMOD::System*self,int index,FMOD::Channel**channel){
    number(1);capture->add(&index,4);if(self!=expectedSystem)invalid();++gets;
    *channel=static_cast<FMOD::Channel*>(expectedChannel);
    return static_cast<FMOD_RESULT>(input->status?17:0);
}
FMOD_RESULT stop(FMOD::Channel*channel){number(2);if(channel!=expectedChannel)invalid();++controls;return static_cast<FMOD_RESULT>(33);}
FMOD_RESULT distance(FMOD::Channel*channel,float a,float b){number(3);if(channel!=expectedChannel)invalid();capture->add(&a,4);capture->add(&b,4);++controls;return static_cast<FMOD_RESULT>(33);}
FMOD_RESULT playing(FMOD::Channel*channel,bool*value){number(4);if(channel!=expectedChannel||*value)invalid();++controls;if(input->value!=2)*value=(input->value&1)!=0;return static_cast<FMOD_RESULT>(input->value>=2?33:0);}
FMOD_RESULT volume(FMOD::Channel*channel,float value){number(5);if(channel!=expectedChannel)invalid();capture->add(&value,4);++controls;return static_cast<FMOD_RESULT>(33);}
FMOD_RESULT pause(FMOD::Channel*channel,bool value){number(6);if(channel!=expectedChannel||value!=bool(input->value&1))invalid();number(value);++controls;return static_cast<FMOD_RESULT>(33);}
void side(void*raw,autotest::Capture&out,bool ours){
    const Case&c=*static_cast<Case*>(raw);input=&c;capture=&out;gets=controls=0;
    uint64_t memory[(sizeof(CSoundManager)+7)/8],system[4],channel[4];
    std::memset(memory,0xa5,sizeof(memory));std::memset(system,0x3c,sizeof(system));std::memset(channel,0x69,sizeof(channel));
    CSoundManager*manager=reinterpret_cast<CSoundManager*>(memory);expectedSystem=system;expectedChannel=channel;
    manager->m_iUnknown18=reinterpret_cast<FMOD::System*>(system);
    static const int counts[]={0,1,7,-7,static_cast<int>(0x80000000u)};manager->m_iUnknown14=counts[c.value];
    for(unsigned i=0;i<64;++i)manager->m_channels[i].m_iUnknown10=reinterpret_cast<CSoundInstance*>(static_cast<uintptr_t>(0x1122334400000000ULL+i));
    unsigned char expected[sizeof(memory)];std::memcpy(expected,memory,sizeof(memory));
    detour::Set d;
    d.redirect(getChannelImport,getChannelImport,&getChannel);
    d.redirect(stopImport,stopImport,&stop);
    d.redirect(distanceImport,distanceImport,&distance);
    d.redirect(playingImport,playingImport,&playing);
    d.redirect(volumeImport,volumeImport,&volume);
    d.redirect(pauseImport,pauseImport,&pause);
    if(d.failed()){invalid();return;}
    static const int indices[]={-1,0,1,63,64,2147483647};int index=indices[c.index];bool valid=index!=-1&&index<=63;
    static const uint32_t bits[]={0,0x80000000u,0x3f800000u,0x7fc12345u};float first,second;
    std::memcpy(&first,&bits[c.value%4],4);std::memcpy(&second,&bits[3-c.value%4],4);
    long long result=0;
    if(c.operation==0){typedef void(*Fn)(CSoundManager*,int);Fn fn=ours?newStop:oldStop;if(!autotest::beginInvocation(out,fn))return;fn(manager,index);out.callCompleted=1;
        int count=c.value==4?0x7fffffff:c.value==0?0:c.value==1?0:c.value==2?6:-8;std::memcpy(expected+0x14,&count,4);
        if(valid){long long zero=0;std::memcpy(expected+0xb8+index*24,&zero,8);}}
    else if(c.operation==1){typedef void(*Fn)(CSoundManager*,int,float,float);Fn fn=ours?newDistance:oldDistance;if(!autotest::beginInvocation(out,fn))return;fn(manager,index,first,second);out.callCompleted=1;}
    else if(c.operation==2){typedef long long(*Fn)(CSoundManager*,int);Fn fn=ours?newPlaying:oldPlaying;if(!autotest::beginInvocation(out,fn))return;result=fn(manager,index);out.callCompleted=1;if(result!=((valid&&!c.status&&(c.value&1))?1:0))invalid();}
    else if(c.operation==3){typedef void(*Fn)(CSoundManager*,int,float);Fn fn=ours?newVolume:oldVolume;if(!autotest::beginInvocation(out,fn))return;fn(manager,index,first);out.callCompleted=1;}
    else {typedef void(*Fn)(CSoundManager*,int,bool);Fn fn=ours?newPause:oldPause;if(!autotest::beginInvocation(out,fn))return;fn(manager,index,bool(c.value&1));out.callCompleted=1;}
    if(gets!=(valid?1u:0u)||controls!=(valid&&(c.operation==0||!c.status)?1u:0u)||std::memcmp(expected,memory,sizeof(memory)))invalid();
    out.add(&gets,4);out.add(&controls,4);out.add(&result,8);out.add(system,sizeof(system));out.add(channel,sizeof(channel));
}
void original(void*p,autotest::Capture&out){side(p,out,false);}
void candidate(void*p,autotest::Capture&out){side(p,out,true);}
int run(const tlhybrid_host*host,unsigned op,const char*name,uintptr_t address){
    autotest::Coverage coverage(name,address);
    for(unsigned index=0;index<6;++index)for(unsigned status=0;status<2;++status)for(unsigned value=0;value<(op==0?5u:4u);++value){
        Case c={op,index,status,value};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(candidate,&c,b);
        if(coverage.observe(host,a,b)){host->log("    channel-control op %u index %u status %u value %u exits %d/%d\n",op,index,status,value,a.childStatus,b.childStatus);coverage.report(host);return 1;}}
    coverage.report(host);return 0;
}
}
TL_TEST(sound_manager_stop_sound){return run(host,0,"sound_manager_stop_sound",reinterpret_cast<uintptr_t>(&oldStop));}
TL_TEST(sound_manager_channel_distance){return run(host,1,"sound_manager_channel_distance",reinterpret_cast<uintptr_t>(&oldDistance));}
TL_TEST(sound_manager_channel_playing){return run(host,2,"sound_manager_channel_playing",reinterpret_cast<uintptr_t>(&oldPlaying));}
TL_TEST(sound_manager_channel_volume){return run(host,3,"sound_manager_channel_volume",reinterpret_cast<uintptr_t>(&oldVolume));}
TL_TEST(sound_manager_channel_pause){return run(host,4,"sound_manager_channel_pause",reinterpret_cast<uintptr_t>(&oldPause));}
