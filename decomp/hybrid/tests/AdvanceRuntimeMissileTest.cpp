#include "SmallMassCompare.h"
#include "TArrayList.h"
#include <map>
TL_ORIGINAL(void,missileOld0,(void*),"_ZN17CMissilePreloader19clearCachedMissilesEv")
TL_ORIGINAL(void,missileOld1,(void*),"_ZN17CMissilePreloader14reloadMissilesEv")
TL_ORIGINAL(void*,missileOld2,(void*,void*,const std::wstring&),"_ZN17CMissilePreloader19createNewMissileRefEP16CResourceManagerRKSbIwSt11char_traitsIwESaIwEE")
TL_ORIGINAL(void,missileOld3,(void*,void*),"_ZN17CMissilePreloader12cacheMissileEP8CMissile")
extern "C" void missileNew0(void*) __asm__("_ZN17CMissilePreloader19clearCachedMissilesEv");
extern "C" void missileNew1(void*) __asm__("_ZN17CMissilePreloader14reloadMissilesEv");
extern "C" void* missileNew2(void*,void*,const std::wstring&) __asm__("_ZN17CMissilePreloader19createNewMissileRefEP16CResourceManagerRKSbIwSt11char_traitsIwESaIwEE");
extern "C" void missileNew3(void*,void*) __asm__("_ZN17CMissilePreloader12cacheMissileEP8CMissile");
TL_FUNCTION(missileUpper,"_ZN7STRINGS11StringUpperERKSbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(missileSetResource,"_ZN16CSceneNodeObject18setResourceManagerEP16CResourceManager")
TL_FUNCTION(missileReset,"_ZN8CMissile12resetMissileEv")
TL_FUNCTION(missileCtor,"_ZN8CMissileC1EP16CResourceManagerPKS_")
TL_FUNCTION(missileResourceCtor,"_ZN16CResourceManagerC1EPN4Ogre12SceneManagerE")
TL_FUNCTION(missileClear,"_ZN17CMissilePreloader5clearEv")
TL_FUNCTION(missileGetString,"_ZN20CDynamicPropertyFile9GetStringEj")
TL_FUNCTION(missileFileSystem,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(missileFileList,"_ZN11CFileSystem11getFileListERKSbIwSt11char_traitsIwESaIwEER10TArrayListIS3_ES3_bbbb")
TL_FUNCTION(missileLoad,"_ZN17CMissilePreloader11loadMissileERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void* missileSingleton __asm__("_ZL18g_MissilePreloader");
extern "C" unsigned missileFolder __asm__("KRESOURCESETTING_S_MISSILE_FOLDER");
namespace {
using namespace smallmass;
struct Loader{unsigned long table,safe;void* settings;std::map<std::wstring,void*> originals;std::map<std::wstring,TArrayList<void*>*> caches;void* resources;TArrayList<void*> active;Loader():table(0),safe(0),settings(0),resources(0),active(2){}};
void** table;void* token;unsigned calls;std::wstring name;
void record(unsigned tag,void* p){event(tag,p);++calls;}
void destroy(void* p){record(1,p);}
void visible(void* p,bool flag){record(2,p);number(flag);}
void* makeMissile(unsigned i){void* p=object(0x2d8);field<void*>(p,0)=table;new(static_cast<char*>(p)+0x2c8)std::wstring(i&1?L"OTHER":name);return p;}
std::wstring upper(const std::wstring& s){record(3,0);text(s);return name;}
void setResource(void* p,void* r){record(4,p);pointer(r);field<void*>(p,0x68)=r;}
void reset(void* p){record(5,p);}
void ctor(void* p,void* r,const void* source){record(6,p);pointer(r);pointer(source);field<void*>(p,0)=table;new(static_cast<char*>(p)+0x2c8)std::wstring(name);}
void resourceCtor(void* p,void* scene){record(7,p);pointer(scene);}
void clear(void* p){record(8,p);}
const std::wstring& getString(void* p,unsigned key){record(9,p);number(key);return name;}
void* fileSystem(){record(10,token);return token;}
unsigned fileList(void* p,const std::wstring& directory,TArrayList<std::wstring>& files,std::wstring pattern,bool a,bool b,bool c,bool d){record(11,p);text(directory);text(pattern);number(a);number(b);number(c);number(d);number(files.size());number(field<unsigned>(&files,16));for(unsigned i=0;i<input->index%5;++i)files.add(i&1?L"second.layout":L"path/Юникод.layout");return input->index%5;}
void load(void* p,const std::wstring& file){record(12,p);text(file);}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;token=object(0x20);table=static_cast<void**>(object(0x60));table[1]=reinterpret_cast<void*>(&destroy);table[0x50/8]=reinterpret_cast<void*>(&visible);name=c.index&1?L"PATH/ЮНИКОД":L"";Loader state,global;state.settings=token;state.resources=c.index&1?token:0;missileSingleton=c.index%7?&global:0;missileFolder=73+c.index;
 void* units[6];for(unsigned i=0;i<6;++i)units[i]=makeMissile(i);if(c.op==0){for(unsigned i=0;i<c.index%4;++i)state.active.add(c.index&16&&i==1?0:units[i]);for(unsigned i=0;i<c.index%3;++i){TArrayList<void*>* cache=i==1&&c.index&8?0:new TArrayList<void*>(c.index%3+1);if(cache)for(unsigned j=0;j<c.index%4;++j)cache->add(c.index&32&&j==1?0:units[2+j]);state.caches[i?L"Z":L"A"]=cache;}}
 if(c.op==2){if(c.index%3)state.caches[name]=new TArrayList<void*>(c.index%2+1);if(!state.caches.empty())for(unsigned i=0;i<c.index%4;++i)state.caches.begin()->second->add(units[i]);if(c.index%5)global.originals[name]=units[4];state.originals[L"THIS_ONLY"]=units[5];if(c.index&8)for(unsigned i=0;i<3;++i)state.active.add(units[i]);}
 if(c.op==3&&c.index%3){TArrayList<void*>* cache=c.index%3==1?0:new TArrayList<void*>(1);if(cache)for(unsigned i=0;i<c.index%4;++i)cache->add(units[i]);state.caches[name]=cache;}
 detour::Set d;TL_REDIRECT(d,missileUpper,&upper);TL_REDIRECT(d,missileSetResource,&setResource);TL_REDIRECT(d,missileReset,&reset);TL_REDIRECT(d,missileCtor,&ctor);TL_REDIRECT(d,missileResourceCtor,&resourceCtor);TL_REDIRECT(d,missileClear,&clear);TL_REDIRECT(d,missileGetString,&getString);TL_REDIRECT(d,missileFileSystem,&fileSystem);TL_REDIRECT(d,missileFileList,&fileList);TL_REDIRECT(d,missileLoad,&load);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op==0)autotest::invoke(out,ours?missileNew0:missileOld0,&state);
 else if(c.op==1)autotest::invoke(out,ours?missileNew1:missileOld1,&state);
 else if(c.op==2){typedef void*(*Fn)(void*,void*,const std::wstring&);Fn fn=ours?missileNew2:missileOld2;if(!autotest::beginInvocation(out,fn))return;void* result=fn(&state,token,L"input/name");out.callCompleted=1;pointer(result);if(result)pointer(field<void*>(result,0x68));}
 else autotest::invoke(out,ours?missileNew3:missileOld3,&state,c.index%7?units[0]:0);
 number(state.resources!=0);number(state.active.size());for(unsigned i=0;i<state.active.size();++i)pointer(state.active[i]);number(state.caches.size());for(std::map<std::wstring,TArrayList<void*>*>::iterator i=state.caches.begin();i!=state.caches.end();++i){text(i->first);number(i->second!=0);if(i->second){number(i->second->size());for(unsigned j=0;j<i->second->size();++j)pointer((*i->second)[j]);delete i->second;}}number(calls);
}
}
TL_TEST(advance_runtime_missile_clear){return smallmass::run(host,0,"advance_runtime_missile_clear",(uintptr_t)missileOld0,execute,84);}
TL_TEST(advance_runtime_missile_reload){return smallmass::run(host,1,"advance_runtime_missile_reload",(uintptr_t)missileOld1,execute,84);}
TL_TEST(advance_runtime_missile_create){return smallmass::run(host,2,"advance_runtime_missile_create",(uintptr_t)missileOld2,execute,84);}
TL_TEST(advance_runtime_missile_cache){return smallmass::run(host,3,"advance_runtime_missile_cache",(uintptr_t)missileOld3,execute,84);}
