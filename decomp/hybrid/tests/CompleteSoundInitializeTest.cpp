#include <cstring>
#include <stdint.h>
#include <OgreLogManager.h>
#include <OgreException.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "SoundManager.h"
#include "SettingsVariables.h"
#include "tests/SystemsNativeMaster.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,initManagerCtor,(CSoundManager*,bool),"_ZN13CSoundManagerC1Eb")
TL_ORIGINAL(void,initManagerDtor,(CSoundManager*),"_ZN13CSoundManagerD1Ev")
TL_ORIGINAL(void,initOriginal,(CSoundManager*,CSettings*),"_ZN13CSoundManager10initializeEP9CSettings")
extern "C" void initCandidate(CSoundManager*,CSettings*) __asm__("_ZN13CSoundManager10initializeEP9CSettings");
TL_FUNCTION(initLevels,"_ZN13CSoundManager17updateAudioLevelsEffbb")
extern "C" FMOD_RESULT initApi(FMOD::System*,int,unsigned,void*) __asm__("_ZN4FMOD6System4initEijPv");
extern "C" FMOD_RESULT initFileApi(FMOD::System*,FMOD_FILE_OPENCALLBACK,FMOD_FILE_CLOSECALLBACK,FMOD_FILE_READCALLBACK,FMOD_FILE_SEEKCALLBACK,FMOD_FILE_ASYNCREADCALLBACK,FMOD_FILE_ASYNCCANCELCALLBACK,int) __asm__("_ZN4FMOD6System13setFileSystemEPF11FMOD_RESULTPKciPjPPvS6_EPFS1_S5_S5_EPFS1_S5_S5_jS4_S5_EPFS1_S5_jS5_EPFS1_P18FMOD_ASYNCREADINFOS5_ESA_i");
extern "C" FMOD_RESULT initSoundGroup(FMOD::System*,const char*,FMOD::SoundGroup**) __asm__("_ZN4FMOD6System16createSoundGroupEPKcPPNS_10SoundGroupE");
extern "C" FMOD_RESULT initChannelGroup(FMOD::System*,const char*,FMOD::ChannelGroup**) __asm__("_ZN4FMOD6System18createChannelGroupEPKcPPNS_12ChannelGroupE");
extern "C" void initLog(Ogre::LogManager*,const std::string&,Ogre::LogMessageLevel,bool) __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
TL_FUNCTION(initOpenCallback,"_ZN13CSoundManager20fmodFileOpenCallbackEPKciPjPPvS4_")
TL_FUNCTION(initCloseCallback,"_ZN13CSoundManager21fmodFileCloseCallbackEPvS0_")
TL_FUNCTION(initReadCallback,"_ZN13CSoundManager20fmodFileReadCallbackEPvS0_jPjS0_")
TL_FUNCTION(initSeekCallback,"_ZN13CSoundManager20fmodFileSeekCallbackEPvjS0_")
namespace {
struct Case{unsigned enabled,settings,musicMuted,soundMuted;int createResult,initResult,fileResult;};Case current;autotest::Capture*cap;SystemsNativeMaster*services;CSoundManager*manager;
void word(unsigned x){cap->add(&x,4);}void real(float x){cap->add(&x,4);}
FMOD_RESULT create(FMOD_SYSTEM**out){word(1);*out=reinterpret_cast<FMOD_SYSTEM*>(0x101);return static_cast<FMOD_RESULT>(current.createResult);}
FMOD_RESULT init(FMOD::System*self,int channels,unsigned flags,void*data){word(2);word(self==reinterpret_cast<FMOD::System*>(0x101));word(channels);word(flags);word(data==NULL);return static_cast<FMOD_RESULT>(current.initResult);}
bool pointer(const void*p,const char*a,const char*b){return p==a||p==b;}
FMOD_RESULT files(FMOD::System*self,FMOD_FILE_OPENCALLBACK o,FMOD_FILE_CLOSECALLBACK c,FMOD_FILE_READCALLBACK r,FMOD_FILE_SEEKCALLBACK s,FMOD_FILE_ASYNCREADCALLBACK ar,FMOD_FILE_ASYNCCANCELCALLBACK ac,int block){word(3);word(self==reinterpret_cast<FMOD::System*>(0x101));word(pointer(reinterpret_cast<const void*>(o),initOpenCallback_original,initOpenCallback_linked));word(pointer(reinterpret_cast<const void*>(c),initCloseCallback_original,initCloseCallback_linked));word(pointer(reinterpret_cast<const void*>(r),initReadCallback_original,initReadCallback_linked));word(pointer(reinterpret_cast<const void*>(s),initSeekCallback_original,initSeekCallback_linked));word(ar==NULL);word(ac==NULL);word(block);return static_cast<FMOD_RESULT>(current.fileResult);}
FMOD_RESULT soundGroup(FMOD::System*self,const char*name,FMOD::SoundGroup**out){word(4);word(self==reinterpret_cast<FMOD::System*>(0x101));cap->addText(std::string(name));*out=reinterpret_cast<FMOD::SoundGroup*>(0x202);return static_cast<FMOD_RESULT>(1);}
FMOD_RESULT channelGroup(FMOD::System*self,const char*name,FMOD::ChannelGroup**out){word(5);word(self==reinterpret_cast<FMOD::System*>(0x101));cap->addText(std::string(name));*out=reinterpret_cast<FMOD::ChannelGroup*>(0x303);return static_cast<FMOD_RESULT>(1);}
void levels(CSoundManager*self,float sound,float music,bool sm,bool mm){word(6);word(self==manager);real(sound);real(music);word(sm);word(mm);}
void log(Ogre::LogManager*self,const std::string&line,Ogre::LogMessageLevel level,bool skip){word(7);word(self==Ogre::LogManager::getSingletonPtr());word(level);word(skip);cap->addText(line);}
void side(void*raw,autotest::Capture&out,bool ours){current=*static_cast<Case*>(raw);cap=&out;
 union S{long double a;unsigned char bytes[sizeof(CSoundManager)];}storage;std::memset(&storage,0,sizeof(storage));manager=reinterpret_cast<CSoundManager*>(storage.bytes);initManagerCtor(manager,current.enabled);
 services->settings->SetInt(KSETTINGS_MUSICMUTE,current.musicMuted?3:0);services->settings->SetInt(KSETTINGS_SOUNDMUTE,current.soundMuted?-2:0);services->settings->SetFloat(KSETTINGS_F_MUSICVOLUME,.875f);services->settings->SetFloat(KSETTINGS_F_SOUNDVOLUME,.125f);
 detour::Set d;d.redirect(reinterpret_cast<char*>(&FMOD_System_Create),reinterpret_cast<char*>(&FMOD_System_Create),&create);d.redirect(reinterpret_cast<char*>(&initApi),reinterpret_cast<char*>(&initApi),&init);d.redirect(reinterpret_cast<char*>(&initFileApi),reinterpret_cast<char*>(&initFileApi),&files);d.redirect(reinterpret_cast<char*>(&initSoundGroup),reinterpret_cast<char*>(&initSoundGroup),&soundGroup);d.redirect(reinterpret_cast<char*>(&initChannelGroup),reinterpret_cast<char*>(&initChannelGroup),&channelGroup);d.redirect(reinterpret_cast<char*>(&initLog),reinterpret_cast<char*>(&initLog),&log);TL_REDIRECT(d,initLevels,&levels);if(d.failed())_exit(64);
 void(*fn)(CSoundManager*,CSettings*)=ours?initCandidate:initOriginal;
 if(autotest::beginInvocation(out,fn)){
  try{fn(manager,current.settings?services->settings:NULL);word(0);out.callCompleted=1;}
  catch(const Ogre::Exception&e){word(1);word(e.getNumber());cap->addText(e.getDescription());cap->addText(e.getSource());cap->addText(e.getFile());word(e.getLine());cap->addText(e.getFullDescription());}
 }
 word(manager->m_pDynamicPropertyFile==(current.settings?services->settings:NULL));word(manager->m_bUnknown6A8);word(manager->m_bUnknown6A9);word(manager->m_iUnknown18==reinterpret_cast<FMOD::System*>(0x101));word(manager->m_iUnknown6E0==reinterpret_cast<FMOD::SoundGroup*>(0x202));word(manager->m_iUnknown6E8==reinterpret_cast<FMOD::ChannelGroup*>(0x303));
 d.restore();manager->m_iUnknown18=NULL;manager->m_iUnknown6E0=NULL;manager->m_iUnknown6E8=NULL;initManagerDtor(manager);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
static int initializeNormalWorker(const tlhybrid_host*host){SystemsNativeMaster native;services=&native;autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_sound_initialize",reinterpret_cast<uintptr_t>(&initOriginal));
 for(unsigned enabled=0;enabled<2;++enabled)for(unsigned settings=0;settings<2;++settings)for(unsigned music=0;music<2;++music)for(unsigned sound=0;sound<2;++sound){Case c={enabled,settings,music,sound,0,0,0};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_initialize",cases++,&coverage);TL_CHECK(failures,ok);}
 for(int code=1;code<99;++code){Case c={1,1,1,1,0,code,0};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_initialize",cases++,&coverage);TL_CHECK(failures,ok);}
 coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}

TL_TEST(complete_sound_initialize){return systems_fixture::isolated(&initializeNormalWorker,host);}

static bool matchingExpectedInitializeThrow(const tlhybrid_host*host,const autotest::Outcome&a,const autotest::Outcome&b){
 bool cleanA=a.childStatus>=0&&WIFEXITED(a.childStatus)&&WEXITSTATUS(a.childStatus)==0;
 bool cleanB=b.childStatus>=0&&WIFEXITED(b.childStatus)&&WEXITSTATUS(b.childStatus)==0;
 return cleanA&&cleanB&&a.reportValid&&b.reportValid&&a.capture.issue==autotest::Capture::Complete&&b.capture.issue==autotest::Capture::Complete&&
  a.capture.callStarted==1&&b.capture.callStarted==1&&a.capture.callCompleted==0&&b.capture.callCompleted==0&&
  a.capture.callTarget==reinterpret_cast<uintptr_t>(&initOriginal)&&host->comparison_pair&&
  host->comparison_pair(a.capture.callTarget,b.capture.callTarget)&&
  a.capture.length==b.capture.length&&!std::memcmp(a.capture.data,b.capture.data,a.capture.length);
}
static int initializeExpectedUnwindWorker(const tlhybrid_host*host){
 SystemsNativeMaster native;services=&native;unsigned count=0;
 for(unsigned stage=0;stage<2;++stage)for(int code=1;code<99;++code){
  Case c={1,1,1,1,stage==0?code:0,0,stage==1?code:0};
  autotest::Outcome a,b;autotest::runChild(original,&c,a,1500,10000);autotest::runChild(candidate,&c,b,1500,10000);
  if(!matchingExpectedInitializeThrow(host,a,b)){
   host->log("    initialize expected unwind mismatch stage %u code %d status %d/%d valid %u/%u completion %u/%u\n",stage,code,a.childStatus,b.childStatus,a.reportValid,b.reportValid,a.capture.callCompleted,b.capture.callCompleted);return 1;
  }
  ++count;
 }
 // This is a supplemental abnormal-return comparison, never a Coverage receipt.
 host->log("    Sound initialize: %u matching expected unwinds, started1/completed0; acceptance credit 0\n",count);
 return count==196?0:1;
}
TL_TEST(complete_sound_initialize_expected_unwind){return systems_fixture::isolated(&initializeExpectedUnwindWorker,host);}
