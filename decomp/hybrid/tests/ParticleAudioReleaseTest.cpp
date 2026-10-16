#include <cstring>
#include <stdint.h>
#include <vector>
#include <string>
#include <new>
#include "TArrayList.h"
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,audioReleaseOld,(void*),"_ZN13CSoundManager19releaseUnusedSoundsEv")
extern "C" void audioReleaseNew(void*) __asm__("_ZN13CSoundManager19releaseUnusedSoundsEv");
TL_FUNCTION(audioReleaseStopTarget,"_ZN13CSoundManager9stopSoundEi")
extern "C" char audioReleaseLogTarget[] __asm__("_ZN4Ogre10LogManager12getSingletonEv");
extern "C" char audioReleaseMessageTarget[] __asm__("_ZN4Ogre10LogManager10logMessageERKSsNS_15LogMessageLevelEb");
namespace {
struct Case{unsigned index;};struct State{autotest::Capture* out;void* manager;uint64_t sounds[6][12],logger;unsigned calls,deleted;};State* active;
void add(unsigned v){active->out->add(&v,4);}void invalid(){active->out->issue=autotest::Capture::InvalidReport;}
void stop(void* p,int channel){if(p!=active->manager)invalid();++active->calls;add(1);add(channel);}
unsigned id(void* p){for(unsigned i=0;i<6;++i)if(p==active->sounds[i])return i;invalid();return 99;}
void destroy(void* p){unsigned n=id(p);if(n==99)return;++active->calls;add(2);add(n);if(active->deleted&(1u<<n))invalid();active->deleted|=1u<<n;int refs;std::memcpy(&refs,reinterpret_cast<char*>(p)+0x48,4);if(refs>0)invalid();}
void* logger(){++active->calls;add(3);return &active->logger;}
void message(void* p,const std::string& text,int level,bool debug){if(p!=&active->logger)invalid();++active->calls;add(4);active->out->addText(text);add(level);add(debug);}
void side(Case& c,bool ours,autotest::Capture& out){
 uint64_t manager[224]={0};State state;std::memset(state.sounds,0,sizeof(state.sounds));state.out=&out;state.manager=manager;state.calls=state.deleted=0;active=&state;void* table[2]={0,reinterpret_cast<void*>(&destroy)};
 std::vector<int>* ids=new(reinterpret_cast<char*>(manager)+0x30)std::vector<int>;std::vector<void*>* queued=new(reinterpret_cast<char*>(manager)+0x48)std::vector<void*>;std::vector<float>* volumes=new(reinterpret_cast<char*>(manager)+0x60)std::vector<float>;std::vector<float>* delays=new(reinterpret_cast<char*>(manager)+0x78)std::vector<float>;TArrayList<void*>* pending=new(reinterpret_cast<char*>(manager)+0x90)TArrayList<void*>(2);
 unsigned count=c.index%7;for(unsigned i=0;i<6;++i){*reinterpret_cast<void***>(state.sounds[i])=table;unsigned refs=(c.index/7+i)%4;refs=refs==3?0xffffffffu:refs;std::memcpy(reinterpret_cast<char*>(state.sounds[i])+0x48,&refs,4);if(i<count)pending->add(state.sounds[i]);}
 if(count)for(unsigned i=0;i<(c.index/3)%5;++i){ids->push_back(i+31);queued->push_back(state.sounds[i%count]);volumes->push_back(i+0.25f);delays->push_back(i+0.5f);}
 int channel=c.index&1?5:-1;std::memcpy(reinterpret_cast<char*>(manager)+0x6f0,&channel,4);
 detour::Set d;TL_REDIRECT(d,audioReleaseStopTarget,&stop);d.redirect(audioReleaseLogTarget,audioReleaseLogTarget,&logger);d.redirect(audioReleaseMessageTarget,audioReleaseMessageTarget,&message);if(d.failed()){invalid();return;}
 typedef void(*Fn)(void*);Fn fn=ours?audioReleaseNew:audioReleaseOld;if(!autotest::beginInvocation(out,fn))return;fn(manager);out.callCompleted=1;add(state.calls);add(state.deleted);out.add(reinterpret_cast<char*>(manager)+0x6f0,4);add(ids->size());add(queued->size());add(volumes->size());add(delays->size());add(pending->size());for(unsigned i=0;i<pending->size();++i)add(id((*pending)[i]));for(unsigned i=0;i<6;++i)out.add(reinterpret_cast<char*>(state.sounds[i])+0x48,4);
 pending->~TArrayList();delays->~vector();volumes->~vector();queued->~vector();ids->~vector();
}
void before(void* p,autotest::Capture& o){side(*static_cast<Case*>(p),false,o);}void after(void* p,autotest::Capture& o){side(*static_cast<Case*>(p),true,o);}
}
TL_TEST(state_audio_a6c650){autotest::Coverage cov("state_audio_a6c650",reinterpret_cast<uintptr_t>(&audioReleaseOld));for(unsigned i=0;i<84;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log(" audio release case%u exits%d/%d issues%u/%u\n",i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return cov.completed==84?0:1;}
