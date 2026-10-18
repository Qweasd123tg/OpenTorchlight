#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "SoundManager.h"
#include "SoundInstance.h"
#include "FileSystem.h"
#include "SettingsVariables.h"
#include "SystemsNativeMaster.h"
TL_ORIGINAL(void,musicCtor,(CSoundManager*,bool),"_ZN13CSoundManagerC1Eb")
TL_ORIGINAL(void,musicDtor,(CSoundManager*),"_ZN13CSoundManagerD1Ev")
TL_ORIGINAL(float,musicOriginal,(CSoundManager*,std::wstring&,bool),"_ZN13CSoundManager9playMusicERSbIwSt11char_traitsIwESaIwEEb")
extern "C" float musicCandidate(CSoundManager*,std::wstring&,bool) __asm__("_ZN13CSoundManager9playMusicERSbIwSt11char_traitsIwESaIwEEb");
TL_FUNCTION(musicInfo,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(musicStop,"_ZN13CSoundManager9stopMusicEv")
TL_FUNCTION(musicCreate,"_ZN13CSoundManager11createSoundESbIwSt11char_traitsIwESaIwEE10SOUND_TYPEbff")
TL_FUNCTION(musicPlay,"_ZN13CSoundManager9playSoundEP14CSoundInstancePN4Ogre9SceneNodeEif")
TL_FUNCTION(musicLevels,"_ZN13CSoundManager17updateAudioLevelsEffbb")
TL_FUNCTION(musicLength,"_ZN13CSoundManager14getSoundLengthEP14CSoundInstance")
extern "C" FMOD_RESULT musicGroup(FMOD::Sound*,FMOD::SoundGroup*) __asm__("_ZN4FMOD5Sound13setSoundGroupEPNS_10SoundGroupE");
extern "C" FMOD_RESULT musicChannel(FMOD::System*,int,FMOD::Channel**) __asm__("_ZN4FMOD6System10getChannelEiPPNS_7ChannelE");
extern "C" FMOD_RESULT musicChannelGroup(FMOD::Channel*,FMOD::ChannelGroup*) __asm__("_ZN4FMOD7Channel15setChannelGroupEPNS_12ChannelGroupE");
namespace {
struct Case{unsigned path,scenario,loop;};const Case*current;autotest::Capture*cap;CSoundInstance*returned;
void word(unsigned x){cap->add(&x,sizeof(x));}void real(float x){cap->add(&x,sizeof(x));}
void info(CFileSystem*,const std::wstring&path,CFileInfo&f,bool compiled,bool binary,bool mods){word(1);cap->addText(path);word(compiled);word(binary);word(mods);f.m_sPath=L"resolved/"+path;}
void stop(CSoundManager*){word(2);}
CSoundInstance* create(CSoundManager*,std::wstring name,SOUND_TYPE type,bool b,float a,float c){word(3);cap->addText(name);word(type);word(b);real(a);real(c);return current->scenario==0?NULL:returned;}
int play(CSoundManager*,CSoundInstance*s,Ogre::SceneNode*n,int channel,float volume){word(4);word(s==returned);word(n==NULL);word(channel);real(volume);return current->scenario==1?-1:19;}
void levels(CSoundManager*,float s,float m,bool sm,bool mm){word(5);real(s);real(m);word(sm);word(mm);}
float length(CSoundManager*,CSoundInstance*s){word(6);word(s==returned);return 3.5f;}
FMOD_RESULT group(FMOD::Sound*s,FMOD::SoundGroup*g){word(7);word(s==reinterpret_cast<FMOD::Sound*>(0x111));word(g==reinterpret_cast<FMOD::SoundGroup*>(0x222));return FMOD_OK;}
FMOD_RESULT channel(FMOD::System*s,int c,FMOD::Channel**p){word(8);word(s==reinterpret_cast<FMOD::System*>(0x333));word(c);*p=reinterpret_cast<FMOD::Channel*>(0x444);return current->scenario==2?static_cast<FMOD_RESULT>(1):FMOD_OK;}
FMOD_RESULT channelGroup(FMOD::Channel*c,FMOD::ChannelGroup*g){word(9);word(c==reinterpret_cast<FMOD::Channel*>(0x444));word(g==reinterpret_cast<FMOD::ChannelGroup*>(0x555));return FMOD_OK;}
void side(void*raw,autotest::Capture&out,bool ours){
 Case c=*static_cast<Case*>(raw);current=&c;cap=&out;SystemsNativeMaster native;
 union S{long double a;unsigned char bytes[sizeof(CSoundManager)];} storage;std::memset(&storage,0,sizeof(storage));CSoundManager*s=reinterpret_cast<CSoundManager*>(storage.bytes);musicCtor(s,false);
 returned=new CSoundInstance;returned->m_pSound=reinterpret_cast<FMOD::Sound*>(0x111);returned->m_referenceCount=5;
 s->m_iUnknown6E0=reinterpret_cast<FMOD::SoundGroup*>(0x222);s->m_iUnknown18=reinterpret_cast<FMOD::System*>(0x333);s->m_iUnknown6E8=reinterpret_cast<FMOD::ChannelGroup*>(0x555);s->m_pDynamicPropertyFile=c.scenario==3?NULL:native.settings;
 native.settings->SetInt(KSETTINGS_MUSICMUTE,c.loop);native.settings->SetInt(KSETTINGS_SOUNDMUTE,c.path&1);native.settings->SetFloat(KSETTINGS_F_MUSICVOLUME,.75f);native.settings->SetFloat(KSETTINGS_F_SOUNDVOLUME,.25f);
 const wchar_t*paths[]={L"Music/track.ogg",L"media/MUSIC/../track.ogg",L"MUSIC",L"./other.ogg",L"/././other.ogg",L"plain.ogg"};std::wstring name=paths[c.path];
 detour::Set d;TL_REDIRECT(d,musicInfo,&info);TL_REDIRECT(d,musicStop,&stop);TL_REDIRECT(d,musicCreate,&create);TL_REDIRECT(d,musicPlay,&play);TL_REDIRECT(d,musicLevels,&levels);TL_REDIRECT(d,musicLength,&length);
 d.redirect(reinterpret_cast<char*>(&musicGroup),reinterpret_cast<char*>(&musicGroup),&group);d.redirect(reinterpret_cast<char*>(&musicChannel),reinterpret_cast<char*>(&musicChannel),&channel);d.redirect(reinterpret_cast<char*>(&musicChannelGroup),reinterpret_cast<char*>(&musicChannelGroup),&channelGroup);if(d.failed())_exit(64);
 float(*fn)(CSoundManager*,std::wstring&,bool)=ours?musicCandidate:musicOriginal;if(autotest::beginInvocation(out,fn)){float r=fn(s,name,c.loop);out.callCompleted=1;real(r);}
 cap->addText(name);word(s->m_iUnknown6D0==returned);word(s->m_iUnknown6D8);
 d.restore();s->m_iUnknown6D0=NULL;s->m_iUnknown18=NULL;s->m_iUnknown6E0=NULL;s->m_iUnknown6E8=NULL;musicDtor(s);returned->m_pSound=NULL;delete returned;
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_sound_music){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_sound_music",reinterpret_cast<uintptr_t>(&musicOriginal));for(unsigned p=0;p<6;++p)for(unsigned s=0;s<5;++s)for(unsigned loop=0;loop<2;++loop){Case c={p,s,loop};autotest::Outcome a,b;autotest::runChild(original,&c,a,1500,10000);autotest::runChild(candidate,&c,b,1500,10000);++cases;bool ok=coverage.observe(host,a,b)==0;TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
