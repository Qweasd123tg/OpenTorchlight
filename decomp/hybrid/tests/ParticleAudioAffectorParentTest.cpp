#include <cstring>
#include <stdint.h>
#include "AutoTest.h"
#include "Detour.h"
TL_ORIGINAL(void,affectorParentOld,(void*,long long),"_ZN16CAffectorWrapper13setParentGuidEx")
extern "C" void affectorParentNew(void*,long long) __asm__("_ZN16CAffectorWrapper13setParentGuidEx");
TL_FUNCTION(affectorRemoveTarget,"_ZN20CParticleTechWrapper14removeAffectorEP16CAffectorWrapper")
TL_FUNCTION(affectorParentTarget,"_ZN16CAffectorWrapper25setParentTechniqueWrapperEP20CParticleTechWrapper")
TL_FUNCTION(affectorFindTarget,"_ZN12CEditorScene16GetObjectInSceneEx")
TL_FUNCTION(affectorEditorTarget,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(affectorDetachTarget,"_ZN16CSceneNodeObject21sceneNodeDetachEntityEv")
extern "C" void* affectorBaseTable[] __asm__("_ZTV17CEditorBaseObject");
extern "C" void* affectorTechTable[] __asm__("_ZTV20CParticleTechWrapper");
namespace {
struct Case{unsigned index;};struct State{autotest::Capture* out;uint64_t* object;uint64_t scene[64],nodes[3][66],oldParent[66],resource,affector;unsigned index,calls;};State* active;
void add(unsigned n){active->out->add(&n,4);}void invalid(){active->out->issue=autotest::Capture::InvalidReport;}void event(unsigned n){++active->calls;add(n);}
void* pointer(void* p,unsigned at){void* q;std::memcpy(&q,reinterpret_cast<char*>(p)+at,8);return q;}void set(void* p,unsigned at,void* q){std::memcpy(reinterpret_cast<char*>(p)+at,&q,8);}unsigned parentID(void* p){if(!p)return 0;if(p==active->oldParent)return 1;if(p==active->nodes[1])return 2;invalid();return 99;}
void remove(void* p,void* child){if(child!=active->object)invalid();event(1);add(parentID(p));}
void parent(void* p,void* q){if(p!=active->object)invalid();event(2);add(parentID(q));if(pointer(p,0x110)){set(p,0x108,q);if(q&&(active->index&32))set(p,0x48,0);}}
void* find(void* p,long long guid){if(p!=active->scene)invalid();event(3);active->out->add(&guid,8);return guid>=1&&guid<=3?active->nodes[guid-1]:0;}
bool editor(void* p){if(p!=&active->resource)invalid();event(4);return active->index&8;}
void detach(void* p){if(p!=active->object)invalid();event(5);}
void side(Case& c,bool ours,autotest::Capture& out){
 uint64_t object[36]={0};State state;std::memset(state.scene,0,sizeof(state.scene));std::memset(state.nodes,0,sizeof(state.nodes));state.out=&out;state.object=object;state.index=c.index;state.calls=0;active=&state;
 for(unsigned i=0;i<3;++i){*reinterpret_cast<void***>(state.nodes[i])=i==1?affectorTechTable+2:affectorBaseTable+2;long long parent=i==0?2:-1;std::memcpy(reinterpret_cast<char*>(state.nodes[i])+0x18,&parent,8);}
 set(object,0x108,c.index&1?state.oldParent:0);set(object,0x110,c.index&2?&state.affector:0);set(object,0x48,c.index&4?state.scene:0);set(object,0x68,&state.resource);set(state.scene,0x48,c.index&16?&state.resource:0);
 long long oldGuid=37;std::memcpy(reinterpret_cast<char*>(object)+0x18,&oldGuid,8);const long long values[]={-1,1,2,3,99};long long guid=values[c.index%5];
 detour::Set d;TL_REDIRECT(d,affectorRemoveTarget,&remove);TL_REDIRECT(d,affectorParentTarget,&parent);TL_REDIRECT(d,affectorFindTarget,&find);TL_REDIRECT(d,affectorEditorTarget,&editor);TL_REDIRECT(d,affectorDetachTarget,&detach);if(d.failed()){invalid();return;}
 typedef void(*Fn)(void*,long long);Fn fn=ours?affectorParentNew:affectorParentOld;if(!autotest::beginInvocation(out,fn))return;fn(object,guid);out.callCompleted=1;add(state.calls);out.add(reinterpret_cast<char*>(object)+0x18,8);add(parentID(pointer(object,0x108)));add(pointer(object,0x48)!=0);
}
void before(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),false,out);}void after(void* p,autotest::Capture& out){side(*static_cast<Case*>(p),true,out);}
}
TL_TEST(state_affector_a17f30){autotest::Coverage cov("state_affector_a17f30",reinterpret_cast<uintptr_t>(&affectorParentOld));for(unsigned i=0;i<160;++i){Case c={i};autotest::Outcome a,b;autotest::runChild(before,&c,a);autotest::runChild(after,&c,b);if(cov.observe(host,a,b)){host->log(" affector parent case%u exits%d/%d issues%u/%u\n",i,a.childStatus,b.childStatus,a.capture.issue,b.capture.issue);cov.report(host);return 1;}}cov.report(host);return cov.completed==160?0:1;}
