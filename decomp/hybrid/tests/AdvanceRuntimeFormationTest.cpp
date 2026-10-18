#include "SmallMassCompare.h"
#include "TArrayList.h"
TL_ORIGINAL(void,formationLayoutOld,(void*,const std::wstring&,void*),"_ZN14CFormationNode13setLayoutFileERKSbIwSt11char_traitsIwESaIwEEP16CResourceManager")
TL_ORIGINAL(void,formationCtorOld,(void*,void*,void*),"_ZN14CFormationNodeC1EP16CResourceManagerP25CFormationNodeSaveAndLoad")
extern "C" void formationLayoutNew(void*,const std::wstring&,void*) __asm__("_ZN14CFormationNode13setLayoutFileERKSbIwSt11char_traitsIwESaIwEEP16CResourceManager");
extern "C" void formationCtorNew(void*,void*,void*) __asm__("_ZN14CFormationNodeC1EP16CResourceManagerP25CFormationNodeSaveAndLoad");
TL_FUNCTION(formationLayoutCtor,"_ZN7CLayoutC1EP16CResourceManager13ELAYOUT_TYPES")
TL_FUNCTION(formationLayoutLoad,"_ZN7CLayout14loadLayoutFileERKSbIwSt11char_traitsIwESaIwEEbP13CTimerStaticsbbj")
TL_FUNCTION(formationObjects,"_ZN12CEditorScene30GetObjectsCreatedByADescriptorERKSbIwSt11char_traitsIwESaIwEEP10TArrayListIP17CEditorBaseObjectE")
TL_FUNCTION(formationRemove,"_ZN6CLevel10removeUnitEP9CBaseUnitb")
TL_FUNCTION(formationVisible,"_ZN10CCharacter10setVisibleEbb")
TL_FUNCTION(formationPositionCtor,"_ZN19CPositionableObjectC1EP16CResourceManagerPN4Ogre12SceneManagerE")
TL_FUNCTION(formationAddUpdate,"_ZN6CLevel15addUpdateObjectEP12iLevelUpdate")
TL_FUNCTION(formationLayoutCall,"_ZN14CFormationNode13setLayoutFileERKSbIwSt11char_traitsIwESaIwEEP16CResourceManager")
TL_FUNCTION(formationSetPosition,"_ZN19CPositionableObject11setPositionERKN4Ogre7Vector3E")
namespace {
using namespace smallmass;
void* units[4];void* resources;void* level;void* self;void** table;unsigned calls;
void record(unsigned tag,void* p){event(tag,p);++calls;}
void destroy(void* p){record(1,p);}
void visibleScene(void* p,bool value){record(2,p);number(value);}
void layoutCtor(void* p,void* r,int type){record(3,p);pointer(r);number(type);field<void*>(p,0)=table;}
void load(void* p,const std::wstring& name,bool a,void* timer,bool b,bool c,unsigned seed){record(4,p);text(name);number(a);pointer(timer);number(b);number(c);number(seed);}
void objects(void* p,const std::wstring& descriptor,TArrayList<void*>* found){record(5,p);text(descriptor);for(unsigned i=0;i<input->index%5;++i)found->add(units[i]);}
void removeUnit(void* p,void* unit,bool value){record(6,p);pointer(unit);number(value);}
void characterVisible(void* p,bool a,bool b){record(7,p);number(a);number(b);}
void positionCtor(void* p,void* r,void* scene){record(8,p);pointer(r);pointer(scene);field<void*>(p,0x68)=r;}
void addUpdate(void* p,void* update){record(9,p);pointer(update);}
void setLayout(void* p,const std::wstring& name,void* r){record(10,p);text(name);pointer(r);}
void position(void* p,const Ogre::Vector3& value){record(11,p);vector(value);}
void execute(Case& c,bool ours,autotest::Capture& out){input=&c;output=&out;calls=0;autotest::g_arenaUsed=0;self=object(0x118);resources=object(0x48);level=object(0x20);table=static_cast<void**>(object(0x58));table[1]=reinterpret_cast<void*>(&destroy);table[0x50/8]=reinterpret_cast<void*>(&visibleScene);field<void*>(resources,0x18)=c.index&1?level:0;for(unsigned i=0;i<4;++i)units[i]=object(0x40);
 void* oldScene=object(0x1f8);field<void*>(oldScene,0)=table;field<void*>(self,0x110)=c.index&2?oldScene:0;
 std::wstring name=c.index&4?L"FORMATION/MONSTERS.LAYOUT":L"";void* saved=object(0x38);new(static_cast<char*>(saved)+0x18)std::wstring(name);field<float>(saved,0x2c)=c.index*.25f;field<float>(saved,0x30)=-3.5f;field<float>(saved,0x34)=0.125f;
 detour::Set d;TL_REDIRECT(d,formationPositionCtor,&positionCtor);TL_REDIRECT(d,formationAddUpdate,&addUpdate);TL_REDIRECT(d,formationSetPosition,&position);
 if(c.op==0){TL_REDIRECT(d,formationLayoutCtor,&layoutCtor);TL_REDIRECT(d,formationLayoutLoad,&load);TL_REDIRECT(d,formationObjects,&objects);TL_REDIRECT(d,formationRemove,&removeUnit);TL_REDIRECT(d,formationVisible,&characterVisible);}else{TL_REDIRECT(d,formationLayoutCall,&setLayout);}
 if(d.failed()){out.issue=autotest::Capture::InvalidReport;return;}
 if(c.op==0){typedef void(*Fn)(void*,const std::wstring&,void*);Fn fn=ours?formationLayoutNew:formationLayoutOld;if(!autotest::beginInvocation(out,fn))return;fn(self,name,resources);out.callCompleted=1;}
 else autotest::invoke(out,ours?formationCtorNew:formationCtorOld,self,resources,c.index&2?saved:0);
 number(calls);if(c.op==0)number(field<void*>(self,0x110)!=0);else {number(field<bool>(self,0x108));number(field<void*>(self,0x110)!=0);pointer(field<void*>(self,0x68));}
 reinterpret_cast<std::wstring*>(static_cast<char*>(saved)+0x18)->~basic_string();
}
}
TL_TEST(advance_runtime_formation_layout){return smallmass::run(host,0,"advance_runtime_formation_layout",(uintptr_t)formationLayoutOld,execute,64);}
TL_TEST(advance_runtime_formation_ctor){return smallmass::run(host,1,"advance_runtime_formation_ctor",(uintptr_t)formationCtorOld,execute,64);}
