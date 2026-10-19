#include <cstring>
#include <stdint.h>
#include <OgreLogManager.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "SoundManager.h"
#include "SoundInstance.h"
TL_ORIGINAL(void,lengthManagerCtor,(CSoundManager*,bool),"_ZN13CSoundManagerC1Eb")
TL_ORIGINAL(void,lengthManagerDtor,(CSoundManager*),"_ZN13CSoundManagerD1Ev")
TL_ORIGINAL(float,lengthOriginal,(CSoundManager*,CSoundInstance*),"_ZN13CSoundManager14getSoundLengthEP14CSoundInstance")
extern "C" float lengthCandidate(CSoundManager*,CSoundInstance*) __asm__("_ZN13CSoundManager14getSoundLengthEP14CSoundInstance");
extern "C" FMOD_RESULT lengthSoundGet(FMOD::Sound*,unsigned int*,unsigned int) __asm__("_ZN4FMOD5Sound9getLengthEPjj");
extern "C" void lengthLog(Ogre::LogManager*,const std::string&,Ogre::LogMessageLevel,bool) __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
namespace {
struct Case { unsigned mode,milliseconds; int result; };Case current;autotest::Capture* cap;FMOD::Sound* handle;
void word(unsigned x){cap->add(&x,4);}
FMOD_RESULT getLength(FMOD::Sound*self,unsigned int*out,unsigned int unit){word(1);word(self==handle);word(unit);*out=current.milliseconds;return static_cast<FMOD_RESULT>(current.result);}
void log(Ogre::LogManager*self,const std::string&text,Ogre::LogMessageLevel level,bool skipped){word(2);word(self==Ogre::LogManager::getSingletonPtr());word(level);word(skipped);cap->addText(text);}
void side(void*raw,autotest::Capture&out,bool ours){
 current=*static_cast<Case*>(raw);cap=&out;
 Ogre::LogManager*owned=Ogre::LogManager::getSingletonPtr()?NULL:new Ogre::LogManager;
 union Storage {long double a;unsigned char bytes[sizeof(CSoundManager)];} storage;std::memset(&storage,0,sizeof(storage));
 CSoundManager*manager=reinterpret_cast<CSoundManager*>(storage.bytes);lengthManagerCtor(manager,false);
 CSoundInstance*instance=new CSoundInstance;instance->m_pSound=NULL;instance->m_referenceCount=37;
 unsigned opaqueSound=0;handle=reinterpret_cast<FMOD::Sound*>(&opaqueSound);if(current.mode==2)instance->m_pSound=handle;
 detour::Set d;d.redirect(reinterpret_cast<char*>(&lengthSoundGet),reinterpret_cast<char*>(&lengthSoundGet),&getLength);d.redirect(reinterpret_cast<char*>(&lengthLog),reinterpret_cast<char*>(&lengthLog),&log);if(d.failed())_exit(64);
 CSoundInstance*arg=current.mode?instance:NULL;
 if(ours)autotest::invoke(out,lengthCandidate,manager,arg);else autotest::invoke(out,lengthOriginal,manager,arg);
 word(instance->m_referenceCount);word(instance->m_pSound==handle);d.restore();instance->m_pSound=NULL;delete instance;lengthManagerDtor(manager);delete owned;
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_sound_length){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_sound_length",reinterpret_cast<uintptr_t>(&lengthOriginal));
 const unsigned ms[]={0,1,999,1000,1001,65535,16777215,16777216,16777217,2147483647u,2147483648u,4294967295u};
 for(unsigned mode=0;mode<3;++mode)for(unsigned i=0;i<12;++i){Case c={mode,ms[i],0};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_length",cases++,&coverage);TL_CHECK(failures,ok);}
 for(int result=1;result<100;++result){Case c={2,4294967295u,result};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_length",cases++,&coverage);TL_CHECK(failures,ok);}
 const int unknown[]={-1,-2147483647-1,65536,2147483647};for(unsigned i=0;i<4;++i){Case c={2,0,unknown[i]};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_length",cases++,&coverage);TL_CHECK(failures,ok);}
 coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
