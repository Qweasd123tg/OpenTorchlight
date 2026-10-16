#include <string>
#include <stdexcept>
#include "AutoTest.h"
#include "Detour.h"
#include "PathNode.h"
#include "CinematicObject.h"
#include "RandomGroup.h"
TL_ORIGINAL(void, nodeVisibleOriginal, (void*,bool), "_ZN9CPathNode10setVisibleEb")
extern "C" void nodeVisibleCandidate(void*,bool) __asm__("_ZN9CPathNode10setVisibleEb");
TL_ORIGINAL(bool, cinematicUpdateOriginal, (void*,float,Ogre::Camera*,const Ogre::Vector3&), "_ZN16CCinematicObject17updateLevelObjectEfPN4Ogre6CameraERKNS0_7Vector3E")
extern "C" bool cinematicUpdateCandidate(void*,float,Ogre::Camera*,const Ogre::Vector3&) __asm__("_ZN16CCinematicObject17updateLevelObjectEfPN4Ogre6CameraERKNS0_7Vector3E");
TL_ORIGINAL(void, cinematicCtorOriginal, (void*,CResourceManager*), "_ZN16CCinematicObjectC1EP16CResourceManager")
TL_ORIGINAL(void, cinematicDtorOriginal, (void*), "_ZN16CCinematicObjectD1Ev")
TL_FUNCTION(setTextTarget,"_ZN9CPathNode7setTextERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(visibleTarget,"_ZN16CSceneNodeObject10setVisibleEb")
TL_FUNCTION(singletonTarget,"_ZN7CGameUI12getSingletonEv")
TL_FUNCTION(removeListenerTarget,"_ZN7CGameUI18removeMenuListenerE10EMENU_TYPEP13iMenuListener")
TL_FUNCTION(broadcastTarget,"_ZN17CEditorBaseObject14BroadcastEventEj")
TL_ORIGINAL(void, randomVisibleOriginal,(void*,bool),"_ZN12CRandomGroup10setVisibleEb")
extern "C" void randomVisibleCandidate(void*,bool) __asm__("_ZN12CRandomGroup10setVisibleEb");
TL_FUNCTION(childrenVisibleTarget,"_ZN12CEditorScene18setChildrenVisibleExb")
namespace {
struct Case{unsigned op,index;};Case* input;autotest::Capture* output;void* self;void* sceneOwner;unsigned calls;char gameUI;
void invalid(){output->issue=autotest::Capture::InvalidReport;}void number(unsigned n){output->add(&n,sizeof(n));}
void text(const std::wstring& s){number(s.size());output->add(s.data(),s.size()*sizeof(wchar_t));}
void setText(void* p,const std::wstring& s){if(p!=self)invalid();number(1);text(s);++calls;static_cast<CPathNode*>(p)->m_sText=s;if(input->index%7==0)throw std::runtime_error("text update");}
void visible(void* p,bool value){if(p!=self)invalid();number(2);number(value);++calls;static_cast<unsigned char*>(p)[0x81]=value;}
void* singleton(){number(3);return &gameUI;}
void removeListener(void* p,int type,void* listener){number(4);number(type);number(listener==static_cast<char*>(self)+0x58);if(p!=&gameUI||type!=1||listener!=static_cast<char*>(self)+0x58)invalid();++calls;}
void broadcast(void* p,unsigned event){number(5);number(event);if(p!=self||event!=92)invalid();++calls;}
bool enabled(void* p){if(p!=sceneOwner)invalid();number(6);++calls;return input->index%3!=0;}
void childrenVisible(void* p,long long guid,bool value){number(7);output->add(&guid,8);number(value);++calls;if(guid!=static_cast<long long>(input->index)*123)invalid();}
void body(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;self=autotest::allocate(1024);detour::Set patches;TL_REDIRECT(patches,setTextTarget,&setText);TL_REDIRECT(patches,visibleTarget,&visible);TL_REDIRECT(patches,singletonTarget,&singleton);TL_REDIRECT(patches,removeListenerTarget,&removeListener);TL_REDIRECT(patches,broadcastTarget,&broadcast);TL_REDIRECT(patches,childrenVisibleTarget,&childrenVisible);if(patches.failed()){invalid();return;}
 if(c.op==0){CPathNode* p=static_cast<CPathNode*>(self);new(&p->m_sText)std::wstring(c.index%5?std::wstring(c.index,L'a'+c.index%20):L"");void(*fn)(void*,bool)=ours?nodeVisibleCandidate:nodeVisibleOriginal;if(!autotest::beginInvocation(out,fn))return;bool threw=false;try{fn(p,c.index%2!=0);}catch(const std::runtime_error&){threw=true;}out.callCompleted=1;number(threw);text(p->m_sText);number(calls);p->m_sText.~basic_string();}
 else if(c.op==1){CCinematicObject* p=static_cast<CCinematicObject*>(self);cinematicCtorOriginal(p,0);const int events[]={-1,0,1,2,3,4,5,6,99,2147483647};p->m_eMenuEvent=static_cast<EMENU_EVENT>(events[c.index%10]);Ogre::Vector3 position(c.index,-2,4);bool(*fn)(void*,float,Ogre::Camera*,const Ogre::Vector3&)=ours?cinematicUpdateCandidate:cinematicUpdateOriginal;if(!autotest::beginInvocation(out,fn))return;bool result=fn(p,c.index*0.125f,0,position);out.callCompleted=1;number(result);number(p->m_eMenuEvent);number(calls);if(result||calls!=(c.index%10>=3&&c.index%10<=5?2u:1u))invalid();cinematicDtorOriginal(p);}
 else{void** table=static_cast<void**>(autotest::allocate(0x100));table[0x48/8]=reinterpret_cast<void*>(&enabled);void* parent=autotest::allocate(1024);std::memcpy(parent,&table,8);sceneOwner=c.index%5==0?0:parent;void* ptr=sceneOwner;std::memcpy(static_cast<char*>(self)+0x48,&ptr,8);void* decoy=c.index%2?0:parent;std::memcpy(static_cast<char*>(self)+0x50,&decoy,8);long long guid=static_cast<long long>(c.index)*123;std::memcpy(static_cast<char*>(self)+0x10,&guid,8);static_cast<unsigned char*>(self)[0x81]=c.index/2%2;static_cast<unsigned char*>(self)[0x150]=c.index/4%2;void(*fn)(void*,bool)=ours?randomVisibleCandidate:randomVisibleOriginal;if(!autotest::beginInvocation(out,fn))return;fn(self,c.index%2);out.callCompleted=1;number(static_cast<unsigned char*>(self)[0x81]);number(calls);}
 patches.restore();}
void original(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),false,out);}void recovered(void* p,autotest::Capture& out){body(*static_cast<Case*>(p),true,out);}
void diagnose(const tlhybrid_host* host,unsigned op,unsigned seed,const autotest::Outcome& a,const autotest::Outcome& b){
 const autotest::Capture& x=a.capture;const autotest::Capture& y=b.capture;
 size_t first=0;while(first<x.length&&first<y.length&&x.data[first]==y.data[first])++first;
 host->log("    world op=%u seed=%u status=%d/%d child=%d/%d valid=%u/%u issue=%u/%u bytes=%lu/%lu call=%lx/%lx started=%u/%u completed=%u/%u firstdiff=%lu\n",op,seed,a.status,b.status,a.childStatus,b.childStatus,unsigned(a.reportValid),unsigned(b.reportValid),x.issue,y.issue,(unsigned long)x.length,(unsigned long)y.length,(unsigned long)x.callTarget,(unsigned long)y.callTarget,x.callStarted,y.callStarted,x.callCompleted,y.callCompleted,(unsigned long)first);
 for(size_t n=0;n<x.length&&n<y.length&&n<80;n+=4){unsigned av=0,bv=0;size_t k=x.length-n<4?x.length-n:4;std::memcpy(&av,x.data+n,k);std::memcpy(&bv,y.data+n,k);host->log("    bytes[%lu]=%08x/%08x\n",(unsigned long)n,av,bv);}
}
int run(const tlhybrid_host* host,unsigned op,const char* name,uintptr_t address){autotest::Coverage coverage(name,address);for(unsigned i=0;i<80;++i){Case c={op,i};autotest::Outcome a,b;autotest::runChild(original,&c,a);autotest::runChild(recovered,&c,b);int observed=coverage.observe(host,a,b);if(i==0||observed)diagnose(host,op,i,a,b);if(observed){coverage.report(host);return 1;}}coverage.report(host);return coverage.completed!=80||coverage.different||coverage.missing;}
}
TL_TEST(world_path_node_visibility){return run(host,0,"world_path_node_visibility",(uintptr_t)&nodeVisibleOriginal);}
TL_TEST(world_cinematic_update){return run(host,1,"world_cinematic_update",(uintptr_t)&cinematicUpdateOriginal);}

TL_TEST(world_random_group_visibility){return run(host,2,"world_random_group_visibility",(uintptr_t)&randomVisibleOriginal);}
