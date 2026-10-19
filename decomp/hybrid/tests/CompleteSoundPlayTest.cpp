#include <cstring>
#include <stdint.h>
#include <OgreRoot.h>
#include <OgreSceneNode.h>
#include <OgreLogManager.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "SoundManager.h"
#include "SoundInstance.h"
#include "SettingsVariables.h"
#include "Console.h"
#include "tests/SystemsNativeMaster.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,playManagerCtor,(CSoundManager*,bool),"_ZN13CSoundManagerC1Eb")
TL_ORIGINAL(void,playManagerDtor,(CSoundManager*),"_ZN13CSoundManagerD1Ev")
TL_ORIGINAL(int,playOriginal,(CSoundManager*,CSoundInstance*,Ogre::SceneNode*,int,float),"_ZN13CSoundManager9playSoundEP14CSoundInstancePN4Ogre9SceneNodeEif")
extern "C" int playCandidate(CSoundManager*,CSoundInstance*,Ogre::SceneNode*,int,float) __asm__("_ZN13CSoundManager9playSoundEP14CSoundInstancePN4Ogre9SceneNodeEif");
TL_FUNCTION(playConsole,"_ZN8CConsole16addTextNoHistoryESbIwSt11char_traitsIwESaIwEE")
extern "C" FMOD_RESULT playApi(FMOD::System*,FMOD_CHANNELINDEX,FMOD::Sound*,bool,FMOD::Channel**) __asm__("_ZN4FMOD6System9playSoundE17FMOD_CHANNELINDEXPNS_5SoundEbPPNS_7ChannelE");
extern "C" FMOD_RESULT playGetChannel(FMOD::System*,int,FMOD::Channel**) __asm__("_ZN4FMOD6System10getChannelEiPPNS_7ChannelE");
extern "C" FMOD_RESULT playPlaying(FMOD::Channel*,bool*) __asm__("_ZN4FMOD7Channel9isPlayingEPb");
extern "C" FMOD_RESULT playGetIndex(FMOD::Channel*,int*) __asm__("_ZN4FMOD7Channel8getIndexEPi");
extern "C" FMOD_RESULT playVolume(FMOD::Channel*,float) __asm__("_ZN4FMOD7Channel9setVolumeEf");
extern "C" FMOD_RESULT playPaused(FMOD::Channel*,bool) __asm__("_ZN4FMOD7Channel9setPausedEb");
extern "C" FMOD_RESULT playStop(FMOD::Channel*) __asm__("_ZN4FMOD7Channel4stopEv");
extern "C" void playLog(Ogre::LogManager*,const std::string&,Ogre::LogMessageLevel,bool) __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
namespace {
struct Case{unsigned gate,scenario,debug,volume,nullSound;int type,requested,result,index;};Case current;autotest::Capture*cap;SystemsNativeMaster*services;Ogre::SceneNode*nodes[2];CConsole*consoleBoundary;unsigned gets;
void word(unsigned x){cap->add(&x,4);}void real(float x){cap->add(&x,4);}
FMOD_RESULT play(FMOD::System*self,FMOD_CHANNELINDEX which,FMOD::Sound*sound,bool paused,FMOD::Channel**out){word(1);word(self==reinterpret_cast<FMOD::System*>(0x101));word(which);word(sound==reinterpret_cast<FMOD::Sound*>(0x202));word(paused);*out=reinterpret_cast<FMOD::Channel*>(0x303);return static_cast<FMOD_RESULT>(current.result);}
FMOD_RESULT get(FMOD::System*self,int index,FMOD::Channel**out){word(2);word(self==reinterpret_cast<FMOD::System*>(0x101));word(index);*out=reinterpret_cast<FMOD::Channel*>(0x303);return current.scenario==3 && gets++==0?static_cast<FMOD_RESULT>(1):FMOD_OK;}
FMOD_RESULT playing(FMOD::Channel*self,bool*out){word(3);word(self==reinterpret_cast<FMOD::Channel*>(0x303));*out=current.scenario!=5;return current.scenario==4?static_cast<FMOD_RESULT>(1):FMOD_OK;}
FMOD_RESULT index(FMOD::Channel*self,int*out){word(4);word(self==reinterpret_cast<FMOD::Channel*>(0x303));*out=current.index;return FMOD_OK;}
FMOD_RESULT volume(FMOD::Channel*self,float value){word(5);word(self==reinterpret_cast<FMOD::Channel*>(0x303));real(value);return FMOD_OK;}
FMOD_RESULT paused(FMOD::Channel*self,bool value){word(6);word(self==reinterpret_cast<FMOD::Channel*>(0x303));word(value);return FMOD_OK;}
FMOD_RESULT stop(FMOD::Channel*self){word(7);word(self==reinterpret_cast<FMOD::Channel*>(0x303));return FMOD_OK;}
void log(Ogre::LogManager*self,const std::string&text,Ogre::LogMessageLevel level,bool skip){word(8);word(self==Ogre::LogManager::getSingletonPtr());word(level);word(skip);cap->addText(text);}
// The Console collaborator is an opaque non-null boundary: only receiver and
// text are observed. This fixture makes no Console constructor/runtime claim.
void console(CConsole*self,std::wstring text){word(9);word(self==consoleBoundary);cap->addText(text);}
void side(void*raw,autotest::Capture&out,bool ours){current=*static_cast<Case*>(raw);cap=&out;gets=0;
 union S{long double a;unsigned char bytes[sizeof(CSoundManager)];} storage;std::memset(&storage,0,sizeof(storage));CSoundManager*m=reinterpret_cast<CSoundManager*>(storage.bytes);playManagerCtor(m,false);
 m->m_iUnknown18=reinterpret_cast<FMOD::System*>(0x101);m->m_bUnknown6A8=current.gate&1;m->m_bUnknown6A9=current.gate&2;m->m_iUnknown14=5;
 CSoundInstance*instance=new CSoundInstance;instance->m_pSound=reinterpret_cast<FMOD::Sound*>(0x202);instance->m_soundType=static_cast<SOUND_TYPE>(current.type);instance->m_soundName=L"\u0422\u0435\u0441\u0442/\U0001f642.ogg";instance->m_volume=.125f;
 if(current.requested>=0 && current.requested<64 && current.scenario)m->m_channels[current.requested].m_iUnknown10=nodes[current.scenario==2?1:0];
 services->settings->SetInt(KSETTINGS_SOUND_DEBUG,current.debug);CConsole*previous=services->master->m_console;services->master->m_console=consoleBoundary;
 detour::Set d;d.redirect(reinterpret_cast<char*>(&playApi),reinterpret_cast<char*>(&playApi),&play);d.redirect(reinterpret_cast<char*>(&playGetChannel),reinterpret_cast<char*>(&playGetChannel),&get);d.redirect(reinterpret_cast<char*>(&playPlaying),reinterpret_cast<char*>(&playPlaying),&playing);d.redirect(reinterpret_cast<char*>(&playGetIndex),reinterpret_cast<char*>(&playGetIndex),&index);d.redirect(reinterpret_cast<char*>(&playVolume),reinterpret_cast<char*>(&playVolume),&volume);d.redirect(reinterpret_cast<char*>(&playPaused),reinterpret_cast<char*>(&playPaused),&paused);d.redirect(reinterpret_cast<char*>(&playStop),reinterpret_cast<char*>(&playStop),&stop);d.redirect(reinterpret_cast<char*>(&playLog),reinterpret_cast<char*>(&playLog),&log);TL_REDIRECT(d,playConsole,&console);if(d.failed())_exit(64);
 const uint32_t floats[]={0x3f000000,0x00000000,0xbf000000,0x7fc12345,0x7f800000,0x3fc00000};float value;std::memcpy(&value,&floats[current.volume],4);
 CSoundInstance*arg=current.nullSound?NULL:instance;if(ours)autotest::invoke(out,playCandidate,m,arg,nodes[0],current.requested,value);else autotest::invoke(out,playOriginal,m,arg,nodes[0],current.requested,value);
 word(m->m_iUnknown14);for(unsigned i=0;i<64;++i){word(m->m_channels[i].m_iUnknown10==nodes[0]);word(m->m_channels[i].m_iUnknown10==nodes[1]);}
 services->master->m_console=previous;d.restore();m->m_iUnknown18=NULL;instance->m_pSound=NULL;delete instance;playManagerDtor(m);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
static int complete_sound_play_worker(const tlhybrid_host*host){SystemsNativeMaster native;services=&native;unsigned consoleToken=0;consoleBoundary=reinterpret_cast<CConsole*>(&consoleToken);Ogre::SceneManager*scene=native.root->createSceneManager(Ogre::ST_GENERIC);nodes[0]=scene->getRootSceneNode()->createChildSceneNode();nodes[1]=scene->getRootSceneNode()->createChildSceneNode();
 autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_sound_play",reinterpret_cast<uintptr_t>(&playOriginal));
 for(unsigned gate=0;gate<4;++gate)for(int type=1;type<7;++type){Case c={gate,0,0,0,0,type,-1,0,19};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_play",cases++,&coverage);TL_CHECK(failures,ok);}
 for(unsigned value=0;value<6;++value)for(unsigned debug=0;debug<2;++debug){Case c={3,0,debug,value,0,2,-1,0,63};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_play",cases++,&coverage);TL_CHECK(failures,ok);}
 const int requests[]={-1,0,63,64};const int types[]={1,2,4,6};for(unsigned t=0;t<4;++t)for(unsigned r=0;r<4;++r)for(unsigned scenario=0;scenario<6;++scenario){Case c={3,scenario,1,0,0,types[t],requests[r],0,19};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_play",cases++,&coverage);TL_CHECK(failures,ok);}
 for(int code=1;code<99;++code){Case c={3,0,0,0,0,2,-1,code,0};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_play",cases++,&coverage);TL_CHECK(failures,ok);}
 for(unsigned gate=0;gate<4;++gate){Case c={gate,0,0,0,1,2,-1,0,0};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_play",cases++,&coverage);TL_CHECK(failures,ok);}
 coverage.report(host);native.root->destroySceneManager(scene);return failures+stats.incomplete+(coverage.completed!=cases);}

TL_TEST(complete_sound_play){return systems_fixture::isolated(&complete_sound_play_worker,host);}
