#include "SmallMassCompare.h"
TL_ORIGINAL(void, guidOriginal,(void*,long long),"_ZN10CRoomPiece16setRoomPieceGuidEx")
extern "C" void guidCandidate(void*,long long) __asm__("_ZN10CRoomPiece16setRoomPieceGuidEx");
TL_ORIGINAL(void, selectOriginal,(void*),"_ZN10CRoomPiece20selectNewVisualIndexEv")
extern "C" void selectCandidate(void*) __asm__("_ZN10CRoomPiece20selectNewVisualIndexEv");
TL_FUNCTION(dataSingleton,"_ZN25CRoomPieceDataInformation12getSingletonEv")
TL_FUNCTION(dataByGuid,"_ZN25CRoomPieceDataInformation27_GetRoomPieceCoreDataByGuidEx")
TL_FUNCTION(initRoom,"_ZN10CRoomPiece13initRoomPieceEv")
TL_FUNCTION(editorRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(randomInteger,"_ZN9UTILITIES20randomIntegerBetweenEii")
TL_FUNCTION(setGuid,"_ZN10CRoomPiece16setRoomPieceGuidEx")
namespace {
using namespace smallmass;void* self;void* manager;void* core;unsigned calls;
void* singleton(){event(1,manager);++calls;return manager;}
void* find(void* p,long long guid){event(2,p);output->add(&guid,8);++calls;return input->index%5?core:0;}
void init(void* p){event(3,p);++calls;field<bool>(p,0x151)=true;}
bool editor(void* p){event(4,p);++calls;return input->index&1;}
int random(int minimum,int maximum){number(5);number(minimum);number(maximum);++calls;return maximum<0?minimum:minimum+(input->index%unsigned(maximum-minimum+1));}
void guid(void* p,long long value){event(6,p);output->add(&value,8);++calls;field<long long>(p,0x140)=value;void* data=field<void*>(p,0x148);if(data){field<long long>(data,0x18)=value;field<void*>(data,0x10)=input->index%7?core:0;}}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;self=object(0x160);manager=object(0x100);core=object(0xb0);void* data=object(0x20);void* resources=object(0x50);field<void*>(self,0x68)=resources;field<void*>(self,0x148)=data;field<void*>(data,0x10)=c.index%4?core:0;field<unsigned>(core,0x88)=(c.index/2)%5;field<int>(self,0x138)=-7;field<long long>(self,0x140)=c.index%3?-1:123;
 detour::Set p;TL_REDIRECT(p,dataSingleton,&singleton);TL_REDIRECT(p,dataByGuid,&find);TL_REDIRECT(p,initRoom,&init);TL_REDIRECT(p,editorRunning,&editor);TL_REDIRECT(p,randomInteger,&random);if(c.op==1){TL_REDIRECT(p,setGuid,&guid);}if(p.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op==0){long long value=c.index%3?9876543210LL:-1;autotest::invoke(out,ours?guidCandidate:guidOriginal,self,value);}else autotest::invoke(out,ours?selectCandidate:selectOriginal,self);
 output->add(static_cast<char*>(self)+0x140,8);output->add(static_cast<char*>(data)+0x18,8);pointer(field<void*>(data,0x10));number(field<bool>(self,0x151));number(field<int>(self,0x138));number(calls);
}
}
TL_TEST(scene_room_guid){return smallmass::run(host,0,"scene_room_guid",(uintptr_t)guidOriginal,execute,32);}
TL_TEST(scene_room_visual_index){return smallmass::run(host,1,"scene_room_visual_index",(uintptr_t)selectOriginal,execute,48);}
