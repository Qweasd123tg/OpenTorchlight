#include "SmallMassCompare.h"
#include "FileSystem.h"
#include <vector>
TL_ORIGINAL(void,masterUnusedOld,(void*),"_ZN22CMasterResourceManager12removeUnusedEv")
TL_ORIGINAL(void,masterAllOld,(void*),"_ZN22CMasterResourceManager9removeAllEv")
TL_ORIGINAL(void*,masterBatchOld,(void*,void*,void*,std::wstring,bool&),"_ZN22CMasterResourceManager13addBatchModelEP16CResourceManagerPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEERb")
TL_ORIGINAL(void*,masterCollisionOld,(void*,std::wstring),"_ZN22CMasterResourceManager17addCollisionModelESbIwSt11char_traitsIwESaIwEE")
extern "C" void masterUnusedNew(void*) __asm__("_ZN22CMasterResourceManager12removeUnusedEv");
extern "C" void masterAllNew(void*) __asm__("_ZN22CMasterResourceManager9removeAllEv");
extern "C" void* masterBatchNew(void*,void*,void*,std::wstring,bool&) __asm__("_ZN22CMasterResourceManager13addBatchModelEP16CResourceManagerPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEERb");
extern "C" void* masterCollisionNew(void*,std::wstring) __asm__("_ZN22CMasterResourceManager17addCollisionModelESbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(masterFilesTarget,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(masterFileInfoTarget,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(masterGenericCtor,"_ZN13CGenericModelC2EP16CResourceManagerPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEES8_b")
TL_FUNCTION(masterAnimationCount,"_ZNK13CGenericModel17getAnimationCountEv")
TL_FUNCTION(masterCollisionCtor,"_ZN15CCollisionModelC1EPN4Ogre12SceneManagerESbIwSt11char_traitsIwESaIwEE")
namespace {
using namespace smallmass;void* token;void** table;unsigned calls;
struct Ref{void* table;void* safe;void* model;int refs;unsigned pad;std::wstring name;};
void record(unsigned tag,void* p){event(tag,p);++calls;}
void destroy(void* p){record(1,p);}
void* files(){record(2,token);return token;}
void fileInfo(void* p,const std::wstring& name,CFileInfo& info,bool a,bool b,bool c){record(3,p);text(name);number(a);number(b);number(c);text(info.m_sModName);text(info.m_sResourceName);text(info.m_sPath);number(info.m_eFormat);number(info.m_eLocation);text(info.m_sResourceGroup);number(info.m_bExists);info.m_bExists=input->index%5;info.m_sResourceGroup="GROUP";info.m_sResourceName="RESOURCE";}
void genericCtor(void* p,void* resources,void* scene,std::wstring name,std::wstring group,bool flag){record(4,p);pointer(resources);pointer(scene);text(name);text(group);number(flag);field<void*>(p,0)=table;}
unsigned animationCount(void* p){record(5,p);return input->index&4?2:0;}
void collisionCtor(void* p,void* scene,std::wstring name){record(6,p);pointer(scene);text(name);field<void*>(p,0)=table;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;void* self=object(0x190);token=object(0x20);table=static_cast<void**>(object(0x10));table[1]=reinterpret_cast<void*>(&destroy);field<void*>(self,0xc8)=token;std::vector<void*>& collision=*new(static_cast<char*>(self)+0x120)std::vector<void*>;std::vector<void*>& batch=*new(static_cast<char*>(self)+0x138)std::vector<void*>;std::vector<void*>& animation=*new(static_cast<char*>(self)+0x150)std::vector<void*>;
 if(c.index&32){collision.reserve(10);batch.reserve(10);animation.reserve(10);}
 std::wstring name=c.index&1?L"model/Юникод.mesh":L"";for(unsigned group=0;group<3;++group){unsigned count=c.op<2?(c.index/(group+1))%6:(group==unsigned(c.op==2)?c.index%3:0);for(unsigned i=0;i<count;++i){void* item=object(0x28);field<void*>(item,0)=table;if(group<2){field<void*>(item,0x10)=token;field<int>(item,0x18)=int((c.index+i)%4)-1;new(static_cast<char*>(item)+0x20)std::wstring(c.index&2&&i==0?name:L"OTHER");}else field<int>(item,0x10)=int((c.index+i)%4)-1;std::vector<void*>& list=group==0?collision:group==1?batch:animation;list.push_back(c.op==1&&i==2&&c.index&8?0:item);}}
 detour::Set d;TL_REDIRECT(d,masterFilesTarget,&files);TL_REDIRECT(d,masterFileInfoTarget,&fileInfo);TL_REDIRECT(d,masterGenericCtor,&genericCtor);TL_REDIRECT(d,masterAnimationCount,&animationCount);TL_REDIRECT(d,masterCollisionCtor,&collisionCtor);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}bool shared=c.index&16;void* result=0;
 if(c.op==0)autotest::invoke(out,ours?masterUnusedNew:masterUnusedOld,self);
 else if(c.op==1)autotest::invoke(out,ours?masterAllNew:masterAllOld,self);
 else if(c.op==2){typedef void*(*Fn)(void*,void*,void*,std::wstring,bool&);Fn fn=ours?masterBatchNew:masterBatchOld;if(!autotest::beginInvocation(out,fn))return;result=fn(self,token,token,name,shared);out.callCompleted=1;number(shared);}
 else{typedef void*(*Fn)(void*,std::wstring);Fn fn=ours?masterCollisionNew:masterCollisionOld;if(!autotest::beginInvocation(out,fn))return;result=fn(self,name);out.callCompleted=1;}
 number(result!=0);number(result==token);for(unsigned group=0;group<3;++group){std::vector<void*>& list=group==0?collision:group==1?batch:animation;number(list.size());for(unsigned i=0;i<list.size();++i){void* p=list[i];pointer(p);if(!p)continue;if(group<2){number(field<int>(p,0x18));if(c.op>=2){text(field<std::wstring>(p,0x20));number(field<void*>(p,0x10)!=0);}}else number(field<int>(p,0x10));}}
 number(calls);collision.~vector();batch.~vector();animation.~vector();
}
}
TL_TEST(advance_runtime_master_unused){return smallmass::run(host,0,"advance_runtime_master_unused",(uintptr_t)masterUnusedOld,execute,84);}
TL_TEST(advance_runtime_master_all){return smallmass::run(host,1,"advance_runtime_master_all",(uintptr_t)masterAllOld,execute,84);}
TL_TEST(advance_runtime_master_batch){return smallmass::run(host,2,"advance_runtime_master_batch",(uintptr_t)masterBatchOld,execute,84);}
TL_TEST(advance_runtime_master_collision){return smallmass::run(host,3,"advance_runtime_master_collision",(uintptr_t)masterCollisionOld,execute,84);}
