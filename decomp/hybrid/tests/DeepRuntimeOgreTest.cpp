#include "tests/SmallMassCompare.h"
#include "FileSystem.h"
#define DECL(ret,id,args,sym) TL_ORIGINAL(ret,id##Old,args,sym) extern "C" ret id##New args __asm__(sym);
DECL(void*,deepOgreMesh,(void*,const std::wstring&,int,const char*),"_ZN14OGRE_UTILITIES12createEntityEPN4Ogre12SceneManagerERKSbIwSt11char_traitsIwESaIwEENS_10EQUERYMASKEPKc")
DECL(void*,deepOgrePrimitive,(void*,int,int,const char*),"_ZN14OGRE_UTILITIES12createEntityEPN4Ogre12SceneManagerENS_11EPRIMITIVESENS_10EQUERYMASKEPKc")
TL_FUNCTION(deepOgreFiles,"_ZN11CFileSystem12getSingletonEv")
TL_FUNCTION(deepOgreInfo,"_ZN11CFileSystem11getFileInfoERKSbIwSt11char_traitsIwESaIwEER9CFileInfobbb")
TL_FUNCTION(deepOgreUnique,"_ZN7STRINGS10uniqueNameERKSs")
namespace {using namespace smallmass;void* token;void* entity;
void* files(){event(1,token);return token;}
void info(void* p,const std::wstring& name,CFileInfo& info,bool a,bool b,bool c){event(2,p);text(name);number(a);number(b);number(c);info.m_bExists=input->index&1;info.m_sResourceName=input->index&4?"mesh/path.mesh":"";info.m_sModName="mod";info.m_sPath=L"filesystem/path.mesh";info.m_sResourceGroup="fixture";}
std::string unique(const std::string& name){number(3);text(name);return name+"__fixture_42";}
void* create(void* p,const std::string& name,const std::string& mesh){event(4,p);text(name);text(mesh);return input->index&2?0:entity;}
void flags(void* p,unsigned mask){event(5,p);number(mask);}
void* mesh(void* p,const std::wstring& name,int query,const char* tag){event(6,p);text(name);number(query);text(std::string(tag));return entity;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;autotest::g_arenaUsed=0;token=object(8);entity=object(8);void** ev=static_cast<void**>(object(0x160));ev[0x158/8]=reinterpret_cast<void*>(&flags);field<void**>(entity,0)=ev;void* manager=object(8);void** mv=static_cast<void**>(object(0x270));mv[0x268/8]=reinterpret_cast<void*>(&create);field<void**>(manager,0)=mv;detour::Set d;TL_REDIRECT(d,deepOgreFiles,&files);TL_REDIRECT(d,deepOgreInfo,&info);TL_REDIRECT(d,deepOgreUnique,&unique);if(c.op==1)d.redirect(reinterpret_cast<char*>(deepOgreMeshOld),reinterpret_cast<char*>(deepOgreMeshNew),&mesh);if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
void* p=c.index&8?0:manager;int mask=int(c.index%5)*17;const char* tag=c.index&16?"entity":"";if(c.op==0){std::wstring name=c.index&32?L"model/Ж.mesh":L"";typedef void*(*Fn)(void*,const std::wstring&,int,const char*);Fn fn=ours?deepOgreMeshNew:deepOgreMeshOld;if(!autotest::beginInvocation(out,fn))return;pointer(fn(p,name,mask,tag));out.callCompleted=1;}else{void*(*fn)(void*,int,int,const char*)=ours?deepOgrePrimitiveNew:deepOgrePrimitiveOld;if(!autotest::beginInvocation(out,fn))return;pointer(fn(p,int(c.index%9)-1,mask,tag));out.callCompleted=1;}}
}
TL_TEST(deep_runtime_ogre_mesh){return smallmass::run(host,0,"deep_runtime_ogre_mesh",(uintptr_t)deepOgreMeshOld,execute,96);}
TL_TEST(deep_runtime_ogre_primitive){return smallmass::run(host,1,"deep_runtime_ogre_primitive",(uintptr_t)deepOgrePrimitiveOld,execute,96);}
