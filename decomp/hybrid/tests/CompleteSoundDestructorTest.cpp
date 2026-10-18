#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "tests/Detour.h"
#include "SoundManager.h"
#include "SoundInstance.h"
TL_ORIGINAL(void,soundDestroyCtor,(CSoundManager*,bool),"_ZN13CSoundManagerC1Eb")
TL_ORIGINAL(void,soundDestroyOriginal,(CSoundManager*),"_ZN13CSoundManagerD1Ev")
extern "C" void soundDestroyCandidate(CSoundManager*) __asm__("_ZN13CSoundManagerD1Ev");
TL_FUNCTION(soundDestroyMusic,"_ZN13CSoundManager9stopMusicEv")
TL_FUNCTION(soundDestroyStop,"_ZN13CSoundManager9stopSoundEi")
extern "C" FMOD_RESULT destroyDSP(FMOD::DSP*) __asm__("_ZN4FMOD3DSP7releaseEv");
extern "C" FMOD_RESULT destroyChannelGroup(FMOD::ChannelGroup*) __asm__("_ZN4FMOD12ChannelGroup7releaseEv");
extern "C" FMOD_RESULT destroySoundGroup(FMOD::SoundGroup*) __asm__("_ZN4FMOD10SoundGroup7releaseEv");
extern "C" FMOD_RESULT destroySystem(FMOD::System*) __asm__("_ZN4FMOD6System7releaseEv");
namespace {
struct Case{unsigned flags,queue,pending;};autotest::Capture*cap;
void word(unsigned x){cap->add(&x,sizeof(x));}
void music(CSoundManager*){word(1);}void stop(CSoundManager*,int c){word(2);word(c);}
FMOD_RESULT dsp(FMOD::DSP*p){word(3);word(reinterpret_cast<uintptr_t>(p));return FMOD_OK;}
FMOD_RESULT channel(FMOD::ChannelGroup*p){word(4);word(reinterpret_cast<uintptr_t>(p));return FMOD_OK;}
FMOD_RESULT group(FMOD::SoundGroup*p){word(5);word(reinterpret_cast<uintptr_t>(p));return FMOD_OK;}
FMOD_RESULT system(FMOD::System*p){word(6);word(reinterpret_cast<uintptr_t>(p));return FMOD_OK;}
CSoundInstance* instance(unsigned count){CSoundInstance*s=new CSoundInstance;s->m_pSound=NULL;s->m_referenceCount=count;s->m_soundName=L"Destructor fixture";return s;}
void side(void*raw,autotest::Capture&out,bool ours){
 Case c=*static_cast<Case*>(raw);cap=&out;union S{long double a;unsigned char bytes[sizeof(CSoundManager)];} storage;std::memset(&storage,0,sizeof(storage));CSoundManager*s=reinterpret_cast<CSoundManager*>(storage.bytes);soundDestroyCtor(s,false);
 s->m_iUnknown6B8=c.flags&1?reinterpret_cast<FMOD::DSP*>(0x101):NULL;s->m_iUnknown6C0=c.flags&2?reinterpret_cast<FMOD::ChannelGroup*>(0x202):NULL;s->m_iUnknown6E0=c.flags&4?reinterpret_cast<FMOD::SoundGroup*>(0x303):NULL;s->m_iUnknown6E8=c.flags&8?reinterpret_cast<FMOD::ChannelGroup*>(0x404):NULL;s->m_iUnknown18=c.flags&16?reinterpret_cast<FMOD::System*>(0x505):NULL;s->m_iUnknown6F0=c.flags&1?-1:29;
 CSoundInstance*queued[3]={0,0,0};for(unsigned i=0;i<c.queue;++i){queued[i]=instance(10+i);s->m_soundList0.push_back(100+i);s->m_soundList1.push_back(queued[i]);s->m_soundList2.push_back(i);s->m_soundList3.push_back(i);}
 for(unsigned i=0;i<c.pending;++i)s->m_pendingSounds.add(instance(20+i));
 detour::Set d;TL_REDIRECT(d,soundDestroyMusic,&music);TL_REDIRECT(d,soundDestroyStop,&stop);
 d.redirect(reinterpret_cast<char*>(&destroyDSP),reinterpret_cast<char*>(&destroyDSP),&dsp);d.redirect(reinterpret_cast<char*>(&destroyChannelGroup),reinterpret_cast<char*>(&destroyChannelGroup),&channel);d.redirect(reinterpret_cast<char*>(&destroySoundGroup),reinterpret_cast<char*>(&destroySoundGroup),&group);d.redirect(reinterpret_cast<char*>(&destroySystem),reinterpret_cast<char*>(&destroySystem),&system);if(d.failed())_exit(64);
 if(ours)autotest::invoke(out,soundDestroyCandidate,s);else autotest::invoke(out,soundDestroyOriginal,s);
 word(s->m_iUnknown6F0);for(unsigned i=0;i<c.queue;++i)word(queued[i]->m_referenceCount);
 d.restore();for(unsigned i=0;i<c.queue;++i)delete queued[i];
}
void original(void*p,autotest::Capture&o){side(p,o,false);}void candidate(void*p,autotest::Capture&o){side(p,o,true);}
}
TL_TEST(complete_sound_destructor){autotest::Stats stats={0,0,0};int failures=0;unsigned cases=0;autotest::Coverage coverage("complete_sound_destructor",reinterpret_cast<uintptr_t>(&soundDestroyOriginal));for(unsigned f=0;f<32;++f)for(unsigned q=0;q<4;++q){Case c={f,q,q%3};bool ok=autotest::compareCase(original,candidate,&c,stats,host,"complete_sound_destructor",cases++,&coverage);TL_CHECK(failures,ok);}coverage.report(host);return failures+stats.incomplete+(coverage.completed!=cases);}
