#include "SmallMassCompare.h"
#include <stdexcept>
TL_ORIGINAL(void, densityOriginal,(void*,bool),"_ZN6CLight18updateLightDensityEb")
extern "C" void densityCandidate(void*,bool) __asm__("_ZN6CLight18updateLightDensityEb");
TL_FUNCTION(editorRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(detachEntity,"_ZN14OGRE_UTILITIES22detachEntityFromParentEPN4Ogre6EntityE")
TL_FUNCTION(attachEntity,"_ZN14OGRE_UTILITIES23attachEntityToSceneNodeEPN4Ogre6EntityEPNS0_9SceneNodeE")
TL_FUNCTION(uniqueName,"_ZN7STRINGS10uniqueNameERKSs")
extern "C" char cloneEntity_linked[] __asm__("_ZNK4Ogre6Entity5cloneERKSs");
namespace {
using namespace smallmass;unsigned calls,editors,clones;void** table;
bool editor(void* p){event(1,p);++calls;++editors;return input->index%7!=0 && (input->index%11!=0||editors==1);}
void detach(void* p){event(2,p);++calls;}
void attach(void* p,void* node){event(3,p);pointer(node);++calls;}
std::string unique(const std::string& prefix){number(4);text(prefix);++calls;return prefix+"-test";}
void* clone(void* p,const std::string& name){event(5,p);text(name);++calls;++clones;if(input->index%13==0)throw std::runtime_error("clone failure");void* entity=object(0x100);field<void*>(entity,0)=table;return entity;}
void queue(void* p,unsigned char n){event(6,p);number(n);++calls;field<unsigned>(p,0x18)=n;}
void query(void* p,unsigned n){event(7,p);number(n);++calls;field<unsigned>(p,0x1c)=n;}
void visibility(void* p,unsigned n){event(8,p);number(n);++calls;field<unsigned>(p,0x20)=n;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=editors=clones=0;autotest::g_arenaUsed=0;void* self=object(0x138);void* resources=object(0x50);void* model=object(0x250);void* source=object(0x100);void* node=object(0x100);field<void*>(self,0x68)=resources;field<void*>(self,0x58)=node;field<void*>(self,0x130)=c.index%9?model:0;field<void*>(model,0x60)=source;new(static_cast<char*>(self)+0x120)std::wstring(c.index%8?L"light.mesh":L"");field<unsigned>(self,0x100)=c.index%4;
 table=static_cast<void**>(object(0x180));table[0x140/8]=reinterpret_cast<void*>(&queue);table[0x158/8]=reinterpret_cast<void*>(&query);table[0x178/8]=reinterpret_cast<void*>(&visibility);
 unsigned n=(c.index/4)%5;void** entities=new void*[n?n:1];for(unsigned i=0;i<n;++i){entities[i]=object(0x100);field<void*>(entities[i],0)=table;}list(self,0x108,entities,n,n?n:1);field<unsigned>(self,0x118)=2;
 detour::Set p;TL_REDIRECT(p,editorRunning,&editor);TL_REDIRECT(p,detachEntity,&detach);TL_REDIRECT(p,attachEntity,&attach);TL_REDIRECT(p,uniqueName,&unique);p.redirect(reinterpret_cast<char*>(0x555c98),cloneEntity_linked,&clone);if(p.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 void(*fn)(void*,bool)=ours?densityCandidate:densityOriginal;if(!autotest::beginInvocation(out,fn))return;bool threw=false;try{fn(self,c.index&1);}catch(const std::runtime_error&){threw=true;}out.callCompleted=1;number(threw);number(field<unsigned>(self,0x110));number(field<unsigned>(self,0x114));number(field<unsigned>(self,0x118));number(clones);number(calls);void** result=field<void**>(self,0x108);for(unsigned i=0;i<field<unsigned>(self,0x110);++i){pointer(result[i]);number(field<unsigned>(result[i],0x18));number(field<unsigned>(result[i],0x1c));number(field<unsigned>(result[i],0x20));}delete[]result;field<std::wstring>(self,0x120).~basic_string();out.addHeapInUse();
}
}
TL_TEST(scene_light_density){return smallmass::run(host,0,"scene_light_density",(uintptr_t)densityOriginal,execute,48);}
