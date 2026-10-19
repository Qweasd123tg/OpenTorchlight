#include <cstring>
#include <stdint.h>
#include <OgreLogManager.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "SoundManager.h"
#include "SoundInstance.h"
#include "tests/SystemsNativeMaster.h"
#include "tests/SystemsFixtureWorker.h"
TL_ORIGINAL(void,createManagerCtor,(CSoundManager*,bool),"_ZN13CSoundManagerC1Eb")
TL_ORIGINAL(void,createManagerDtor,(CSoundManager*),"_ZN13CSoundManagerD1Ev")
TL_ORIGINAL(CSoundInstance*,createOriginal,(CSoundManager*,std::wstring,SOUND_TYPE,bool,float,float),"_ZN13CSoundManager11createSoundESbIwSt11char_traitsIwESaIwEE10SOUND_TYPEbff")
extern "C" CSoundInstance* createCandidate(CSoundManager*,std::wstring,SOUND_TYPE,bool,float,float) __asm__("_ZN13CSoundManager11createSoundESbIwSt11char_traitsIwESaIwEE10SOUND_TYPEbff");
extern "C" FMOD_RESULT createSoundApi(FMOD::System*,const char*,unsigned,FMOD_CREATESOUNDEXINFO*,FMOD::Sound**) __asm__("_ZN4FMOD6System11createSoundEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE");
extern "C" FMOD_RESULT createStreamApi(FMOD::System*,const char*,unsigned,FMOD_CREATESOUNDEXINFO*,FMOD::Sound**) __asm__("_ZN4FMOD6System12createStreamEPKcjP22FMOD_CREATESOUNDEXINFOPPNS_5SoundE");
extern "C" FMOD_RESULT createReleaseApi(FMOD::Sound*) __asm__("_ZN4FMOD5Sound7releaseEv");
extern "C" void createLogApi(Ogre::LogManager*,const std::string&,Ogre::LogMessageLevel,bool) __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
namespace {
struct Case{unsigned enabled,path,cache,loop;int type,result;};Case current;autotest::Capture*cap;
const wchar_t*names[]={L"plain.wav",L"media/Music.ogg",L"\u0422\u0435\u0441\u0442.oGg.bak",L"\U0001f642 audio.wav",L""};
void word(unsigned x){cap->add(&x,4);}void real(float x){cap->add(&x,4);}
FMOD_RESULT load(FMOD::System*self,const char*name,unsigned flags,FMOD_CREATESOUNDEXINFO*info,FMOD::Sound**out,unsigned kind){
 word(kind);word(self==reinterpret_cast<FMOD::System*>(0x101));word(info==NULL);word(flags);const CSoundInstance*s=reinterpret_cast<const CSoundInstance*>(name);cap->addText(s->m_soundName);word(s->m_soundType);word(s->m_loop);word(s->m_referenceCount);real(s->m_volume);real(s->m_volumeVariance);word(s->m_stream.isNull());*out=reinterpret_cast<FMOD::Sound*>(0x202);return static_cast<FMOD_RESULT>(current.result);
}
FMOD_RESULT sound(FMOD::System*s,const char*n,unsigned f,FMOD_CREATESOUNDEXINFO*i,FMOD::Sound**o){return load(s,n,f,i,o,1);}FMOD_RESULT stream(FMOD::System*s,const char*n,unsigned f,FMOD_CREATESOUNDEXINFO*i,FMOD::Sound**o){return load(s,n,f,i,o,2);}
FMOD_RESULT release(FMOD::Sound*p){word(3);word(p==NULL);return FMOD_OK;}
void log(Ogre::LogManager*self,const std::string&line,Ogre::LogMessageLevel level,bool skip){word(4);word(self==Ogre::LogManager::getSingletonPtr());word(level);word(skip);cap->addText(line);}
void side(void*raw,autotest::Capture&out,bool ours){current=*static_cast<Case*>(raw);cap=&out;
 union S{long double a;unsigned char bytes[sizeof(CSoundManager)];} storage;std::memset(&storage,0,sizeof(storage));CSoundManager*m=reinterpret_cast<CSoundManager*>(storage.bytes);createManagerCtor(m,false);m->m_bUnknown6A8=current.enabled;m->m_iUnknown18=reinterpret_cast<FMOD::System*>(0x101);
 std::wstring name=names[current.path];CSoundInstance*cached=NULL;
 if(current.cache){cached=new CSoundInstance;cached->m_soundName=current.cache==2?L"other":name;cached->m_soundType=static_cast<SOUND_TYPE>(current.cache==3?19:current.type);cached->m_loop=current.cache==4;cached->m_volume=current.cache==5?4.0f:.25f;cached->m_referenceCount=7;m->m_pendingSounds.add(cached);}
 detour::Set d;d.redirect(reinterpret_cast<char*>(&createSoundApi),reinterpret_cast<char*>(&createSoundApi),&sound);d.redirect(reinterpret_cast<char*>(&createStreamApi),reinterpret_cast<char*>(&createStreamApi),&stream);d.redirect(reinterpret_cast<char*>(&createReleaseApi),reinterpret_cast<char*>(&createReleaseApi),&release);d.redirect(reinterpret_cast<char*>(&createLogApi),reinterpret_cast<char*>(&createLogApi),&log);if(d.failed())_exit(64);
 CSoundInstance*(*fn)(CSoundManager*,std::wstring,SOUND_TYPE,bool,float,float)=ours?createCandidate:createOriginal;
 CSoundInstance*ret=NULL;if(autotest::beginInvocation(out,fn)){ret=fn(m,name,static_cast<SOUND_TYPE>(current.type),current.loop,.25f,.875f);out.callCompleted=1;}
 word(ret!=NULL);word(ret==cached);word(m->m_pendingSounds.size());if(ret){cap->addText(ret->m_soundName);word(ret->m_soundType);word(ret->m_loop);real(ret->m_volume);real(ret->m_volumeVariance);word(ret->m_referenceCount);word(ret->m_pSound==reinterpret_cast<FMOD::Sound*>(0x202));word(ret->m_stream.isNull());word(ret->m_pSoundData==NULL);}
 if(cached)word(cached->m_referenceCount);for(unsigned i=0;i<m->m_pendingSounds.size();++i)m->m_pendingSounds[i]->m_pSound=NULL;
 d.restore();m->m_iUnknown18=NULL;createManagerDtor(m);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
static int complete_sound_create_worker(const tlhybrid_host*host){SystemsNativeMaster native;autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_sound_create",reinterpret_cast<uintptr_t>(&createOriginal));
 for(unsigned path=0;path<5;++path)for(int type=0;type<9;++type)for(unsigned loop=0;loop<2;++loop){Case c={1,path,0,loop,type,0};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_create",cases++,&coverage);TL_CHECK(failures,ok);}
 for(int code=1;code<99;++code){Case c={1,static_cast<unsigned>(code%5),0,0,1+code%6,code};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_create",cases++,&coverage);TL_CHECK(failures,ok);}
 for(unsigned cache=1;cache<6;++cache)for(int type=1;type<7;++type){Case c={1,2,cache,1,type,0};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_create",cases++,&coverage);TL_CHECK(failures,ok);}
 for(unsigned enabled=0;enabled<2;++enabled){Case c={enabled,0,1,0,1,0};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_create",cases++,&coverage);TL_CHECK(failures,ok);}
 coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}

TL_TEST(complete_sound_create){return systems_fixture::isolated(&complete_sound_create_worker,host);}
