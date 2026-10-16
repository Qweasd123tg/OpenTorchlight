#include <string>
#include <new>
#include <stdexcept>
#include <OgreLogManager.h>
#include "AutoTest.h"
#include "Detour.h"
#define private public
#include "CollisionModel.h"
#undef private
#include "PuzzleRandomizer.h"
TL_ORIGINAL(void, puzzleCtorOriginal, (void*,CResourceManager*), "_ZN17CPuzzleRandomizerC1EP16CResourceManager")
TL_ORIGINAL(void, puzzleDtorOriginal, (void*), "_ZN17CPuzzleRandomizerD1Ev")
TL_ORIGINAL(void, puzzleActiveOriginal, (void*,unsigned), "_ZN17CPuzzleRandomizer15setActiveInputsEj")
TL_ORIGINAL(void, puzzleTriggerOriginal, (void*,EPUZZLE_INPUTS), "_ZN17CPuzzleRandomizer7triggerE14EPUZZLE_INPUTS")
TL_ORIGINAL(void, collisionCtorOriginal, (void*,Ogre::SceneManager*,const std::wstring&), "_ZN15CCollisionModelC1EPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void, collisionDtorOriginal, (void*), "_ZN15CCollisionModelD1Ev")
TL_ORIGINAL(void, collisionUnloadOriginal, (void*), "_ZN15CCollisionModel11unloadModelEv")
extern "C" void puzzleCtorCandidate(void*,CResourceManager*) __asm__("_ZN17CPuzzleRandomizerC1EP16CResourceManager");
extern "C" void puzzleDtorCandidate(void*) __asm__("_ZN17CPuzzleRandomizerD1Ev");
extern "C" void puzzleActiveCandidate(void*,unsigned) __asm__("_ZN17CPuzzleRandomizer15setActiveInputsEj");
extern "C" void puzzleTriggerCandidate(void*,EPUZZLE_INPUTS) __asm__("_ZN17CPuzzleRandomizer7triggerE14EPUZZLE_INPUTS");
extern "C" void collisionCtorCandidate(void*,Ogre::SceneManager*,const std::wstring&) __asm__("_ZN15CCollisionModelC1EPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEE");
extern "C" void collisionUnloadCandidate(void*) __asm__("_ZN15CCollisionModel11unloadModelEv");
TL_FUNCTION(randomTarget,"_ZN9UTILITIES28randomIntegerBetweenVolatileEii")
TL_FUNCTION(listenerTarget,"_ZN17CPuzzleRandomizer16addLevelListenerEv")
TL_FUNCTION(loadTarget,"_ZN15CCollisionModel9loadModelESbIwSt11char_traitsIwESaIwEE")
namespace {
struct Case { unsigned op,index; }; Case* input; autotest::Capture* output; unsigned calls; void* object;
void invalid(){output->issue=autotest::Capture::InvalidReport;}
void number(unsigned value){output->add(&value,sizeof(value));}
void text(const std::wstring& value){unsigned n=value.size();number(n);output->add(value.data(),n*sizeof(wchar_t));}
int randomBetween(int low,int high){number(1);number(low);number(high);++calls;if(low||high<1||high>4)invalid();if(input->op==0&&input->index%7==0&&calls==2)throw std::runtime_error("puzzle constructor");return (input->index*17+calls*7)%(high+1);}
void listener(void* p){if(p!=object)invalid();number(2);++calls;}
void load(void* p,const std::wstring& name){if(p!=object)invalid();number(3);text(name);++calls;if(input->index%4==3)throw std::runtime_error("model constructor");static_cast<CCollisionModel*>(p)->m_sFilename=name;}
void puzzleState(CPuzzleRandomizer* p){number(p->m_bUnknown60);number(p->m_iActiveInputs);number(p->m_bEnabled);for(unsigned i=0;i<6;++i){number(p->m_inputOrder[i]);number(p->m_inputTriggered[i]);}number(p->m_iUnknown8C);number(p->m_pResourceManager==reinterpret_cast<CResourceManager*>(uintptr_t(0x123400)));}
void body(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;object=autotest::allocate(1024);int before=g_iTotalCountOfObjects;
 detour::Set patches;TL_REDIRECT(patches,randomTarget,&randomBetween);TL_REDIRECT(patches,listenerTarget,&listener);TL_REDIRECT(patches,loadTarget,&load);if(patches.failed()){invalid();return;}
 if(c.op<=3){CPuzzleRandomizer* p=static_cast<CPuzzleRandomizer*>(object);
  if(c.op==0){void(*fn)(void*,CResourceManager*)=ours?puzzleCtorCandidate:puzzleCtorOriginal;if(!autotest::beginInvocation(out,fn))return;bool threw=false;try{fn(p,reinterpret_cast<CResourceManager*>(uintptr_t(0x123400)));}catch(const std::runtime_error&){threw=true;}out.callCompleted=1;int constructed=g_iTotalCountOfObjects;number(threw);number(constructed-before);if(!threw){puzzleState(p);puzzleDtorOriginal(p);}number(g_iTotalCountOfObjects-before);if(constructed!=before+1||g_iTotalCountOfObjects!=constructed)invalid();}
  else{puzzleCtorOriginal(p,reinterpret_cast<CResourceManager*>(uintptr_t(0x123400)));calls=0;int constructed=g_iTotalCountOfObjects;
   if(c.op==1){TSafePointer<CRunicCore> witness;witness.setObject(p);p->SetName(std::wstring(c.index+1,L'X'));void(*fn)(void*)=ours?puzzleDtorCandidate:puzzleDtorOriginal;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;number(witness.getObject()==0);number(g_iTotalCountOfObjects-before);if(witness.getObject()||constructed!=before+1||g_iTotalCountOfObjects!=constructed)invalid();}
   else if(c.op==2){const unsigned counts[]={0,1,2,3,4,5,6,7,100,0xffffffffu};void(*fn)(void*,unsigned)=ours?puzzleActiveCandidate:puzzleActiveOriginal;if(!autotest::beginInvocation(out,fn))return;fn(p,counts[c.index%10]);out.callCompleted=1;puzzleState(p);number(calls);puzzleDtorOriginal(p);}
   else{p->m_iActiveInputs=2+c.index%4;p->m_bEnabled=c.index%11!=0;p->m_bUnknown60=c.index%13==0;p->m_iUnknown8C=17;for(unsigned i=0;i<6;++i){p->m_inputOrder[i]=(i+1)%p->m_iActiveInputs;p->m_inputTriggered[i]=i<c.index%7;}unsigned mode=c.index/4%4;int value=mode==0?int(c.index%p->m_iActiveInputs):mode==1?int((c.index%p->m_iActiveInputs+1)%p->m_iActiveInputs):mode==2?-1:p->m_iActiveInputs;
    Ogre::LogManager* manager=0;if(!Ogre::LogManager::getSingletonPtr())manager=new Ogre::LogManager;
    void(*fn)(void*,EPUZZLE_INPUTS)=ours?puzzleTriggerCandidate:puzzleTriggerOriginal;if(!autotest::beginInvocation(out,fn))return;fn(p,static_cast<EPUZZLE_INPUTS>(value));out.callCompleted=1;puzzleState(p);number(calls);delete manager;puzzleDtorOriginal(p);}
  }
 }else{CCollisionModel* p=static_cast<CCollisionModel*>(object);Ogre::SceneManager* scene=reinterpret_cast<Ogre::SceneManager*>(uintptr_t(0x456700));
  if(c.op==4){std::wstring name=c.index%5==0?L"":std::wstring(c.index+1,L'a'+c.index%20);void(*fn)(void*,Ogre::SceneManager*,const std::wstring&)=ours?collisionCtorCandidate:collisionCtorOriginal;if(!autotest::beginInvocation(out,fn))return;bool threw=false;try{fn(p,scene,name);}catch(const std::runtime_error&){threw=true;}out.callCompleted=1;int constructed=g_iTotalCountOfObjects;number(threw);number(constructed-before);number(calls);if(!threw){text(p->m_sFilename);number(p->m_sMeshName.size());out.add(&p->m_vUnknown20,sizeof(Ogre::Vector3));out.add(&p->m_vUnknown2C,sizeof(Ogre::Vector3));number(p->m_pCollisionList==0);number(p->m_pSceneManager==scene);collisionDtorOriginal(p);}number(g_iTotalCountOfObjects-before);if(constructed!=before+1||g_iTotalCountOfObjects!=constructed)invalid();}
  else{std::wstring empty;collisionCtorOriginal(p,scene,empty);p->m_sFilename=std::wstring(c.index*4,L'Z');p->m_sMeshName=std::string(c.index,'k');void(*fn)(void*)=ours?collisionUnloadCandidate:collisionUnloadOriginal;if(!autotest::beginInvocation(out,fn))return;fn(p);out.callCompleted=1;text(p->m_sFilename);number(p->m_sMeshName.size());number(p->m_pSceneManager==scene);collisionDtorOriginal(p);}
 }
 patches.restore();
}
void original(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),false,out);}void recovered(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),true,out);}
void diagnose(const tlhybrid_host* host,unsigned op,unsigned seed,const autotest::Outcome& a,const autotest::Outcome& b){
 const autotest::Capture& x=a.capture;const autotest::Capture& y=b.capture;
 size_t first=0;while(first<x.length&&first<y.length&&x.data[first]==y.data[first])++first;
 host->log("    world op=%u seed=%u status=%d/%d child=%d/%d valid=%u/%u issue=%u/%u bytes=%lu/%lu call=%lx/%lx started=%u/%u completed=%u/%u firstdiff=%lu\n",op,seed,a.status,b.status,a.childStatus,b.childStatus,unsigned(a.reportValid),unsigned(b.reportValid),x.issue,y.issue,(unsigned long)x.length,(unsigned long)y.length,(unsigned long)x.callTarget,(unsigned long)y.callTarget,x.callStarted,y.callStarted,x.callCompleted,y.callCompleted,(unsigned long)first);
 for(size_t n=0;n<x.length&&n<y.length&&n<80;n+=4){unsigned av=0,bv=0;size_t k=x.length-n<4?x.length-n:4;std::memcpy(&av,x.data+n,k);std::memcpy(&bv,y.data+n,k);host->log("    bytes[%lu]=%08x/%08x\n",(unsigned long)n,av,bv);}
}
int run(const tlhybrid_host* host,unsigned op,const char* name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned i=0;i<80;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int observed=coverage.observe(host,a,b);if(i==0||observed)diagnose(host,op,i,a,b);if(observed){coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=80||coverage.different||coverage.missing;}
}
TL_TEST(world_puzzle_constructor){return run(host,0,"world_puzzle_constructor",(uintptr_t)&puzzleCtorOriginal);}
TL_TEST(world_puzzle_destructor){return run(host,1,"world_puzzle_destructor",(uintptr_t)&puzzleDtorOriginal);}
TL_TEST(world_puzzle_active_inputs){return run(host,2,"world_puzzle_active_inputs",(uintptr_t)&puzzleActiveOriginal);}
TL_TEST(world_puzzle_trigger){return run(host,3,"world_puzzle_trigger",(uintptr_t)&puzzleTriggerOriginal);}
TL_TEST(world_collision_constructor){return run(host,4,"world_collision_constructor",(uintptr_t)&collisionCtorOriginal);}
TL_TEST(world_collision_unload){return run(host,5,"world_collision_unload",(uintptr_t)&collisionUnloadOriginal);}
