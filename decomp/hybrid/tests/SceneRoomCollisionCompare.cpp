#include "SmallMassCompare.h"
#include <stdexcept>
TL_ORIGINAL(void, collisionOriginal,(void*,const std::wstring&),"_ZN10CRoomPiece24setCollisionMeshFilePathERKSbIwSt11char_traitsIwESaIwEE")
extern "C" void collisionCandidate(void*,const std::wstring&) __asm__("_ZN10CRoomPiece24setCollisionMeshFilePathERKSbIwSt11char_traitsIwESaIwEE");
TL_FUNCTION(masterSingleton,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(removeCollision,"_ZN22CMasterResourceManager20removeCollisionModelEP15CCollisionModel")
TL_FUNCTION(addCollision,"_ZN22CMasterResourceManager17addCollisionModelESbIwSt11char_traitsIwESaIwEE")
TL_FUNCTION(editorRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
namespace {
using namespace smallmass;void* manager;void* collision;unsigned calls;
void* singleton(){event(1,manager);++calls;return manager;}
void remove(void* p,void* value){event(2,p);pointer(value);++calls;}
void* add(void* p,std::wstring value){event(3,p);text(value);++calls;if(input->index%11==0)throw std::runtime_error("load collision");return input->index%5?collision:0;}
bool editor(void* p){event(4,p);++calls;return input->index&1;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;void* self=object(0x160);void* resources=object(0x50);manager=object(0x100);collision=object(0x20);field<void*>(self,0x68)=resources;field<void*>(self,0x118)=c.index%4?collision:0;field<bool>(self,0x150)=c.index&2;
 new(static_cast<char*>(self)+0x128)std::wstring(c.index%3?L"visual.mesh":L"");new(static_cast<char*>(self)+0x130)std::wstring(c.index%5?L"old.collision":L"");std::wstring path=c.index%4?L"new.collision":L"";const std::wstring& argument=c.index%7==0?field<std::wstring>(self,0x128):c.index%7==1?field<std::wstring>(self,0x130):path;
 detour::Set p;TL_REDIRECT(p,masterSingleton,&singleton);TL_REDIRECT(p,removeCollision,&remove);TL_REDIRECT(p,addCollision,&add);TL_REDIRECT(p,editorRunning,&editor);if(p.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 void(*fn)(void*,const std::wstring&)=ours?collisionCandidate:collisionOriginal;if(!autotest::beginInvocation(out,fn))return;bool threw=false;try{fn(self,argument);}catch(const std::runtime_error&){threw=true;}out.callCompleted=1;
 number(threw);pointer(field<void*>(self,0x118));text(field<std::wstring>(self,0x128));text(field<std::wstring>(self,0x130));number(calls);field<std::wstring>(self,0x128).~basic_string();field<std::wstring>(self,0x130).~basic_string();out.addHeapInUse();
}
}
TL_TEST(scene_room_collision_path){return smallmass::run(host,0,"scene_room_collision_path",(uintptr_t)collisionOriginal,execute,48);}
