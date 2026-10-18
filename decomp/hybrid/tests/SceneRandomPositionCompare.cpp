#include "SmallMassCompare.h"
#include "RandomGroup.h"
#include <new>
TL_ORIGINAL(void, positionOriginal,(void*,const Ogre::Vector3&),"_ZN12CRandomGroup15positionUpdatedERKN4Ogre7Vector3E")
extern "C" void positionCandidate(void*,const Ogre::Vector3&) __asm__("_ZN12CRandomGroup15positionUpdatedERKN4Ogre7Vector3E");
TL_ORIGINAL(void, randomCtorOriginal,(void*,CResourceManager*),"_ZN12CRandomGroupC1EP16CResourceManager")
TL_ORIGINAL(void, randomDtorOriginal,(void*),"_ZN12CRandomGroupD1Ev")
extern "C" void randomCtorCandidate(void*,CResourceManager*) __asm__("_ZN12CRandomGroupC1EP16CResourceManager");
extern "C" void randomDtorCandidate(void*) __asm__("_ZN12CRandomGroupD1Ev");
TL_ORIGINAL(void, positionCtorOriginal,(void*,CResourceManager*,Ogre::SceneManager*),"_ZN19CPositionableObjectC1EP16CResourceManagerPN4Ogre12SceneManagerE")
TL_ORIGINAL(void, positionDtorOriginal,(void*),"_ZN19CPositionableObjectD1Ev")
TL_FUNCTION(editorRunning,"_ZN16CResourceManager18getEditorIsRunningEv")
TL_FUNCTION(calculateChildren,"_ZN12CRandomGroup17calculateChildrenEv")
TL_FUNCTION(getPosition,"_ZN19CPositionableObject11getPositionEb")
TL_FUNCTION(setPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
namespace {
using namespace smallmass;unsigned calls,editors;CRandomGroup* self;CPositionableObject* children[3];
bool editor(void* p){event(1,p);++calls;++editors;return editors==1?input->index%5!=0:editors==2?input->index%3!=0:input->index%7!=0;}
void calculate(void* p){event(2,p);++calls;for(unsigned i=0;i<input->index%4;++i)self->m_children.add(children[i]);}
Ogre::Vector3 get(void* p,bool absolute){event(3,p);number(absolute);++calls;return field<Ogre::Vector3>(p,0x84);}
void set(void* p,const Ogre::Vector3& value){event(4,p);vector(value);++calls;for(unsigned i=0;i<2;++i)if(p==children[i])number(static_cast<CRandomGroup*>(children[i])->m_bPropagatePosition);field<Ogre::Vector3>(p,0x84)=value;}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=editors=0;autotest::g_arenaUsed=0;self=static_cast<CRandomGroup*>(object(sizeof(CRandomGroup)));CResourceManager* resources=static_cast<CResourceManager*>(object(0x50));void* level=object(0x300);field<void*>(resources,0x18)=c.index%11?level:0;field<bool>(level,0x1a0)=c.index&1;field<void*>(self,0x68)=resources;
 for(unsigned i=0;i<3;++i){if(i<2){children[i]=static_cast<CPositionableObject*>(object(sizeof(CRandomGroup)));randomCtorOriginal(children[i],NULL);}else{children[i]=static_cast<CPositionableObject*>(object(sizeof(CPositionableObject)));positionCtorOriginal(children[i],NULL,NULL);}field<Ogre::Vector3>(children[i],0x84)=Ogre::Vector3(i+1,-2,3);field<void*>(children[i],0x38)=(c.index+i)%3?resources:level;}
 field<void*>(self,0x38)=resources;new(&self->m_children)TArrayList<CPositionableObject*>(2);for(unsigned i=0;i<c.index%4;++i)self->m_children.add(children[i]);self->m_bPropagatePosition=c.index%7!=0;self->m_bIsDynamicGroup=c.index%4!=0;self->m_lastPosition=Ogre::Vector3(c.index%3?1:0,2,3);Ogre::Vector3 value=c.index%6?Ogre::Vector3(1,-2,3):Ogre::Vector3::ZERO;
 detour::Set p;TL_REDIRECT(p,editorRunning,&editor);TL_REDIRECT(p,calculateChildren,&calculate);TL_REDIRECT(p,getPosition,&get);TL_REDIRECT(p,setPosition,&set);if(p.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 autotest::invoke(out,ours?positionCandidate:positionOriginal,self,value);vector(self->m_lastPosition);vector(field<Ogre::Vector3>(self,0x84));number(self->m_children.size());for(unsigned i=0;i<3;++i){vector(field<Ogre::Vector3>(children[i],0x84));if(i<2)number(static_cast<CRandomGroup*>(children[i])->m_bPropagatePosition);}number(calls);p.restore();self->m_children.~TArrayList();for(unsigned i=0;i<3;++i){if(i<2)randomDtorOriginal(children[i]);else positionDtorOriginal(children[i]);}out.addHeapInUse();
}
void lifetime(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;autotest::g_arenaUsed=0;CRandomGroup* objectSelf=static_cast<CRandomGroup*>(object(sizeof(CRandomGroup)));int before=g_iTotalCountOfObjects;
 if(c.op==1){autotest::invoke(out,ours?randomCtorCandidate:randomCtorOriginal,objectSelf,static_cast<CResourceManager*>(NULL));number(objectSelf->m_bPropagatePosition);number(objectSelf->m_iMinimumChildren);number(objectSelf->m_iMaximumChildren);number(objectSelf->m_iChildSelectionLimit);number(objectSelf->m_iChildSpawnLimit);number(objectSelf->m_iRandomType);number(objectSelf->m_iRandomWeight);number(objectSelf->m_iNumberOfPicks);vector(objectSelf->m_lastPosition);number(objectSelf->m_children.size());number(objectSelf->m_bIsDynamicGroup);text(objectSelf->m_sQuestHasToBeComplete);text(objectSelf->m_sQuestHasToBeActive);text(objectSelf->m_sQuestCannotBeActiveOrComplete);text(objectSelf->m_sQuestHasToBeActiveOrComplete);text(objectSelf->m_sQuestNotComplete);text(objectSelf->m_sPlayerClassName);text(objectSelf->m_sDungeonForGroup);number(objectSelf->m_iDifficulty);number(g_iTotalCountOfObjects-before);}
 else{randomCtorOriginal(objectSelf,NULL);for(unsigned i=0;i<c.index%5;++i)objectSelf->m_children.add(static_cast<CPositionableObject*>(object(0x100)));objectSelf->m_sQuestHasToBeComplete=c.index%2?L"quest complete":L"";objectSelf->m_sQuestHasToBeActive=c.index%3?L"quest active":L"";objectSelf->m_sQuestCannotBeActiveOrComplete=L"excluded";objectSelf->m_sQuestHasToBeActiveOrComplete=L"required";objectSelf->m_sQuestNotComplete=L"not complete";objectSelf->m_sPlayerClassName=L"class";objectSelf->m_sDungeonForGroup=L"dungeon";}
 TSafePointer<CRandomGroup> reference;reference.setObject(objectSelf);int constructed=g_iTotalCountOfObjects;
 if(c.op==1)randomDtorOriginal(objectSelf);else autotest::invoke(out,ours?randomDtorCandidate:randomDtorOriginal,objectSelf);
 number(reference.getObject()==NULL);number(g_iTotalCountOfObjects==constructed);if(reference.getObject()||g_iTotalCountOfObjects!=constructed)out.issue=autotest::Capture::InvalidReport;out.addHeapInUse();
}

}
TL_TEST(scene_random_position){return smallmass::run(host,0,"scene_random_position",(uintptr_t)positionOriginal,execute,48);}

TL_TEST(scene_random_construct){return smallmass::run(host,1,"scene_random_construct",(uintptr_t)randomCtorOriginal,lifetime,24);}
TL_TEST(scene_random_destroy){return smallmass::run(host,2,"scene_random_destroy",(uintptr_t)randomDtorOriginal,lifetime,24);}
