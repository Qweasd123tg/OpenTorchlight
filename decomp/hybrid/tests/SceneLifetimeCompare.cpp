#include "SmallMassCompare.h"
#include "RoomPiece.h"
#include "PropertyNode.h"
#include "SafePointer.h"
#include <new>
TL_ORIGINAL(void, roomCtorOriginal,(void*,CResourceManager*),"_ZN10CRoomPieceC1EP16CResourceManager")
extern "C" void roomCtorCandidate(void*,CResourceManager*) __asm__("_ZN10CRoomPieceC1EP16CResourceManager");
TL_ORIGINAL(void, roomDtorOriginal,(void*),"_ZN10CRoomPieceD1Ev")
extern "C" void roomDtorCandidate(void*) __asm__("_ZN10CRoomPieceD1Ev");
TL_ORIGINAL(void, roomResetOriginal,(void*),"_ZN10CRoomPiece14resetRoomPieceEv")
extern "C" void roomResetCandidate(void*) __asm__("_ZN10CRoomPiece14resetRoomPieceEv");
TL_ORIGINAL(void, propertyCtorOriginal,(void*,CResourceManager*),"_ZN13CPropertyNodeC1EP16CResourceManager")
extern "C" void propertyCtorCandidate(void*,CResourceManager*) __asm__("_ZN13CPropertyNodeC1EP16CResourceManager");
TL_ORIGINAL(void, propertyDtorOriginal,(void*),"_ZN13CPropertyNodeD1Ev")
extern "C" void propertyDtorCandidate(void*) __asm__("_ZN13CPropertyNodeD1Ev");
TL_FUNCTION(masterSingleton,"_ZN22CMasterResourceManager12getSingletonEv")
TL_FUNCTION(removeBatch,"_ZN22CMasterResourceManager16removeBatchModelEP13CGenericModel")
TL_FUNCTION(removeCollision,"_ZN22CMasterResourceManager20removeCollisionModelEP15CCollisionModel")
TL_FUNCTION(editorRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(updateBounds,"_ZN13CPropertyNode17updateBoundingBoxEv")
TL_FUNCTION(removeListener,"_ZN6CLevel29removeCharacterUpdateListenerEP22iLevelUpdatedCharacter")
TL_FUNCTION(roomDataSingleton,"_ZN25CRoomPieceDataInformation12getSingletonEv")
TL_FUNCTION(roomDataByGuid,"_ZN25CRoomPieceDataInformation27_GetRoomPieceCoreDataByGuidEx")
namespace {
using namespace smallmass;void* manager;void* core;unsigned calls;
void* singleton(){event(1,manager);++calls;return manager;}
void batch(void* p,void* m){event(2,p);pointer(m);++calls;}
void collision(void* p,void* m){event(3,p);pointer(m);++calls;}
bool editor(void* p){event(4,p);++calls;return false;}
void bounds(void* p){event(5,p);++calls;}
void listener(void* p,void* c){event(6,p);pointer(c);++calls;}
void* data(void* p,long long guid){event(7,p);output->add(&guid,8);++calls;return core;}
void roomState(void* p){pointer(field<void*>(p,0x118));pointer(field<void*>(p,0x120));text(field<std::wstring>(p,0x128));text(field<std::wstring>(p,0x130));number(field<int>(p,0x138));output->add(static_cast<char*>(p)+0x140,8);output->add(static_cast<char*>(p)+0x150,6);number(field<int>(p,0x158));number(field<bool>(p,0x15c));number(field<bool>(p,0x15d));void* d=field<void*>(p,0x148);number(d!=0);if(d){pointer(field<void*>(d,0x10));output->add(static_cast<char*>(d)+0x18,8);}}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;void* self=object(0x200);CResourceManager* resources=static_cast<CResourceManager*>(object(0x50));manager=object(0x100);core=object(0xb0);field<void*>(resources,0x18)=c.index%3?object(0x300):0;
 detour::Set p;TL_REDIRECT(p,masterSingleton,&singleton);TL_REDIRECT(p,removeBatch,&batch);TL_REDIRECT(p,removeCollision,&collision);TL_REDIRECT(p,editorRunning,&editor);TL_REDIRECT(p,updateBounds,&bounds);TL_REDIRECT(p,removeListener,&listener);TL_REDIRECT(p,roomDataSingleton,&singleton);TL_REDIRECT(p,roomDataByGuid,&data);if(p.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 int before=g_iTotalCountOfObjects;
 if(c.op<3){
  if(c.op==0){autotest::invoke(out,ours?roomCtorCandidate:roomCtorOriginal,self,static_cast<CResourceManager*>(NULL));field<void*>(self,0x68)=resources;roomState(self);number(g_iTotalCountOfObjects-before);if(g_iTotalCountOfObjects!=before+2)out.issue=autotest::Capture::InvalidReport;}
  else{roomCtorOriginal(self,static_cast<CResourceManager*>(NULL));field<void*>(self,0x68)=resources;CRoomPiece* room=static_cast<CRoomPiece*>(self);room->m_collisionMeshFile=c.index%2?L"collision":L"";room->m_meshFile=c.index%3?L"mesh file":L"";room->m_iVisualIndex_140=c.index%2?-1:1234;room->m_bUnknown154=c.index%3==0;room->m_collisionModel=reinterpret_cast<CCollisionModel*>(core);
   if(c.op==1){TSafePointer<CRoomPieceData> reference;reference.setObject(room->m_pRoomPieceData);int constructed=g_iTotalCountOfObjects;autotest::invoke(out,ours?roomDtorCandidate:roomDtorOriginal,self);number(reference.getObject()==NULL);number(g_iTotalCountOfObjects==constructed);pointer(room->m_collisionModel);pointer(room->m_pGenericModel);pointer(room->m_pRoomPieceData);if(reference.getObject()||g_iTotalCountOfObjects!=constructed)out.issue=autotest::Capture::InvalidReport;number(calls);return;}
   autotest::invoke(out,ours?roomResetCandidate:roomResetOriginal,self);roomState(self);
  }
  CRoomPiece* room=static_cast<CRoomPiece*>(self);TSafePointer<CRoomPiece> ref;TSafePointer<CRoomPieceData> owned;ref.setObject(room);owned.setObject(room->m_pRoomPieceData);int constructed=g_iTotalCountOfObjects;roomDtorOriginal(self);number(ref.getObject()==NULL);number(owned.getObject()==NULL);number(g_iTotalCountOfObjects==constructed);if(ref.getObject()||owned.getObject()||g_iTotalCountOfObjects!=constructed)out.issue=autotest::Capture::InvalidReport;
 }else{
  if(c.op==3){autotest::invoke(out,ours?propertyCtorCandidate:propertyCtorOriginal,self,static_cast<CResourceManager*>(NULL));number(field<int>(self,0x108));number(field<unsigned>(self,0x10c));number(field<bool>(self,0x110));number(field<bool>(self,0x111));number(field<bool>(self,0x112));number(field<int>(self,0x114));number(field<bool>(self,0x118));vector(field<Ogre::Vector3>(self,0x120));vector(field<Ogre::Vector3>(self,0x12c));number(field<int>(self,0x138));number(field<void*>(self,0x140)==NULL);out.add(static_cast<char*>(field<void*>(self,0x148))+0x10,72);number(field<bool>(self,0x150));number(g_iTotalCountOfObjects-before);if(g_iTotalCountOfObjects!=before+2)out.issue=autotest::Capture::InvalidReport;}
  else propertyCtorOriginal(self,static_cast<CResourceManager*>(NULL));
  field<void*>(self,0x68)=resources;CPropertyNode* property=static_cast<CPropertyNode*>(self);TSafePointer<CPropertyNode> ref;TSafePointer<CCullingBounds> owned;ref.setObject(property);owned.setObject(property->m_cullingBounds);int constructed=g_iTotalCountOfObjects;
  if(c.op==3)propertyDtorOriginal(self);else autotest::invoke(out,ours?propertyDtorCandidate:propertyDtorOriginal,self);
  number(ref.getObject()==NULL);number(owned.getObject()==NULL);number(g_iTotalCountOfObjects==constructed);pointer(property->m_cullingBounds);if(ref.getObject()||owned.getObject()||g_iTotalCountOfObjects!=constructed)out.issue=autotest::Capture::InvalidReport;
 }
 number(calls);out.addHeapInUse();
}
}
TL_TEST(scene_room_construct){return smallmass::run(host,0,"scene_room_construct",(uintptr_t)roomCtorOriginal,execute,24);}
TL_TEST(scene_room_destroy){return smallmass::run(host,1,"scene_room_destroy",(uintptr_t)roomDtorOriginal,execute,24);}
TL_TEST(scene_room_reset){return smallmass::run(host,2,"scene_room_reset",(uintptr_t)roomResetOriginal,execute,24);}
TL_TEST(scene_property_construct){return smallmass::run(host,3,"scene_property_construct",(uintptr_t)propertyCtorOriginal,execute,24);}
TL_TEST(scene_property_destroy){return smallmass::run(host,4,"scene_property_destroy",(uintptr_t)propertyDtorOriginal,execute,24);}
