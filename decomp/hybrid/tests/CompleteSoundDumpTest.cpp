#include <cstring>
#include <stdint.h>
#include <OgreLogManager.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "SoundManager.h"
#include "SoundInstance.h"
TL_ORIGINAL(void,soundDumpCtor,(CSoundManager*,bool),"_ZN13CSoundManagerC1Eb")
TL_ORIGINAL(void,soundDumpDtor,(CSoundManager*),"_ZN13CSoundManagerD1Ev")
TL_ORIGINAL(void,soundDumpOriginal,(CSoundManager*),"_ZN13CSoundManager10dumpSoundsEv")
extern "C" void soundDumpCandidate(CSoundManager*) __asm__("_ZN13CSoundManager10dumpSoundsEv");
extern "C" void dumpRootCtor(void*,const std::string&,const std::string&,const std::string&) __asm__("_ZN4Ogre4RootC1ERKSsS2_S2_");
extern "C" void dumpRootDtor(void*) __asm__("_ZN4Ogre4RootD1Ev");
extern "C" void dumpLog(Ogre::LogManager*,const std::string&,Ogre::LogMessageLevel,bool) __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
namespace {
struct Case{unsigned count,pattern;};autotest::Capture*cap;
void log(Ogre::LogManager*self,const std::string&line,Ogre::LogMessageLevel level,bool skip){cap->addText(line);unsigned l=level,b=skip,s=self==&Ogre::LogManager::getSingleton();cap->add(&l,4);cap->add(&b,4);cap->add(&s,4);}
void side(void*raw,autotest::Capture&out,bool ours){
 Case c=*static_cast<Case*>(raw);cap=&out;void*root=Ogre::NedAllocImpl::allocBytes(0x398,0,0,0);std::string empty;dumpRootCtor(root,empty,empty,empty);
 union S{long double a;unsigned char bytes[sizeof(CSoundManager)];} storage;std::memset(&storage,0,sizeof(storage));CSoundManager*s=reinterpret_cast<CSoundManager*>(storage.bytes);soundDumpCtor(s,false);
 const wchar_t*names[]={L"",L"a/b.ogg",L"\u0422\u0435\u0441\u0442.wav",L"\U0001f642 sound"};for(unsigned i=0;i<c.count;++i){CSoundInstance*sound=new CSoundInstance;sound->m_pSound=NULL;sound->m_soundName=names[(i+c.pattern)%4];s->m_pendingSounds.add(sound);}
 detour::Set d;d.redirect(reinterpret_cast<char*>(&dumpLog),reinterpret_cast<char*>(&dumpLog),&log);if(d.failed())_exit(64);
 if(ours)autotest::invoke(out,soundDumpCandidate,s);else autotest::invoke(out,soundDumpOriginal,s);
 d.restore();soundDumpDtor(s);dumpRootDtor(root);Ogre::NedAllocImpl::deallocBytes(root);
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_sound_dump){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_sound_dump",reinterpret_cast<uintptr_t>(&soundDumpOriginal));for(unsigned n=0;n<5;++n)for(unsigned p=0;p<4;++p){Case c={n,p};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_dump",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
